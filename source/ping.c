
//==================================================================
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip_icmp.h>
#include <netdb.h>
#include <errno.h>

#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>

#include <asm/errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <linux/route.h>
#include <sys/time.h>
#include <sys/mount.h>
#include <sys/vfs.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <termios.h>
#include <pthread.h>
#include <errno.h>
#include <linux/videodev.h>
#include <sys/reboot.h>
#include <netdb.h>   

#include <sys/types.h>
#include <sys/socket.h>
//timeout
#include <setjmp.h> 
#include <time.h> 
#include <signal.h> 


//#include "http_client/CSocket.h"
//#include "precomp.h"

#define MAX_WAIT_TIME   1

#define ICMP_HEADSIZE   8 /* icmp packet header size */
#define PACKET_SIZE     4096
#define MAX_NO_PACKETS  3
struct timeval tvsend,tvrecv;//
struct sockaddr_in dest_addr,from;
int sockfd;
pid_t pid;//use the process id as ICMP's id

//definition of fuctions
void timeout(int signo);
void statistics(int signo);
unsigned short cal_chksum(unsigned short *addr,int len);//
int pack(int pkt_no,char *sendpacket);//
int send_packet(int pkt_no,char *sendpacket);//
int recv_packet(int pkt_no,char *recvpacket);
int unpack(int cur_seq,char *buf,int len);//
void tv_sub(struct timeval *out,struct timeval *in);

extern int comm_uartsend2(int iUART, void *pBuffer, int len);
extern int connect_nonb(int sockfd, struct sockaddr *saptr, socklen_t salen, int nsec);

void ping_printf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
	va_list ap;
    char string[10*1024];

    va_start(ap,str);
    vsprintf(string,str,ap);
	comm_uartsend(0, &string, strlen(string)) ;
    va_end(ap);
}
int ping_send(int sock, const void *buf, size_t len, const struct sockaddr *to)
{
	struct timeval timeo;
	
	ping_printf("setsockopt ...\r\n");
	timeo.tv_sec = 5;	
	timeo.tv_usec = 0;	//500
	if (setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO|SO_RCVTIMEO, &timeo, sizeof(timeo)) == -1)	 
	{
		ping_printf("setsockopt err\r\n");	
		close(sock);
		return -1;
	}  	
	if( connect( sock, to, sizeof( struct sockaddr ) ) )
	{		
		ping_printf("connect err\r\n");		
		close( sock );		
		return -1;
	}
	int rc;
	
	ping_printf("%s\r\n","ping_send ...");
	if((rc = send(sock,buf, len, 0)) == -1)
	{
		if((errno != EWOULDBLOCK) && (errno != EAGAIN))
		{
			close( sock );	
			return -1;
		}
	}
	return 0;

}
static sigjmp_buf  sendto_jmpbuf; 
static void sendto_alarm_func(int arg) 	
{ 
     siglongjmp(sendto_jmpbuf, 1); 
} 
  
ssize_t sendto_timeout(int sock, const void *buf, size_t len, int flags, const struct sockaddr *to, socklen_t tolen,int time)
{ 
	 ssize_t nRet;

     signal(SIGALRM, sendto_alarm_func); 
     if(sigsetjmp(sendto_jmpbuf, 1) != 0) 
     { 
		   ping_printf("sendto_timeout exit\r\n");
		   alarm(0);//timout 
           signal(SIGALRM, SIG_IGN); 
           return NULL; 
     } 
     alarm(time);//setting alarm 
     ping_printf("sendto_timeout...\r\n");
     nRet=sendto(sock,buf,len,flags,to,tolen );
     signal(SIGALRM, SIG_IGN); 
	 
     return nRet; 
} 

void timeout(int signo)
{
	printf("Request Timed Out\n");
	exit(1);
}

/*checksum computing*/
unsigned short cal_chksum(unsigned short *addr,int len)
{       int nleft=len;
        int sum=0;
        unsigned short *w=addr;
        unsigned short answer=0;
        while(nleft>1)
        {       sum+=*w++;
                nleft-=2;
        }
        if( nleft==1)
        {       *(unsigned char *)(&answer)=*(unsigned char *)w;
                sum+=answer;
        }
        sum=(sum>>16)+(sum&0xffff);
        sum+=(sum>>16);
        answer=~sum;
        return answer;
}
int pack(int pkt_no,char*sendpacket)
{       int i,packsize;
        struct icmp *icmp;
        struct timeval *tval;
        icmp=(struct icmp*)sendpacket;
        icmp->icmp_type=ICMP_ECHO;
        icmp->icmp_code=0;
        icmp->icmp_cksum=0;
        icmp->icmp_seq=pkt_no;
        icmp->icmp_id=pid;
        packsize=ICMP_HEADSIZE+sizeof(struct timeval);
        tval= (struct timeval *)icmp->icmp_data;
        gettimeofday(tval,NULL);
        icmp->icmp_cksum=cal_chksum( (unsigned short *)icmp,packsize); 
        return packsize;
}

int send_packet(int pkt_no,char *sendpacket)
{    
	int packetsize;       
       	packetsize=pack(pkt_no,sendpacket); /*set the ICMP header*/
	    gettimeofday(&tvsend,NULL); 
		ping_printf("ping send_packet...\r\n");
      	if(sendto_timeout(sockfd,sendpacket,packetsize,MSG_DONTWAIT,(struct sockaddr *)&dest_addr,sizeof(dest_addr),5 )<0)
		//if(ping_send(sockfd,sendpacket,packetsize,(struct sockaddr *)&dest_addr)<0)	
		//if(sendto(sockfd,sendpacket,packetsize,0,(struct sockaddr *)&dest_addr,sizeof(dest_addr))<0)
        {      
		     ping_printf("sendto error\r\n");
                return -1;
        }
	return 0;
}

