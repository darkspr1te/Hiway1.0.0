#include <setjmp.h> 
#include <time.h> 
#include <signal.h> 
#include <unistd.h> 
#include <stdio.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
//#include "precomp.h
#include <sys/stat.h>
//#include <linux/if.h>
//#include <linux/route.h>
#include <net/if_arp.h> 
#include <netdb.h>
//#include <ifaddrs.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <errno.h>
#include <ctype.h>
////////////
#include <asm/types.h>
#include <netinet/ether.h>
#include <sys/ioctl.h>
#include <linux/netlink.h>
#include <linux/rtnetlink.h>
#include<stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <net/if_arp.h> 
#include "./gui/MessageBox.h"



#include "ping.c"

typedef int						HFILE;

typedef char					CHAR;
typedef short					SHORT;
typedef int						INT;

typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16;
typedef unsigned int			DWORD, UINT32, u32;
typedef long					LONG;
typedef unsigned long long		UINT64, u64;

typedef unsigned short			WPARAM;
typedef unsigned long			LPARAM;

#ifndef NULL
#define NULL					(0)
#endif /*NULL*/
#ifndef TRUE
#define TRUE					(1)
#endif /*TRUE*/
#ifndef FALSE
#define FALSE					(0)
#endif /*FALSE*/
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE	(-1)
#endif /*INVALID_HANDLE_VALUE*/



extern BOOL				dbComm_ipIsDHCP;
extern BOOL				dbComm_dhcpSuccess;
extern BYTE				dbComm_macAddress[6];
extern WORD				dbComm_wPortNum;
extern DWORD			dbComm_ipAddress;
extern DWORD			dbComm_ipSubnetMask;
extern DWORD			dbComm_ipDefaultGateway;
extern DWORD			dbComm_ipPcBackground;

#define DNSIP_FILENAME		("/etc/resolv.conf")
#define LEASETIME_FILENAME		("/etc/my1.conf")
#define HOSTNAME_EFILENAME		("/etc/hostname.conf")
extern void xprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
);
extern int ping(struct sockaddr_in peer);
BOOL DnsServerIpRead(void);
void DnsServerIpSet(DWORD ipPcBackground);
BOOL DhcpIPRead(char *eth_str);
extern DWORD dwDhcpRealTime;
extern DWORD			dbComm_DHCPLeaseTime;
static unsigned char uDhcpcStartFlag=0;
DWORD dwuDhcpcRealTime = 0; 



int connect_nonb(int sockfd, struct sockaddr *saptr, socklen_t salen, int nsec)
{
//xprintf("i am in connect_nonb1111\r\n");
       int flags, n, error;
       socklen_t len;
       fd_set rset, wset;
       struct timeval tval;

       // 获取当前socket的属性， 并设置 noblocking 属性
       flags = fcntl(sockfd, F_GETFL, 0);
       fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);
       errno = 0;

       if ( (n = connect(sockfd, saptr, salen)) < 0)
       {
		//xprintf("error==%d\r\n",errno);	
		//xprintf("n==%d\r\n",EINPROGRESS);
		//xprintf("EINPROGRESS==%d\r\n",n);
		//如果不是阻塞错误就返回，阻塞的话就继续执行下面的处理	
		if (errno != EINPROGRESS)//一个阻塞的套接口调用正在运行中
                   	  return (-1);
       }
       // 可以做任何其它的操作
      
       
       if (n == 0)
              goto done; // 一般是同一台主机调用，会返回 0

       FD_ZERO(&rset);
       FD_SET(sockfd, &rset);

       wset = rset;  // 这里会做 block copy
       tval.tv_sec = nsec;
       tval.tv_usec = 0;

       // 如果nsec 为0，将使用缺省的超时时间，即其结构指针为 NULL

       // 如果tval结构中的时间为0，表示不做任何等待，立刻返回

      //if ((n = select(sockfd+1, &rset, &wset, NULL,&tval)) == 0) 
       if ((n = select(sockfd+1, &rset, &wset, NULL,&tval)) < 1) 
      {
              close(sockfd);
              errno = ETIMEDOUT;
              return (-1);
       }
	   if ( connect(sockfd, saptr, salen) < 0 && errno !=EISCONN)
	   {
		
              	close(sockfd);
              	return (-1);			
	   }

 done:

       fcntl(sockfd, F_SETFL, flags); // 恢复socket 属性
       xprintf("i am in connect_nonb2222\r\n");
       return (0);

}


static sigjmp_buf jmpbuf; 
static void alarm_func(int arg) 
{ 
     siglongjmp(jmpbuf, 1); 
} 
  extern void wdog_app_alive(void);

unsigned int AsciiToDec(char *str)
{  
         unsigned int a;  
         sscanf(str,"%d",&a);  
	  return a;
}
//用前面的字符串与后面的匹配，如果不匹配则返回NULL
//如果成功返回非NULL
//这个用于判断得到的信息是否需要处理
char *mystrstr(char *haystack, char *needle)
{	//assert(haystack != NULL && needle != NULL);	
	if (strlen(haystack) < strlen(needle)) return NULL;	
	char *head_n = (char *)needle;	
	char *head_h = (char *)haystack;	
	while (*haystack != '\0') 
	{		
		while (*needle != '\0') 
			{			
			if (*haystack != *needle) break;			
			haystack++;			
			needle++;			
			if (*needle == '\0') 
				return head_h;		
			}		
		needle = head_n;		
		head_h++;		
		haystack = head_h;	
	}	
	return NULL;
}

 char* Http_CfgstrGet2(char *buff,char *dest1,char *dest2,char *ret)
{
	int dest_len;
	char *pos1 = 0;
	char *pos2 = 0;	
	//char str_out[30]; 

	dest_len=strlen(dest1);	
	//memset(str_out,0,sizeof(str_out));
	pos1 = mystrstr(buff, dest1);
	if(pos1)
	   pos2 = mystrstr(pos1+1,dest2);	
	//if(pos1)
	//	httpprintf("pos1=%s\n",pos1);
	//if(pos2)
	//	httpprintf("pos2=%s\n",pos2);	
	if(pos1 && pos2 && (pos1!=pos2))
	{
	    strncpy(ret,pos1+dest_len,pos2-pos1-dest_len); 
	}
	else
	{
        		//xprintf("=%s\n","Http_CfgstrGet return 0");
		return 0;
	}
	//str_out = str_src.substr( pos1+dest_len, pos2-pos1-dest_len );
	//pos1 = str_src.find_last_of( "/", str_src.size() );
	//filename = str_src.substr( pos1+1, str_src.size()-pos1-1 );
	//ret=str_out;
	return (pos2);

}
  
/*
相关函数：longjmp, siglongjmp, setjmp 
表头文件：#include <setjmp.h> 
函数定义：int sigsetjmp(sigjmp_buf env, int savesigs) 
函数说明：sigsetjmp()会保存目前堆栈环境，然后将目前的地址作一个记号，而在程序其他地方调用siglongjmp()时便会直接跳到这个记号位置，然后还原堆栈，继续程序好执行。 
参数env为用来保存目前堆栈环境，一般声明为全局变量 
参数savesigs若为非0则代表搁置的信号集合也会一块保存 
当sigsetjmp()返回0时代表已经做好记号上，若返回非0则代表由siglongjmp（）跳转回来。 
返回值  ：返回0代表局促存好目前的堆栈环境，随时可供siglongjmp()调用， 若返回非0值则代表由siglongjmp()返回 
*/
 DWORD  gngethostbyname(char *HostName, int timeout) 
{ 


	DWORD			dbComm;	
	FILE *f;
	int nFileSize;
	int result = 0;
	BOOL bRet;
	BYTE buf[1024];

	char *pos ;	
	char str[30];	
	int ip[4];
       int i;
	DWORD    dwTimeLedStart;
	
	COMMAND_EXE("killall gethost");	
	COMMAND_EXE("cp  /usr/hostname.conf    /sb3000t/enroll/hostname.conf");	   
	COMMAND_EXE("/gethost %s &",HostName);	
	dwTimeLedStart = uiTimeGetTickCount();
       while (uiTimeGetTickCount() -dwTimeLedStart <timeout*1000)
       	{
       	     			wdog_app_alive();//added by hym
       	}



		
	xprintf("read /etc/hostname.conf ...\r\n");
	
	f = fopen(HOSTNAME_EFILENAME, "r");
	if (!f)
	{
			fclose(f);
			return 0;
	}
	
	memset(buf, 0, sizeof(buf));
	result = fread( buf, sizeof(buf), 1,f);	
	if (result == -1) //ERROR
		memset(buf, 0, sizeof(buf));	
	fclose(f);
	xprintf("%s\r\n",buf);
	if(buf[0]=='N')
		{
		    xprintf("DNS get Error\r\n",buf);
		   return  0;
		}
	///////////////////////////////////////////////////////
	memset(str,0,30);
	pos=Http_CfgstrGet2((char *)buf,"hostaddr=",".",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);	
	ip[0]=AsciiToDec(str);

	memset(str,0,30);
	pos=Http_CfgstrGet2(pos,".",".",str);
	if(pos==0)
		return 0;
	xprintf("%s\r\n",str);	
	ip[1]=AsciiToDec(str);

	memset(str,0,30);
	pos=Http_CfgstrGet2(pos,".",".",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);	
	ip[2]=AsciiToDec(str);

	memset(str,0,30);
	pos=Http_CfgstrGet2(pos,".","#",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);
	ip[3]=AsciiToDec(str);	

    dbComm = UI_IP_MAKE(ip[0], ip[1], ip[2], ip[3]);

	return dbComm;
	

} 