int recv_packet(int pkt_no,char *recvpacket)
{       	
	int n,fromlen;
        extern int errno;
        signal(SIGALRM,timeout);
        fromlen=sizeof(from);
        alarm(MAX_WAIT_TIME);
	    while(1)
		{
			  if( (n=recvfrom(sockfd,recvpacket,PACKET_SIZE,0,(struct sockaddr *)&from,(socklen_t*)&fromlen)) <0)
	    	  {   
				   if(errno==EINTR)return -1;
		          	//perror("recvfrom error");		          	
					ping_printf("ping recvfrom error\r\n");
		                return -2;
	      	  }	
		      gettimeofday(&tvrecv,NULL); 
	      	  if(unpack(pkt_no,recvpacket,n)==-1)continue;
	       	  return 0;
	    }
}

int unpack(int cur_seq,char *buf,int len)
{    
	
	int iphdrlen;
        struct ip *ip;
        struct icmp *icmp;
        
        ip=(struct ip *)buf;
        iphdrlen=ip->ip_hl<<2;
        icmp=(struct icmp *)(buf+iphdrlen);
        len-=iphdrlen;
        if( len<8)
                return -1;       
        if( (icmp->icmp_type==ICMP_ECHOREPLY) && (icmp->icmp_id==pid) && (icmp->icmp_seq==cur_seq))
       		return 0;	
        else     return -1;
}
int ping_main(int argc,char *argv[])
{     
	char sendpacket[PACKET_SIZE];
	char recvpacket[PACKET_SIZE];	
	
	double rtt;
	char hostname[32];
	struct hostent *host;
	struct protoent *protocol;
     	int i,recv_status;

        if(argc!=2)
        {       printf("usage:%s hostname/IPaddress\n",argv[0]);
                exit(1);
        }
        if( (protocol=getprotobyname("icmp") )==NULL)
        {       perror("getprotobyname");
                exit(1);
        }
        /* set destination host information */
	strcpy(hostname,argv[1]);
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;	
	if((host=gethostbyname(hostname))==NULL){
		fprintf(stderr,"Cant get serverhost info!\n");
		exit(1);
	}
	bcopy((char*)host->h_addr,(char*)&dest_addr.sin_addr,host->h_length);

	/* creat the raw socket for icmp */
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		perror("socket");
		exit(2);
	}

        /*get process id and used as icmp id*/
        pid=getpid();
        printf("PING %s(%s):\n",hostname,inet_ntoa(dest_addr.sin_addr));	
	for(i=0;i<MAX_NO_PACKETS;i++){		
		if(fork()==0)
		{			
       			if(send_packet(i,sendpacket)<0)continue;	
			if(!recv_packet(i,recvpacket)){	
              			tv_sub(&tvrecv,&tvsend);
                		rtt=tvrecv.tv_sec*1000+tvrecv.tv_usec/1000;  
                		printf("reply from %s(%s): time=%.3f ms\n",hostname,inet_ntoa(dest_addr.sin_addr),rtt);
				exit(0);
			}
		}
		else wait(&recv_status);		
	}       
        return 0;
}

void tv_sub(struct timeval *out,struct timeval *in)
{       if( (out->tv_usec-=in->tv_usec)<0)
        {       --out->tv_sec;
                out->tv_usec+=1000000;
        }
        out->tv_sec-=in->tv_sec;
}

int ping(struct sockaddr_in peer)
{     
	char sendpacket[PACKET_SIZE];
	char recvpacket[PACKET_SIZE];	
	
	double rtt;
	//struct hostent *host;
	struct protoent *protocol;
    int i,recv_status;
	
	ping_printf("ping ...\r\n");

    //if( (protocol=getprotobyname("icmp") )==NULL)
   // {       ping_printf("getprotobyname err\r\n");
    //       return 0;
   // }
        /* set destination host information */
	bzero(&dest_addr, sizeof(dest_addr));		
	dest_addr=peer;
	dest_addr.sin_family = AF_INET;	
	//bcopy((char*)host->h_addr,(char*)&dest_addr.sin_addr,host->h_length);

	/* creat the raw socket for icmp */
	if ((sockfd = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) < 0) {
		ping_printf("ping socket err\r\n");
		return 0;
	}	
	ping_printf("ping socket ok\r\n");

    /*get process id and used as icmp id*/
    //pid=getpid();
    pid=5;
    for(i=0;i<MAX_NO_PACKETS;i++){		
		//if(fork()==0)
		{			
	   			if(send_packet(i,sendpacket)<0)continue;	
			    if(!recv_packet(i,recvpacket)){	
	      			//tv_sub(&tvrecv,&tvsend);
	        		//rtt=tvrecv.tv_sec*1000+tvrecv.tv_usec/1000;  
	        		//printf("reply from %s(%s): time=%.3f ms\n",hostname,inet_ntoa(dest_addr.sin_addr),rtt);
	        		ping_printf("%s\r\n","Ping OK");
					close(sockfd);
					return 1;
			   }
		}
		//else sleep(&recv_status);		
	}
	ping_printf("%s\r\n","Ping Err");
	close(sockfd);
    return 0;
}

BOOL  PingIp(unsigned char a,unsigned char b,unsigned char c,unsigned char d)
{
	struct sockaddr_in peer;
	int fd;
	struct timeval timeo;
	DWORD			ip;		
	
//	httpprintf("ip=%d.%d.%d.%d\r\n",a, b, c, d);
	UI_IP_UNMAKE(ip, a, b, c, d); 
	bzero( &peer, sizeof(peer) );
	peer.sin_family = AF_INET;
	peer.sin_addr.s_addr = htonl(ip);
	//peer.sin_port	=htonl(80);

	return 	ping(peer);
}