static sigjmp_buf jmpbuf_connect; 
static void alarm_connect(int arg) 
{ 
     siglongjmp(jmpbuf_connect, 1); 
}   
int connect_timeout(int sockfd,struct sockaddr * serv_addr,int addrlen,int time_out)
{ 
     int nRet; 

	 //if(Route_Test()==0)
	 //	return 0;

     signal(SIGALRM, alarm_connect); 
     if(sigsetjmp(jmpbuf_connect, 1) != 0) 
     { 
           alarm(0);//timout 
           signal(SIGALRM, SIG_IGN); 
           return 1; 
     } 
     alarm(time_out);//setting alarm 
     nRet = connect( sockfd,serv_addr,addrlen); 
     signal(SIGALRM, SIG_IGN); 
	 
     return nRet; 
} 

static sigjmp_buf jmpbuf_send; 
static void alarm_Send(int arg) 
{ 
     siglongjmp(jmpbuf_send, 1); 
}   
ssize_t send_timeout(int sock, const void *buf, size_t len, int flags,int time_out)
{ 
     int nRet; 

	 //if(Route_Test()==0)
	 //	return 0;

     signal(SIGALRM, alarm_Send); 
     if(sigsetjmp(jmpbuf_send, 1) != 0) 
     { 
           alarm(0);//timout 
           signal(SIGALRM, SIG_IGN); 
           return -1; 
     } 
     alarm(time_out);//setting alarm 
     nRet = send( sock,buf, len, flags ); 
     signal(SIGALRM, SIG_IGN); 
	 
     return nRet; 
} 

static sigjmp_buf jmpbuf_recv; 
static void alarm_recv(int arg) 
{ 
     siglongjmp(jmpbuf_recv, 1); 
}   
ssize_t recv_timeout(int sock, void *buf, size_t len, int flags,int time_out)
{ 
     ssize_t nRet; 

	 //if(Route_Test()==0)
	 //	return 0;

     signal(SIGALRM, alarm_recv); 
     if(sigsetjmp(jmpbuf_recv, 1) != 0) 
     { 
           alarm(0);//timout 
           signal(SIGALRM, SIG_IGN); 
           return NULL; 
     } 
     alarm(time_out);//setting alarm 
     nRet = recv(sock, buf, len, flags); 
     signal(SIGALRM, SIG_IGN); 
	 
     return nRet; 
} 


long getlength( FILE *fp )
{
 long cur_pos;
 long len;
 
 //取得当前文件流的读取位置
 cur_pos = ftell( fp );
 //将文件流的读取位置设为文件末尾
 fseek( fp, 0, SEEK_END );
 //获取文件末尾的读取位置,即文件大小
 len = ftell( fp );
 //将文件流的读取位置还原为原先的值
 fseek( fp, cur_pos, SEEK_SET );
 return len;
}


BOOL DnsFileWrite(void *pBuffer, int len)
{
	FILE *f;
	int nFileSize;
	int nCount;
	BOOL bRet;

	bRet = TRUE;
	
	xprintf("write /etc/resolv.conf ...\r\n");

	f = fopen(DNSIP_FILENAME, "wb");
	if (!f)
	{
		xprintf("write /etc/resolv.conf err!\r\n");
		return 0;
	}
	nFileSize=getlength(f);
	fseek( f, nFileSize, SEEK_SET );
	fwrite(pBuffer, len, 1,f);
	fclose(f);

	return  bRet;

}


BOOL DnsHostsRead(void)
{
	FILE *f;
	int nFileSize;
	int result = 0;
	BOOL bRet;
	BYTE buf[10*1024];

	bRet = TRUE;	
	
	xprintf("read /etc/hosts ...\r\n");

	f = fopen("/etc/hosts", "r");
	if (!f)
	{
	   return 0;
	}
	
	memset(buf, 0, sizeof(buf));
	result = fread( buf, sizeof(buf), 1,f);	
	if (result == -1) //ERROR
		memset(buf, 0, sizeof(buf));	
	fclose(f);
	xprintf("hosts data=\r\n%s\r\n", buf);

}


void COMMAND_EXE(	
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
	va_list ap;
    char string[1024];

    va_start(ap,str);
    vsprintf(string,str,ap);
	SB_EXEC((const char*)&string);
    va_end(ap);

}
unsigned char  StopDhchclient(int pid)
{
	if (dbSetupTotal.setSystem.bDHCPUse==0 || uDhcpcStartFlag==FALSE)
		return 0;

	xprintf("StopDhchclient pid=%d\r\n",pid);

	//system("killall udhcpc \n");
    COMMAND_EXE("/sbin/killall dhclient");
    //COMMAND_EXE("/bin/kill %d",pid);
	uDhcpcStartFlag=FALSE;
}

unsigned char  StartEth0(void)
{
    //system("udhcpc &\n");
    COMMAND_EXE("ifconfig eht0 up");
}
unsigned char  StopEth0(void)
{
    //system("killall udhcpc \n");
    COMMAND_EXE("ifconfig eth0 down");
}



static char ETH_STR[10];
void EthStr_Set(char *str)
{
 
  memset(ETH_STR,0,10);
 	strncpy(ETH_STR,str,10);
}
char *EthStr_Get(void)
{

  return ETH_STR;
}

bool GetGateWay(char *gateway);
bool GetLoadDHCP();
BOOL DhcpReadLeaseTime(void);

extern struct sockaddr_in serverip;
void ClearConfFile(void)
{
	COMMAND_EXE("cp  /usr/resolv.conf /enrolldata/resolv.conf");
	memset(&serverip,0,sizeof(serverip));
}

void   StartDhchclient(void  )
{
       int  dwCurTime,dwSTime;
	   
     	if (dbSetupTotal.setSystem.bDHCPUse==0 || uDhcpcStartFlag==TRUE)
		return;
//	if(Net_LinkIsOk()==0)
//		return 0;
	  
	dbComm_ipDefaultGateway=0;
	dbComm_dhcpSuccess=FALSE;
	dbComm_ipAddress=0;
	dbComm_ipSubnetMask=0;

	xprintf("StartDhchclient\r\n");	
	ClearConfFile();
	if(Net_LinkIsOk()==0)
	{
		return;
	}

	uiLcdProgressDlgShow(UISTR_STATUS_DHCP_CONFIGURING); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_STATUS_DHCP_CONFIGURING);

	COMMAND_EXE("/udhcpc -q -n -i eth0");

	///// 
	dwCurTime = dwSTime = uiTimeGetTickCount();
	while (dwCurTime < dwSTime + 1000)
	{
		uiLcdProgress(LCDPROG_PERCENT(dwCurTime - dwSTime, 1000));
		dwCurTime = uiTimeGetTickCount();
		wdog_app_alive();
	}
	uiLcdProgressEnd();
	uiLcdProgressDlgExit(); g_bProgress = FALSE;
	///////

       if (!GetLoadDHCP())
	   	return;

      if (dbSetupTotal.setSystem.szHostByName[0]!=0)
		DnsIpRead();
	
	DhcpReadLeaseTime();   
}

bool GetLoadDHCP()
{
	struct sockaddr_in *my_ip;
	struct sockaddr_in *addr;
	struct sockaddr_in myip;
	char *local_ip;
	char *local_mask;
	my_ip = &myip;
	struct ifreq ifr;
	int sock;

	char *pos ;	
	char str[10];	
	int ip[4];
       int i,j;
	char gateway[30]; 


	//////////////////// //网关
	memset(gateway,'\0',30);
	if(GetGateWay(gateway) )
	{
		     xprintf("DHCP ok\r\n");
	           dbComm_dhcpSuccess=TRUE;		
		    uiLcdMessageBox(UI_MSG_OK, UISTR_STATUS_DHCP_CONFIGURE_SUCCESS, UI_MSGTIMEOUT);	
	}
      else
      	{
	  	xprintf("DHCP error\r\n");
	  	dbComm_dhcpSuccess=FALSE;
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_DHCP_CONFIGURE_FAIL, UI_MSGTIMEOUT);
		return FALSE;
      	}

	xprintf("default gateway:%s\n", gateway);  
	
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(gateway[i]!='.')
			str[i]=gateway[i];
	       else 
		   break;
      	}		
	xprintf("%s\r\n",str);	
	ip[0]=AsciiToDec(str);
	

	memset(str,0,10);
      for(i=i+1,j=i;i<8;i++)
	{  	if(gateway[i]!='.')
			str[i-j]=gateway[i];
	       else 
		   break;
      	}		
	xprintf("%s\r\n",str);	
	ip[1]=AsciiToDec(str);

	memset(str,0,10);
      for(i=i+1,j=i;i<12;i++)
	{  	if(gateway[i]!='.')
			str[i-j]=gateway[i];
	       else 
		   break;
      	}		
	xprintf("%s\r\n",str);	
	ip[2]=AsciiToDec(str);


	memset(str,0,10);
      for(i=i+1,j=i;i<16;i++)
	{  	if(gateway[i]!='\0')
			str[i-j]=gateway[i];
	       else 
		   break;
      	}		
	xprintf("%s\r\n",str);	
	ip[3]=AsciiToDec(str);
	dbComm_ipDefaultGateway = UI_IP_MAKE(ip[0], ip[1], ip[2], ip[3]);
	 ////////////////////


	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		return FALSE;
	}

       strcpy(ifr.ifr_name, "eth0");
	//取本机IP地址
	if(ioctl(sock, SIOCGIFADDR, &ifr) < 0)
	{
    		return FALSE;
	}	
	my_ip->sin_addr = ((struct sockaddr_in *)(&ifr.ifr_addr))->sin_addr;
	local_ip = inet_ntoa(my_ip->sin_addr);
	xprintf(" local_ip is %s\n", local_ip);

	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_ip!='.')
			str[i]=*local_ip;
	       else 
		   break;
		   local_ip++;
      	}		
	xprintf("%s\r\n",str);	
	ip[0]=AsciiToDec(str);
	
      local_ip++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_ip!='.')
			str[i]=*local_ip;
	       else 
		   break;
	   local_ip++;
      	}		
	xprintf("%s\r\n",str);	
	ip[1]=AsciiToDec(str);


      local_ip++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_ip!='.')
			str[i]=*local_ip;
	       else 
		   break;
	   local_ip++;
      	}		
	xprintf("%s\r\n",str);	
	ip[2]=AsciiToDec(str);

	
      local_ip++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_ip!='\0')
			str[i]=*local_ip;
	       else 
		   break;
	   local_ip++;
      	}		
	xprintf("%s\r\n",str);	
	ip[3]=AsciiToDec(str);
	dbComm_ipAddress = UI_IP_MAKE(ip[0], ip[1], ip[2], ip[3]);
	

	//取本机掩码
	if( ioctl( sock, SIOCGIFNETMASK, &ifr) == -1 )
	{
  		 perror("[-] ioctl");
  	 	return FALSE;
	}
	addr = (struct sockaddr_in *) & (ifr.ifr_addr);
	local_mask = inet_ntoa( addr->sin_addr);
	xprintf(" local_mask is %s\n",local_mask);
	close(sock);


	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_mask!='.')
			str[i]=*local_mask;
	       else 
		   break;
		   local_mask++;
      	}		
	xprintf("%s\r\n",str);	
	ip[0]=AsciiToDec(str);
	
      local_mask++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_mask!='.')
			str[i]=*local_mask;
	       else 
		   break;
	   local_mask++;
      	}		
	xprintf("%s\r\n",str);	
	ip[1]=AsciiToDec(str);


      local_mask++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_mask!='.')
			str[i]=*local_mask;
	       else 
		   break;
	   local_mask++;
      	}		
	xprintf("%s\r\n",str);	
	ip[2]=AsciiToDec(str);

	
      local_mask++;
	memset(str,0,10);
      for(i=0;i<4;i++)
	{  	if(*local_mask!='\0')
			str[i]=*local_mask;
	       else 
		   break;
	   local_mask++;
      	}		
	xprintf("%s\r\n",str);	
	ip[3]=AsciiToDec(str);
	dbComm_ipSubnetMask = UI_IP_MAKE(ip[0], ip[1], ip[2], ip[3]);	
	return TRUE;
} 

char* String_CfgGet(char *buff,char *dest1,char *dest2,char *ret,int len);

BOOL DhcpReadLeaseTime(void)
{
	FILE *f;
	int nFileSize;
	int result = 0;
	BOOL bRet;
	BYTE buf[1024];

	char *pos ;	
	char str[10];	
	int ip[4];
       int i;
	
	xprintf("read /etc/my1.conf ...\r\n");

	f = fopen(LEASETIME_FILENAME, "r");
	if (!f)
	{
			fclose(f);
			return 0;
	}
	
	memset(buf, 0, sizeof(buf));
	result = fread( buf, sizeof(buf), 1,f);	
	if (result == -1) //ERROR
		memset(buf, 0, sizeof(buf));	
	fclose(f);

	
	xprintf("%s\r\n",buf);
	///////////////////////////////////////////////////////
	memset(str,'\0',10);
	pos=String_CfgGet((char *)buf,"lease time=",";",str,10);
	xprintf("%s\r\n",str);
	dbComm_DHCPLeaseTime=AsciiToDec(str);
	xprintf("dbComm_DHCPLeaseTime=%d\r\n",dbComm_DHCPLeaseTime);	

	dwDhcpRealTime=uiTimeGetTickCount();
}

bool GetGateWay(char *gateway)    
{    
    FILE *fp;    
    char buf[512];    
    char cmd[128];    
    
    char *tmp;
	int i;
   
    strcpy(cmd, "ip route");    
    fp = popen(cmd, "r");    
    if(NULL == fp)    
    {    
        perror("popen error");    
         
    }   
	i=0;
    while(fgets(buf, sizeof(buf), fp) != NULL)    
    {    
        tmp =buf;    
        while(*tmp && isspace(*tmp))    
           { 
               ++ tmp;  
            }
        if(strncmp(tmp, "default", strlen("default")) == 0)    
            break;    
	 i++;
    }    
    sscanf(buf, "%*s%*s%s", gateway);           
    pclose(fp);
     return i;
}  

char* String_CfgGet(char *buff,char *dest1,char *dest2,char *ret,int len)
{
	int dest_len;
	char *pos1 = 0;
	char *pos2 = 0;	
	char *pos3 = 0;	
	//char str_out[30]; 

	dest_len=strlen(dest1);	
	//memset(str_out,0,sizeof(str_out));
	pos1 = mystrstr(buff, dest1);
	if(pos1)
	   pos2 = mystrstr(pos1+1,dest2);	
	if(pos1 && pos2 && (pos1!=pos2))
	{
        if((pos2-pos1-dest_len)>len)
			return 0;
		strncpy(ret,pos1+dest_len,pos2-pos1-dest_len); 
	}
	else
	{
		return 0;
	}
	return (pos2);

}


BOOL DnsServerIpRead(void)
{
	FILE *f;
	int nFileSize;
	int result = 0;
	BOOL bRet;
	BYTE buf[1024];
	
	xprintf("read /etc/resolv.conf ...\r\n");

	f = fopen(DNSIP_FILENAME, "r");
	if (!f)
	{
		xprintf("read /enrolldata/resolv.conf ...\r\n");

		f = fopen("/enrolldata/resolv.conf", "r");
		if (!f)
		{		
			fclose(f);
			return 0;
		}	
	}
	
	memset(buf, 0, sizeof(buf));
	result = fread( buf, sizeof(buf), 1,f);	
	if (result == -1) //ERROR
		memset(buf, 0, sizeof(buf));
	
	fclose(f);
	xprintf("resolv.conf data=\r\n%s", buf);



	
}

BOOL DnsIpRead(void)
{
	FILE *f;
	int nFileSize;
	int result = 0;
	BOOL bRet;
	BYTE buf[1024];

	xprintf("DnsIpRead..............\r\n");
	xprintf("read /etc/resolv.conf ...\r\n");
	f = fopen(DNSIP_FILENAME, "r");
	if (!f)
	{
		xprintf("read /enrolldata/resolv.conf ...\r\n");
		f = fopen("/enrolldata/resolv.conf", "r");
		if (!f)
		{		
			fclose(f);
			return 0;
		}	
	}
	
	memset(buf, 0, sizeof(buf));
	result = fread( buf, sizeof(buf), 1,f);	
	if (result == -1) //ERROR
		memset(buf, 0, sizeof(buf));
	
	fclose(f);

	xprintf("resolv.conf data=\r\n%s", buf);

	bRet = TRUE;	

	char *pos ;	
	char str[10];	
	int ip[4];

	memset(str,0,10);
	pos=Http_CfgstrGet2((char *)buf,"nameserver ",".",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);	
	ip[0]=AsciiToDec(str);

	memset(str,0,10);
	pos=Http_CfgstrGet2(pos,".",".",str);
	if(pos==0)
		return 0;
	xprintf("%s\r\n",str);	
	ip[1]=AsciiToDec(str);

	memset(str,0,10);
	pos=Http_CfgstrGet2(pos,".",".",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);	
	ip[2]=AsciiToDec(str);

	memset(str,0,10);
	pos=Http_CfgstrGet2(pos,".","\n",str);
	if(pos==0)
		return 0;	
	xprintf("%s\r\n",str);
	ip[3]=AsciiToDec(str);	

    dbComm_ipPcBackground = UI_IP_MAKE(ip[0], ip[1], ip[2], ip[3]);
    return TRUE;

}


void DnsServerIpSet(DWORD ipPcBackground)
{
	int a, b, c, d;
	BYTE			macAddress[6];														//6
	DWORD			ipAddress;															//4
	DWORD			ipSubnetMask;														//4
	DWORD			ipDefaultGateway;													//4
	char *szCommand = (char*)malloc(1024);

	if (dbSetupTotal.setSystem.bDHCPUse==0)
		return ;

    //UI_IP_UNMAKE(dbSetupTotal.setSystem.ipPCBackground, a, b, c, d); 
	UI_IP_UNMAKE(ipPcBackground, a, b, c, d); 		

	if (!szCommand)
		return ;
	sprintf(szCommand, "echo \"nameserver %d.%d.%d.%d \">> /etc/resolv.conf", a,b,c,d);
	xprintf("%s\r\n", szCommand);	

	SB_EXEC(szCommand);
	FREE(szCommand);	
	//DnsIpRead();
}

//静态IP设置时调用
void DnsIpSet(DWORD ipPcBackground)
{
#if 1
	int a, b, c, d;
	BYTE			macAddress[6];														//6
	DWORD			ipAddress;															//4
	DWORD			ipSubnetMask;														//4
	DWORD			ipDefaultGateway;													//4
	char *szCommand = (char*)malloc(1024);

	if (dbSetupTotal.setSystem.bDHCPUse)   
		return ;
	
	ClearConfFile();
	
	if (dbComm_ipIsDHCP)
	{
		xifconfig("eth0", macAddress, &ipAddress, &ipSubnetMask, &ipDefaultGateway, FALSE);
		UI_IP_UNMAKE(ipDefaultGateway, a, b, c, d); 
	}
	else
	{
 
		UI_IP_UNMAKE(ipPcBackground, a, b, c, d); 
		
     }
	
	if (!szCommand)
		return ;
	sprintf(szCommand, "echo \"nameserver %d.%d.%d.%d \">> /etc/resolv.conf", a,b,c,d);
	xprintf("%s\r\n", szCommand);	

	SB_EXEC(szCommand);
	FREE(szCommand);
	
	DnsServerIpRead();
	
#endif
}



