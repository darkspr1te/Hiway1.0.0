#include "precomp.h"
#include <QtGui/QApplication>
#include <QtCore/QDir>
#include <QtGui/QLabel>
#include <QtCore/QMutex>
#include <QtGui/QPixmap>
#include "gui/MessageBox.h"
#include "dns.c"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <netdb.h>
#include <fcntl.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string>
#include <iostream>
using namespace std;

//web而加的
u8 WEB_CONNECT_SIGN = FALSE;//web连接上的标志
static u32 connect_count = 0;//递归次数标志
#define tid  "9100000";//设备类型"9100000"
char Hid[40];//硬件版本LNSC_PRODUCTNAME
char Sid[40];//软件版本LNSC_FIRMWAREVERSION
typedef struct _db_department
 {
	 char	 idstr[10];				 //1
	 char	 namestr[20];				 //1
 }DB_DEPARTMENT; 					
 
 DB_DEPARTMENT http_department_str[100];
static  int http_department_str_Num=0;

 char str_PunchedIn[40]; 
 char str_PunchedOut[40]; 
 char str_EmployeeName[40]; 
 char str_DepartmentName[40]; 
 char str_LastPunch[40]; 
 char str_CurrentTime[40]; 
 char str_UTCOffset[40]; 
 char str_AccountName[40];




extern void UniToStr(unsigned short *uni,unsigned char *str);

typedef struct
{
	int	wId;
	char	NameA[24];  
} PACKED_NAME_INFO;


CHAR	nUattendMachineID[20];   //"CB1000-2YAMREEV";


PACKED_NAME_INFO packed_name_info;
BOOL TCPCLIENT_SEND_DATA=0;
st_UserData UserData;
extern BOOL uiEnrollUserInfo(USER_INFO *pUserInfo);

/*
st_HeadString  UserIdLetterData[ ]={
{0,"ab"},
{3,"hxgds"},
{2,"bxa"},
{9,"12"},
{89,"lf"},

};
*/
static BOOL USER_ID_HEAD_OK=0;
char *UserIdLetterGet(DWORD LetterNum,int *len)
{
	int i;
	*len=0;
	USER_ID_HEAD_OK=0;
	for(i=0;i<MaxIdHeadListCount;i++)
	{
      if(gpUserIdHeadData[i].Index==LetterNum)
      	{
		   
		   *len=strlen(gpUserIdHeadData[i].Letter);
		   if(*len==0)
		       break;
		   USER_ID_HEAD_OK=1;  
		   return gpUserIdHeadData[i].Letter;
      	}
	}
	return  (" ");
}
DWORD UserIdIndexGet(char *Str)
{
	int i;
	USER_ID_HEAD_OK=0;
	if(strlen(Str)==0)
		return 0;
	for(i=0;i<MaxIdHeadListCount;i++)
	{
      if(memcmp(Str,gpUserIdHeadData[i].Letter,strlen(Str))==0)
      	{
		  USER_ID_HEAD_OK=1;
		  return gpUserIdHeadData[i].Index;
      	}
	}
	return  0;
}

BOOL UserId_isOk(void)
{
#if PRODUCT_AB == 1
   return  USER_ID_HEAD_OK;
#else
   return 1;
#endif
}

//////////////////////////////////////////////////////////////////////////
char* UserId_BCDtoSTR(UINT64 nID)
{
#if PRODUCT_AB == 1
	static char szID[IDNUMBER_LENGTH+1];
	int i,j;
	BYTE number;
    char *str;
	int len;
	
   // xprintf("UserId_BCDtoSTR  nID=%d \r\n",nID);	
	memset(szID, 0, sizeof(szID));

	for (i=IDNUMBER_LENGTH-1; i>=0; i--)
	{
		number = (BYTE)(nID % 10);
		if(i>(1))
		   szID[i] = '0' + number;
	    else
	    	{
	    	   str=UserIdLetterGet(nID,&len);
			   //xprintf("UserId_BCDtoSTR  i=0x%x str=%s \r\n",i,str);
			   //xprintf("UserId_BCDtoSTR  szID=%s \r\n",&szID[i]);
			   break;
	    	}
		nID /= 10;
		//xprintf("UserId_BCDtoSTR  szID=%s \r\n",&szID[i]);
	}
    for (i=0; i<len; i++)
    {
	  szID[i]=str[i];
    }	
	//xprintf("UserId_BCDtoSTR  strID=%s \r\n",szID);
	return szID;
	
#else

	static char szID[IDNUMBER_LENGTH];
	int i;
	BYTE number;

	memset(szID, 0, sizeof(szID));

	for (i=IDNUMBER_LENGTH-1; i>=0; i--)
	{
		number = (BYTE)(nID % 10);
		szID[i] = '0' + number;
		nID /= 10;
	}

//_lExit:
	return szID;
#endif
}

//////////////////////////////////////////////////////////////////////////
UINT64 UserId_STRtoBCD(char* strID)
{
#if PRODUCT_AB == 1
	int nLength, i,j;
	UINT64 nID = 0;
	BYTE number;
    char str[9];
	DWORD tmp;
	int letterlen;
	int numlen;	
	
	if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
	{
		USER_ID_HEAD_OK=0;
		return 0;
	}
    memset(str, 0, sizeof(str));
	letterlen=0;
	for (i=0; i<nLength; i++)
	{
	 		if ((strID[i] >= 'A' && strID[i] <= 'Z')||(strID[i] >= 'a' && strID[i] <= 'z'))
				letterlen++;
			else
				break;

	}
	numlen=nLength-letterlen;

	for (j=0; j<letterlen; j++)
	{
	  str[j]=strID[j];
	}
    tmp=UserIdIndexGet(str);
    if(tmp>9)
   	{
   	  nID +=(tmp/10)%10;
	  nID *= 10;
	  nID +=(tmp%10);
   	}
    else
      nID +=tmp;	
   
	for (i=0; i<(6-numlen); i++)
	{
			nID *= 10;
			number = 0;
			nID += number;
	}	
	
	for (i=letterlen; i<(letterlen+numlen); i++)
	{
			nID *= 10;
			if (strID[i] >= '0' && strID[i] <= '9')
				number = strID[i] - '0';
			else
				number = 0;
			nID += number;
	}	
	//xprintf("UserId_STRtoBCD strID=%s nID=%d \r\n", strID,nID);
	return nID;

#else

	int nLength, i;
	UINT64 nID = 0;
	BYTE number;

	if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
		return 0;

	for (i=0; i<nLength; i++)
	{
		nID *= 10;

		if (strID[i] >= '0' && strID[i] <= '9')
			number = strID[i] - '0';
// 		else if (strID[i] >= 'A' && strID[i] <= 'Z')
// 			number = 10 + strID[i] - 'A';
// 		else if (strID[i] >= 'a' && strID[i] <= 'z')
// 			number = 10 + strID[i] -'a';
		else
			number = 0;
		nID += number;
	}

	return nID;
#endif
}


	
/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX_SOCKS			1
#define INVALID_SOCK_HANDLE	-1
#define PORT_NUM			5005
#define TCP_RECV_TIMEOUT	5000  
#define TCP_RECV_CMD_TIMEOUT 20//改动过原是20  
#define UART_RECV_TIMEOUT	7000
#define USB_RECV_CMD_TIMEOUT 100
#define USB_RECV_TIMEOUT	5000
#define SOCK_BUFFER_SIZE	1024
#define COMM_COMPANY_MARK	0xA6F6   
#define COMM_PWD_TCPIP		dbSetupTotal.setSystem.dwCommPassword
#define COMM_PWD_SERIAL		0
#define UART_WAIT_UNTIL_SENT 0x6A47

#define	COMM_BLOCK_SIZE		1020

#define SOCKET_CLOSE(_h_)	{((_h_) && ((_h_)!=INVALID_SOCK_HANDLE))?close((_h_)):(_h_); (_h_)=INVALID_SOCK_HANDLE;}

extern int __DOOR_STATUS[4];
extern QLabel *g_StatusWindow;

extern void comm_sendtime (void);	



int uiProcDrawStatus();
//////////////////////////////////////////////////////////////////////////
HFILE	g_hServerSock = INVALID_SOCK_HANDLE;
HFILE	g_hClientSocks[MAX_SOCKS];
int		g_hClientSocksInfo[MAX_SOCKS];
DWORD	g_dwClientIP[MAX_SOCKS];

struct sockaddr_in client_addr;   
volatile HFILE  Client_Sock;              

DWORD dwRealTime = 0;
DWORD dwTimeSynTime = 0;

DWORD dwDhcpRealTime = 0; 
DWORD dwSendAckRealTime = 0; 
BOOL  bSendAckTimeout=0;
DWORD dbComm_DHCPLeaseTime=0;

int   nRealSpaceTime = 10;//以前是10秒一次        
//
//
//////////////////////////////////////////////////////////////////////////
BOOL comm_tcpserver_init(void)
{
	int i;
	struct sockaddr_in server_addr;
	socklen_t server_len;
	struct timeval tv;
	int nUsed = 1;
	WORD wPortNum;

	if (g_hServerSock != INVALID_HANDLE_VALUE)
		return TRUE;

	for (i=0; i<MAX_SOCKS; i++)
	{
		g_hClientSocks[i] = INVALID_SOCK_HANDLE;
		g_hClientSocksInfo[i] = 0;
		g_dwClientIP[i] = 0;
	}

	g_hServerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (g_hServerSock < 0)
	{
//		printf("Server Socket Create Error !\n");
		g_hServerSock = INVALID_SOCK_HANDLE;
		return FALSE;
	}

	tv.tv_sec = 0;
	tv.tv_usec = 500;
	if (setsockopt(g_hServerSock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
	{
//		printf("Socket Option setting(SO_RCVTIMEO) fail !\n");
		SOCKET_CLOSE(g_hServerSock);
		return FALSE;
	}

	if (setsockopt(g_hServerSock, SOL_SOCKET, SO_REUSEADDR, &nUsed, sizeof(nUsed)) == -1)
	{
//		printf("Socket Option setting(SO_REUSEADDR) fail !\n");
		SOCKET_CLOSE(g_hServerSock);
		return FALSE;
	}

	wPortNum = dbComm_wPortNum;  
	if (!wPortNum)
		dbComm_wPortNum = wPortNum = PORT_NUM;
	server_len = sizeof(server_addr);
	bzero(&server_addr, server_len);

                                          
		server_addr.sin_family = AF_INET;
		server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
		server_addr.sin_port = htons(wPortNum);

		if (bind(g_hServerSock, (struct sockaddr*)&server_addr, server_len) != 0)
		{
	//		printf("Socket Binding Error !\n");
			SOCKET_CLOSE(g_hServerSock);
			return FALSE;
		}

		if (listen(g_hServerSock, 1) < 0)
		{
	//		printf("Socket Listening Error !\n");
			SOCKET_CLOSE(g_hServerSock);
			return FALSE;
		}   

//	printf("Server Socket Create Success !\n");

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void comm_tcpserver_close(void)
{
	char c;
	int ret, i;

	if (g_hServerSock == INVALID_HANDLE_VALUE)
		return;

	for (i=0; i<MAX_SOCKS; i++)
	{
		if (g_hClientSocks[i] == INVALID_SOCK_HANDLE)
			continue;

		while (read(g_hClientSocks[i], &c, 1) == 1){};
		ret = shutdown(g_hClientSocks[i], SHUT_RDWR);
		SOCKET_CLOSE(g_hClientSocks[i]);
	}

	if (g_hServerSock != INVALID_SOCK_HANDLE)
	{
		while (read(g_hServerSock, &c, 1) == 1){};
		ret = shutdown(g_hServerSock, SHUT_RDWR);
		SOCKET_CLOSE(g_hServerSock);
	}
}

//////////////////////////////////////////////////////////////////////////
void comm_tcpclient_accept(void)
{
	int i, _empty_idx = -1;
	int nTime;
	HFILE hSock;
	struct sockaddr addr;
	struct sockaddr_in* client_addr = (struct sockaddr_in*)&addr;
	int client_len = sizeof(addr);

	nTime = GetMainTickCount();

	for (i=0; i<MAX_SOCKS; i++)
	{
		if (g_hClientSocks[i] == INVALID_SOCK_HANDLE)
		{
			g_hClientSocksInfo[i] = 0;
//			g_dwClientIP[i] = 0;
			_empty_idx = i;
		}
		else
		{
			if (comm_tcpcheck_close(g_hClientSocks[i]))
			{
				comm_tcpclient_close(g_hClientSocks[i]);
				g_hClientSocksInfo[i] = 0;
				g_dwClientIP[i] = 0;
				_empty_idx = i;
			}
			else if (nTime - g_hClientSocksInfo[i] >= 5000)
			{
				comm_tcpclient_close(g_hClientSocks[i]);
				g_hClientSocksInfo[i] = 0;
//				g_dwClientIP[i] = 0;
				_empty_idx = i;
			}
		}
	}

	if (g_hServerSock != INVALID_SOCK_HANDLE)
	{
		hSock = accept(g_hServerSock, (struct sockaddr*)&addr, (socklen_t*)&client_len);
		if (hSock < 0)
			return;

		if (g_bDisableDevice && g_dwClientIP[_empty_idx] && htonl(client_addr->sin_addr.s_addr) != g_dwClientIP[_empty_idx])
		{
			shutdown(hSock, SHUT_RDWR);
			SOCKET_CLOSE(hSock);
		}

		g_hClientSocks[_empty_idx] = hSock;
		g_hClientSocksInfo[_empty_idx] = nTime;
		g_dwClientIP[_empty_idx] = htonl(client_addr->sin_addr.s_addr);
	}
}

//////////////////////////////////////////////////////////////////////////
void comm_tcpclient_close(HFILE hSock)
{
	char c;
	int ret, i;

	if (hSock == INVALID_SOCK_HANDLE)
		return;

	for (i=0; i<MAX_SOCKS; i++)
	{
		if (g_hClientSocks[i] == hSock)
			break;
	}

	if (i < MAX_SOCKS)
	{
		while (read(g_hClientSocks[i], &c, 1) == 1){};
		ret = shutdown(g_hClientSocks[i], SHUT_RDWR);
		SOCKET_CLOSE(g_hClientSocks[i]);
	}
}

//////////////////////////////////////////////////////////////////////////
BOOL comm_tcpcheck_close(HFILE hSock)
{
	fd_set rdFD;
	struct timeval tv;
	char temp;

	tv.tv_sec = 0;
	tv.tv_usec = 0;

	FD_ZERO(&rdFD);
	FD_SET(hSock, &rdFD);

	if (select(hSock + 1, &rdFD, 0, 0, &tv) == 1)
	{
		if (recv(hSock, &temp, 1, MSG_PEEK) == 0)
			return TRUE;
	}

	return FALSE;
}

struct sockaddr_in serverip;
unsigned int connect_fail_count=0;
DWORD DNS_SDDR=0;

//////////////////////////////////////////////////////////////////////////
BOOL comm_tcpclient_connect(void)
{
	WORD  wPortNum;
    	struct hostent *host;
	int a, b, c, d;
	struct timeval timeo,tv;
	int  flags,retcode,err;
	socklen_t len;
	fd_set rdevents,wrevents,exevents;

	wPortNum = dbSetupTotal.setSystem.wPortNumBack;
	if (!wPortNum)
		wPortNum = PORT_NUM;

 
    	if (Client_Sock)
	{
      		SOCKET_CLOSE(Client_Sock);   
 	}
	Client_Sock = socket(AF_INET, SOCK_STREAM, 0);  
	if (Client_Sock)
	{
		bzero(&client_addr, sizeof(client_addr));
		client_addr.sin_family = AF_INET;
		//client_addr.sin_port = htons(wPortNum);
		//xprintf("szHostByName[0]=%d \r\n",dbSetupTotal.setSystem.szHostByName[0]);

		if (!dbSetupTotal.setSystem.szHostByName[0])//如果不是按域名获取，那么就取后台ip
		{
			 client_addr.sin_addr.s_addr = htonl(dbComm_ipPcBackground);
			 client_addr.sin_port = htons(wPortNum);
		}
		else 
		{
			if(serverip.sin_addr.s_addr && connect_fail_count<5)
			{
			   	client_addr=serverip;
			}
			else
			{
			          if(DNS_SDDR==0)	 	
				   {
					 char *szFile = &dbSetupTotal.setSystem.szHostByName[0];
					 
				//	 xprintf("gngethostbyname... host=%s\r\n",szFile);
				//	 host = gngethostbyname(szFile,15);
				//	 if ( host == NULL )
				       	wdog_app_alive();//added by hym			     
				       	DNS_SDDR=gngethostbyname(szFile,1);				 			     
					 if(DNS_SDDR==0)
					 {
						xprintf("%s","gngethostbyname fail \r\n");
						memset(&serverip,0,sizeof(serverip));
						SOCKET_CLOSE(Client_Sock);
						return false;
					 }
			        }
				 xprintf("%s","gngethostbyname end\r\n");
	              	//    memcpy(&client_addr.sin_addr, host->h_addr,host->h_length);
			//	 UI_IP_UNMAKE(client_addr.sin_addr.s_addr, a, b, c, d);
			//	 dbComm_ipPcBackground = UI_IP_MAKE(a, b, c, d);
			        	 client_addr.sin_addr.s_addr = htonl(DNS_SDDR);			       
				 client_addr.sin_port = htons(wPortNum);
				 serverip=client_addr;
			}
		}

/*    
        		timeo.tv_sec = 5;   
        		timeo.tv_usec = 0;  //500
    		if (setsockopt(Client_Sock, SOL_SOCKET, SO_SNDTIMEO, &timeo, sizeof(timeo)) == -1)   
		{
			SOCKET_CLOSE(Client_Sock);
			return FALSE;
		} 

		tv.tv_sec = 0;
		tv.tv_usec = 500;
		if (setsockopt(Client_Sock, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv)) == -1)
		{
//			printf("Socket Option setting(SO_RCVTIMEO) fail !\n");
			SOCKET_CLOSE(Client_Sock);
			return FALSE;
		}
*/		   
        		//xprintf("comm_tcpclient_connect...\r\n");			
		//comm_sendtime();
		//if (connect(Client_Sock, (struct sockaddr*)&client_addr, sizeof(struct sockaddr)) != 0)   //3s debug
		if (connect_nonb(Client_Sock, (struct sockaddr*)&client_addr, sizeof(struct sockaddr),4)  !=  0)//原来是8
		{
		      	DNS_SDDR=0;
			SOCKET_CLOSE(Client_Sock);
	        		//comm_sendtime();		
		    	//xprintf("%s","comm_tcpclient_connect fail \r\n");	
			connect_fail_count++;
			return FALSE;
		}  
		
		if(fcntl(Client_Sock, F_SETFL, O_NONBLOCK) == -1) 
		{ 
		        DNS_SDDR=0;
			SOCKET_CLOSE(Client_Sock);
			connect_fail_count++;
			return FALSE;
		}
		
        		comm_sendtime();		
		xprintf("%s","comm_tcpclient_connect succeed\n");		
		connect_fail_count=0;
	}

	//make_connect();//当连接上时，就发送本设备的具体信息
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
int comm_tcpclient_send(void *pBuffer, int len)
{
	int ret = 0;

    	//ret = sendto(Client_Sock, pBuffer, len, 0, (struct sockaddr*)&client_addr, sizeof(client_addr));

	//下面这个是作为分包发送的备份，如若上面的不行，可以采用下面的试试
	ret = comm_socksend(Client_Sock, pBuffer, len);
/*	if(ret != len)
	{
		ret = comm_socksend(Client_Sock, pBuffer, len);
		if(ret != len)
		{
			printf("send is error!!\r\n");
			return ret;
		}
	}
*/	
   	return ret;
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
int comm_sockrecv(HFILE hSock, void *pBuffer, int len, int nTimeout)
{
	int nETime;
	int nReqSize = len;
	int nReadSize = 0;
	BYTE* pBufIdx = (BYTE*)pBuffer;
//xprintf("2222 i am in my world!!\r\n");	
	if (dbLicense.byTcpipMode == TCPIP_SERVER)   //这是作为服务端的接收
	{                                           
		if (hSock == INVALID_SOCK_HANDLE)   
			return -1;                      

		uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

		nETime = GetMainTickCount() + nTimeout;
		
		while ((len > 0) && GetMainTickCount() < nETime)
		{
			int nCurrentReadSize = MIN(1024, len);
			
			uiLcdProgress(LCDPROG_PERCENT(nReadSize, nReqSize));

			nCurrentReadSize = recv(hSock, pBufIdx, nCurrentReadSize, 0);  

			if (nCurrentReadSize > 0)
			{
				pBufIdx += nCurrentReadSize;
				len -= nCurrentReadSize;
				nReadSize += nCurrentReadSize;
				nETime = GetMainTickCount() + nTimeout;
				continue;
			}
			else if (nCurrentReadSize < 0)
			{
				if (errno == EWOULDBLOCK)
				{
					continue;
				}
			}

	//		printf("nRet=%d, errno=%d\n", nRet, errno);
			comm_tcpclient_close(hSock);
	//		xifconfig("eth0", dbComm_macAddress, &dbComm_ipAddress, &dbComm_ipSubnetMask, &dbComm_ipDefaultGateway, TRUE);
			break;
		}   

		uiLcdProgressEnd();
		return nReadSize;
	}
	else           //这才是我作为客户端所关注的
	{
		uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);
//xprintf("33333\r\n");
		nETime = GetMainTickCount() + nTimeout;//准备超时时间，以毫秒为基础
		
		while ((len > 0) && GetMainTickCount() < nETime)
		{
			int nCurrentReadSize = MIN(1024, len);//原为1024
			
			uiLcdProgress(LCDPROG_PERCENT(nReadSize, nReqSize));

			nCurrentReadSize = recv(Client_Sock, pBufIdx, nCurrentReadSize, 0);//接收数据
		//	comm_uartsend(0, &nCurrentReadSize, sizeof(nCurrentReadSize));
		
			if (nCurrentReadSize > 0)//没接收完，继续接收，做接收的准备
			{
				//xprintf("read HTTP data %d\r\n",nCurrentReadSize);
				pBufIdx += nCurrentReadSize;//数据指针增加
				len -= nCurrentReadSize;//规定数据减少
				nReadSize += nCurrentReadSize;//实际接收增加
				nETime = GetMainTickCount() + nTimeout;//时间重新设置
                			continue;//继续接收
			}
            		else if (nCurrentReadSize < 0)//接收为0的话，就返回
			{
				if (errno == EWOULDBLOCK)
				{
					//xprintf("nCurrentReadSize==%d\r\n",nCurrentReadSize);
					continue;
				}
				//xprintf("nCurrentReadSize1111111==%d\r\n",nCurrentReadSize);
			}

		//	break;
		}   

		uiLcdProgressEnd();
		return nReadSize;
	}   
}

//////////////////////////////////////////////////////////////////////////
int comm_socksend(HFILE hSock, void *pBuffer, int len)
{
	int nETime;   
	int counter = SOCK_BUFFER_SIZE;
	int nReqSize = len;
	int nWrittenSize = 0;
	BYTE* pBufIdx = (BYTE*)pBuffer;
/*
	//测试socket环境，缓冲区大小
	int rcvbuf_len;
     	socklen_t xxx = sizeof(rcvbuf_len);
    	if( getsockopt( hSock, SOL_SOCKET, SO_SNDBUF, (void *)&rcvbuf_len, &xxx ) < 0 ){
        		perror("getsockopt: ");
        		return -1;
    	}
    	xprintf("the recevice buf len: %d\n", rcvbuf_len );
	
*/
	if (dbLicense.byTcpipMode == TCPIP_SERVER)  
	{                                          
		if (hSock == INVALID_SOCK_HANDLE)
			return -1;
		
		uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

		while ((len > 0) && (counter-- > 0))
		{
			int nCurrentWrittenSize = MIN(SOCK_BUFFER_SIZE, len);

			uiLcdProgress(LCDPROG_PERCENT(nWrittenSize, nReqSize));

			nCurrentWrittenSize = send(hSock, pBufIdx, nCurrentWrittenSize, 0);  
			
			if (nCurrentWrittenSize > 0)
			{
				pBufIdx += nCurrentWrittenSize;
				len -= nCurrentWrittenSize;
				nWrittenSize += nCurrentWrittenSize;
				counter = SOCK_BUFFER_SIZE;
				continue;
			}
			else if (nCurrentWrittenSize < 0)
			{
				if (errno == -EWOULDBLOCK)
					continue;
			}
			
			break;
		}
		
		uiLcdProgressEnd();

		return nWrittenSize;
	}
	else
	{
        		uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

		nETime = GetMainTickCount() + TCP_RECV_TIMEOUT;
		
		while ((len > 0) && GetMainTickCount() < nETime)
		{
			int nCurrentWrittenSize = MIN(SOCK_BUFFER_SIZE, len);

			uiLcdProgress(LCDPROG_PERCENT(nWrittenSize, nReqSize));

			nCurrentWrittenSize = send(Client_Sock, pBufIdx, nCurrentWrittenSize, 0);
			if (nCurrentWrittenSize < 0)
			{
				//xprintf("errno ==%d\r\n",errno);
				if (errno == -EWOULDBLOCK || errno == 11 || errno == 32)//为解决大数据发送失败而加入的判断
					continue;			
			}
			pBufIdx += nCurrentWrittenSize;
			len -= nCurrentWrittenSize;
			nWrittenSize += nCurrentWrittenSize;
		}
		uiLcdProgressEnd();
		return nWrittenSize;
	}  
}
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
//////////////////////////////////////////////////////////////////////////
int comm_udpsend(HFILE hSock, void *pBuffer, int len)
{
	int ret = 0;
	struct sockaddr_in addr;
	WORD wPortNum;

	wPortNum = dbComm_wPortNum;
	if (!wPortNum)
		wPortNum = PORT_NUM;

	hSock = socket(AF_INET, SOCK_DGRAM, 0);
	if (hSock)
	{
		bzero(&addr, sizeof(addr));
		addr.sin_family = AF_INET;
		addr.sin_addr.s_addr = htonl(dbComm_ipPcBackground);
		addr.sin_port = htons(wPortNum);
		ret = sendto(hSock, pBuffer, len, 0, (struct sockaddr*)&addr, sizeof(addr));
		close(hSock);
//		printf("addr=%08x, %d\n", dbComm_ipPcBackground, dbComm_wPortNum);
	}
	return ret;
}

//////////////////////////////////////////////////////////////////////////
int comm_uartrecv(int iUART, void *pBuffer, int len, int nTimeout)
{
	int i;
	unsigned char* pTemp = (unsigned char*)pBuffer;
	fd_set s_fd_in;
	struct timeval s_timeval;
	int s_check, s_read_bytes;
	HFILE s_handle = g_hUart[iUART];
	
	if (s_handle == INVALID_HANDLE_VALUE)
		return 0;

//	g_ComMutex.lock();

	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	i = 0;
	while (i < len)
	{
		uiLcdProgress(LCDPROG_PERCENT(i, len));

		FD_ZERO(&s_fd_in);
		FD_SET(s_handle, &s_fd_in);
		s_timeval.tv_sec = (long)(nTimeout / 1000), s_timeval.tv_usec = (long)(nTimeout % 1000) * 1000;
		s_check = select(s_handle + 1, (fd_set *)(&s_fd_in), (fd_set *)0, (fd_set *)0, (struct timeval *)(&s_timeval)); 
		if (s_check <= 0)
			break;
		s_read_bytes = read(s_handle, (void*)&pTemp[i], (size_t)(len - i));
		if (s_read_bytes > 0)
			i += s_read_bytes;
	}
	
	uiLcdProgressEnd();

//	g_ComMutex.unlock();

	return i;
}

//////////////////////////////////////////////////////////////////////////
int comm_uartsend(int iUART, void *pBuffer, int len)
{
	int nReqSize = len;
	int nWrittenSize = 0;
	BYTE* pBufIdx = (BYTE*)pBuffer;
	HFILE s_handle = g_hUart[iUART];

	if (s_handle == INVALID_HANDLE_VALUE)
		return 0;

//	g_ComMutex.lock();
	if (iUART == 1)
		RS485_ENABLE();

// 	printf("sending start");
// 	for (int i=0; i<len; i++)
// 		printf("%02x ", ((BYTE*)pBuffer)[i]);
// 	printf("\n");
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	while (len > 0)
	{
		int nCurrentWrittenSize = MIN(1024, len);

		uiLcdProgress(LCDPROG_PERCENT(nWrittenSize, nReqSize));

		nCurrentWrittenSize = write(s_handle, pBufIdx, nCurrentWrittenSize);

		if (nCurrentWrittenSize > 0)
		{
			pBufIdx += nCurrentWrittenSize;
			len -= nCurrentWrittenSize;
			nWrittenSize += nCurrentWrittenSize;
			continue;
		}
		else if (nCurrentWrittenSize < 0)
		{
			if (errno == -EWOULDBLOCK)
				continue;
		}

// 		printf("uart_send: nCurrentWrittenSize=%d, err=%s\n", nCurrentWrittenSize, strerror(errno));
		break;
	}

	uiLcdProgressEnd();

//	printf("uart_send: len=%d\n", len);
// 	printf("sending exit\n");
	if (iUART == 1)
	{
		int nleft;
// 		DelayMicroSecond(100*1000);
		do
		{
			nleft = ioctl(g_hUart[1], TIOCMIWAIT, UART_WAIT_UNTIL_SENT);
		} while (nleft > 0);
//		DelayMicroSecond(10*1000);
		RS485_DISABLE();
	}

//	g_ComMutex.unlock();

	return nWrittenSize;
}

//////////////////////////////////////////////////////////////////////////
void comm_uartclear(int iUART)
{
	HFILE s_handle = g_hUart[iUART];
	
	if (s_handle == INVALID_HANDLE_VALUE)
		return;

	ioctl(s_handle, TCFLSH, TCIOFLUSH);
}

//////////////////////////////////////////////////////////////////////////
int comm_usbrecv(HFILE hUsb, void *pBuffer, int len, int nTimeout)
{
	int nETime;
	int nReqSize = len;
	int nReadSize = 0;
	BYTE* pBufIdx = (BYTE*)pBuffer;
	if(hUsb == INVALID_HANDLE_VALUE)
		return 0;

	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);
	nETime = GetMainTickCount() + nTimeout;
	while ((len > 0) && GetMainTickCount() < nETime)
	{
		int nCurrentReadSize = MIN(1024, len);
		uiLcdProgress(LCDPROG_PERCENT(nReadSize, nReqSize));
		nCurrentReadSize = read(hUsb, pBufIdx, nCurrentReadSize);
		if (nCurrentReadSize > 0)
		{
			pBufIdx += nCurrentReadSize;
			len -= nCurrentReadSize;
			nReadSize += nCurrentReadSize;
			nETime = GetMainTickCount() + nTimeout;
			continue;
		}
		else if (nCurrentReadSize <= 0)
		{
			if (nCurrentReadSize == 0)
				continue;
			if (errno == EWOULDBLOCK)
			{
				continue;
			}
		}
		
		break;
	}
	uiLcdProgressEnd();
	return nReadSize;
}
int comm_usbsend(HFILE hUsb, void *pBuffer, int len)
{
	int counter = SOCK_BUFFER_SIZE;
	int nReqSize = len;
	int nWrittenSize = 0;
	BYTE* pBufIdx = (BYTE*)pBuffer;
	if(hUsb == INVALID_HANDLE_VALUE)
		return 0;
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);
	while ((len > 0) && (counter-- > 0))
	{
		int nCurrentWrittenSize = MIN(SOCK_BUFFER_SIZE, len);
		uiLcdProgress(LCDPROG_PERCENT(nWrittenSize, nReqSize));
		nCurrentWrittenSize = write(hUsb, pBufIdx, nCurrentWrittenSize);
		if (nCurrentWrittenSize > 0)
		{
			pBufIdx += nCurrentWrittenSize;
			len -= nCurrentWrittenSize;
			nWrittenSize += nCurrentWrittenSize;
			counter = SOCK_BUFFER_SIZE;
			continue;
		}
		else if (nCurrentWrittenSize < 0)
		{
			if (nCurrentWrittenSize == 0)
				continue;
			if (errno == -EWOULDBLOCK)
				continue;
		}
		break;
	}
	uiLcdProgressEnd();
	return nWrittenSize;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
enum
{
	RES_ACK = 1,
	RES_NACK
};

int comm_mode = COMM_MODE_NONE;
int comm_sub_mode = -1;

BOOL comm_send_cmd(WORD cmd);
long comm_recv_ack(DWORD* pData);
BOOL comm_send_data(void* pbuf, int nsize);
void comm_close();

/************************************************************************/
/*                                                                      */
/************************************************************************/
void comm_crypt(void* pbuf, int nsize, DWORD dwCommPassword)
{
	int i;
	if (dbLicense.byTcpipMode == TCPIP_SERVER)   
	{                                                         
		DWORD dwPwd = dwCommPassword + COMM_COMPANY_MARK;
		BYTE *pData = (BYTE*)pbuf;
		BYTE *pKey = (BYTE*)&dwPwd;
		for (i = 0; i < nsize; i++) *pData++ ^= pKey[i % 4];  
    }  
}

BOOL comm_send(void* pbuf, int nsize)
{
	BOOL bRet;

	if (comm_mode != COMM_MODE_UDP) comm_crypt(pbuf, nsize, (comm_mode == COMM_MODE_TCP) ? COMM_PWD_TCPIP : COMM_PWD_SERIAL);
	switch (comm_mode)
	{
	case COMM_MODE_SERIAL:
		bRet = (comm_uartsend(comm_sub_mode, pbuf, nsize) == nsize);
		break;
	case COMM_MODE_USB:
		bRet = (comm_usbsend(g_hUSBDevice, pbuf, nsize) == nsize);
		break;
	case COMM_MODE_TCP:
		bRet = (comm_socksend(g_hClientSocks[comm_sub_mode], pbuf, nsize) == nsize);
		break;
	case COMM_MODE_UDP:
		if (dbLicense.byTcpipMode == TCPIP_SERVER)    
			 bRet = (comm_udpsend(0, pbuf, nsize) == nsize);
        else bRet = (comm_tcpclient_send(pbuf, nsize) == nsize);   
		break;
	default:
		bRet = FALSE;
		break;
	}
	if (comm_mode != COMM_MODE_UDP) comm_crypt(pbuf, nsize, (comm_mode == COMM_MODE_TCP) ? COMM_PWD_TCPIP : COMM_PWD_SERIAL);
	return bRet;
}

BOOL comm_recv(void* pbuf, int nsize)
{
	BOOL bRet;

	switch (comm_mode)
	{
	case COMM_MODE_SERIAL:
		bRet = (comm_uartrecv(comm_sub_mode, pbuf, nsize, UART_RECV_TIMEOUT) == nsize);
		break;
	case COMM_MODE_USB:
		bRet = (comm_usbrecv(g_hUSBDevice, pbuf, nsize, USB_RECV_TIMEOUT) == nsize);
		break;
	case COMM_MODE_TCP:
		bRet = (comm_sockrecv(g_hClientSocks[comm_sub_mode], pbuf, nsize, TCP_RECV_TIMEOUT) == nsize);
		break;
	default:
		bRet = FALSE;
		break;
	}

	if (bRet) comm_crypt(pbuf, nsize, (comm_mode == COMM_MODE_TCP) ? COMM_PWD_TCPIP : COMM_PWD_SERIAL);
	return bRet;
}

BOOL comm_open(int nCommMode, WORD /*wMachineID*/, DWORD dwPassword, WPARAM /*wParam*/, LPARAM /*lParam*/)
{
	long nRet;
	comm_close();

	switch (nCommMode)
	{
	case COMM_MODE_SERIAL:
		/*comm_base = &comm_serial;*/
		comm_mode = COMM_MODE_SERIAL;
		comm_sub_mode = 1;
		comm_uartclear(comm_sub_mode);
		break;
	case COMM_MODE_USB:		/*comm_base = &comm_usb;*/		break;
	case COMM_MODE_TCP:		/*comm_base = &comm_tcp;*/		break;
	default:				/*comm_base = NULL;*/			break;
	}

// 	if (!comm_base)
// 	{
// 		_comm_last_error = E_INVALID_COMMMODE;
// 		return FALSE;
// 	}
// 	if (!comm_base->Open(wMachineID, dwPassword, wParam, lParam))
// 	{
// 		comm_close();
// 		return FALSE;
// 	}
	if (!comm_send_cmd(CMD_INTERNAL_CHECK_PWD) ||
		comm_recv_ack(0) != RES_ACK ||
		!comm_send_data(&dwPassword, 4))
	{
		comm_close();
//		_comm_last_error = E_SOCK_SEND;
		return FALSE;
	}

	if ((nRet = comm_recv_ack(0)) != RES_ACK)
	{
		comm_close();
//		_comm_last_error = (nRet == RES_NACK? E_INVALID_PWD : E_SOCK_SEND);
		return FALSE;
	}

	comm_mode = nCommMode;
	return TRUE;
}

void comm_close()
{
// 	if (comm_base)
// 		comm_base->Close();
// 	comm_base = NULL;

	comm_mode = COMM_MODE_NONE;
}

BOOL comm_set_machineid(WORD /*wMachineID*/)
{
// 	if (!comm_base)
// 		return FALSE;
// 	comm_base->SetMachineID(wMachineID);
	return TRUE;
}

BOOL comm_wakeup_machine()
{
// 	if (!comm_base)
// 		return FALSE;
// 	return comm_base->WakeupMachine();
	return TRUE;
}

BYTE comm_get_disabledevice()
{
	int nRet = DISABLE_MODE_NONE;

	switch (comm_mode)
	{
	case COMM_MODE_SERIAL:
		if (comm_sub_mode >= 0 && comm_sub_mode <= 2)
			nRet = DISABLE_MODE_UART0 + comm_sub_mode;
		break;
	case COMM_MODE_USB:
		nRet = DISABLE_MODE_USB;
		break;
	case COMM_MODE_TCP:
		nRet = DISABLE_MODE_TCP;
		break;
	case COMM_MODE_UDP:
		nRet = DISABLE_MODE_UDP;  
		break;
	}
	return (BYTE)nRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define STX1				0x55
#define STX2				0xAA
#define STX3				0x5A
#define STX4				0xA5

typedef struct {		//	cmd			ack			csum			reserve
	BYTE 	head1;		//	55=STX1		AA=STX2		5A=STX3			A5=STX4
	BYTE 	head2;		//	AA=STX2		55=STX1		A5=STX4			5A=STX3
	WORD    devid;
	DWORD 	data;
	WORD	wPadding;
	WORD 	csum;
} STAFF;				// 12 BYTE  

#define STAFF_SIZE		sizeof(STAFF)

#define CMD_ACK		1
#define CMD_NAK		0



//////////////////////////////////////////////////////////////////////////
WORD comm_csum(void* pbuf, int nsize)
{
	WORD csum = 0;
	int i;
	
	for(i=0;i<nsize;i++)
		csum += ((BYTE*)pbuf)[i];
	
	return csum;
}
/*
u32 comm_csum1(void* pbuf, int nsize)
{
	u32 csum = 0;
	int i;
	
	for(i=0;i<nsize;i++)
		csum += ((BYTE*)pbuf)[i];
	
	return csum;
}
*/
BOOL comm_check_staff(STAFF* pstaff, BYTE head1, BYTE head2)
{
	if (pstaff->head1 != head1 ||
		pstaff->head2 != head2 ||
		pstaff->devid != DEVID ||
		pstaff->csum != comm_csum(pstaff, STAFF_SIZE - 2))
	{
		return FALSE;
	}
	
	return TRUE;
}

#define comm_check_cmd(pstaff)		comm_check_staff(pstaff, STX1, STX2)
#define comm_check_ack(pstaff)		comm_check_staff(pstaff, STX2, STX1)
#define comm_check_csum(pstaff)		comm_check_staff(pstaff, STX3, STX4)
#define comm_check_nack(pstaff)		comm_check_staff(pstaff, STX4, STX3)

void comm_make_staff(STAFF* pstaff, BYTE head1, BYTE head2)
{
	pstaff->head1 = head1;
	pstaff->head2 = head2;
	pstaff->devid = DEVID;
	pstaff->csum = comm_csum(pstaff, STAFF_SIZE - 2);
}

#define comm_make_cmd(pstaff)		comm_make_staff(pstaff, STX1, STX2)
#define comm_make_ack(pstaff)		comm_make_staff(pstaff, STX2, STX1)
#define comm_make_csum(pstaff)		comm_make_staff(pstaff, STX3, STX4)
#define comm_make_nack(pstaff)		comm_make_staff(pstaff, STX4, STX3)
#define comm_make_resp(ack, pstaff)	(ack == CMD_ACK ? comm_make_ack(pstaff) : comm_make_nack(pstaff))
//////////////////////////////////////////////////////////////////////////
BOOL comm_send_cmd(WORD cmd)
{
	STAFF staff;
	
	staff.data = cmd;
	comm_make_cmd(&staff);
	
	if(!comm_send(&staff, STAFF_SIZE))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL comm_send_ack(WORD ack, DWORD dwData)
{
	STAFF staff;
	
	staff.data = dwData;

	comm_make_resp(ack, &staff);
	
	if(!comm_send(&staff, STAFF_SIZE))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL comm_send_event(int nEvent, void *data, int len)
{
	static BYTE event_buf[EVENT_LENGTH];
	int *pEventType = (int*)&event_buf[0];
	BYTE *pEventBuf = &event_buf[4];
	int comm_mode_prev = comm_mode;

    if(tcpclient_connect_isok()==0)
		 return 0;
	
	dwRealTime = uiTimeGetTickCount();

	comm_mode = COMM_MODE_UDP;   

	bzero(event_buf, sizeof(event_buf));
	*pEventType = nEvent;
	memcpy(pEventBuf, data, MIN(EVENT_LENGTH - 4, len));
	memcpy(&event_buf[36], LNSC_FIRMWAREVERSION, 28);


	if (!comm_send_data(event_buf, EVENT_LENGTH))
	{
		comm_mode = comm_mode_prev;
		return FALSE;
	}

	comm_mode = comm_mode_prev;
	return TRUE;
}
BOOL comm_send_event_long(int nEvent, void *data, int len)
{
	static BYTE event_buf[EVENT_LENGTH];
	int *pEventType = (int*)&event_buf[0];
	BYTE *pEventBuf = &event_buf[4];
	int comm_mode_prev = comm_mode;

	

    if(tcpclient_connect_isok()==0)
		 return 0;
	
	dwRealTime = uiTimeGetTickCount();

	comm_mode = COMM_MODE_UDP;   

	bzero(event_buf, sizeof(event_buf));
	*pEventType = nEvent;
	memcpy(pEventBuf, data, MIN(EVENT_LENGTH - 4, len));
	memcpy(&event_buf[36], LNSC_FIRMWAREVERSION, 28);


	if (!comm_send_data(event_buf, EVENT_LENGTH))
	{
		comm_mode = comm_mode_prev;
		return FALSE;
	}

	comm_mode = comm_mode_prev;
	return TRUE;
}
BOOL comm_send_event2(int nEvent, void *data, int len)
{
	static BYTE event_buf[EVENT_LENGTH];
	int *pEventType = (int*)&event_buf[0];
	BYTE *pEventBuf = &event_buf[4];
	int comm_mode_prev = comm_mode;

    if(tcpclient_connect_isok()==0)
		 return 0;

	comm_mode = COMM_MODE_UDP;   

	bzero(event_buf, sizeof(event_buf));
	*pEventType = nEvent;
	memcpy(pEventBuf, data, MIN(EVENT_LENGTH - 4, len));
	//memcpy(&event_buf[36], LNSC_FIRMWAREVERSION, 28);


	if (!comm_send_data(event_buf, EVENT_LENGTH))
	{
		comm_mode = comm_mode_prev;
		return FALSE;
	}

	comm_mode = comm_mode_prev;
	return TRUE;
}

long comm_recv_ack(DWORD* pData)
{
	STAFF staff;
	long nRet = 0;
	
	if(!comm_recv(&staff, STAFF_SIZE))
		return nRet;
	
	if (comm_check_ack(&staff))
	{
		nRet = RES_ACK;
	}
	else if (comm_check_nack(&staff))
	{
		nRet = RES_NACK;
	}
	
	if (pData) *pData = staff.data;
	
	return nRet;
}

BOOL comm_recv_ack_and_check()
{
	return (comm_recv_ack(NULL) == RES_ACK);
}

BOOL comm_send_data(void* pbuf, int nsize)
{
	STAFF staff;

	staff.data = comm_csum(pbuf, nsize);
	comm_make_csum(&staff);

	if(!comm_send(pbuf, nsize) ||
		!comm_send(&staff, STAFF_SIZE))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL comm_send_data_gather(void** pbufs, int* nsizes, int ncount)
{
	STAFF staff;
	int i;
	WORD csum = 0;

	for (i=0; i<ncount; i++)
	{
		csum += comm_csum(pbufs[i], nsizes[i]);
	}
	staff.data = csum;
	comm_make_csum(&staff);

	for (i=0; i<ncount; i++)
	{
		if(!comm_send(pbufs[i], nsizes[i]))
			return FALSE;
	}
	if(!comm_send(&staff, STAFF_SIZE))
	{
		return FALSE;
	}
	
	return TRUE;
}

BOOL comm_recv_data(void* pbuf, int nsize)
{
	STAFF staff;
	

	if(!comm_recv(pbuf, nsize) ||
		!comm_recv(&staff, STAFF_SIZE) ||
		!comm_check_csum(&staff) ||
		staff.data != comm_csum(pbuf, nsize))
	{
		return FALSE;
	}

	return TRUE;
}

BOOL comm_recv_data_scatter(void** pbufs, int* nsizes, int ncount)
{
	STAFF staff;
	int i;
	WORD csum = 0;

	for (i=0; i<ncount; i++)
	{
		if(!comm_recv(pbufs[i], nsizes[i]))
			return FALSE;
	}
	if(!comm_recv(&staff, STAFF_SIZE))
		return FALSE;

	for (i=0; i<ncount; i++)
	{
		csum += comm_csum(pbufs[i], nsizes[i]);
	}
	if(staff.data != csum)
	{
		return FALSE;
	}

	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static BYTE cmd_buf[CMDSIZE];
static int cmd_buf_cnt = 0;

BOOL comm_uart_get_cmd(int iUART, STAFF* pvCMD)
{
//	static int s_retry_counter = 0;
	int s_buffer_cnt;
	HFILE s_handle = g_hUart[iUART];
	BYTE dummy[4];

	if (s_handle == INVALID_HANDLE_VALUE)
		return FALSE;

	while (TRUE)
	{
		ioctl(s_handle, FIONREAD, &s_buffer_cnt);

		if (cmd_buf_cnt + s_buffer_cnt < (int)STAFF_SIZE)
		{
// 			if (s_retry_counter++ >= 20)
// 			{
// 				read(s_handle, pvCMD, s_buffer_cnt);
// 				s_retry_counter = 0;
// 			}
//			comm_uartclear(iUART);
			return FALSE;
		}
		
		if (cmd_buf_cnt < 1)
		{
			dummy[0] = 0;
			read(s_handle, &dummy[0], 1);
			cmd_buf[0] = dummy[0];
			cmd_buf_cnt = 1;
		}
		else
		{
			dummy[0] = cmd_buf[0];
		}
		comm_crypt(&dummy[0], 1, COMM_PWD_SERIAL);
		if (dummy[0] != STX1)
			goto _lContinue;

		if (cmd_buf_cnt < 2)
		{
			dummy[1] = 0;
			read(s_handle, &dummy[1], 1);
			cmd_buf[1] = dummy[1];
			cmd_buf_cnt = 2;
		}
		else
		{
			dummy[1] = cmd_buf[1];
		}
		comm_crypt(&dummy[0], 2, COMM_PWD_SERIAL);
		if (dummy[1] != STX2)
			goto _lContinue;

		read(s_handle, &cmd_buf[cmd_buf_cnt], STAFF_SIZE - cmd_buf_cnt);
		cmd_buf_cnt = STAFF_SIZE;

		comm_crypt(cmd_buf, STAFF_SIZE, COMM_PWD_SERIAL);
		if (comm_check_cmd((STAFF*)cmd_buf))
		{
			memcpy(pvCMD, cmd_buf, STAFF_SIZE);
			memset(cmd_buf, 0, STAFF_SIZE);
			cmd_buf_cnt = 0;
			comm_mode = COMM_MODE_SERIAL;
			comm_sub_mode = iUART;
			return TRUE;
		}

		comm_crypt(cmd_buf, STAFF_SIZE, COMM_PWD_SERIAL);

_lContinue:
		cmd_buf_cnt--;
		if (cmd_buf_cnt > 0)
			memcpy(&cmd_buf[0], &cmd_buf[1], cmd_buf_cnt);
	}
	
	return FALSE;
}

BOOL comm_tcp_get_cmd(HFILE hSock, STAFF* pvCMD)
{
	if (comm_sockrecv(hSock, pvCMD, STAFF_SIZE, TCP_RECV_CMD_TIMEOUT) == STAFF_SIZE)
	{
		comm_crypt(pvCMD, STAFF_SIZE, COMM_PWD_TCPIP);
		if (comm_check_cmd(pvCMD))
		{
			comm_mode = COMM_MODE_TCP;
			return TRUE;
		}
	}

	return FALSE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL hcCommanProc(int nCMD);
BOOL arm_comm_tcp_get_cmd(HFILE hSock, CMDPKT* pvCMD);
//BOOL arm_comm_tcp_get_cmd3(HFILE hSock, PACK* pvCMD);//web2.0
BOOL Com_UartGetCMD(int iUART, CMDPKT* pvCMD);
BOOL Com_USBGetCMD(HFILE hUsb, CMDPKT* pvCMD);
BOOL Com_CommanProc(CMDPKT* vCMD);
//BOOL Com_CommanProc1(PACK* vCMD);
//int Com_CheckCMD_WEB(PACK* pvCMD);


//static volatile int __tcpclient_connect_status = 0;//0:没有连接1:已连接2:正在连接
volatile int __tcpclient_connect_status = 0;//0:没有连接1:已连接2:正在连接
extern BOOL http_WEB_CONNECT;

//////////////////////////////////////////////////////////////////////////
BYTE hcProcMain()
{
	CMDPKT vCMD;
	STAFF sCMD;

	PACK_HEAD gPACK;//web2.0

	comm_mode = COMM_MODE_NONE;
	
	bzero(&vCMD, sizeof(vCMD));
	if (dbLicense.bUseRS232 && dbSetupTotal.setSystem.bRS485Use && 
		(!g_bDisableDevice || g_bDisableDevice == DISABLE_MODE_UART1)) //RS485
	{
		if (Com_UartGetCMD(1, &vCMD))
		{
			Com_CommanProc(&vCMD);
			comm_mode = COMM_MODE_NONE;
			comm_sub_mode = -1;
		}
		else{//Setting Prog
			memcpy(&sCMD, &vCMD, STAFF_SIZE);
//			comm_crypt(&sCMD, STAFF_SIZE, COMM_PWD_SERIAL);

			if (comm_check_cmd(&sCMD))
			{
				comm_mode = COMM_MODE_SERIAL;
				comm_sub_mode = 1;
// 				if((sCMD.data >= CMD_DOWN_DOWNLOADER_WRITE && sCMD.data <= CMD_TEST_GET_IMAGE) || sCMD.data == CMD_INTERNAL_CHECK_PWD){
// 					hcCommanProc_Set(sCMD.data);
// 				}
				hcCommanProc(sCMD.data);
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
			}
		}
	}

	bzero(&vCMD, sizeof(vCMD));
	bzero(&gPACK, sizeof(gPACK));//web2.0
	if(dbLicense.bUseEthernet && dbSetupTotal.setSystem.bEthernetUse &&
		(!g_bDisableDevice || g_bDisableDevice == DISABLE_MODE_TCP)) //TCPIP
	{

		//增加web2.0 接收
		if(__tcpclient_connect_status == 1 )//首先确定连接到服务端
		{
			if (web2_get_cmd(Client_Sock, &gPACK))
			{						
				//Com_CommanProc1(&gPACK);
				web2_run_cmd(Client_Sock,&gPACK);
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
				
			}			
		}
		else
		{
			tcpclient_connect_start();
		}

	}

	bzero(&vCMD, sizeof(vCMD));
	if(dbLicense.bUseRS232 && dbSetupTotal.setSystem.bRS232Use && !dbSetupTotal.setSystem.dwBindingID
		&& (!g_bDisableDevice || g_bDisableDevice == DISABLE_MODE_UART0)) //RS232
	{
		if (Com_UartGetCMD(0, &vCMD))
		{
			Com_CommanProc(&vCMD);
			comm_mode = COMM_MODE_NONE;
			comm_sub_mode = 0;
		}
		else{//Setting Prog
			memcpy(&sCMD, &vCMD, STAFF_SIZE);
//			comm_crypt(&sCMD, STAFF_SIZE, COMM_PWD_SERIAL);
			
			if (comm_check_cmd(&sCMD))
			{
				comm_mode = COMM_MODE_SERIAL;
				comm_sub_mode = 0;
// 				if((sCMD.data >= CMD_DOWN_DOWNLOADER_WRITE && sCMD.data <= CMD_TEST_GET_IMAGE) || sCMD.data == CMD_INTERNAL_CHECK_PWD){
// 					hcCommanProc_Set(sCMD.data);
// 				}
				hcCommanProc(sCMD.data);
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = 0;
			}
		}
	}

	bzero(&vCMD, sizeof(vCMD));
	if (dbLicense.bUseUSB && dbSetupTotal.setSystem.bUSBSlaveUse && (!g_bDisableDevice || g_bDisableDevice == DISABLE_MODE_USB)) //USB Slave
	{
		if (Com_USBGetCMD(g_hUSBDevice, &vCMD))
		{
			Com_CommanProc(&vCMD);
			comm_mode = COMM_MODE_NONE;
			comm_sub_mode = -1;
		}
		else{//Setting Prog
			memcpy(&sCMD, &vCMD, STAFF_SIZE);
			comm_crypt(&sCMD, STAFF_SIZE, COMM_PWD_SERIAL);

			if (comm_check_cmd(&sCMD))
			{
				comm_mode = COMM_MODE_USB;
				comm_sub_mode = 1;
				hcCommanProc(sCMD.data);
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
			}
		}
	}
//static int k = 0;
//xprintf("k==%d\r\n",k++);
	
	//未收到反馈超时，向服务器主动建立连接 zwh 2010.10.15
	if ((dbLicense.byTcpipMode == TCPIP_CLIENT) && bSendAckTimeout && (uiTimeGetTickCount() - dwSendAckRealTime >= 40 * 1000/*120 * 1000*/))//时间缩短点  
	{
        		comm_sendtime();
		xprintf("%s","Rec data Ack Timeout\n");
		bSendAckTimeout=0;
		//测试
		http_WEB_CONNECT=0;
		WEB_CONNECT_SIGN = 0;
			
		if (!dbComm_ipIsDHCP)//静态IP
		{
            		xprintf("%s","write ip\n");
			dbComm_ipAddress = dbSetupTotal.setSystem.ipAddress;
			dbComm_ipSubnetMask = dbSetupTotal.setSystem.ipSubnetMask;
			dbComm_ipDefaultGateway = dbSetupTotal.setSystem.ipDefaultGateway;
			dbComm_ipPcBackground = dbSetupTotal.setSystem.ipPCBackground;
			//xifconfig("eth0", dbComm_macAddress, &dbComm_ipAddress, &dbComm_ipSubnetMask, &dbComm_ipDefaultGateway, TRUE);
//		    	DM9000_Reset();
		}
	   	tcpclient_connect_start();
	}
	
	if (dbComm_ipIsDHCP && (uiTimeGetTickCount() - dwDhcpRealTime >= (dbComm_DHCPLeaseTime * 1000)/2))   //zwh 2010.10.15
	{
		 StartDhchclient();
	}

//xprintf("the dblicense.bytcpipmode==%d\r\n",dbLicense.byTcpipMode);
//xprintf("TCPIP_CLIENT==%d\r\n",TCPIP_CLIENT);
//xprintf("TCPIP_SERVER==%d\r\n",TCPIP_SERVER);

//xprintf("(uiTimeGetTickCount() - dwRealTime)==%d\r\n",(uiTimeGetTickCount() - dwRealTime));
//xprintf("(nRealSpaceTime * 1000)==%d\r\n",(nRealSpaceTime * 1000));
//xprintf("(uiTimeGetTickCount() - dwRealTime) - (nRealSpaceTime * 1000)==%d\r\n",(uiTimeGetTickCount() - dwRealTime) - (nRealSpaceTime * 1000));

	if ((dbLicense.byTcpipMode == TCPIP_CLIENT) && ((uiTimeGetTickCount() - dwRealTime) >= (nRealSpaceTime * 1000) ))   
	{
		if (bSendAckTimeout==0)			
		   dwSendAckRealTime= uiTimeGetTickCount();
		bSendAckTimeout=1;
		
		//定时发送连接信号
		if(__tcpclient_connect_status == 1)
		{		
			make_connect();
		}
		else
		{
			tcpclient_connect_start();
		}
		xprintf("DbGLogCount()==%d\r\n",DbGLogCount());
		xprintf("DbGLogCountALL()==%d\r\n",DbGLogCountAll());
		xprintf("dbSetupTotal.setNoMenu.nReadALogPos==%d\r\n",dbSetupTotal.setNoMenu.nReadALogPos);
		if ((uiTimeGetTickCount() - dwTimeSynTime) >=nRealSpaceTime * 60000)   
		{	
			xprintf("(uiTimeGetTickCount() - dwTimeSynTime) >=nRealSpaceTime * 60000)\r\n");
			dwTimeSynTime=uiTimeGetTickCount();
		}
		//离线后保存信息，等在线在上传
		else if (DbGLogCount() != 0 )
		{   

			ALOG_INFO gLog;  
			DbGLogGet(&gLog, DbGLogGetReadPos(), 1);
			if(http_WEB_CONNECT == TRUE && tcpclient_connect_isok()==1)
			{				
				web2_send_glog(&gLog);//发送成功后在把数据加入
			}
	/*		ALOG_INFO gLog; 
			int lost_count = DbGLogCount();
			//DbGLogGet(&gLog, DbGLogGetReadPos(), 1);  
			//确认tcp/ip连上并且服务端有回应才发送
			if(http_WEB_CONNECT == TRUE && tcpclient_connect_isok()==1)
			{				
				CMessageBox *msgBox; 
      				msgBox	= new CMessageBox; 
				msgBox->MsgBoxProc_Message3(UISTR(UISTR_WAIT_FOR_COMMUNICATING));
				for(int i=0;i<lost_count;i++)
				{
					//ALOG_INFO gLog; 
					xprintf("#################%d\r\n",i);
					bzero(&gLog, sizeof(ALOG_INFO));
					DbGLogGet(&gLog, DbGLogGetReadPos(), 1);
					if(!web2_send_glog(&gLog))//发送成功后在把数据加入
					{
						xprintf("***************%d\r\n",i);
						//if(msgBox)
          						//delete msgBox;
						break;
					}
				}
				if(msgBox)
          				delete msgBox;
				//web2_send_glog(&gLog);//发送成功后在把数据加入
				//发完就得等待1000接受
				//web2_recv_data(1000);//add by l;oveywm 2013.02.21
				//xprintf("the glog is recv ok!!\r\n");
				nRealSpaceTime = 10;
			}	
	*/	}
		//离线时保存注册位置，在线时上传
		else if(http_WEB_CONNECT == TRUE && tcpclient_connect_isok()==1)
		{
			if(ComClientFpDataUpLoad())
			{
		    		 nRealSpaceTime = 10;
			}	
		}
		else 
		{
			if (dbSetupTotal.setSystem.nRealSpaceTime != 0)
				 nRealSpaceTime = dbSetupTotal.setSystem.nRealSpaceTime;
			else nRealSpaceTime = 10;
			//else nRealSpaceTime = 15;
		}
		
		dwRealTime = uiTimeGetTickCount();
	}   

	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
#define DEL_UINFO_ADD	1000
// (UINFO_* + DEL_UINFO_ADD) means "delete UINFO_* ".   Here "UINFO_*" is (UINFO_FP_1 ~ UINFO_CARD)
enum
{
	UINFO_DELETE = -1,
	UINFO_CHANGE_ID = 0,
	UINFO_FP_1 = 1,
	UINFO_FP_10 = 10,
	UINFO_PWD ,
	UINFO_CARD,
	UINFO_USE_GTZ,
	UINFO_USE_GVM,
	UINFO_PRIVILEGE,
	UINFO_ENABLE,
	UINFO_ACCESS_TIME,
	UINFO_PERSON_VM,
	UINFO_NAME,
	UINFO_DEPARTMENT,
	UINFO_DURESS_FP_1 = 21,
	UINFO_DURESS_FP_10 = 30,
	UINFO_DEL_FP_1 = UINFO_FP_1 + DEL_UINFO_ADD,
	UINFO_DEL_FP_10 = UINFO_FP_10 + DEL_UINFO_ADD,
	UINFO_DEL_PWD ,
	UINFO_DEL_CARD,
};

#define USER_PWD_LEN		6

#define MIN_ID	1
#define MAX_ID	999999999	//99999

enum
{
	LOG_TYPE_SUPER = 0,
	LOG_TYPE_GENERAL,
};

enum
{
	DS_MAX_ENROLL = 1,
	DS_MAX_SLOG,
	DS_MAX_GLOG,
	DS_FLASH_SIZE,
	DS_USER_COUNT,
	DS_MGR_COUNT,
	DS_SMGR_COUNT,
	DS_FP_COUNT,
	DS_PWD_COUNT,
	DS_CARD_COUNT,
	DS_FLASH_FREESPACE,
	DS_RELEASE_DATE,
	DS_SERIAL_NO,
	DS_MANUFACTURER,
	DS_PRODUCT_NAME,
	DS_PRODUCT_CODE,
	DS_ENGINE_VERSION,
	DS_FW_VERSION,
	DS_DOORSENSOR,
	DS_NEW_GLOG,   
	DS_NEW_SLOG,    
};

enum
{
	DI_DATEFORMAT = 1,
	DI_TIME,
	DI_LANGUAGE_KIND,
	DI_VOICE_OUT,
	DI_VOLUME,
	DI_KEY_TONES,
	DI_MAX_MGR,
	DI_CAMERA_SAVE,
	DI_CAMERARATE_FP,
	DI_CAMERARATE_PWD,
	DI_CAMERARATE_CARD,
	DI_SHOW_PHOTO,
	DI_SHOW_FP,
	DI_DAYLIGHT_CHANGETIME,
	DI_DAYLIGHT_RESTORETIME,
	DI_DAYLIGHT_OFFSET,
	DI_F1_STATUS,
	DI_F2_STATUS,
	DI_F3_STATUS,
	DI_F4_STATUS,
	DI_AUTO_POWERON,
	DI_AUTO_POWEROFF,
	DI_AUTO_SLEEP,
	DI_IDLETIME_POWEROFF,
	DI_IDLETIME_SLEEP,
	DI_IDLETIME_SCREENSAVER,
	DI_USE_POWERKEY,
	DI_GLOG_TZ,
	DI_SERIAL_BAUDRATE,
	DI_MACHINE_ID,
	DI_USE_ETHERNET,
	DI_IP_ADDRESS,
	DI_SUBNET_MASK,
	DI_GATEWAY,
	DI_USE_RS232,
	DI_USE_RS485,
	DI_COMM_PWD,
	DI_USE_DHCP,
	DI_SLOG_WARN,
	DI_GLOG_WARN,
	DI_REVERIFY_INTERVAL,
	DI_UNLOCK_TIME,
	DI_OPENNING_TOUT,
	DI_DOORSENSOR_SET,
	DI_PWDVERIFY_ALARM,
	DI_USE_KEYALARM,
	DI_ALARM_DELAY,
	DI_IDENTFAIL_NUM,
	DI_USE_ANTIPASS,
	DI_ALARM_STATUS,
	DI_LOCK_OPERATE,
	DI_MAINOPENGROUP,
	DI_MULTI_IDENT,
	DI_ACCESSTIME_SET,
	DI_ACCESSTIME_GROUP,
	DI_MESSAGE,
	DI_BELL,
	DI_WIEGAND,
	DI_SUPERMGR_PWD,
	DI_MANAGERPC_IP,
	DI_BINDING_ID,
	DI_TIMEFORMAT,
	DI_IDENT_MODE,	//new added for AC100
	DI_CAMRA_SHOW,
	DI_DEFAULT_VM,
	DI_DEFAULT_GVM,
	DI_NETWORK_SPEED,
	DI_THEME_MODE,
	DI_WGN_SWITCH,
	DI_USB_SLAVEUSED,
	DI_PASS_TZ,
	DI_GROUP_TZ,
	DI_TIME_TZ,
	DI_END = DI_TIME_TZ
};

#define GEN_STR_LEN			32

enum
{
	PC_POWER_OFF = 0,
	PC_POWER_ON,
	PC_RESTART,
};

enum
{
	DF_TYPE_SCREENSAVER_IMG = 0,
	DF_TYPE_SCREENSAVER_MP3,
	DF_TYPE_SYSTEM_MP3,
	DF_TYPE_USER_VOICE,
	DF_TYPE_USER_PHOTO,
	DF_TYPE_PHOTO_LOG,
	DF_TYPE_PART_SET,
	DF_TYPE_ENROLL_DAT,
	DF_TYPE_SLOG_DAT,
	DF_TYPE_GLOG_DAT,
};

#define FNAME_LEN			20

#define MAX_DATA_FILE_LEN	(sizeof(allUserFlag))
#define PART_SETFILE		"part"
#define SCREENSAVER_MP3FILE	"screensaver"

const char *dfPath[]  = {
	ENROLLDATA_MOUNTPOINT "/screensaver/",          ".jpg", 
	ENROLLDATA_MOUNTPOINT "/screensaver/",          ".mp3", 
	ENROLLDATA_MOUNTPOINT "/mp3/",                  ".mp3", 
	SDCARD_MOUNTPOINT     "/user-voice/",  ".wav", 
	SDCARD_MOUNTPOINT     "/user-photo/",  ".jpg", 
	SDCARD_MOUNTPOINT     "/photo-log/",   ".jpg", 
	ENROLLDATA_MOUNTPOINT "/",                      ".txt",
	ENROLLDATA_MOUNTPOINT "/",                      ".dat",
	ENROLLDATA_MOUNTPOINT "/",                      ".dat",
	ENROLLDATA_MOUNTPOINT "/",                      ".dat",
};

#define WEBSERVER_PAYLOAD_SIZE	1024

const int dfMaxSize[] = {
	LCD_SIZE_X * LCD_SIZE_Y * (LCD_BPP >> 3),
	5 * 1024 * 1024,
	1 * 1024 * 1024,
	1 * 1024 * 1024,
	16* 1024,
	16* 1024,
	1 * 1024 * 1024,
	sizeof(T_ENROLLDB_HDR) + FLASH_UI_INDEX_SIZE + MAX_USER_COUNT * (sizeof(BYTE) + sizeof(USER_INFO) + sizeof(FPINFO)) + 2*WEBSERVER_PAYLOAD_SIZE, //Auto calc
	MAX_SLOG_COUNT * sizeof(MLOG_INFO) + WEBSERVER_PAYLOAD_SIZE,
	MAX_GLOG_COUNT * sizeof(ALOG_INFO) + WEBSERVER_PAYLOAD_SIZE,
};


#define DATA_MASK_ENROLL	1
#define DATA_MASK_SLOG		2
#define DATA_MASK_GLOG		4
#define DATA_MASK_ALL		(DATA_MASK_ENROLL | DATA_MASK_SLOG | DATA_MASK_GLOG)


//////////////////////////////////////////////////////////////////////////
void Com_DispCmd(int nCMD)
{
	switch( nCMD )
	{
	case CMD_INTERNAL_CHECK_LIVE:  
		printf("CMD_INTERNAL_CHECK_LIVE\r\n");
		break;
	case CMD_INTERNAL_CHECK_PWD:  
		printf("CMD_INTERNAL_CHECK_PWD\r\n");
		break;
//////////////////////////////////////////////////////////////////////////
	case CMD_GET_ALLID:  
		printf("CMD_GET_ALLID\r\n");
		break;
	case CMD_GET_ONEID:  
		printf("CMD_GET_ONEID\r\n");
		break;
	case CMD_GET_UINFO:  
		printf("CMD_GET_UINFO\r\n");
		break;
	case CMD_SET_UINFO:  
		printf("CMD_SET_UINFO\r\n");
		break;
	case CMD_GET_LOG_COUNT:  
		printf("CMD_GET_LOG_COUNT\r\n");
		break;
	case CMD_GET_SLOG:  
		printf("CMD_GET_SLOG\r\n");
		break;
	case CMD_GET_GLOG:  
		printf("CMD_GET_GLOG\r\n");
		break;
	case CMD_GET_DEVICE_STATUS:  
		printf("CMD_GET_DEVICE_STATUS\r\n");
		break;
	case CMD_GET_DEVICE_INFO:  
		printf("CMD_GET_DEVICE_INFO\r\n");
		break;
	case CMD_SET_DEVICE_INFO:  
		printf("CMD_SET_DEVICE_INFO\r\n");
		break;
	case CMD_GET_DATA_FILE:  
		printf("CMD_GET_DATA_FILE\r\n");
		break;
	case CMD_SET_DATA_FILE:  
		printf("CMD_SET_DATA_FILE\r\n");
		break;
	case CMD_SET_DATA_FILE_WS:  
		printf("CMD_SET_DATA_FILE_WS\r\n");
		break;
	case CMD_ENABLE_DEVICE:  
		printf("CMD_ENABLE_DEVICE\r\n");
		break;
	case CMD_POWER_CONTROL:  
		printf("CMD_POWER_CONTROL\r\n");
		break;
	case CMD_EMPTY_DATA:  
		printf("CMD_EMPTY_DATA\r\n");
		break;
	case CMD_FW_UPGRADE:  
		printf("CMD_FW_UPGRADE\r\n");
		break;
	case CMD_FW_UPGRADE_WS:  
		printf("CMD_FW_UPGRADE_WS\r\n");
		break;
	case CMD_GET_PHOTOLIST:
		printf("CMD_GET_PHOTOLIST\r\n");
		break;
//////////////////////////////////////////////////////////////////////////
	case CMD_DOWN_DOWNLOADER_WRITE:
		printf("CMD_SB_FIRMWARE_WRITE\r\n");
		break;
	case CMD_DOWN_RESTART:
		printf("CMD_SB_RESTART\r\n");
		break;
	case CMD_DOWN_INIT_GET:
		printf("CMD_SB_INIT_GET\r\n");
		break;
	case CMD_DOWN_INIT_SET:
		printf("CMD_SB_INIT_SET\r\n");
		break;
	case CMD_DOWN_KERNEL_WRITE:
		printf("CMD_SB_KERNEL_WRITE\r\n");
		break;
	case CMD_DOWN_ROOTFS_WRITE:
		printf("CMD_SB_ROOTFS_WRITE\r\n");
		break;
	case CMD_DOWN_ROMWRITE:
		printf("CMD_SB_ROMWRITE\r\n");
		break;
	case CMD_DOWN_FLASHINIT:
		printf("CMD_SB_FLASHINIT\r\n");
		break;
	case CMD_DOWN_BOOTSPLASH:
		printf("CMD_DOWN_BOOTSPLASH\r\n");
		break;
//////////////////////////////////////////////////////////////////////////
	case CMD_ANTIPASS_SEND:
		printf("CMD_ANTIPASS_SEND\r\n");
		break;
//////////////////////////////////////////////////////////////////////////
	default:
		printf("***** CMD_UNKNOWN: %d\r\n", nCMD);
		break;
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL ComDownDownloaderWrite()
{
// 	BOOL bRet = TRUE;
// 	BYTE* pFirmware = (BYTE*)malloc( DOWNLOADER_IMAGE_SIZE );
// 
// 	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
// 	bRet = comm_recv_data(&pFirmware[0], DOWNLOADER_IMAGE_SIZE);
// 	uiLcdProgressDlgExit(); g_bProgress = FALSE;
// 
// 	if(!bRet)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		free(pFirmware);
// 		return FALSE;
// 	}
// 	
// 	bRet = _Db_FWWriteToFlash(pFirmware, MAKE_SECTOR_SIZE(DOWNLOADER_IMAGE_SIZE));
// 
// 	comm_send_ack(bRet ? CMD_ACK : CMD_NAK, 0);
// 
// 	free(pFirmware);
	return TRUE;
}

BOOL ComDownRestart()
{
	uiLcdSetLabelText(g_StatusWindow, UISTR(UISTR_STATUS_RESTART), QColor(g_rgbForeColor)/*FOREGROUND_COLOR*/);
	POST_EVENTS();
	uiPowerReboot();
	return TRUE;
}

typedef struct  
{
#define NAND_FLASH_MAGIC	0x19860320
	DWORD	dwFlashMagic;
	DWORD	dwBuildNumber;
	DWORD   dwSystemCheck;             
	//
	int		nDownloaderSize;
	int		nKernelSize;
	int		nRootfsSize;
	int		nConsoleUse;
	//
	char	szReleaseDate[GEN_STR_LEN];
	char	strSN[GEN_STR_LEN];
	char	szManufacturer[GEN_STR_LEN];
	char	szProductName[GEN_STR_LEN];
	char	strProductCode[GEN_STR_LEN];
	char	szFPEngineVer[GEN_STR_LEN];
	char	szFWVer[GEN_STR_LEN];
	char	szHostByName[GEN_STR_LEN];		   
	
	int		nLockContorl;
	int		nWebServer;
	int		nAlarm;
	int		nSound;
	int		nUsePOE;
	int		nUseEthernet;
	int		nUseRS232_485;
	int		nUseUSB;
	int		nIDCard;
	int		nWiegand;
	int		nCamera;
	int     nTcpipMode;   
	int           nOnLineEnroll;
	
	int		nMaxEnrollCount;
	int		nCMOS;
	int		nLanguage;
	DWORD	dwSeconds;
	DWORD	dwMachineID;
	int		nBaudrate;
	BYTE	byMACaddr[8];
	DWORD	ipAddress;
	DWORD	ipSubnetMask;
	DWORD	ipDefaultGateway;
	DWORD	dwCommPassword;
} SETTING_INFO;

BOOL ComDownInitGet()
{
	SETTING_INFO init_settings;

	memset(&init_settings, 0, sizeof(init_settings));

	init_settings.dwFlashMagic		= g_params.dwFlashMagic;
	init_settings.dwBuildNumber		= dbLicense.dwBuildNumber;
	init_settings.dwSystemCheck     = dbLicense.dwSystemCheck;  
	
	init_settings.nDownloaderSize	= g_params.nDownloaderSize;
	init_settings.nKernelSize		= g_params.nKernelSize;
	init_settings.nRootfsSize		= g_params.nRootfsSize;
	init_settings.nConsoleUse		= g_params.nConsoleUse;
	
	memcpy(init_settings.szReleaseDate, dbLicense.szFirstDate, sizeof(dbLicense.szFirstDate));
	memcpy(init_settings.strSN, dbLicense.szSerialNumber, sizeof(dbLicense.szSerialNumber));
	memcpy(init_settings.szManufacturer, dbLicense.szTradeMark, sizeof(dbLicense.szTradeMark));
	memcpy(init_settings.szProductName, dbLicense.szProductName, sizeof(dbLicense.szProductName));
	memcpy(init_settings.strProductCode, dbLicense.szProductType, sizeof(dbLicense.szProductType));
	memcpy(init_settings.szFPEngineVer, dbLicense.szEngineVersion, sizeof(dbLicense.szEngineVersion));
    memcpy(init_settings.szFWVer, LNSC_FIRMWAREVERSION, sizeof(init_settings.szFWVer));  
	
	init_settings.nLockContorl		= dbLicense.bUseACFunction;
	init_settings.nWebServer		= dbLicense.bUseWebServer;
	init_settings.nAlarm			= dbLicense.bUseAlarmFunction;
 	init_settings.nSound			= dbLicense.bUseMP3;
 	init_settings.nUsePOE			= dbLicense.bUsePOE;
	init_settings.nUseEthernet		= dbLicense.bUseEthernet;
 	init_settings.nUseRS232_485		= dbLicense.bUseRS232;
	init_settings.nUseUSB			= dbLicense.bUseUSB;
 	init_settings.nIDCard			= dbLicense.bUseCard;
 	init_settings.nWiegand			= dbLicense.bUseWiegand;
	init_settings.nCamera			= dbLicense.bUseCamera;

	init_settings.nTcpipMode		= dbLicense.byTcpipMode;   
	init_settings.nOnLineEnroll           = dbLicense.bOnLineEnroll;
	
	init_settings.nMaxEnrollCount	= dbLicense.nMaxEnrollCount;
	init_settings.nCMOS				= dbLicense.nCMOS;
	init_settings.nLanguage			= dbSetupTotal.setSystem.nLanguage;
	init_settings.dwSeconds			= uiRtcGetSeconds();
	init_settings.dwMachineID		= dbSetupTotal.setSystem.nMachineID;

	init_settings.nBaudrate			= dbSetupTotal.setSystem.nBaudrate;
	memcpy(init_settings.byMACaddr, dbLicense.byMACaddr, 6);
	init_settings.ipAddress			= dbSetupTotal.setSystem.ipAddress;
	init_settings.ipSubnetMask		= dbSetupTotal.setSystem.ipSubnetMask;
	init_settings.ipDefaultGateway	= dbSetupTotal.setSystem.ipDefaultGateway;
	init_settings.dwCommPassword	= dbSetupTotal.setSystem.dwCommPassword;

	memcpy(init_settings.szHostByName, dbSetupTotal.setSystem.szHostByName, sizeof(init_settings.szHostByName));    

	return comm_send_data(&init_settings, sizeof(init_settings));
}

BOOL ComDownInitSet()
{
	SETTING_INFO init_settings;
	DWORD dwDataKeep;
	
	memset(&init_settings, 0, sizeof(init_settings));
	if (!comm_recv_data(&dwDataKeep, 4) || 
		!comm_recv_data(&init_settings, sizeof(init_settings)) || 
		!comm_send_ack(CMD_ACK, 0))
		return FALSE;

	if (dbLicense.nMaxEnrollCount != init_settings.nMaxEnrollCount) dwDataKeep = 0;

	if (!dwDataKeep)
		DbSetupTotal2Default();

// 	g_params.dwFlashMagic		= init_settings.dwFlashMagic;
// 	dbLicense.dwBuildNumber		= init_settings.dwBuildNumber;
	
// 	g_params.nDownloaderSize	= init_settings.nDownloaderSize;
// 	g_params.nKernelSize		= init_settings.nKernelSize;
	g_params.nRootfsSize		= init_settings.nRootfsSize;
	g_params.nConsoleUse		= init_settings.nConsoleUse;
	
	memcpy(dbLicense.szFirstDate, init_settings.szReleaseDate, sizeof(dbLicense.szFirstDate));
	memcpy(dbLicense.szSerialNumber, init_settings.strSN, sizeof(dbLicense.szSerialNumber));
	memcpy(dbLicense.szTradeMark, init_settings.szManufacturer, sizeof(dbLicense.szTradeMark));
	memcpy(dbLicense.szProductName, init_settings.szProductName, sizeof(dbLicense.szProductName));
	memcpy(dbLicense.szProductType, init_settings.strProductCode, sizeof(dbLicense.szProductType));
	memcpy(dbLicense.szEngineVersion, init_settings.szFPEngineVer, sizeof(dbLicense.szEngineVersion));
	
	dbLicense.bUseACFunction	= init_settings.nLockContorl;
	dbLicense.bUseWebServer		= init_settings.nWebServer;
	dbLicense.bUseAlarmFunction = init_settings.nAlarm;
	dbLicense.bUseMP3			= init_settings.nSound;
	dbLicense.bUsePOE			= init_settings.nUsePOE;
	dbLicense.bUseEthernet		= init_settings.nUseEthernet;
	dbLicense.bUseRS232			= init_settings.nUseRS232_485;
	dbLicense.bUseUSB			= init_settings.nUseUSB;
	dbLicense.bUseCard			= init_settings.nIDCard;
	dbLicense.bUseWiegand		= init_settings.nWiegand;
	dbLicense.bUseCamera		= init_settings.nCamera;
	
	dbLicense.dwSystemCheck     = init_settings.dwSystemCheck;  
    dbLicense.byTcpipMode       = init_settings.nTcpipMode;     
		dbLicense.bOnLineEnroll         = init_settings.nOnLineEnroll;

	dbLicense.nMaxEnrollCount				= init_settings.nMaxEnrollCount;
	dbLicense.nCMOS							= init_settings.nCMOS;
	dbSetupTotal.setSystem.nLanguage		= init_settings.nLanguage;
	uiRtcSetSeconds(init_settings.dwSeconds);
	dbSetupTotal.setSystem.nMachineID		= init_settings.dwMachineID;
	
	dbSetupTotal.setSystem.nBaudrate		= init_settings.nBaudrate;
	memcpy(dbLicense.byMACaddr, init_settings.byMACaddr, 6);
	dbSetupTotal.setSystem.ipAddress		= init_settings.ipAddress;
	dbSetupTotal.setSystem.ipSubnetMask		= init_settings.ipSubnetMask;
	dbSetupTotal.setSystem.ipDefaultGateway = init_settings.ipDefaultGateway;
	dbSetupTotal.setSystem.dwCommPassword	= init_settings.dwCommPassword;

	memcpy(dbSetupTotal.setSystem.szHostByName, init_settings.szHostByName, sizeof(dbSetupTotal.setSystem.szHostByName));  

	if (!dwDataKeep)
	{
		Db_DeleteAllEnrollData();
		Db_DeleteAllLogData();
		DELETE_FILE(FLASH_PART_FILENAME);
	}
	DbLicenseWrite();
	DbSetupTotalWrite();

	g_uiLicenseChanged = g_uiBuildMenu = TRUE;

	return TRUE;
}

BOOL ComDownKernelWrite()
{
// 	BOOL bRet = TRUE;
// 	DWORD dwSize;
// 	BYTE* pKernelImage;
// 
// 	if (!comm_recv_data(&dwSize, 4) || dwSize > KERNEL_IMAGE_SIZE)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		return FALSE;
// 	}
// 
// 	pKernelImage = (BYTE*)malloc(KERNEL_IMAGE_SIZE);
// 	if (!pKernelImage)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		return FALSE;
// 	}
// 
// 	comm_send_ack(CMD_ACK, 0);
// 
// 	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
// 	bRet = comm_recv_data(&pKernelImage[0], dwSize);
// 	uiLcdProgressDlgExit(); g_bProgress = FALSE;
// 	if(!bRet)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		free(pKernelImage);
// 		return FALSE;
// 	}
// 
// 	bRet = _Db_FWWriteToFlash(pKernelImage, MAKE_SECTOR_SIZE(KERNEL_IMAGE_SIZE));
// 
// 	comm_send_ack(bRet ? CMD_ACK : CMD_NAK, 0);
// 
// 	free(pKernelImage);
	return TRUE;
}

BOOL ComDownRootfsWrite()
{
// 	BOOL bRet = TRUE;
// 	DWORD dwSize;
// 	BYTE* pRootfslImage;
// 
// 	if (!comm_recv_data(&dwSize, 4) || dwSize > ROOTFS_IMAGE_SIZE)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		return FALSE;
// 	}
// 	
// 	pRootfslImage = (BYTE*)malloc(ROOTFS_IMAGE_SIZE);
// 	if (!pRootfslImage)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		return FALSE;
// 	}
// 
// 	comm_send_ack(CMD_ACK, 0);
// 	
// 	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
// 	bRet = comm_recv_data(&pRootfslImage[0], dwSize);
// 	uiLcdProgressDlgExit(); g_bProgress = FALSE;
// 	if(!bRet)
// 	{
// 		comm_send_ack(CMD_NAK, 0);
// 		free(pRootfslImage);
// 		return FALSE;
// 	}
// 	
// 	bRet = _Db_FWWriteToFlash(pRootfslImage, MAKE_SECTOR_SIZE(dwSize));
// 
// 	comm_send_ack(bRet ? CMD_ACK : CMD_NAK, 0);
// 	free(pRootfslImage);
// //	DbFpLoad();
	return TRUE;
}

#define ROMIMAGE_WEB_PADDING	1024
BOOL ComDownRomWrite(BOOL bWebserver)
{
	BOOL bRet = TRUE;
	DWORD dwSize;
	BYTE* pRomImage;

	if (!comm_recv_data(&dwSize, 4) || 
		(!bWebserver && (int)dwSize > ROM_IMAGE_SIZE) ||
		(bWebserver && (int)dwSize > (ROM_IMAGE_SIZE + ROMIMAGE_WEB_PADDING))
		)
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}

	Db_FreeAllData();

	pRomImage = (BYTE*)malloc(MAKE_SECTOR_SIZE(dwSize));
	if (!pRomImage)
	{
		bRet = FALSE;
		goto _lExit;
	}

	comm_send_ack(CMD_ACK, 0);

	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
	bRet = comm_recv_data(&pRomImage[0], dwSize);
	if (bRet && bWebserver)
	{
		long nSizePadding;
		bRet = comm_recv_data(&nSizePadding, sizeof(nSizePadding));
		dwSize -= nSizePadding;
	}
	uiLcdProgressDlgExit(); g_bProgress = FALSE;
	if(!bRet)
	{
		bRet = FALSE;
		goto _lExit;
	}

	bRet = _Db_FWWriteToFlash(pRomImage, dwSize);

_lExit:
	comm_send_ack(bRet ? CMD_ACK : CMD_NAK, 0);

	FREE(pRomImage);
	Db_LoadAllData(TRUE);

	return TRUE;
}

BOOL ComDownFlashInit()
{
	return FALSE;
}

BOOL ComDownBootsplash()
{
	BOOL bRet = TRUE;
	DWORD dwSize;
	BYTE* pSplashImage;

	if (!comm_recv_data(&dwSize, 4))
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}

	pSplashImage = (BYTE*)malloc(DWORD_ALIGN(dwSize));
	if (!pSplashImage)
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}

	comm_send_ack(CMD_ACK, 0);

	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
	bRet = comm_recv_data(&pSplashImage[0], DWORD_ALIGN(dwSize));
	uiLcdProgressDlgExit(); g_bProgress = FALSE;
	if(!bRet)
	{
		free(pSplashImage);
		return FALSE;
	}

	if (TRUE)
	{
		int mtd_fd = INVALID_HANDLE_VALUE;
		mtd_fd = open(PARTITION_DOWNLOADER, O_RDWR);
		if (mtd_fd != INVALID_HANDLE_VALUE)
		{
			pwrite(mtd_fd, pSplashImage, DWORD_ALIGN(dwSize), OFFSET_SPLASH);
			sync();
			FD_CLOSE(mtd_fd);
		}
	}

	comm_send_ack(CMD_ACK, 0);
	free(pSplashImage);
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int		nAllIDCount = 0;
void	*pTempBuffer = allUserFlag;	//size = 8 * MAX_ENROLL_COUNT

BOOL ComCheckPwd()
{
	DWORD	dwCommPwd;
	
	if (!comm_recv_data(&dwCommPwd, 4)) return FALSE;
	return comm_send_ack(dbSetupTotal.setSystem.dwCommPassword == dwCommPwd ? CMD_ACK : CMD_NAK, 0);
}

BOOL ComGetAllUserID() 
{
	nAllIDCount = Db_GetUserCount();

	GetAllUserID();
	if (!comm_send_ack(CMD_ACK, nAllIDCount)) return FALSE;
	if (nAllIDCount == 0) return TRUE;

	return comm_send_data(allUserFlag, sizeof(COM_USER_INFO) * nAllIDCount);
}

BOOL ComGetOneUserID() 
{
	long param[2];
	
	if (!comm_recv_data(param, 8)) return FALSE;
	if (param[1] == -1)
	{
		nAllIDCount = Db_GetUserCount();
		GetAllUserID();
		return comm_send_ack(CMD_ACK, nAllIDCount);
	}

	if (param[0] < 0 || param[0] >= nAllIDCount || param[1] < 0) return comm_send_ack(CMD_NAK, 0);
	if (param[0] + param[1] > nAllIDCount) param[1] = nAllIDCount - param[0];

	if (!comm_send_ack(CMD_ACK, param[1]))return FALSE;
	if (param[1] == 0) return TRUE;
	
	return comm_send_data(&allUserFlag[param[0]], sizeof(COM_USER_INFO) * param[1]);
}

BOOL ComGetUserInfo() 
{
	long	param[2];
	long	dwUserID, dwInfo;
	void	*pData;
	int		nSize;
	USER_INFO	*pUInfo;

	if (!comm_recv_data(param, 8)) return FALSE;
	dwUserID = param[0];
	dwInfo = param[1];
	
	if (dwUserID < MIN_ID || dwUserID > MAX_ID || 
		dwInfo < UINFO_FP_1 || (UINFO_DEPARTMENT < dwInfo && dwInfo < UINFO_DURESS_FP_1) || dwInfo > UINFO_DURESS_FP_10 ||
		!(pUInfo = (USER_INFO*)DbUserInfoGetPointer(dwUserID)))
	{
		nSize = 0;
		goto l_exit;
	}

	if (UINFO_FP_1 <= dwInfo && dwInfo <= UINFO_FP_10)
	{
		pData = DbUserInfoGetPointer(dwUserID, (BACKUP_FINGER0 + dwInfo - UINFO_FP_1));
		nSize = pData ? sizeof(FPINFO) : 0;
	}
	else if (dwInfo == UINFO_PWD)
	{
		pData = DbUserInfoGetPointer(dwUserID, BACKUP_PASSWORD);
		if (pData)
		{
			pData = PWD2STRING(*(DWORD*)pData);
			nSize = USER_PWD_LEN;
		}
		else
			nSize = 0;
	}
	else if (dwInfo == UINFO_NAME)
	{
		pData = pUInfo->NAME;
		nSize = USERNAME_LENGTH * 2;
	}
	else
	{
		nSize = 4;
		switch (dwInfo)
		{
		case UINFO_CARD:
			pData = DbUserInfoGetPointer(dwUserID, BACKUP_CARD);
			(pData ? (dwInfo = *(DWORD*)pData) : nSize = 0);
			break;
		case UINFO_USE_GTZ:
			dwInfo = DbUserInfoFlagGTZStatusGet(pUInfo);
			break;
		case UINFO_USE_GVM:
			dwInfo = DbUserInfoFlagGVMStatusGet(pUInfo);
			break;
		case UINFO_PRIVILEGE:
			dwInfo = DbUserInfoFlagManagerGet(pUInfo);
			break;
		case UINFO_ENABLE:
			dwInfo = DbUserInfoFlagDisableStatusGet(pUInfo);
			break;
		case UINFO_ACCESS_TIME:
			{
				int nTZ1, nTZ2, nTZ3;
				DbUserInfoGetTimezone(pUInfo, &nTZ1, &nTZ2, &nTZ3);

				((BYTE*)&dwInfo)[0] = pUInfo->TIMEGROUP;
				((BYTE*)&dwInfo)[1] = nTZ1;
				((BYTE*)&dwInfo)[2] = nTZ2;
				((BYTE*)&dwInfo)[3] = nTZ3;
			}
			break;
		case UINFO_PERSON_VM:
		//	dwInfo = pUInfo->VERIFYMODE;  //sb 091125
            dwInfo = VERIFYMODE2INDEX(pUInfo->VERIFYMODE);  //sb 091125
			break;
		case UINFO_DEPARTMENT:
			dwInfo = pUInfo->PART;
			break;
		default:
			if (UINFO_DURESS_FP_1 <= dwInfo && dwInfo <= UINFO_DURESS_FP_10)
			{
				int nbk = (BACKUP_FINGER0 + dwInfo - UINFO_DURESS_FP_1);
				dwInfo = DbUserInfoGetPointer(dwUserID, nbk) ? DbUserInfoFlagDuressStatusGet(pUInfo, nbk) : 0;
			}
			else
				nSize = 0;
			break;
		}
	}

l_exit:
	if (nSize > 0)
	{
		BOOL nRet = comm_send_ack(CMD_ACK, dwInfo);
		if (nRet && nSize > 4)
		{
			nRet = comm_send_data(pData, nSize);
		}
		return nRet;
	}
	else 
	{
		return comm_send_ack(CMD_NAK, 0);
	}
}

//////////////////////////////////////////////////////////////////////////
#define	E_SETINFO_DUP	3
#define	MAX_MGR_COUNT		10
#define TIME_FORMAT_COUNT	2
#define DATE_FORMAT_COUNT	10
#define IDENT_MODE_COUNT	7
#define BELL_KIND_COUNT		5

typedef struct {
	DWORD	byOpt	: 8;			// Option
	DWORD	SHour	: 6;			// start of the access enabled period
	DWORD	SMin	: 6;			// 
	DWORD	EHour	: 6;			// end of the access enabled period
	DWORD	EMin	: 6;			// 
} ATOMIC_TZONE;

// structure for access time set of a week
typedef struct {
	ATOMIC_TZONE
		dayAccessTime[7];
} ACCESS_TIME_SET;

#pragma pack(1)
typedef struct {
	BYTE	byBellKind;				// bell kind
	BYTE	byHour;					// time to sound
	BYTE	byMin;
	BYTE	bySec;
	WORD	wLength;
} BELL_INFO;

#pragma pack()

//////////////////////////////////////////////////////////////////////////


BOOL ComSetUserInfo() 
{
	long dwUserID, dwInfo, dwData;
	long param[2];
	void	*pData = pTempBuffer;
	int		nSize, nUIPos = 0;
	USER_INFO	*pUInfo = NULL;
	WORD	resp;

	if (!comm_recv_data(param, 8)) return FALSE;
	dwUserID = param[0];
	dwInfo = param[1];
	param[0] = 0;
	
	if (dwUserID < MIN_ID || dwUserID > MAX_ID || 
		dwInfo < UINFO_DELETE || (UINFO_DEPARTMENT < dwInfo && dwInfo < UINFO_DURESS_FP_1) || 
		(UINFO_DURESS_FP_10 < dwInfo && dwInfo < UINFO_DEL_FP_1) || UINFO_DEL_CARD < dwInfo)
	{
		resp = CMD_NAK;
		goto l_exit;
	}

	if ((nUIPos = DbUserInfoGetPosition(dwUserID)) == dbLicense.nMaxEnrollCount)
	{
		if (dwInfo < UINFO_FP_1 || UINFO_CARD < dwInfo)
		{
			resp = CMD_NAK;
			goto l_exit;
		}
	}
	else
	{
		pUInfo = &gpUserInfoEnrollData[nUIPos];
	}

	if (dwInfo == UINFO_DELETE)
	{
		DbUserInfoDelete(dwUserID, 0xFFFFFFFF);
		resp = DbUserInfoGetPointer(dwUserID) ? CMD_NAK : CMD_ACK;
		goto l_exit;
	}
	else if (dwInfo >= UINFO_DEL_FP_1)
	{
		resp = DbUserInfoDelete(dwUserID, 0x01 << (BACKUP_FINGER0 + dwInfo - UINFO_DEL_FP_1)) ? CMD_ACK : CMD_NAK;
		goto l_exit;
	}
	else if (UINFO_FP_1 <= dwInfo && dwInfo <= UINFO_FP_10)
	{
		nSize = sizeof(FPINFO);
	}
	else if (dwInfo == UINFO_PWD)
	{
		nSize = USER_PWD_LEN;
	}
	else if (dwInfo == UINFO_NAME)
	{
		nSize = USERNAME_LENGTH * 2;
	}
	else
	{
		nSize = 4;
	}

	if (!comm_send_ack(CMD_ACK, 0)) return FALSE;

	if (comm_recv_data(pData, nSize))
	{
		if (UINFO_FP_1 <= dwInfo && dwInfo <= UINFO_CARD)
		{
			if (dwInfo == UINFO_PWD)
			{
				((char*)pData)[USER_PWD_LEN] = 0;
				if (!((*(DWORD*)pData) = STRING2PWD((char*)pData)))
				{
					resp = CMD_NAK;
					goto l_exit;
				}
			}
			memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
			gUserInfoTemp.ID = dwUserID;
			gUserInfoTemp.FLAG.members.byMgr = PRIV_USER;
			resp = DbUserInfoEnroll(&gUserInfoTemp, dwInfo - UINFO_FP_1, pData, TRUE, FALSE) ? CMD_ACK : CMD_NAK;
		}
		else 
		{
			if (!pUInfo)
			{
				resp = CMD_NAK;
				goto l_exit;
			}
			dwData = *(DWORD*)pData;
			if (
				(dwInfo == UINFO_CHANGE_ID &&
				(dwData < MIN_ID || dwData > MAX_ID))
				||
				(((UINFO_DURESS_FP_1 <= dwInfo && dwInfo <= UINFO_DURESS_FP_10) ||
				dwInfo == UINFO_ENABLE || dwInfo == UINFO_USE_GTZ || dwInfo == UINFO_USE_GVM) &&
				dwData != 0 && dwData != 1)
				||
				(dwInfo == UINFO_PRIVILEGE &&
				dwData != PRIV_USER && dwData != PRIV_MGR && dwData != PRIV_SMGR)
				||
				(dwInfo == UINFO_PERSON_VM &&
				(dwData < 1 || dwData >= IDENT_MODE_COUNT))
				||
				(dwInfo == UINFO_DEPARTMENT &&
				(dwData < 0 || dwData > 255))
				)
			{
				resp = CMD_NAK;
				goto l_exit;
			}
			resp = CMD_ACK;
			switch (dwInfo)
			{
			case UINFO_CHANGE_ID:
				if (DbUserInfoGetPosition(dwData) == dbLicense.nMaxEnrollCount)
				{
					resp = CMD_NAK;
					param[0] = E_SETINFO_DUP;
				}
				else
				{
					pUInfo->ID = dwData;
				}
				break;
			case UINFO_USE_GTZ:
				DbUserInfoFlagGTZStatusSet(pUInfo, dwData);
				break;
			case UINFO_USE_GVM:
				DbUserInfoFlagGVMStatusSet(pUInfo, dwData);
				break;
			case UINFO_PRIVILEGE:
				resp = DbUserInfoFlagManagerSet(pUInfo, dwData) ? CMD_ACK : CMD_NAK;
				break;
			case UINFO_ENABLE:
				DbUserInfoFlagDisableStatusSet(pUInfo, dwData);
				break;
			case UINFO_ACCESS_TIME:
				{
					BYTE *tgz = (BYTE*)pData;
					if (tgz[0] < 1 || tgz[0] > ACCESS_USER_GROUP_COUNT ||
						/*tgz[1] < 0 ||*/ tgz[1] > ACCESS_TIME_SET_COUNT || /*disable warning*/
						/*tgz[2] < 0 ||*/ tgz[2] > ACCESS_TIME_SET_COUNT ||
						/*tgz[3] < 0 ||*/ tgz[3] > ACCESS_TIME_SET_COUNT)
					{
						resp = CMD_NAK;
					}
					else 
					{
						pUInfo->TIMEGROUP = tgz[0];
						pUInfo->UserTZ[0] = tgz[1];
						pUInfo->UserTZ[1] = tgz[2];
						pUInfo->UserTZ[2] = tgz[3];
					}
				}
				break;
			case UINFO_PERSON_VM:
			//	pUInfo->VERIFYMODE = dwData;  //sb091125
				////sb 091125
				if (INDEX2VERIFYMODE(dwData) != -1)
					pUInfo->VERIFYMODE = INDEX2VERIFYMODE(dwData);
				////sb 091125
				break;
			case UINFO_NAME:
				memcpy(pUInfo->NAME, pData, nSize);
				break;
			case UINFO_DEPARTMENT:
				pUInfo->PART = (BYTE)dwData;
				break;
			default:
				if (UINFO_DURESS_FP_1 <= dwInfo && dwInfo <= UINFO_DURESS_FP_10)
				{
					int nbk = (BACKUP_FINGER0 + dwInfo - UINFO_DURESS_FP_1);
					if (DbUserInfoGetPointer(dwUserID, nbk))
					{
						DbUserInfoFlagDuressStatusSet(pUInfo, nbk, (*(DWORD*)pData));
					}
					else
					{
						resp = CMD_NAK;
					}
				}
				else
					resp = CMD_NAK;
				break;
			}
			if (resp == CMD_ACK)
			{
				resp = DbUserInfoSaveOne(nUIPos) ? CMD_ACK : CMD_NAK;
			}
		}
	}
	else
	{
		return FALSE;
	}
	
l_exit:
	return comm_send_ack(resp, param[0]) && (resp == CMD_ACK);
}

BOOL ComGetLogCount() 
{
	long param[2];
	
	if (!comm_recv_data(param, 4)) return FALSE;

	if (param[0] == LOG_TYPE_SUPER)
	{
		param[0] = DbSLogCountAll();
		param[1] = DbSLogGetReadPos();
	}
	else
	{
		param[0] = DbGLogCountAll();
		param[1] = DbGLogGetReadPos();
	}

	return comm_send_data(param, 8);
}

BOOL ComGetSuperLog() 
{
	long nCount, param[3], nTotalCount;
	BOOL bRet = FALSE;
	MLOG_INFO* pLogs = NULL;
	
	if (!comm_recv_data(param, 12)) return FALSE;
	
	//param[0] = dwStartPos;
	//param[1] = dwCount;
	//param[2] = dwMarkReadPos;
	nTotalCount = DbSLogCountAll();
	if (param[0] < 0 || param[0] >= nTotalCount)
	{
		comm_send_ack(CMD_NAK, 0);
		goto l_exit;
	}
	nCount = (param[0] + param[1] > nTotalCount) ? (nTotalCount - param[0] ) : param[1];
	if (!(pLogs = (MLOG_INFO*)malloc(sizeof(MLOG_INFO) * (nCount + 1))))
	{
		comm_send_ack(CMD_NAK, 0);
		goto l_exit;
	}
	nCount = DbSLogGet(pLogs, param[0], nCount);
	if (!comm_send_ack(CMD_ACK, nCount)) goto l_exit;
	if (nCount > 0)
	{
		if (!comm_send_data(pLogs, nCount * sizeof(MLOG_INFO)) ||
			comm_recv_ack(0) != RES_ACK) 
			goto l_exit;
	}
	bRet = TRUE;
	if (param[2] == 1)
	{
		bRet = DbSLogSetReadPos((param[0] + nCount) % dbLicense.nSlogMaxCount);
	}
	comm_send_ack(CMD_ACK, 0);        
l_exit:
	if (pLogs) free(pLogs);
	return bRet;
}

BOOL ComGetGeneralLog() 
{
	long nCount, param[3], nTotalCount;
	BOOL bRet = FALSE;
	ALOG_INFO* pLogs = NULL;
	
	if (!comm_recv_data(param, 12)) return FALSE;
	
	//param[0] = dwStartPos;
	//param[1] = dwCount;
	//param[2] = dwMarkReadPos;
	nTotalCount = DbGLogCountAll();
	if (param[0] < 0 || param[0] >= nTotalCount)
	{
		comm_send_ack(CMD_NAK, 0);
		goto l_exit;
	}
	nCount = (param[0] + param[1] > nTotalCount) ? (nTotalCount - param[0] ) : param[1];
	if (!(pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (nCount + 1))))
	{
		comm_send_ack(CMD_NAK, 0);
		goto l_exit;
	}
	nCount = DbGLogGet(pLogs, param[0], nCount);
	if (!comm_send_ack(CMD_ACK, nCount)) goto l_exit;
	if (nCount > 0)
	{
		if (!comm_send_data(pLogs, nCount * sizeof(ALOG_INFO)) ||
			comm_recv_ack(0) != RES_ACK) 
			goto l_exit;
	}
	bRet = TRUE;
	if (param[2] == 1)
	{
		bRet = DbGLogSetReadPos((param[0] + nCount) % dbLicense.nGlogMaxCount);
	}
	comm_send_ack(CMD_ACK, 0);        
l_exit:
	if (pLogs) free(pLogs);
	return bRet;
}


BOOL ComGetDeviceStatus() 
{
	DWORD dwStatus;
	int	nSize;
	CHAR sztemp[100];
	void *pData = sztemp;
	
	if (!comm_recv_data(&dwStatus, 4)) return FALSE;
    if (dwStatus < DS_MAX_ENROLL || dwStatus > DS_NEW_SLOG)  
	{
		return comm_send_ack(CMD_NAK, 0);
	}
	nSize = 4;
	switch (dwStatus)
	{
	case DS_MAX_ENROLL:
		dwStatus = dbLicense.nMaxEnrollCount;
		break;
	case DS_MAX_SLOG:
		dwStatus = dbLicense.nSlogMaxCount - 1;
		break;
	case DS_MAX_GLOG:
		dwStatus = dbLicense.nGlogMaxCount - 1;
		break;
	case DS_FLASH_SIZE:
		dwStatus = total_flash_size();
		break;
	case DS_USER_COUNT:
		dwStatus = Db_GetUserCount();
		break;
	case DS_MGR_COUNT:
		dwStatus = Db_GetManagerCount(PRIV_MGR);
		break;
	case DS_SMGR_COUNT:
		dwStatus = Db_GetManagerCount(PRIV_SMGR);
		break;
	case DS_FP_COUNT:
		dwStatus = DbUserInfoGetCount(BACKUP_FINGER);
		break;
	case DS_PWD_COUNT:
		dwStatus = DbUserInfoGetCount(BACKUP_PASSWORD);
		break;
	case DS_CARD_COUNT:
		dwStatus = DbUserInfoGetCount(BACKUP_CARD);
		break;
	case DS_FLASH_FREESPACE:
		dwStatus = free_space_flash();
		break;
	case DS_RELEASE_DATE:
		pData = dbLicense.szFirstDate;
		nSize = GEN_STR_LEN;
		break;
	case DS_SERIAL_NO:
		pData = dbLicense.szSerialNumber;
		nSize = GEN_STR_LEN;
		break;
	case DS_MANUFACTURER:
		pData = dbLicense.szTradeMark;
		nSize = GEN_STR_LEN;
		break;
	case DS_PRODUCT_NAME:
		pData = dbLicense.szProductName;
		nSize = GEN_STR_LEN;
		break;
	case DS_PRODUCT_CODE:
		pData = dbLicense.szProductType;
		nSize = GEN_STR_LEN;
		break;
	case DS_ENGINE_VERSION:
		pData = dbLicense.szEngineVersion;
		nSize = GEN_STR_LEN;
		break;
	case DS_FW_VERSION:
		pData = dbLicense.szFirmwareVersion;  
		nSize = GEN_STR_LEN;
		break;
	case DS_DOORSENSOR:
		dwStatus = (DWORD)uiDoorSensorStatus();
		break;
	case DS_NEW_GLOG:
        dwStatus = DbGLogCountAll() - DbGLogGetReadPos();
		break;
	case DS_NEW_SLOG:
        dwStatus = DbSLogCountAll() - DbSLogGetReadPos(); 
		break;
	default :
		return comm_send_ack(CMD_NAK, 0);
		break;
	}
	if (!comm_send_ack(CMD_ACK, dwStatus)) return FALSE;
	return (nSize > 4 ? comm_send_data(pData, nSize) : TRUE);
}

BOOL ComGetDeviceInfo() 
{

	DWORD dwInfo, dwData = 0;
	long nLen, i;
	BOOL bRet = TRUE;
	
	if (!comm_recv_data(&dwInfo, 4)) return FALSE;
	if (dwInfo < DI_DATEFORMAT || dwInfo > DI_END)
	{
		return comm_send_ack(CMD_NAK, 0);
	}

	nLen = 0;
	switch (dwInfo)
	{
	case DI_DATEFORMAT:
		dwData = dbSetupTotal.setSystem.nDateFormat + 1;
		break;
	case DI_TIME:
		dwData = uiRtcGetSeconds();
		break;
	case DI_LANGUAGE_KIND:
		dwData = dbSetupTotal.setSystem.nLanguage;
		break;
	case DI_VOICE_OUT:
		dwData = dbSetupTotal.setSystem.bVoiceOut;
		break;
	case DI_VOLUME:
		dwData = dbSetupTotal.setSystem.nVolume;
		break;
	case DI_KEY_TONES:
		dwData = dbSetupTotal.setSystem.bKeyTones;
		break;
	case DI_MAX_MGR:
		dwData = dbSetupTotal.setSystem.nManagersNumber;
		break;
	case DI_CAMERA_SAVE:
		dwData = dbSetupTotal.setSystem.bCameraSave;
		break;
	case DI_CAMERARATE_FP:
		dwData = dbSetupTotal.setSystem.byCameraRateForFP;
		break;
	case DI_CAMERARATE_PWD:
		dwData = dbSetupTotal.setSystem.byCameraRateForPWD;
		break;
	case DI_CAMERARATE_CARD:
		dwData = dbSetupTotal.setSystem.byCameraRateForCard;
		break;
	case DI_SHOW_PHOTO:
		dwData = dbSetupTotal.setSystem.bPhotoShow;
		break;
	case DI_SHOW_FP:
		dwData = dbSetupTotal.setSystem.bFPShow;
		break;
	case DI_DAYLIGHT_CHANGETIME:
		dwData = dbSetupTotal.setSystem.dwDaylightChangeTime;
		break;
	case DI_DAYLIGHT_RESTORETIME:
		dwData = dbSetupTotal.setSystem.dwDaylightRestoreTime;
		break;
	case DI_DAYLIGHT_OFFSET:
		dwData = dbSetupTotal.setSystem.nDaylightOffset;
		break;
	case DI_F1_STATUS:
		dwData = dbSetupTotal.setSystem.byF1Status;
		break;
	case DI_F2_STATUS:
		dwData = dbSetupTotal.setSystem.byF2Status;
		break;
	case DI_F3_STATUS:
		dwData = dbSetupTotal.setSystem.byF3Status;
		break;
	case DI_F4_STATUS:
		dwData = dbSetupTotal.setSystem.byF4Status;
		break;
	case DI_AUTO_POWERON:
		dwData = dbSetupTotal.setSystem.dwAutoPoweronTime;
		break;
	case DI_AUTO_POWEROFF:
		dwData = dbSetupTotal.setSystem.dwAutoPoweroffTime;
		break;
	case DI_AUTO_SLEEP:
		dwData = dbSetupTotal.setSystem.dwAutoSleepTime;
		break;
	case DI_IDLETIME_POWEROFF:
		dwData = dbSetupTotal.setSystem.nIdletimeForPoweroff;
		break;
	case DI_IDLETIME_SLEEP:
		dwData = dbSetupTotal.setSystem.nIdletimeForSleep;
		break;
	case DI_IDLETIME_SCREENSAVER:
		dwData = dbSetupTotal.setSystem.nIdletimeForLcdswitch;
		break;
	case DI_USE_POWERKEY:
		dwData = dbSetupTotal.setSystem.bPowerkeyLock;
		break;
	case DI_SERIAL_BAUDRATE:
		dwData = dbSetupTotal.setSystem.nBaudrate;
		break;
	case DI_MACHINE_ID:
		dwData = dbSetupTotal.setSystem.nMachineID;
		break;
	case DI_USE_ETHERNET:
		dwData = dbSetupTotal.setSystem.bEthernetUse;
		break;
	case DI_IP_ADDRESS:
		dwData = dbSetupTotal.setSystem.ipAddress;
		break;
	case DI_SUBNET_MASK:
		dwData = dbSetupTotal.setSystem.ipSubnetMask;
		break;
	case DI_GATEWAY:
		dwData = dbSetupTotal.setSystem.ipDefaultGateway;
		break;
	case DI_USE_RS232:
		dwData = dbSetupTotal.setSystem.bRS232Use;
		break;
	case DI_USE_RS485:
		dwData = dbSetupTotal.setSystem.bRS485Use;
		break;
	case DI_COMM_PWD:
		dwData = dbSetupTotal.setSystem.dwCommPassword;
		break;
	case DI_USE_DHCP:
		dwData = dbSetupTotal.setSystem.bDHCPUse;
		break;
	case DI_SLOG_WARN:
		dwData = dbSetupTotal.setSystem.nMLogWarning;
		break;
	case DI_GLOG_WARN:
		dwData = dbSetupTotal.setSystem.nGLogWarning;
		break;
	case DI_REVERIFY_INTERVAL:
		dwData = dbSetupTotal.setSystem.nReverifyTime;
		break;
	case DI_UNLOCK_TIME:
		dwData = dbSetupTotal.setSystem.nLockTime;
		break;
	case DI_OPENNING_TOUT:
		dwData = dbSetupTotal.setSystem.nDoorOpenTime;
		break;
	case DI_DOORSENSOR_SET:
		dwData = dbSetupTotal.setSystem.nDoorSensorStatus;
		break;
	case DI_PWDVERIFY_ALARM:
		dwData = dbSetupTotal.setSystem.bPwdAlarmUse;
		break;
	case DI_USE_KEYALARM:
		dwData = dbSetupTotal.setSystem.bSOSKeyUse;
		break;
	case DI_ALARM_DELAY:
		dwData = dbSetupTotal.setSystem.nAlarmDelay;
		break;
	case DI_IDENTFAIL_NUM:
		dwData = dbSetupTotal.setSystem.nIllegalVerifyWarning;
		break;
	case DI_USE_ANTIPASS:
		dwData = dbSetupTotal.setSystem.byAntipassStatus;
		break;
	case DI_ALARM_STATUS:
		dwData = g_uiProcStatus.bAlarming;
		break;
	case DI_LOCK_OPERATE:
		dwData = dbSetupTotal.setNoMenu.byDoorStatus;
		break;
	case DI_MAINOPENGROUP:
		dwData = dbSetupTotal.setSystem.nLockGroupMain;
		break;
	case DI_MANAGERPC_IP:
		dwData = dbSetupTotal.setSystem.ipPCBackground;
		break;
	case DI_BINDING_ID:
		dwData = dbSetupTotal.setSystem.dwBindingID;
		break;
	case DI_TIMEFORMAT:
		dwData = dbSetupTotal.setSystem.nTimeFormat + 1;
		break;
	case DI_CAMRA_SHOW://Camera show
		dwData = dbSetupTotal.setSystem.bCameraShow;
		break;
	case DI_DEFAULT_VM://Default Verfy Mode
		dwData = VERIFYMODE2INDEX(dbSetupTotal.setSystem.nVerifyMode);
		break;
// 	case DI_DEFAULT_GVM://Group Verify Mode
// 		dwData = VERIFYMODE2INDEX(dbSetupTotal.setSystem.byDefaultGVM);
// 		break;
	case DI_NETWORK_SPEED:
		dwData = dbSetupTotal.setSystem.byNetworkSpeed;
		break;
	case DI_THEME_MODE:
		dwData = dbSetupTotal.setSystem.byTheme;
		break;
	case DI_WGN_SWITCH:
		dwData = dbSetupTotal.setSystem.byWiegandFormat;
		break;
	case DI_USB_SLAVEUSED:
		dwData = dbSetupTotal.setSystem.bUSBSlaveUse;
		break;
	//////////////////////////////////////////////////////////////////////////
	case DI_GLOG_TZ:
		{
			ATOMIC_TZONE* pLogTZ = (ATOMIC_TZONE*)pTempBuffer;
			nLen = sizeof(ATOMIC_TZONE) * LOG_TZONE_COUNT;
			for (i = 0; i < LOG_TZONE_COUNT; i++)
			{
				pLogTZ[i].byOpt = (BYTE)dbSetupTotal.setTimezone.tzTr[i].STATUS;
				pLogTZ[i].SHour = dbSetupTotal.setTimezone.tzTr[i].RANGE.bStartHour;
				pLogTZ[i].SMin = dbSetupTotal.setTimezone.tzTr[i].RANGE.bStartMinute;
				pLogTZ[i].EHour = dbSetupTotal.setTimezone.tzTr[i].RANGE.bEndHour;
				pLogTZ[i].EMin = dbSetupTotal.setTimezone.tzTr[i].RANGE.bEndMinute;
			}		
		}
		break;
	case DI_MULTI_IDENT:
		{
			BYTE *pMultiIG = (BYTE*)pTempBuffer;
			DWORD tVal;
			nLen = 5 * MULTI_IDENT_SET_COUNT;
			for (i = 0; i < MULTI_IDENT_SET_COUNT; i++)
			{
				tVal = LOCKGROUP2NUMBER(dbSetupTotal.setTimezone.tzLockGroup[i]);
				pMultiIG[i * 5 + 0] = tVal % 10; tVal /= 10;
				pMultiIG[i * 5 + 1] = tVal % 10; tVal /= 10;
				pMultiIG[i * 5 + 2] = tVal % 10; tVal /= 10;
				pMultiIG[i * 5 + 3] = tVal % 10; tVal /= 10;
				pMultiIG[i * 5 + 4] = tVal % 10;
			}
		}
		break;
	case DI_ACCESSTIME_SET:
		{
			ACCESS_TIME_SET *pAcessTS = (ACCESS_TIME_SET*)pTempBuffer;
			nLen = sizeof(ACCESS_TIME_SET) * ACCESS_TIME_SET_COUNT;
			for (i = 0; i < ACCESS_TIME_SET_COUNT; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					pAcessTS[i].dayAccessTime[j].SHour = dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bStartHour;
					pAcessTS[i].dayAccessTime[j].SMin = dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bStartMinute;
					pAcessTS[i].dayAccessTime[j].EHour = dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bEndHour;
					pAcessTS[i].dayAccessTime[j].EMin = dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bEndMinute;
				}
			}
		}
		break;
	case DI_ACCESSTIME_GROUP:
		{
			BYTE *pAccessG = (BYTE*)pTempBuffer;
			nLen = 4 * ACCESS_USER_GROUP_COUNT;
			for (i = 0; i < ACCESS_USER_GROUP_COUNT; i++)
			{
				pAccessG[i * 4 + 0] = dbSetupTotal.setTimezone.tzGroup[i].bGroupA;
				pAccessG[i * 4 + 1] = dbSetupTotal.setTimezone.tzGroup[i].bGroupB;
				pAccessG[i * 4 + 2] = dbSetupTotal.setTimezone.tzGroup[i].bGroupC;
				pAccessG[i * 4 + 3] = dbSetupTotal.setTimezone.tzGrupVM[i];
			}
		}
		break;
	case DI_MESSAGE:
		{
			MSG_INFO *pMsgs = (MSG_INFO*)pTempBuffer;
			nLen = sizeof(MSG_INFO) * MSG_INFO_COUNT;
			memcpy(pMsgs, dbSetupTotal.setTimezone.tzMsg, nLen);
		}
		break;
	case DI_BELL:
		{
			BELL_INFO *pBells = (BELL_INFO*)pTempBuffer;
			nLen = sizeof(BELL_INFO) *BELL_INFO_COUNT;
			for (i = 0; i < BELL_INFO_COUNT; i++)
			{
				pBells[i].byBellKind = (BYTE)dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndHour;
				pBells[i].byHour = dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartHour;
				pBells[i].byMin = dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartMinute;
				pBells[i].bySec = 0;
				pBells[i].wLength = dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndMinute;
			}
		}
		break;
	case DI_WIEGAND:
		{
			WIEGAND_TYPE *pWiegand_type = (WIEGAND_TYPE*)pTempBuffer;
			nLen = sizeof(WIEGAND_TYPE);
			memcpy(pWiegand_type, &dbSetupTotal.setNoMenu.wiegand_type, nLen);
		}
		break;
	case DI_SUPERMGR_PWD:
		{
			nLen = USER_PWD_LEN;
			memcpy(pTempBuffer, PWD2STRING(dbSetupTotal.setSystem.dwSManagerPwd), nLen);
		}
		break;
	case DI_IDENT_MODE:
		bRet = FALSE;
		break;
	case DI_PASS_TZ://Pass Timezone
		{
			DB_TIMESECTION_A *pPassTime = (DB_TIMESECTION_A*)pTempBuffer;
			nLen = sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT;
			memcpy(pPassTime, &dbSetupTotal.setTimezone.tzHighTIME[0], nLen);
		}
		break;
	case DI_GROUP_TZ:
		{
			BYTE *pGroupTime = (BYTE*)pTempBuffer;
			nLen = TIMEGROUP_COUNT * TIMECOUNT_PER_TG;
			memcpy(pGroupTime, &dbSetupTotal.setTimezone.tzHighTG[0], nLen);
		}
		break;
	case DI_TIME_TZ:
		{
			BYTE *pTime_TZ = (BYTE*)pTempBuffer;
			nLen = ACCESS_TIME_SET_COUNT_HIGH * 7;
			memcpy(pTime_TZ, &dbSetupTotal.setTimezone.tzHighAccess[0], nLen);
		}
		break;
	default:
		bRet = FALSE;
		break;
	}

	if (!comm_send_ack(bRet ? CMD_ACK : CMD_NAK, dwData)) return FALSE;
	
	return (nLen ? comm_send_data(pTempBuffer, nLen) : TRUE);
}

BOOL ComSetDeviceInfo() 
{
	DWORD dwInfo, dwData = 0;
	DWORD param[2];
	long nLen, i, nRet;
	
	if (!comm_recv_data(param, 8)) return FALSE;
	dwInfo = param[0];
	dwData = param[1];
	if (dwInfo < DI_DATEFORMAT || dwInfo > DI_END)
	{
		return comm_send_ack(CMD_NAK, 0);
	}

	nLen = 0;
	nRet = TRUE;
	switch (dwInfo)
	{
	case DI_DATEFORMAT:
		nRet = (1 <= dwData && dwData <= DATE_FORMAT_COUNT);
		if (nRet) dbSetupTotal.setSystem.nDateFormat = dwData - 1;
		break;
	case DI_TIME:
		nRet = TRUE;
		if (nRet) uiRtcSetSeconds(dwData);
		break;
	case DI_LANGUAGE_KIND:
		nRet = (dwData < UILANG_CNT);
		if (nRet) dbSetupTotal.setSystem.nLanguage = dwData;
		break;
	case DI_VOICE_OUT:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bVoiceOut = dwData;
		break;
	case DI_VOLUME:
		nRet = (dwData <= 100);
		if (nRet) dbSetupTotal.setSystem.nVolume = dwData;
		break;
	case DI_KEY_TONES:
		nRet = (dwData <= 1UL);
		if (nRet) dbSetupTotal.setSystem.bKeyTones = dwData;
		break;
	case DI_MAX_MGR:
		nRet = (MAX(1, Db_GetManagerCountMax()) <= (int)dwData && dwData <= MAX_MGR_COUNT);
		if (nRet) dbSetupTotal.setSystem.nManagersNumber = dwData;
		break;
	case DI_CAMERA_SAVE:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bCameraSave = dwData;
		break;
	case DI_CAMERARATE_FP:
		nRet = (dwData <= 100);
		if (nRet) dbSetupTotal.setSystem.byCameraRateForFP = dwData;
		break;
	case DI_CAMERARATE_PWD:
		nRet = (dwData <= 100);
		if (nRet) dbSetupTotal.setSystem.byCameraRateForPWD = dwData;
		break;
	case DI_CAMERARATE_CARD:
		nRet = (dwData <= 100);
		if (nRet) dbSetupTotal.setSystem.byCameraRateForCard = dwData;
		break;
	case DI_SHOW_PHOTO:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bPhotoShow = dwData;
		if (dbSetupTotal.setSystem.bPhotoShow) //RSI090701
		{
			dbSetupTotal.setSystem.bCameraShow = FALSE;
			dbSetupTotal.setSystem.bFPShow = FALSE;
		}
		break;
	case DI_SHOW_FP:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bFPShow = dwData;
		if (dbSetupTotal.setSystem.bFPShow) //RSI090701
		{
			dbSetupTotal.setSystem.bPhotoShow = FALSE;
			dbSetupTotal.setSystem.bCameraShow = FALSE;
		}
		break;
	case DI_DAYLIGHT_CHANGETIME:
		{
			int nYear, nMonth, nDay, nHour, nMinute, nSecond;
			
			uiRtcSeconds2YMDHMS(dwData, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
			nRet = TRUE;
		}
		if (nRet) dbSetupTotal.setSystem.dwDaylightChangeTime = dwData;
		break;
	case DI_DAYLIGHT_RESTORETIME:
		{
			int nYear, nMonth, nDay, nHour, nMinute, nSecond;
			
			uiRtcSeconds2YMDHMS(dwData, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
			nRet = TRUE;
		}
		if (nRet) dbSetupTotal.setSystem.dwDaylightRestoreTime = dwData;
		break;
	case DI_DAYLIGHT_OFFSET:
		nRet = (dwData <= 5);
		if (nRet) dbSetupTotal.setSystem.nDaylightOffset = dwData;
		break;
	case DI_F1_STATUS:
		nRet = (dwData <= 11);
		if (nRet) dbSetupTotal.setSystem.byF1Status = (BYTE)dwData;
		break;
	case DI_F2_STATUS:
		nRet = (dwData <= 11);
		if (nRet) dbSetupTotal.setSystem.byF2Status = (BYTE)dwData;
		break;
	case DI_F3_STATUS:
		nRet = (dwData <= 11);
		if (nRet) dbSetupTotal.setSystem.byF3Status = (BYTE)dwData;
		break;
	case DI_F4_STATUS:
		nRet = (dwData <= 11);
		if (nRet) dbSetupTotal.setSystem.byF4Status = (BYTE)dwData;
		break;
	case DI_AUTO_POWERON:
		nRet = (dwData < 24 * 3600);
		if (nRet) dbSetupTotal.setSystem.dwAutoPoweronTime = dwData;
		break;
	case DI_AUTO_POWEROFF:
		nRet = (dwData < 24 * 3600);
		if (nRet) dbSetupTotal.setSystem.dwAutoPoweroffTime = dwData;
		break;
	case DI_AUTO_SLEEP:
		nRet = (dwData < 24 * 3600);
		if (nRet) dbSetupTotal.setSystem.dwAutoSleepTime = dwData;
		break;
	case DI_IDLETIME_POWEROFF:
		nRet = (dwData <= 9999);
		if (nRet) dbSetupTotal.setSystem.nIdletimeForPoweroff = dwData;
		break;
	case DI_IDLETIME_SLEEP:
		nRet = (dwData <= 9999);
		if (nRet) dbSetupTotal.setSystem.nIdletimeForSleep = dwData;
		break;
	case DI_IDLETIME_SCREENSAVER:
		nRet = (dwData <= 9999);
		if (nRet) dbSetupTotal.setSystem.nIdletimeForLcdswitch = dwData;
		break;
	case DI_USE_POWERKEY:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bPowerkeyLock = dwData;
		break;
	case DI_SERIAL_BAUDRATE:
		nRet = (dwData <= BAUDRATE_115200);
		if (nRet) dbSetupTotal.setSystem.nBaudrate = dwData;
		break;
	case DI_MACHINE_ID:
		nRet = (1 <= dwData && dwData <= 255);
		if (nRet) dbSetupTotal.setSystem.nMachineID = dwData;
		break;
	case DI_USE_ETHERNET:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bEthernetUse = dwData;
		break;
	case DI_IP_ADDRESS:
		nRet = TRUE;
		if (nRet) dbSetupTotal.setSystem.ipAddress = dwData;
		break;
	case DI_SUBNET_MASK:
		nRet = TRUE;
		if (nRet) dbSetupTotal.setSystem.ipSubnetMask = dwData;
		break;
	case DI_GATEWAY:
		nRet = TRUE;
		if (nRet) dbSetupTotal.setSystem.ipDefaultGateway = dwData;
		break;
	case DI_USE_RS232:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bRS232Use = dwData;
		break;
	case DI_USE_RS485:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bRS485Use = dwData;
		break;
	case DI_COMM_PWD:
		nRet = (dwData <= 99999999);
		if (nRet) dbSetupTotal.setSystem.dwCommPassword = dwData;
		break;
	case DI_USE_DHCP:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bDHCPUse = dwData;
		break;
	case DI_SLOG_WARN:
		nRet = (dwData <= 100);
		if (nRet) dbSetupTotal.setSystem.nMLogWarning = dwData;
		break;
	case DI_GLOG_WARN:
		nRet = (dwData <= 1000);
		if (nRet) dbSetupTotal.setSystem.nGLogWarning = dwData;
		break;
	case DI_REVERIFY_INTERVAL:
		nRet = (dwData <= 255);
		if (nRet) dbSetupTotal.setSystem.nReverifyTime = dwData;
		break;
	case DI_UNLOCK_TIME:
		nRet = (dwData <= 10);
		if (nRet) dbSetupTotal.setSystem.nLockTime = dwData;
		break;
	case DI_OPENNING_TOUT:
		nRet = (dwData <= 255);
		if (nRet) dbSetupTotal.setSystem.nDoorOpenTime = dwData;
		break;
	case DI_DOORSENSOR_SET:
		nRet = (dwData <= 2);
		if (nRet) dbSetupTotal.setSystem.nDoorSensorStatus = dwData;
		break;
	case DI_PWDVERIFY_ALARM:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bPwdAlarmUse = dwData;
		break;
	case DI_USE_KEYALARM:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bSOSKeyUse = dwData;
		break;
	case DI_ALARM_DELAY:
		nRet = (dwData <= 255);
		if (nRet) dbSetupTotal.setSystem.nAlarmDelay = dwData;
		break;
	case DI_IDENTFAIL_NUM:
		nRet = (dwData <= 9);
		if (nRet) dbSetupTotal.setSystem.nIllegalVerifyWarning = dwData;
		break;
	case DI_USE_ANTIPASS:
		nRet = (dwData <= ANTIPASS_END);
		if (nRet) dbSetupTotal.setSystem.byAntipassStatus = dwData;
		break;
	case DI_ALARM_STATUS:
		nRet = (dwData <= 1);
		if (nRet) 
		{
			if (dwData == 0)
			{
				uiAlarmStop();
				uiEventSend_ALARM_OFF(-1, ALARMRELEASE_OCX, 0);
			}
			else
			{
				uiAlarmStart(UI_ALARM_PCCMD);
				uiEventSend_ALARM_ON(UI_ALARM_PCCMD, 0);
			}
		}

		if (!comm_send_ack(nRet ? CMD_ACK : CMD_NAK, 0))
			return FALSE;
		return TRUE;
		
		break;
	case DI_LOCK_OPERATE:
		nRet = (dwData <= 2);
		if (nRet) dbSetupTotal.setNoMenu.byDoorStatus = dwData;
		break;
	case DI_MAINOPENGROUP:
		nRet = (dwData <= 5);
		if (nRet) dbSetupTotal.setSystem.nLockGroupMain = dwData;
		break;
	case DI_MANAGERPC_IP:
		nRet = TRUE;
		if (nRet) dbSetupTotal.setSystem.ipPCBackground = dwData;
		break;
	case DI_BINDING_ID:
		nRet = TRUE;
		if (nRet) dbSetupTotal.setSystem.dwBindingID = dwData;
		break;
	case DI_TIMEFORMAT:
		nRet = (1 <= dwData && dwData <= TIME_FORMAT_COUNT);
		if (nRet) dbSetupTotal.setSystem.nTimeFormat = dwData - 1;
		break;
	//////////////////////////////////////////////////////////////////////////
	case DI_GLOG_TZ:
		nLen = sizeof(ATOMIC_TZONE) * LOG_TZONE_COUNT;
		break;
	case DI_MULTI_IDENT:
		nLen = 5 * MULTI_IDENT_SET_COUNT;
		break;
	case DI_ACCESSTIME_SET:
		nLen = sizeof(ACCESS_TIME_SET) * ACCESS_TIME_SET_COUNT;
		break;
	case DI_ACCESSTIME_GROUP:
		nLen = 4 * ACCESS_USER_GROUP_COUNT;
		break;
	case DI_MESSAGE:
		nLen = sizeof(MSG_INFO) * MSG_INFO_COUNT;
		break;
	case DI_BELL:
		nLen = sizeof(BELL_INFO) *BELL_INFO_COUNT;
		break;
	case DI_WIEGAND:
		nLen = sizeof(WIEGAND_TYPE);
		break;
	case DI_SUPERMGR_PWD:
		nLen = USER_PWD_LEN;
		break;
	case DI_IDENT_MODE:
		nRet = FALSE;
		break;
	case DI_CAMRA_SHOW://Camera show
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bCameraShow = dwData;
		if (dbSetupTotal.setSystem.bCameraShow) //RSI090701
		{
			dbSetupTotal.setSystem.bPhotoShow = FALSE;
			dbSetupTotal.setSystem.bFPShow = FALSE;
		}
		break;
	case DI_DEFAULT_VM://Default Verfy Mode
		nRet = INDEX2VERIFYMODE(dwData);
		if(nRet != -1)
			dbSetupTotal.setSystem.nVerifyMode = nRet;
		break;
// 	case DI_DEFAULT_GVM://Group Verify Mode
// 		nRet = INDEX2VERIFYMODE(dwData);
// 		if(nRet != -1)
// 			dbSetupTotal.setSystem.byDefaultGVM = nRet;
// 		break;
	case DI_NETWORK_SPEED:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.byNetworkSpeed = (BYTE)dwData;
		break;
	case DI_THEME_MODE:
		nRet = (dwData <= 2);
		if (nRet) dbSetupTotal.setSystem.byTheme = (BYTE)dwData;
		break;
	case DI_WGN_SWITCH:
		nRet = (dwData <= 2);
		if (nRet) dbSetupTotal.setSystem.byWiegandFormat = (BYTE)dwData;
		break;
	case DI_USB_SLAVEUSED:
		nRet = (dwData <= 1);
		if (nRet) dbSetupTotal.setSystem.bUSBSlaveUse = (BOOL)dwData;
		break;
	case DI_PASS_TZ:
		nLen = sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT;
		break;
	case DI_GROUP_TZ:
		nLen = TIMEGROUP_COUNT * TIMECOUNT_PER_TG;
		break;
	case DI_TIME_TZ:
		nLen = ACCESS_TIME_SET_COUNT_HIGH * 7;
		break;

	default:
		nRet = FALSE;
		break;
	}

	if (!comm_send_ack(nRet ? CMD_ACK : CMD_NAK, 0)) return FALSE;

	if (nRet && !nLen)
	{
		nRet = DbSetupTotalWrite();
	}
	
	if (nRet && nLen)
	{
		if (!comm_recv_data(pTempBuffer, nLen)) return FALSE;
		nRet = TRUE;
		if (dwInfo == DI_GLOG_TZ)
		{
			ATOMIC_TZONE* pLogTZ = (ATOMIC_TZONE*)pTempBuffer;
			for (i = 0; i < LOG_TZONE_COUNT; i++)
			{
				if (pLogTZ[i].byOpt > 7 ||	// GLOG action mode
					pLogTZ[i].SHour > 23 ||	// Hour
					pLogTZ[i].SMin > 59 ||	// Minute
					pLogTZ[i].EHour > 23 ||	// Hour
					pLogTZ[i].EMin > 59)	// Minute
				{
					nRet = FALSE; break;
				}
			}
			if (nRet)
			{
				for (i = 0; i < LOG_TZONE_COUNT; i++)
				{
					dbSetupTotal.setTimezone.tzTr[i].STATUS = pLogTZ[i].byOpt;
					dbSetupTotal.setTimezone.tzTr[i].RANGE.bStartHour = pLogTZ[i].SHour;
					dbSetupTotal.setTimezone.tzTr[i].RANGE.bStartMinute = pLogTZ[i].SMin;
					dbSetupTotal.setTimezone.tzTr[i].RANGE.bEndHour = pLogTZ[i].EHour;
					dbSetupTotal.setTimezone.tzTr[i].RANGE.bEndMinute = pLogTZ[i].EMin;
				}		
			}
		}
		else if (dwInfo == DI_MULTI_IDENT)
		{
			BYTE *pMultiIG = (BYTE*)pTempBuffer;
			BYTE temp[MULTI_IDENT_SET_COUNT];
			int tval;

			memset(temp, 0, sizeof(temp));
			for (i = 0; i < 5 * MULTI_IDENT_SET_COUNT; i++)
			{
				if (pMultiIG[i] > ACCESS_USER_GROUP_COUNT)					// access time group No.
				{
					nRet = FALSE; break;
				}
			}
			if (nRet)
			{
				for (i=0; i<MULTI_IDENT_SET_COUNT; i++)
				{
					tval = pMultiIG[i * 5 + 0] +
						pMultiIG[i * 5 + 1] * 10 +
						pMultiIG[i * 5 + 2] * 100 +
						pMultiIG[i * 5 + 3] * 1000 +
						pMultiIG[i * 5 + 4] * 10000;
					tval = NUMBER2LOCKGROUP(tval);
					nRet = LOCKGROUP_VALIDCHECK(temp, (BYTE)tval);
					if (!nRet) break;
					temp[i] = (BYTE)tval;
				}
				if (nRet)
				{
					memcpy(dbSetupTotal.setTimezone.tzLockGroup, temp, sizeof(temp));
				}
			}
		}
		else if (dwInfo == DI_ACCESSTIME_SET)
		{
			ACCESS_TIME_SET *pAcessTS = (ACCESS_TIME_SET*)pTempBuffer;
			for (i = 0; i < ACCESS_TIME_SET_COUNT; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (pAcessTS[i].dayAccessTime[j].SHour > 23 ||	// Hour
						pAcessTS[i].dayAccessTime[j].SMin > 59 ||	// Minute
						pAcessTS[i].dayAccessTime[j].EHour > 23 ||	// Hour
						pAcessTS[i].dayAccessTime[j].EMin > 59) 	// Minute
					{
						nRet = FALSE; break;
					}
				}
				if (!nRet) break;
			}
			if (nRet)
			{
				for (i = 0; i < ACCESS_TIME_SET_COUNT; i++)
				{
					for (int j = 0; j < 7; j++)
					{
						dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bStartHour = pAcessTS[i].dayAccessTime[j].SHour;
						dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bStartMinute = pAcessTS[i].dayAccessTime[j].SMin;
						dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bEndHour = pAcessTS[i].dayAccessTime[j].EHour;
						dbSetupTotal.setTimezone.tzAccess[i].RANGE[j].bEndMinute = pAcessTS[i].dayAccessTime[j].EMin;
					}
				}
			}
		}
		else if (dwInfo == DI_ACCESSTIME_GROUP)
		{
			BYTE *pAccessG = (BYTE*)pTempBuffer;
			for (i = 0; i < ACCESS_USER_GROUP_COUNT; i++)
			{
				if (pAccessG[i * 4 + 0] > ACCESS_TIME_SET_COUNT ||		// access time set No.
					pAccessG[i * 4 + 1] > ACCESS_TIME_SET_COUNT ||
					pAccessG[i * 4 + 2] > ACCESS_TIME_SET_COUNT ||
					pAccessG[i * 4 + 3] < 1 ||
					pAccessG[i * 4 + 3] >= IDENT_MODE_COUNT)
				{
					nRet = FALSE; break;
				}
			}
			if (nRet)
			{
				for (i = 0; i < ACCESS_USER_GROUP_COUNT; i++)
				{
					dbSetupTotal.setTimezone.tzGroup[i].bGroupA = pAccessG[i * 4 + 0];
					dbSetupTotal.setTimezone.tzGroup[i].bGroupB = pAccessG[i * 4 + 1];
					dbSetupTotal.setTimezone.tzGroup[i].bGroupC = pAccessG[i * 4 + 2];
					dbSetupTotal.setTimezone.tzGrupVM[i] = pAccessG[i * 4 + 3];
				}
			}
		}
		else if (dwInfo == DI_MESSAGE)
		{
			MSG_INFO *pMsgs = (MSG_INFO*)pTempBuffer;
			for (i = 0; i < MSG_INFO_COUNT; i++)
			{
				if (pMsgs[i].Valid > 1 || 
					pMsgs[i].Tag > 2 || 
					/*(pMsgs[i].Tag == 1 && (pMsgs[i].Belong < 0 || pMsgs[i].Belong > MAX_ID)) ||*/
					(pMsgs[i].Tag == 2 && (pMsgs[i].Belong < 1 || pMsgs[i].Belong > ACCESS_USER_GROUP_COUNT)))
				{
					nRet = FALSE; break;
				}
			}
			if (nRet) memcpy(dbSetupTotal.setTimezone.tzMsg, pMsgs, nLen);
		}
		else if (dwInfo == DI_BELL)
		{
			BELL_INFO *pBells = (BELL_INFO*)pTempBuffer;
			for (i = 0; i < BELL_INFO_COUNT; i++)
			{
				if (pBells[i].byBellKind >= BELL_KIND_COUNT ||		// kind
					pBells[i].byHour > 23 ||			// Hour
					pBells[i].byMin > 59 || 			// Minute
					pBells[i].bySec > 59)				// Second
				{
					nRet = FALSE; break;
				}
			}
			if (nRet)
			{
				for (i = 0; i < BELL_INFO_COUNT; i++)
				{
					dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartHour = pBells[i].byHour;
					dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartMinute = pBells[i].byMin;
					dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndHour = pBells[i].byBellKind;
					dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndMinute = pBells[i].wLength;
				}
			}
		}
		else if (dwInfo == DI_WIEGAND)
		{
			WIEGAND_TYPE *pWiegand_type = (WIEGAND_TYPE*)pTempBuffer;
			memcpy(&dbSetupTotal.setNoMenu.wiegand_type, pWiegand_type, nLen);
			nRet = TRUE;
		}
		else if (dwInfo == DI_SUPERMGR_PWD)
		{
			((char*)pTempBuffer)[USER_PWD_LEN] = 0;
			nRet = (dwData = STRING2PWD((char*)pTempBuffer));
			if (nRet) dbSetupTotal.setSystem.dwSManagerPwd = dwData;
		}
		else if (dwInfo == DI_PASS_TZ)//Pass Timezone
		{
			DB_TIMESECTION_A *pPassTime = (DB_TIMESECTION_A*)pTempBuffer;

			for(i = 0; i < TIMEZONE_COUNT; i++){
				if(pPassTime[i].bStartHour > 23 ||
				   pPassTime[i].bStartMinute > 59 ||
				   pPassTime[i].bEndHour > 23 ||
				   pPassTime[i].bEndMinute > 59)
				{
					nRet = FALSE; break;
				}
			}

			if(nRet){
				memcpy(&dbSetupTotal.setTimezone.tzHighTIME[0], (void*)pPassTime, sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT);
			}
		}
		else if (dwInfo == DI_GROUP_TZ)
		{
			BYTE *pGroupTime = (BYTE*)pTempBuffer;

			for(i = 0; i < TIMEGROUP_COUNT * TIMECOUNT_PER_TG; i++){
				if(pGroupTime[i] > 31){
					nRet = FALSE; break;
				}
			}

			if(nRet){
				memcpy((void *)&dbSetupTotal.setTimezone.tzHighTG[0], (void*)pGroupTime, TIMEGROUP_COUNT * TIMECOUNT_PER_TG);
			}
		}
		else if (dwInfo == DI_TIME_TZ)
		{
			BYTE *pTime_TZ = (BYTE*)pTempBuffer;

			for(i = 0; i < ACCESS_TIME_SET_COUNT_HIGH * 7; i++){
				if(pTime_TZ[i] > 31){
					nRet = FALSE; break;
				}
			}
			
			if(nRet){
				memcpy((void *)dbSetupTotal.setTimezone.tzHighAccess, (void*)pTime_TZ, ACCESS_TIME_SET_COUNT_HIGH * 7);
			}
		}
		else
		{
			nRet = FALSE;
		}
		if (nRet) nRet = DbSetupTotalWrite();
		if (!comm_send_ack(nRet ? CMD_ACK : CMD_NAK, 0)) return FALSE;
	}

	return TRUE;
}

BOOL ComGetPhotoList()
{
	DWORD param[2];

	if (!comm_recv_data(param, 8)) return FALSE;

	if (!SDCARD_MOUNT())
		return comm_send_ack(CMD_NAK, 0);

	long dwStartPos, dwCount, nRet, i;
	QDir dir(dfPath[DF_TYPE_PHOTO_LOG * 2], "*.jpg");
	QStringList files = dir.entryList();
	char *pName;
	
	dwStartPos = param[0];
	dwCount = param[1];
	
	if (dwStartPos < 0 || dwCount < 0 || dwCount > 1024)
	{
		return comm_send_ack(CMD_NAK, 0);
	}

	nRet = dir.count();
	if (dwCount == 0)
	{
		return comm_send_ack(CMD_ACK, nRet);
	}

	nRet -= dwStartPos;
	if (nRet > dwCount) nRet = dwCount;
	if (nRet <= 0) return comm_send_ack(CMD_NAK, 0);

	if (!comm_send_ack(CMD_ACK, nRet)) return FALSE;
	memset(pTempBuffer, 0, nRet * FNAME_LEN);

	for (i = 0; i < nRet; i++)
	{
		pName = STR2ASCII(files[i + dwStartPos]);
		memcpy(((char*)pTempBuffer) + i * FNAME_LEN, pName, 19);
	}
	return	comm_send_data(pTempBuffer, nRet * FNAME_LEN);
}

BOOL ComGetDataFile() 
{
	char param[8 + FNAME_LEN];
	char szFileName[128];
	long dwfiletype, nSize, fd = INVALID_HANDLE_VALUE, nFileSize, nRet;
	void *ptbuff = NULL;
	
	if (!comm_recv_data(param, 8 + FNAME_LEN)) return FALSE;
	dwfiletype = ((long*)param)[0];
	nSize = ((long*)param)[1];

	if (dwfiletype < DF_TYPE_SCREENSAVER_IMG || dwfiletype > DF_TYPE_GLOG_DAT || nSize < -1)
	{
		return comm_send_ack(CMD_NAK, 0);
	}
	memmove(param, param + 8, FNAME_LEN); memset(param + FNAME_LEN, 0, 8);
	switch (dwfiletype)
	{
	case DF_TYPE_SCREENSAVER_IMG:
		nRet = TRUE;
		break;
	case DF_TYPE_SCREENSAVER_MP3:
		nRet = (strcmp(SCREENSAVER_MP3FILE, param) == 0);
		break;
	case DF_TYPE_SYSTEM_MP3:
		{
			int nNo = atoi(param);
			nRet = FALSE;
			if (SOUND_START <= nNo && nNo < SOUND_END)
			{
				sprintf(szFileName, "%d", nNo);
				nRet = (strcmp(szFileName, param) == 0);
			}
		}
		break;
	case DF_TYPE_USER_VOICE:
		{
			int nNo = atoi(param);
			nRet = FALSE;
			if (MIN_ID <= nNo && nNo <= MAX_ID)
			{
				sprintf(szFileName, "%05dvoice", nNo);
				if ((nRet = (int)(strcmp(szFileName, param) == 0)))
				{
					if (!DbUserInfoHasVoice(nNo))
						nRet = FALSE;
				}
			}
		}
		break;
	case DF_TYPE_USER_PHOTO:
		{
			int nNo = atoi(param);
			nRet = FALSE;
			if (MIN_ID <= nNo && nNo <= MAX_ID)
			{
				sprintf(szFileName, "%05d", nNo);
				if ((nRet = (int)(strcmp(szFileName, param) == 0)))
				{
					if (!DbUserInfoHasPhoto(nNo))
						nRet = FALSE;
				}
			}
		}
		break;
	case DF_TYPE_PHOTO_LOG:
		nRet = TRUE;
		break;
	case DF_TYPE_PART_SET:
		nRet = (strcmp(PART_SETFILE, param) == 0);
		break;
	case DF_TYPE_ENROLL_DAT:
		nRet = (strcmp(DB_ENROLLDATA_FILENAME, param) == 0);
		break;
	case DF_TYPE_SLOG_DAT:
		nRet = (strcmp(DB_SLOGDATA_FILENAME, param) == 0);
		break;
	case DF_TYPE_GLOG_DAT:
		nRet = (strcmp(DB_GLOGDATA_FILENAME, param) == 0);
		break;
	default:
		nRet = FALSE;
		break;
	}

	if (!nRet) return comm_send_ack(CMD_NAK, 0);

	if (dwfiletype == DF_TYPE_ENROLL_DAT)
	{
		DWORD dwMagic = MAGIC_ENROLLDB;
		T_ENROLLDB_HDR hdr;
		void* enroll_dbs[] = {&dwMagic, &hdr, gpUIIndexData, gpIndexData, gpUserInfoEnrollData, gpFingerEnrollData};
		int sizes[] = {4, sizeof(hdr), FLASH_UI_INDEX_SIZE, dbLicense.nMaxEnrollCount, 
			dbLicense.nMaxEnrollCount * sizeof(USER_INFO), dbLicense.nMaxEnrollCount * sizeof(FPINFO)};
		int i;
		int total_size = 0;

		for (i=0; i<(int)ITEM_CNT(sizes); i++)
			total_size += sizes[i];

		hdr.dwUIIndexSize  = FLASH_UI_INDEX_SIZE;
		hdr.dwFPIndexSize  = dbLicense.nMaxEnrollCount;
		hdr.dwUserInfoSize = dbLicense.nMaxEnrollCount * sizeof(USER_INFO);
		hdr.dwFPSize       = dbLicense.nMaxEnrollCount * sizeof(FPINFO);

		if (nSize != -1 && nSize < total_size)
			return comm_send_ack(CMD_NAK, 0);
		if (!comm_send_ack(CMD_ACK, total_size)) return FALSE;
		if (nSize == -1) return TRUE;
		uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
		nRet = comm_send_data_gather(enroll_dbs, sizes, ITEM_CNT(sizes));
		uiLcdProgressDlgExit(); g_bProgress = FALSE;
		return nRet;
	}
	if (dwfiletype == DF_TYPE_SLOG_DAT)
	{
		int nLogCount;
		BYTE *pLog = (BYTE*)malloc(dbLicense.nSlogMaxCount * sizeof(MLOG_INFO) + 4);
		if (!pLog)
			return comm_send_ack(CMD_NAK, 0);
		
		*(DWORD*)pLog = MAGIC_SLOG;
		nLogCount = DbSLogGet((MLOG_INFO*)&pLog[4], DbSLogGetReadPos(), DbSLogCountAll() + 1);

		nFileSize = 4 + nLogCount * sizeof(MLOG_INFO);
		if (nSize != -1 && nSize < nFileSize) {comm_send_ack(CMD_NAK, 0); nRet = FALSE; goto l_exit_slog;}
		if (!comm_send_ack(CMD_ACK, nFileSize)) {nRet = FALSE; goto l_exit_slog;}
		if (nSize == -1) {nRet = TRUE; goto l_exit_slog;}
		uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
		nRet = comm_send_data(pLog, nFileSize);
		uiLcdProgressDlgExit(); g_bProgress = FALSE;
l_exit_slog:
		FREE(pLog);
		return nRet;
	}
	if (dwfiletype == DF_TYPE_GLOG_DAT)
	{
		int nLogCount;
		BYTE *pLog = (BYTE*)malloc(dbLicense.nGlogMaxCount * sizeof(ALOG_INFO) + 4);
		if (!pLog)
			return comm_send_ack(CMD_NAK, 0);

		*(DWORD*)pLog = MAGIC_GLOG;
		nLogCount = DbGLogGet((ALOG_INFO*)&pLog[4], DbGLogGetReadPos(), DbGLogCountAll() + 1);

		nFileSize = 4 + nLogCount * sizeof(ALOG_INFO);
		if (nSize != -1 && nSize < nFileSize) {comm_send_ack(CMD_NAK, 0); nRet = FALSE; goto l_exit_glog;}
		if (!comm_send_ack(CMD_ACK, nFileSize)) {nRet = FALSE; goto l_exit_glog;}
		if (nSize == -1) {nRet = TRUE; goto l_exit_glog;}
		uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
		nRet = comm_send_data(pLog, nFileSize);
		uiLcdProgressDlgExit(); g_bProgress = FALSE;
l_exit_glog:
		FREE(pLog);
		return nRet;
	}

	sprintf(szFileName, "%s%s%s", dfPath[dwfiletype * 2], param, dfPath[dwfiletype * 2 + 1]);

	if (QString(szFileName).contains(SDCARD_MOUNTPOINT) == TRUE)
	{
		if (!SDCARD_MOUNT())
			return comm_send_ack(CMD_NAK, 0);
	}
	
	fd = open(szFileName, O_RDONLY);
	if (fd == INVALID_HANDLE_VALUE) 
	{
		return comm_send_ack(CMD_NAK, 0);
	}
	else
	{
		ioctl(fd, FIONREAD, &nFileSize);
		if (nSize == -1)
		{
			nRet = comm_send_ack(CMD_ACK, nFileSize);
		}
		else
		{
// 			if (nFileSize > MAX_DATA_FILE_LEN) nFileSize = MAX_DATA_FILE_LEN;
			if (nFileSize > nSize) nFileSize = nSize;
			if (nFileSize < 0) nFileSize = 0;
			if (nFileSize > 0) 
			{
				if ((ptbuff = malloc(nFileSize)))
				{
					nFileSize = read(fd, ptbuff, nFileSize);
					if (!comm_send_ack(CMD_ACK, nFileSize)) {nRet = FALSE; goto l_exit;}
					nRet = nFileSize > 0 ? comm_send_data(ptbuff, nFileSize) : TRUE;
				}
				else
				{
					nRet = comm_send_ack(CMD_NAK, 3);
				}
			}
			else
			{
				nRet = comm_send_ack(CMD_ACK, nFileSize);
			}
		}
	}
	
l_exit:
	FD_CLOSE(fd);
	if (ptbuff) free(ptbuff);
	return nRet;
}

BOOL ComSetDataFile(BOOL bWebserver) 
{
	char param[8 + FNAME_LEN];
	char szFileName[128];
	long dwfiletype, nSize, fd, nRet;
	int nNo = 0;

	if (!comm_recv_data(param, 8 + FNAME_LEN)) return FALSE;
	dwfiletype = ((long*)param)[0];
	nSize = ((long*)param)[1];
	if (dwfiletype < DF_TYPE_SCREENSAVER_IMG || dwfiletype == DF_TYPE_PHOTO_LOG || dwfiletype > DF_TYPE_GLOG_DAT || nSize < -1)
	{
		return comm_send_ack(CMD_NAK, 0);
	}
	memmove(param, param + 8, FNAME_LEN); memset(param + FNAME_LEN, 0, 8);
	switch (dwfiletype)
	{
	case DF_TYPE_SCREENSAVER_IMG:
		nRet = TRUE;
		break;
	case DF_TYPE_SCREENSAVER_MP3:
		nRet = (strcmp(SCREENSAVER_MP3FILE, param) == 0);
		break;
	case DF_TYPE_SYSTEM_MP3:
		{
			nNo = atoi(param);
			nRet = FALSE;
			if (SOUND_START <= nNo && nNo < SOUND_END)
			{
				sprintf(szFileName, "%d", nNo);
				nRet = (strcmp(szFileName, param) == 0);
			}
		}
		break;
	case DF_TYPE_USER_VOICE:
		{
			nNo = atoi(param);
			nRet = FALSE;
			if (MIN_ID <= nNo && nNo <= MAX_ID)
			{
				sprintf(szFileName, "%05dvoice", nNo);
				if ((nRet = (int)(strcmp(szFileName, param) == 0)))
					nRet = DbUserInfoIsUsedID(nNo);
			}
		}
		break;
	case DF_TYPE_USER_PHOTO:
		{
			nNo = atoi(param);
			nRet = FALSE;
			if (MIN_ID <= nNo && nNo <= MAX_ID)
			{
				sprintf(szFileName, "%05d", nNo);
				if ((nRet = (int)(strcmp(szFileName, param) == 0)))
					nRet = DbUserInfoIsUsedID(nNo);
			}
		}
		break;
	case DF_TYPE_PHOTO_LOG:
		nRet = FALSE;
		break;
	case DF_TYPE_PART_SET:
		nRet = (strcmp(PART_SETFILE, param) == 0);
		break;
	case DF_TYPE_ENROLL_DAT:
		nRet = (strcmp(DB_ENROLLDATA_FILENAME, param) == 0);
		break;
	case DF_TYPE_SLOG_DAT:
		nRet = (strcmp(DB_SLOGDATA_FILENAME, param) == 0);
		if (nRet)
			nRet = DbSLogDeleteAll();
		break;
	case DF_TYPE_GLOG_DAT:
		nRet = (strcmp(DB_GLOGDATA_FILENAME, param) == 0);
		if (nRet)
			nRet = DbGLogDeleteAll();
		break;
	default:
		nRet = FALSE;
		break;
	}
	nRet = (nRet && (nSize <= dfMaxSize[dwfiletype]));
	if (!nRet) return comm_send_ack(CMD_NAK, 0);
	
	sprintf(szFileName, "%s%s%s", dfPath[dwfiletype * 2], param, dfPath[dwfiletype * 2 + 1]);

	if (QString(szFileName).contains(SDCARD_MOUNTPOINT) == TRUE)
	{
		if (!SDCARD_MOUNT())
			return comm_send_ack(CMD_NAK, 0);
	}

	if (nSize == -1)
	{
		if (!(nRet = unlink(szFileName)))
		{
			if (dwfiletype == DF_TYPE_PART_SET)
				DbPartReload();
			else if (dwfiletype == DF_TYPE_USER_VOICE)
				DbUserInfoSetVoice(nNo, FALSE);
			else if (dwfiletype == DF_TYPE_USER_PHOTO)
				DbUserInfoSetPhoto(nNo, FALSE);
		}
		return comm_send_ack((nRet == 0 ? CMD_ACK : CMD_NAK), 0);
	}
	
	if (dwfiletype == DF_TYPE_ENROLL_DAT)
	{
		DWORD dwMagic = MAGIC_ENROLLDB;
		T_ENROLLDB_HDR hdr;
		void* enroll_dbs[] = {&dwMagic, &hdr, gpUIIndexData, gpIndexData, gpUserInfoEnrollData, gpFingerEnrollData, NULL};
		int sizes[] = {4, sizeof(hdr), FLASH_UI_INDEX_SIZE, dbLicense.nMaxEnrollCount, 
			dbLicense.nMaxEnrollCount * sizeof(USER_INFO), dbLicense.nMaxEnrollCount * sizeof(FPINFO), 0};
		int last_index = ITEM_CNT(sizes) - 1;
		int i;
		int total_size = 0;

		for (i=0; i<last_index; i++)
			total_size += sizes[i];
		if (nSize < total_size)
			return comm_send_ack(CMD_NAK, 0);
		if (nSize > total_size)
		{
			if (nSize - total_size > 1024)
				return comm_send_ack(CMD_NAK, 0);
			if (!(enroll_dbs[last_index] = (BYTE*)malloc(nSize - total_size)))
				return comm_send_ack(CMD_NAK, 0);
			sizes[last_index] = nSize - total_size;
		}

		if (!comm_send_ack(CMD_ACK, 0)) return FALSE;
		uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
		nRet = comm_recv_data_scatter(enroll_dbs, sizes, nSize == total_size ? last_index : last_index + 1);
		uiLcdProgressDlgExit(); g_bProgress = FALSE;
		if (bWebserver)
		{
			long nSizePadding;
			nRet = comm_recv_data(&nSizePadding, sizeof(nSizePadding));
		}
		FREE(enroll_dbs[last_index]);

		if (dwMagic != MAGIC_ENROLLDB ||
			hdr.dwUIIndexSize != FLASH_UI_INDEX_SIZE ||
			hdr.dwFPIndexSize != (DWORD)dbLicense.nMaxEnrollCount ||
			hdr.dwUserInfoSize != dbLicense.nMaxEnrollCount * sizeof(USER_INFO) ||
			hdr.dwFPSize  != dbLicense.nMaxEnrollCount * sizeof(FPINFO)
			)
		{
			Db_FreeAllData();
			Db_LoadAllData(TRUE);
			comm_send_ack(CMD_NAK, 0);
			return FALSE;
		}

		uiLcdProgressDlgShow(UISTR_FILEWRITE); g_bProgress = TRUE;
		DbFpSave();
		DbFPIndexSave();
		DbUserInfoSave();
		DbUIIndexSave();
		uiLcdProgressDlgExit(); g_bProgress = FALSE;
		return comm_send_ack(CMD_ACK, 0);
	}

	if (FREE_SPACE((char*)dfPath[dwfiletype * 2]) + FILE_SIZE(szFileName) <= nSize)
		return comm_send_ack(CMD_NAK, 0);

// 	if (nSize > MAX_DATA_FILE_LEN) 
// 	{
// 		nRet = FALSE;
// 	}
// 	else
	{
		nRet = comm_send_ack(CMD_ACK, 0);
		
		if (nRet && nSize > 0)
		{
			void *ptbuff = malloc(nSize);
			if (!ptbuff) return FALSE;
			uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
			nRet = comm_recv_data(ptbuff, nSize);
			uiLcdProgressDlgExit(); g_bProgress = FALSE;
			if (nRet)
			{
				if (bWebserver)
				{
					long nSizePadding;
					nRet = comm_recv_data(&nSizePadding, sizeof(nSizePadding));
					nSize -= nSizePadding;
				}
				
				if (nRet)
				{
					switch (dwfiletype)
					{
					case DF_TYPE_SCREENSAVER_IMG:
						{
							QPixmap pmap;
							if (!pmap.loadFromData((BYTE*)ptbuff, nSize) || pmap.width() != LCD_SIZE_X || pmap.height() != LCD_SIZE_Y)
								nRet = FALSE;
						}
						break;
					case DF_TYPE_SCREENSAVER_MP3:
						break;
					case DF_TYPE_SYSTEM_MP3:
					case DF_TYPE_USER_VOICE:
						{
							int speed, bits, stereo;
							int nTotalCount = 0;
							check_wave_buf((BYTE*)ptbuff,&speed, &bits, &stereo, &nTotalCount);
							if(bits != 16 || nRet != 1)
								nRet = FALSE;
						}
						break;
					case DF_TYPE_USER_PHOTO:
						{
							QPixmap pmap;
							if (!pmap.loadFromData((BYTE*)ptbuff, nSize) || !pmap.width() || !pmap.height())
								nRet = FALSE;
						}
						break;
					case DF_TYPE_PHOTO_LOG:
						break;
					case DF_TYPE_PART_SET:
						{
							DWORD dwMagic = MAGIC_UTF8;
							nRet = (memcmp(&dwMagic, ptbuff, 3) == 0);
						}
						break;
					case DF_TYPE_ENROLL_DAT:
						break;
					case DF_TYPE_SLOG_DAT:
						{
							int idx;
							MLOG_INFO *pLog = (MLOG_INFO*)ptbuff;
							for (idx=0; idx<(int)(nSize/sizeof(MLOG_INFO)); idx++)
							{
								if (/*(pLog[idx].byAction < SLOG_START) || */(pLog[idx].byAction > SLOG_END))
								{
									nRet = FALSE;
									break;
								}
							}
						}
						break;
					case DF_TYPE_GLOG_DAT:
						{
							int idx;
							ALOG_INFO *pLog = (ALOG_INFO*)ptbuff;
							for (idx=0; idx<(int)(nSize/sizeof(ALOG_INFO)); idx++)
							{
								if (/*pLog[idx].byAction < VM_START || */pLog[idx].byAction > VM_END)
								{
									nRet = FALSE;
									break;
								}
							}
						}
						break;
					}

					if (!nRet)
					{
//						printf("set data file failed !\n");
						FREE(ptbuff);
						goto _lExit;
					}

					if (dwfiletype == DF_TYPE_SLOG_DAT)
						DbSLogDeleteAll();
					else if (dwfiletype == DF_TYPE_GLOG_DAT)
						DbGLogDeleteAll();
					else
						unlink(szFileName);

					DIR_CHECK_AND_MAKE(szFileName);

					if ((fd = open(szFileName, O_WRONLY | O_CREAT | O_TRUNC, 0x777)) != INVALID_HANDLE_VALUE) 
					{
						if (dwfiletype == DF_TYPE_SLOG_DAT)
						{
							write(fd, (BYTE*)ptbuff + 4, nSize - 4);
							DbSLogLoad();
						}
						else if (dwfiletype == DF_TYPE_GLOG_DAT)
						{
							write(fd, (BYTE*)ptbuff + 4, nSize - 4);
							DbGLogLoad();
						}
						else
							write(fd, ptbuff, nSize);
						close(fd);
					}
					else
					{
						nRet = FALSE;
					}
				}
			}
			free(ptbuff);
		}
	}

	if (nRet)
	{
		if (dwfiletype == DF_TYPE_PART_SET)
			nRet = DbPartReload();
		else if (dwfiletype == DF_TYPE_USER_VOICE)
			nRet = DbUserInfoSetVoice(nNo, TRUE);
		else if (dwfiletype == DF_TYPE_USER_PHOTO)
			nRet = DbUserInfoSetPhoto(nNo, TRUE);
	}
_lExit:
	return comm_send_ack(nRet ? CMD_ACK : CMD_NAK, 0);
}

BOOL ComEnableDevice()
{
	DWORD bEnable;
	
	if (!comm_recv_data(&bEnable, 4)) return FALSE;
	g_bDisableDevice = bEnable ? (BYTE)DISABLE_MODE_NONE : comm_get_disabledevice();
	return comm_send_ack(CMD_ACK, bEnable);
}

BOOL ComPowerControl()
{
	DWORD dwPowerAction;
	if (!comm_recv_data(&dwPowerAction, 4)) return FALSE;
	if (dwPowerAction != PC_POWER_OFF && dwPowerAction != PC_RESTART)
	{
		return comm_send_ack(CMD_NAK, dwPowerAction);
	}
	if (!comm_send_ack(CMD_ACK, dwPowerAction)) return FALSE;
	if (dwPowerAction == PC_POWER_OFF)
	{
		uiPowerSetStatus(UI_POWER_OFF, 1);
	}
	else if (dwPowerAction == PC_RESTART)
	{
		ComDownRestart();
	}

	return TRUE;
}

BOOL ComEmptyData() 
{
	DWORD dwDataKind;
	if (!comm_recv_data(&dwDataKind, 4)) return FALSE;
	dwDataKind &= DATA_MASK_ALL;

	if (dwDataKind & DATA_MASK_GLOG) DbGLogDeleteAll();
	if (dwDataKind & DATA_MASK_SLOG) DbSLogDeleteAll();
	if (dwDataKind & DATA_MASK_ENROLL) Db_DeleteAllEnrollData();

	return comm_send_ack(CMD_ACK, dwDataKind);
}

BOOL ComAntipassSend()
{
	int nVerifyMode;
	BYTE *pTemplate;
	FPINFO FP;
	DWORD dwCardNumber;
	int nLength;
	USER_INFO UserInfo;
	BYTE RESULT[3];
	BOOL bSuccess;

	if (!comm_recv_data(&nVerifyMode, 4) ||
		dbSetupTotal.setSystem.byAntipassStatus != ANTIPASS_MASTER)
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}

	if (nVerifyMode == UI_VERIFY_FP)
	{
		pTemplate = (BYTE*)&FP;
		nLength = sizeof(FPINFO);
	}
	else if (nVerifyMode == UI_VERIFY_RF)
	{
		pTemplate = (BYTE*)&dwCardNumber;
		nLength = sizeof(dwCardNumber);
	}
	else
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}

	if (!comm_recv_data(pTemplate, nLength))
	{
		comm_send_ack(CMD_NAK, 0);
		return FALSE;
	}
	
	if (nVerifyMode == UI_VERIFY_FP)
		bSuccess = uiFpVerifyO2N((FPINFO*)pTemplate, &UserInfo, &RESULT[0], &RESULT[1], &RESULT[2]);
	else
		bSuccess = uiCardVerify(dwCardNumber, &UserInfo, &RESULT[0]);

	comm_send_ack(CMD_ACK, 0);

	if (bSuccess)
	{
		BYTE bAntipassOut = DbAntipassGet(UserInfo.ID);
		if (bAntipassOut == ANTIPASSOUT_OUT)
		{
			UserInfo.RES[0] = 1;
		}
		else
		{
			uiDoorOpen(UserInfo.ID);
			xprintf("i am in comantipasssend!!\r\n");
			uiLogGlogAdd(UserInfo.ID, (nVerifyMode == UI_VERIFY_FP) ? VM_FP : VM_RF, 0, TRUE);
		}
		comm_send_data(&UserInfo, sizeof(USER_INFO));
		comm_send_data(RESULT, sizeof(RESULT));
	}
	else
	{
		memset(&UserInfo, 0, sizeof(USER_INFO));
		comm_send_data(&UserInfo, sizeof(USER_INFO));
		comm_send_data(RESULT, sizeof(RESULT));
	}
	return bSuccess;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL hcCommanProc(int nCMD)
{
	int nRet;	

	dwRealTime = uiTimeGetTickCount();
	//dwTimeSynTime=dwRealTime;	
	bSendAckTimeout=0;

	if (!comm_send_ack(CMD_ACK, 0))
	{
		return FALSE;
	}

	if (g_uiWorkingDisplay)
		uiProcDrawStatus();

	g_uiCommandProc = TRUE;

/*	if (!g_bDisableDevice && nCMD >= CMD_GET_ALLID)
	{
//		uiBuzzerAlarm();
		BUZZER_ALARM();
	}
	else
	{
		if (nCMD >= CMD_DOWN_DOWNLOADER_WRITE && nCMD != CMD_TEST_GET_IMAGE_ORG && nCMD <= CMD_TEST_GET_IMAGE)
			BUZZER_ALARM();
	}  *//////1.34

//	Com_DispCmd(nCMD);

	switch (nCMD)
	{
	case CMD_DOWN_DOWNLOADER_WRITE:
		nRet = ComDownDownloaderWrite();
		break;
	case CMD_DOWN_RESTART:
		nRet = ComDownRestart();
		break;
	case CMD_DOWN_INIT_GET:
		nRet = ComDownInitGet();
		break;
	case CMD_DOWN_INIT_SET:
		nRet = ComDownInitSet();
		break;
	case CMD_DOWN_KERNEL_WRITE:
		nRet = ComDownKernelWrite();
		break;
	case CMD_DOWN_ROOTFS_WRITE:
		nRet = ComDownRootfsWrite();
		break;
	case CMD_DOWN_ROMWRITE:
		tcpclient_connect_threadStop();
		nRet = ComDownRomWrite(FALSE);
		//SB_EXEC("reboot"); 
		SystemReset();
		break;
	case CMD_DOWN_FLASHINIT:
		nRet = ComDownFlashInit();
		break;
	case CMD_DOWN_BOOTSPLASH:
		nRet = ComDownBootsplash();
		break;
	case CMD_TEST_GET_IMAGE_TRIGGER:
		g_bDisableDevice = g_bDisableDevice ? (BYTE)DISABLE_MODE_NONE : comm_get_disabledevice();
		nRet = comm_send_ack(CMD_ACK, g_bDisableDevice ? TRUE : FALSE);
		break;
	case CMD_TEST_GET_IMAGE_ORG:
		{
			void* pOrgImage = SB_FP__FIRSTIMAGE;
			long param[2];
			param[0] = g_bDisableDevice ? TRUE : FALSE;
			param[1] = 640;

			if(g_bDisableDevice)
			{
				SB_FP_CAPTUREONEFRAME();
				pOrgImage = SB_FP__LIVEIMAGE;
			}
			nRet = (comm_send_data(param, 8) && comm_send_data(pOrgImage, param[1] * 480));
		}
		break;
	case CMD_TEST_GET_IMAGE:
		if(!g_bDisableDevice || SB_FP_CAPTUREFINGER() != FP_ERR_SUCCESS)
		{
			nRet = comm_send_ack(CMD_NAK, g_bDisableDevice ? TRUE : FALSE);
			break;
		}

		nRet = comm_send_ack(CMD_ACK, g_bDisableDevice ? TRUE : FALSE);
		nRet = comm_send_data(SB_FP__256IMAGE, 256*256);
		break;
//////////////////////////////////////////////////////////////////////////
	case CMD_INTERNAL_CHECK_PWD:  
		nRet = ComCheckPwd();
		break;
	case CMD_GET_ALLID:
		nRet = ComGetAllUserID();
		break;
	case CMD_GET_ONEID:
		nRet = ComGetOneUserID();
		break;
	case CMD_GET_UINFO:
		nRet = ComGetUserInfo();
		break;
	case CMD_SET_UINFO:
		nRet = ComSetUserInfo();
		break;
	case CMD_GET_LOG_COUNT:  
		nRet = ComGetLogCount();
		break;
	case CMD_GET_SLOG:  
		nRet = ComGetSuperLog();
		break;
	case CMD_GET_GLOG:  
		nRet = ComGetGeneralLog();
		break;			
	case CMD_GET_DEVICE_STATUS:  
		nRet = ComGetDeviceStatus();
		break;
	case CMD_GET_DEVICE_INFO:  
		nRet = ComGetDeviceInfo();
		break;
	case CMD_SET_DEVICE_INFO:  
		nRet = ComSetDeviceInfo();
		break;
	case CMD_GET_DATA_FILE:  
		nRet = ComGetDataFile();
		break;
	case CMD_SET_DATA_FILE:  
		nRet = ComSetDataFile(FALSE);
		break;
	case CMD_SET_DATA_FILE_WS:  
		nRet = ComSetDataFile(TRUE);
		break;
	case CMD_ENABLE_DEVICE:  
		nRet = ComEnableDevice();
		break;
	case CMD_POWER_CONTROL:  
		nRet = ComPowerControl();
		break;
	case CMD_EMPTY_DATA:  
		nRet = ComEmptyData();
		break;
	case CMD_FW_UPGRADE:  
		nRet = ComDownRomWrite(FALSE);
		break;
	case CMD_FW_UPGRADE_WS:  
		nRet = ComDownRomWrite(TRUE);
		break;
	case CMD_GET_PHOTOLIST:
		nRet = ComGetPhotoList();
		break;
	case CMD_ANTIPASS_SEND:
		nRet = ComAntipassSend();
		break;
//////////////////////////////////////////////////////////////////////////
	}

	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define WINAPI

enum
{
	E_SUCCESS = 0,
	E_INVALID_COMMMODE,
	E_COM_CREATE,
	E_COM_SETUP,
	E_SOCK_CREATE,
	E_SOCK_SETOPTION,
	E_SOCK_CONNECT,
	E_SOCK_SEND,
	E_SOCK_RECV,
	E_INVALID_PWD,
};

static int		__prev_commmode  = COMM_MODE_NONE;
static WORD		__prev_machineid = 0;
static DWORD	__prev_password  = 0;
static WPARAM	__prev_wparam    = 0;
static LPARAM	__prev_lparam    = 0;
static DWORD	_comm_last_error = 0;

BOOL WINAPI StartCommX(int nCommMode, WORD wMachineID, DWORD dwPassword, WPARAM wParam, LPARAM lParam)
{
	if (TRUE)
	{
		__prev_commmode  = nCommMode;
		__prev_machineid = wMachineID;
		__prev_password  = dwPassword;
		__prev_wparam    = wParam;
		__prev_lparam    = lParam;
	}

	_comm_last_error = E_SUCCESS;
	return comm_open(nCommMode, wMachineID, dwPassword, wParam, lParam);
}

BOOL WINAPI SetMachineIDX(DWORD dwMachineID)
{
 	_comm_last_error = E_SUCCESS;
	return comm_set_machineid((WORD)dwMachineID);
}

BOOL WINAPI SendCommandX(WORD wCmd)
{
//	BOOL bResult = TRUE;
	DWORD dwLastError = _comm_last_error;

	_comm_last_error = E_SUCCESS;

	if (dwLastError && !StartCommX(__prev_commmode, __prev_machineid, __prev_password, __prev_wparam, __prev_lparam))
		return FALSE;

	if (comm_send_cmd(wCmd))
		return TRUE;

	if (!StartCommX(__prev_commmode, __prev_machineid, __prev_password, __prev_wparam, __prev_lparam))
		return FALSE;

	return comm_send_cmd(wCmd);
}

BOOL WINAPI SendAckX(WORD ack)
{
	_comm_last_error = E_SUCCESS;
	return comm_send_ack(ack, 0);
}

long WINAPI RecvAckX(DWORD* pData, int /*nTimeout*/)
{
	_comm_last_error = E_SUCCESS;
	return comm_recv_ack(pData);
}

BOOL WINAPI RecvAcknCheckX(int /*nTimeout*/)
{
	_comm_last_error = E_SUCCESS;
	return comm_recv_ack_and_check();
}

BOOL WINAPI SendDataX(void* pBuf, int nSize)
{
	_comm_last_error = E_SUCCESS;
	return comm_send_data(pBuf, nSize);
}

BOOL WINAPI RecvDataX(void* pBuf, int nSize, int /*nTimeout*/)
{
	_comm_last_error = E_SUCCESS;
	return comm_recv_data(pBuf, nSize);
}

BOOL WINAPI ComWakeUpX()
{
	_comm_last_error = E_SUCCESS;
	return comm_wakeup_machine();
}

BOOL WINAPI ExitCommX()
{
	_comm_last_error = E_SUCCESS;
	comm_close();
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_AntipassSend(int nVerifyMode, void *pTemplate, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber)
{
	BYTE RESULT[3] = {0, 0, 0};

	if (nVerifyMode != UI_VERIFY_FP && nVerifyMode != UI_VERIFY_RF)
		return FALSE;

	if (pbDisabled) *pbDisabled = RESULT[0];
	if (pbAdapted)  *pbAdapted = RESULT[1];
	if (pbFingerNumber) *pbFingerNumber = RESULT[2];

	if (!StartCommX(COMM_MODE_SERIAL, dbComm_machineID, dbSetupTotal.setSystem.dwCommPassword, 0, 0))
		return FALSE;
	if (!SendCommandX(CMD_ANTIPASS_SEND) ||
		!RecvAcknCheckX(2000) ||
		!SendDataX(&nVerifyMode, 4) ||
		!SendDataX(pTemplate, (nVerifyMode == UI_VERIFY_FP) ? sizeof(FPINFO) : 4) ||
		!RecvAcknCheckX(2000) ||
		!RecvDataX(pUserInfo, sizeof(USER_INFO), 2000) ||
		!RecvDataX(RESULT, sizeof(RESULT), 2000))
	{
		return FALSE;
	}
	
	if (pbDisabled) *pbDisabled = RESULT[0];
	if (pbAdapted)  *pbAdapted = RESULT[1];
	if (pbFingerNumber) *pbFingerNumber = RESULT[2];

// _lExit:
	ExitCommX();
	return TRUE;
}

/************************************************************************/
/* ARM7 Modules                                                         */
/************************************************************************/

BYTE			gFpPacket[1416];
BYTE                     gFpImage[256*256+12];

//////////////////////////////////////////////////////////////////////////
/*
int comm_GetUserPriv(int nID)
{
	USER_INFO	*pUInfo;

    if(!(pUInfo = (USER_INFO*)DbUserInfoGetPointer(nID)))
		return -1;
*///sb 091125
int comm_GetUserPriv(int nID, USER_INFO *pUInfo = NULL)
{
	if (!pUInfo)
	{
		if(!(pUInfo = (USER_INFO*)DbUserInfoGetPointer(nID)))
			return -1;
	}
////sb 091125
	int nMachinePriv = DbUserInfoFlagManagerGet(pUInfo);

	if(nMachinePriv == PRIV_USER)
		return 0;
	else if(nMachinePriv == PRIV_MGR)
		return 2;
	else if(nMachinePriv == PRIV_SMGR)
		return 1;
	else
		return -1;
}

int comm_OCX2Machine_UserPriv(int nOcxUserPriv)
{
	if(nOcxUserPriv == 0)
		return PRIV_USER;
	else if(nOcxUserPriv == 2 || nOcxUserPriv == 3 || nOcxUserPriv == 4)
		return PRIV_MGR;
	else if(nOcxUserPriv == 1)
		return PRIV_SMGR;
	else
		return 0;
}

//////////////////////////////////////////////////////////////////////////
BOOL arm_comm_send(void* pbuf, int nsize)
{
	BOOL bRet;

//	if (comm_mode != COMM_MODE_UDP) comm_crypt(pbuf, nsize);
	switch (comm_mode)
	{
	case COMM_MODE_SERIAL:
		bRet = (comm_uartsend(comm_sub_mode, pbuf, nsize) == nsize);
		break;
	case COMM_MODE_USB:
		bRet = (comm_usbsend(g_hUSBDevice, pbuf, nsize) == nsize);
		break;
	case COMM_MODE_TCP:
		bRet = (comm_socksend(g_hClientSocks[comm_sub_mode], pbuf, nsize) == nsize);
		break;
	case COMM_MODE_UDP:
		if (dbLicense.byTcpipMode == TCPIP_SERVER)    
			 bRet = (comm_udpsend(0, pbuf, nsize) == nsize);
        else bRet = (comm_tcpclient_send(pbuf, nsize) == nsize);  
		break;
	default:
		bRet = FALSE;
		break;
	}
//	if (comm_mode != COMM_MODE_UDP) comm_crypt(pbuf, nsize);
	return bRet;
}

BOOL arm_comm_recv(void* pbuf, int nsize)
{
	BOOL bRet;

	switch (comm_mode)
	{
	case COMM_MODE_SERIAL:
		bRet = (comm_uartrecv(comm_sub_mode, pbuf, nsize, UART_RECV_TIMEOUT) == nsize);
		break;
	case COMM_MODE_USB:
		bRet = (comm_usbrecv(g_hUSBDevice, pbuf, nsize, USB_RECV_TIMEOUT) == nsize);
		break;
	case COMM_MODE_TCP:
		bRet = (comm_sockrecv(g_hClientSocks[comm_sub_mode], pbuf, nsize, TCP_RECV_TIMEOUT) == nsize);
		break;
	default:
		bRet = FALSE;
		break;
	}

//	if (bRet) comm_crypt(pbuf, nsize);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
int Com_CheckCMD(CMDPKT* pvCMD)
{
	int i;
	BYTE byData[CMDSIZE];
	WORD wChkSum = 0;
	
	memcpy((void*)byData, (void*)pvCMD, CMDSIZE);
	if(byData[0] != STX1)
		return CMD_ANS_NAK;
    	
	if(byData[1] != STX2)
		return CMD_ANS_NAK;

	if(pvCMD->MachineID != DEVID)
		return -5;

	for(i=0;i<CMDSIZE-2;i++)
		wChkSum += byData[i];

	if(pvCMD->ChkSum != wChkSum)
		return CMD_ANS_NAK;

	return CMD_ANS_ACK;
}

BOOL Com_UartGetCMD(int iUART, CMDPKT* pvCMD)
{
//	static int s_retry_counter = 0;
	int s_buffer_cnt;
	HFILE s_handle = g_hUart[iUART];
	BYTE dummy[4];
	BOOL bSetting_COM = FALSE;

	if (s_handle == INVALID_HANDLE_VALUE)
		return FALSE;
	while (TRUE)
	{
		ioctl(s_handle, FIONREAD, &s_buffer_cnt);

		if (cmd_buf_cnt + s_buffer_cnt < (int)STAFF_SIZE)
		{
// 			if (s_retry_counter++ >= 20)
// 			{
// 				read(s_handle, pvCMD, s_buffer_cnt);
// 				s_retry_counter = 0;
// 			}
//			comm_uartclear(iUART);
			return FALSE;
		}

		if (cmd_buf_cnt < 1)
		{
			dummy[0] = 0;
			read(s_handle, &dummy[0], 1);
			cmd_buf[0] = dummy[0];
			cmd_buf_cnt = 1;
		}
		else
		{
			dummy[0] = cmd_buf[0];
		}
//		comm_crypt(&dummy[0], 1);
		if (dummy[0] != STX1)
		{
			comm_crypt(&dummy[0], 1, COMM_PWD_SERIAL);
			if (dummy[0] != STX1){
				comm_crypt(&dummy[0], 1, COMM_PWD_SERIAL);
				goto _lContinue;
			}
			comm_crypt(&dummy[0], 1, COMM_PWD_SERIAL);
		}

		if (cmd_buf_cnt < 2)
		{
			dummy[1] = 0;
			read(s_handle, &dummy[1], 1);
			cmd_buf[1] = dummy[1];
			cmd_buf_cnt = 2;
		}
		else
		{
			dummy[1] = cmd_buf[1];
		}
//		comm_crypt(&dummy[0], 2);
		if (dummy[1] != STX2)
		{
			comm_crypt(&dummy[0], 2, COMM_PWD_SERIAL);
			if (dummy[1] != STX2){
				comm_crypt(&dummy[0], 2, COMM_PWD_SERIAL);
				goto _lContinue;
			}
			else{
				comm_crypt(&dummy[0], 2, COMM_PWD_SERIAL);

				if (dbLicense.byTcpipMode == TCPIP_SERVER)  
		  		    bSetting_COM = TRUE;   
			}
		}

		if(!bSetting_COM)
		{
			if (s_buffer_cnt + cmd_buf_cnt < CMDSIZE)
				return FALSE;
			read(s_handle, &cmd_buf[cmd_buf_cnt], CMDSIZE - cmd_buf_cnt);
			cmd_buf_cnt = CMDSIZE;
			if (Com_CheckCMD((CMDPKT*)cmd_buf))
			{
				memcpy(pvCMD, cmd_buf, CMDSIZE);
				memset(cmd_buf, 0, CMDSIZE);
				cmd_buf_cnt = 0;
				comm_mode = COMM_MODE_SERIAL;
				comm_sub_mode = iUART;
				return TRUE;
			}
		}
		else
		{
			read(s_handle, &cmd_buf[cmd_buf_cnt], STAFF_SIZE - cmd_buf_cnt);
			cmd_buf_cnt = STAFF_SIZE;
			comm_crypt(cmd_buf, STAFF_SIZE, COMM_PWD_SERIAL);
			if (comm_check_cmd((STAFF*)cmd_buf))
			{
				memcpy(pvCMD, cmd_buf, STAFF_SIZE);
				memset(cmd_buf, 0, STAFF_SIZE);
				cmd_buf_cnt = 0;
				comm_mode = COMM_MODE_SERIAL;
				comm_sub_mode = iUART;
				return FALSE;
			}
			comm_crypt(cmd_buf, STAFF_SIZE, COMM_PWD_SERIAL);
		}

		bSetting_COM = FALSE;

_lContinue:
		cmd_buf_cnt--;
		if (cmd_buf_cnt > 0)
			memcpy(&cmd_buf[0], &cmd_buf[1], cmd_buf_cnt);
	}

	return FALSE;
}
BOOL Com_USBGetCMD(HFILE hUsb, CMDPKT* pvCMD)
{
	int nsize = 0;
	if (!hUsb)
		return FALSE;
	ioctl(hUsb, FIONREAD, &nsize);
	if (nsize < (int)STAFF_SIZE)
		return FALSE;

	if (comm_usbrecv(hUsb, pvCMD, CMDSIZE, USB_RECV_CMD_TIMEOUT) == CMDSIZE)
	{
		if (Com_CheckCMD(pvCMD))
		{
			comm_mode = COMM_MODE_USB;
			return TRUE;
		}
	}
	return FALSE;
}
//////////////////////////////////////////////////////////////////////////
BOOL Com_SendCmdAck(WORD wResult)
{
	WORD vSum;
	ACKPKT vACK;

	vACK.Head1 = STX3;			vSum = vACK.Head1;
	vACK.Head2 = STX4;			vSum += vACK.Head2;
	vACK.MachineID = DEVID; 
	vSum += LOBYTE(DEVID);
	vSum += HIBYTE(DEVID);
	vACK.Response = wResult;	vSum += LOBYTE(wResult);vSum += HIBYTE(wResult);
	vACK.ChkSum = vSum;

	if(!arm_comm_send(&vACK, ACKSIZE))
	{
		return FALSE;
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void Com_SendExeResult( WORD wResult, DWORD dwOutParam )
{
	WORD vSum;

	RESULTPKT vRESULT={0, 0, 0, 0, 0, 0, 0};

	vRESULT.Head1 = STX2;			vSum = vRESULT.Head1;
	vRESULT.Head2 = STX1;			vSum += vRESULT.Head2;
	vRESULT.MachineID = DEVID; 
	vSum += LOBYTE(DEVID);
	vSum += HIBYTE(DEVID);
	vRESULT.Ret = wResult;			vSum += LOBYTE(wResult);vSum += HIBYTE(wResult);
	vRESULT.OutParam = dwOutParam;  vSum += LOBYTE(LOWORD(dwOutParam));vSum += LOBYTE(HIWORD(dwOutParam));
	vSum += HIBYTE(LOWORD(dwOutParam));vSum += HIBYTE(HIWORD(dwOutParam));
	vRESULT.ChkSum = vSum; 

	arm_comm_send(&vRESULT, EXERETSIZE);
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_RecData(void* pData, int nsize)
{
	int i;
	WORD CheckSum;
	int RecSize = nsize + 6;
	BYTE*	pRecBuff = (BYTE*)malloc ( RecSize );

	if(!arm_comm_recv(pRecBuff, RecSize) /*
		||
				!comm_recv(&staff, STAFF_SIZE) ||
				!comm_check_csum(&staff) ||
				staff.data != comm_csum(pData, nsize)*/
		)
	{
		free( pRecBuff );
		return FALSE;
	}

	if( pRecBuff[0] != STX3 )
	{
		free( pRecBuff );
		return FALSE;
	}
	CheckSum = pRecBuff[0];

	if( pRecBuff[1] != STX4 )
	{
		free( pRecBuff );
		return FALSE;
	}
	CheckSum += pRecBuff[1];

	if( *(WORD*)(pRecBuff + 2) != (WORD)DEVID )
	{
		free( pRecBuff );
		return FALSE;
	}
	CheckSum += pRecBuff[2];
	CheckSum += pRecBuff[3];

	for ( i = 4; i < RecSize - 2; i++ ){
		CheckSum += pRecBuff[i];
	}

	if( CheckSum != *(WORD*)&pRecBuff[RecSize - 2] )
	{
		free( pRecBuff );
		return FALSE;
	}
	memcpy ( pData, pRecBuff + 4, nsize );
	free( pRecBuff );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_SendData(void* pData, int nsize)
{
	int i;
	WORD CheckSum;
	int SendSize = nsize + 6;
	BYTE*	pSendBuff = (BYTE*)malloc( SendSize );

	pSendBuff[0] = STX4;
	CheckSum = pSendBuff[0];

	pSendBuff[1] = STX3;
	CheckSum += pSendBuff[1];

	*(WORD*)(pSendBuff + 2) = (WORD)DEVID;
	CheckSum += pSendBuff[2];
	CheckSum += pSendBuff[3];

	memcpy( pSendBuff + 4, pData, nsize );
	for ( i = 0; i < nsize; i++ ) CheckSum += pSendBuff[i+4];
	*(WORD*)&pSendBuff[4+nsize] = CheckSum;

	if(!arm_comm_send(pSendBuff, SendSize))
	{
		free( pSendBuff );
		return FALSE;
	}
	free( pSendBuff );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
volatile BOOL g_vbRemain = FALSE;
int Com_RecBigData(void* pData, DWORD dwSize )
{
	int /*nRet,*/ i;
	WORD CheckSum;
	BYTE*	pRecBuff = (BYTE*)malloc (COMM_BLOCK_SIZE+6);
	BYTE*	pPoint = (BYTE*)pData;
	int Bytes, Remain = (int)dwSize;

	if ( pRecBuff == NULL ) return -1;

	Bytes = dwSize;
	while( Remain > 0 )
	{
		if ( Remain > COMM_BLOCK_SIZE )
			Bytes = COMM_BLOCK_SIZE;
		else
			Bytes = Remain;
		if (Remain > Bytes) {
			g_vbRemain = TRUE;
		}
// 		if ( bCommState == 2 ){
// 			for( i=0; i < 1; i++ ){
// 				//				if ( Uart_FindByte ( STX3 ) == 1 ){
// 				nRet = Uart_GetData(0, pRecBuff, Bytes + 6);
// 				if ( nRet != 0 ) break;
// 				//				}
// 			}
// 		}
// 		else if ( bCommState == 3 ){
// 			for( i=0; i < 1000; i++ ){
// 				//				if ( Uart_FindByte ( STX3 ) == 1 ){
// 				nRet = Uart_GetData(1, pRecBuff, Bytes + 6);
// 				if ( nRet != 0 ) break;
// 				//				}
// 			}
// 		}
// 		else if ( bCommState == 1 ){
// 			for( i=0; i <2; i++ ){
// 				nRet = tcp_receiveData(pRecBuff, Bytes + 6 );
// 				if ( nRet != 0 ) break;
// 			}		
// 		}
		
		
		g_vbRemain = FALSE;
		if (!arm_comm_recv(pRecBuff, Bytes + 6)){
			free ( pRecBuff );
			return -1;
		}

		if( pRecBuff[0] != STX3 ) {
			free ( pRecBuff );
			return -1;
		}
		CheckSum = pRecBuff[0];

		if( pRecBuff[1] != STX4 ) {
			free ( pRecBuff );
			return -1;
		}
		CheckSum += pRecBuff[1];

		if( *(WORD*)(pRecBuff + 2) != (WORD)DEVID)
		{
			free( pRecBuff );
			return -1;
		}
		CheckSum += pRecBuff[2];
		CheckSum += pRecBuff[3];

		for ( i = 0; i < Bytes; i++ ){
			CheckSum += pRecBuff[i+4];
		}

		if( CheckSum != *(WORD*)&pRecBuff[Bytes + 4] ){
			free ( pRecBuff );
			return -1;
		}

		memcpy ( pPoint, pRecBuff + 4, Bytes );
		pPoint += Bytes;
		Remain -= Bytes;
	}
	free(pRecBuff);
	return 1;
}

//////////////////////////////////////////////////////////////////////////
int Com_SendBigData(void* pData, DWORD dwSize )
{
//	int nRet;
	DWORD i/*, count = 0*/;
	WORD CheckSum;
	BYTE*	pSendBuff = (BYTE*)malloc(COMM_BLOCK_SIZE+6);
	BYTE*	pPoint = (BYTE*)pData;
	int	Remain = dwSize, Bytes;

	if ( pSendBuff == NULL ) return -1;

	while ( Remain > 0 ){
		if ( Remain > COMM_BLOCK_SIZE )
			Bytes = COMM_BLOCK_SIZE;
		else
			Bytes = Remain;
		
		pSendBuff[0] = STX3;
		CheckSum = pSendBuff[0];

		pSendBuff[1] = STX4;
		CheckSum += pSendBuff[1];

		*(WORD*)(pSendBuff + 2) = (WORD)DEVID;
		CheckSum += pSendBuff[2];
		CheckSum += pSendBuff[3];

		memcpy( pSendBuff + 4, pPoint, Bytes );
		for ( i = 0; i < (DWORD)Bytes; i++ ) CheckSum += (WORD)pSendBuff[i+4];
		*(WORD*)&pSendBuff[4+Bytes] = CheckSum;

		if (!arm_comm_send(pSendBuff, Bytes + 6))
		{
			free(pSendBuff);
			return -1;
		}

		pPoint += Bytes;
		Remain -= Bytes;
	}
	free( pSendBuff );
	return 1;
}

//////////////////////////////////////////////////////////////////////////
DWORD Com_MakeCheckSum(DWORD* pdwBuf, int nSize)
{
	DWORD dwChkSum = 0;
	DWORD* pdwBuf1 = pdwBuf;
	int i;

	for(i=0;i<nSize;i++)
		dwChkSum += *(pdwBuf1+i);
	
	return dwChkSum;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_MakeImage(BYTE* pFpData, int nSize)
{
	DWORD dwChkSum;
	DWORD* pdwBuf = (DWORD*)pFpData;

	dwChkSum = Com_MakeCheckSum(pdwBuf, nSize/4);
	gFpImage[0] = (BYTE)'S';
	gFpImage[1] = (BYTE)'m';
	gFpImage[2] = (BYTE)'a';
	gFpImage[3] = (BYTE)'c';
	gFpImage[4] = (BYTE)'k';
	gFpImage[5] = (BYTE)'B';
	gFpImage[6] = (BYTE)'i';
	gFpImage[7] = (BYTE)'o';
	
	memcpy(&gFpImage[8], (BYTE*)pdwBuf, nSize);
	*((DWORD*)&gFpImage[8+nSize]) = dwChkSum;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_MakePacket(BYTE* pFpData, int nSize)
{
	DWORD dwChkSum;
	DWORD* pdwBuf = (DWORD*)pFpData;

	dwChkSum = Com_MakeCheckSum(pdwBuf, nSize/4);
	gFpPacket[0] = (BYTE)'S';
	gFpPacket[1] = (BYTE)'m';
	gFpPacket[2] = (BYTE)'a';
	gFpPacket[3] = (BYTE)'c';
	gFpPacket[4] = (BYTE)'k';
	gFpPacket[5] = (BYTE)'B';
	gFpPacket[6] = (BYTE)'i';
	gFpPacket[7] = (BYTE)'o';
	
	memcpy(&gFpPacket[8], (BYTE*)pdwBuf, nSize);
	*((DWORD*)&gFpPacket[8+nSize]) = dwChkSum;

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_MakeFpData(void)
{
	DWORD dwChkSum;
	DWORD* pdwBuf = (DWORD*)&gFpPacket[8];

	if(gFpPacket[0] != (BYTE)'S')
		return FALSE;
	if(gFpPacket[1] != (BYTE)'m')
		return FALSE;
	if(gFpPacket[2] != (BYTE)'a')
		return FALSE;
	if(gFpPacket[3] != (BYTE)'c')
		return FALSE;
	if(gFpPacket[4] != (BYTE)'k')
		return FALSE;
	if(gFpPacket[5] != (BYTE)'B')
		return FALSE;
	if(gFpPacket[6] != (BYTE)'i')
		return FALSE;
	if(gFpPacket[7] != (BYTE)'o')
		return FALSE;

	dwChkSum = Com_MakeCheckSum(pdwBuf, 1404/4);
	if(dwChkSum != *((DWORD*)&gFpPacket[8+1404]))
		return FALSE;

	memcpy(gFpData, &gFpPacket[8], 1404);
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
BOOL ComGetEnrollDataFP ( CMDPKT* pCMD )
{
	int nID, nFP;
	FPINFO* pFPinfo;

	//nID = pCMD->Length & 0xFFFFFFF;
	//nFP = pCMD->Length >> 28;
	nID = pCMD->Length;
	nFP = pCMD->InParam>> 8;

	if ( nID < 1 || nID > MAX_ID || nFP < BACKUP_FINGER0 || nFP > BACKUP_FINGER9)
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	pFPinfo = (FPINFO*)DbUserInfoGetPointer(nID, nFP);
	
	if ( pFPinfo )
	{
		int nUserPriv = comm_GetUserPriv(nID);
		if(nUserPriv == -1){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		Com_SendExeResult( EXE_RES_TRUE, nUserPriv);
		
		Com_MakePacket((BYTE*)pFPinfo, sizeof(FPINFO));
		
		if ( Com_SendBigData(gFpPacket, sizeof(FPINFO) + 12) == -1 )
			return FALSE;

		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGetEnrollDataPWD ( CMDPKT* pCMD )
{
//	int i;
	DWORD /*dwPwd = 0, */dwPwd2 = 0;
//	char buf[16];
	void* pData;
//	PASSWORD_DATA* pPWD;

	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	pData = DbUserInfoGetPointer(pCMD->Length, BACKUP_PASSWORD);
	if (pData)
	{
		int nUserPriv = comm_GetUserPriv(pCMD->Length);
		if(nUserPriv == -1){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		Com_SendExeResult( EXE_RES_TRUE, nUserPriv);

		dwPwd2 = atoi((char*)PWD2STRING(*(DWORD*)pData));

		Com_SendData( &dwPwd2, 4 );
		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGetEnrollDataCARD ( CMDPKT* pCMD )
{
	DWORD dwCard = 0;
//	CARD_DATA* pCARD;
	void* pData;

	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	pData = DbUserInfoGetPointer(pCMD->Length, BACKUP_CARD);

	if ( pData )
	{
		int nUserPriv = comm_GetUserPriv(pCMD->Length);
		if(nUserPriv == -1){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		Com_SendExeResult( EXE_RES_TRUE, nUserPriv);

		dwCard = *(DWORD*)(pData);
		Com_SendData( &dwCard, 4 );
		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSetEnrollDataFP( CMDPKT* pCMD )
{
	int nID, nFP;

	//nID = pCMD->Length & 0xFFFFFFF;
	//nFP = pCMD->Length >> 28;
	nID = pCMD->Length;
	nFP = pCMD->InParam>> 8;
	
	if ( nID < 1 || nID > MAX_ID || nFP < BACKUP_FINGER0 || nFP > BACKUP_FINGER9 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	//Delay( 500 );
	if ( Com_RecBigData( gFpPacket, sizeof(FPINFO) + 12 ) == -1 ||
		Com_MakeFpData() == FALSE)
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	gUserInfoTemp.ID = nID;

	BYTE nUserPriv = (BYTE)comm_OCX2Machine_UserPriv((pCMD->InParam&0xf0)>> 4);
	if(nUserPriv == 0){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}   
	gUserInfoTemp.FLAG.members.byMgr = nUserPriv;
	if (!DbUserInfoEnroll(&gUserInfoTemp, nFP, gFpData, TRUE, FALSE))
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}   

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSetEnrollDataPWD ( CMDPKT* pCMD )
{
	DWORD dwPwd = 0;

	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	//Delay( 500 );
	if ( Com_RecData( &dwPwd, 4 ) == FALSE )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}
	
	char buf[16];
	sprintf(buf, "%d", dwPwd);
	dwPwd = STRING2PWD(buf);

	if(dwPwd == 0){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	gUserInfoTemp.ID = pCMD->Length;
	BYTE nUserPriv = (BYTE)comm_OCX2Machine_UserPriv((pCMD->InParam&0xf0)>> 4);
	if(nUserPriv == 0){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	gUserInfoTemp.FLAG.members.byMgr = nUserPriv;
	if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_PASSWORD, &dwPwd))
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}  

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSetEnrollDataCARD ( CMDPKT* pCMD )
{
	DWORD dwCard = 0;

	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}
	
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	//Delay( 500 );
	if ( Com_RecData( &dwCard, 4 ) == FALSE )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	gUserInfoTemp.ID = pCMD->Length;
	BYTE nUserPriv = (BYTE)comm_OCX2Machine_UserPriv((pCMD->InParam&0xf0) >> 4);
	if(nUserPriv == 0){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	gUserInfoTemp.FLAG.members.byMgr = nUserPriv;
	if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_CARD, &dwCard))
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}  

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeleteEnrollDataFP ( CMDPKT* pCMD )
{
	int nID, nFP;

	//nID = pCMD->Length & 0xFFFFFFF;
	//nFP = pCMD->Length >> 28;
	nID = pCMD->Length;
	nFP = pCMD->InParam>> 8;
	
	if ( nID < 1 || nID > MAX_ID || nFP < BACKUP_FINGER0 || nFP > BACKUP_FINGER9 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	if(DbUserInfoDelete(nID, 0x01 << nFP))
	{
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeleteEnrollDataPWD ( CMDPKT* pCMD )
{
	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	if(DbUserInfoDelete(pCMD->Length, 0x01 << BACKUP_PASSWORD))
	{
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeleteEnrollDataCARD ( CMDPKT* pCMD )
{
	if ( pCMD->Length < 1 || pCMD->Length > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	if(DbUserInfoDelete(pCMD->Length, 0x01 << BACKUP_CARD))
	{
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		return TRUE;
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeleteEnrollDataAllFP ( CMDPKT* pCMD )
{
	int nID = (int)pCMD->Length;
	int nBackup = 0;

	if ( nID < 1 || nID > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	for (int i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
		nBackup |= (0x01 << i);

	DbUserInfoDelete(nID, nBackup);

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeleteEnrollDataAll ( CMDPKT* pCMD )
{
	int nID = (int)pCMD->Length;

	if ( nID < 1 || nID > MAX_ID )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	DbUserInfoDelete(nID, 0xFFFF);
	
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSlogGetCount(void)
{
	Com_SendExeResult( EXE_RES_TRUE, DbSLogCountAll());
	int nSLogReadCnt = DbSLogGetReadPos();
	Com_SendData(&nSLogReadCnt, 4);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSlogGet ( CMDPKT* pCMD )
{
	WORD count;
	int SendCount;//, nRecvSendCount;

	count = DbSLogCountAll();
	if ( pCMD->InParam == 0 )
	{
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)count );
	}
	else
	{
		if ( pCMD->InParam - 1 > count || pCMD->InParam < 1 )
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if ( pCMD->Length + pCMD->InParam - 1 > count )
			SendCount = count - pCMD->InParam - 1;
		else
			SendCount = pCMD->Length;
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)SendCount );

		MLOG_INFO* pLogs = (MLOG_INFO*)malloc(sizeof(MLOG_INFO) * (SendCount + 1));
		if(!pLogs){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if(!DbSLogGet(pLogs, pCMD->InParam - 1, SendCount)){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		ARM_MLOG_INFO* pLogs_ARM = (ARM_MLOG_INFO*)malloc(sizeof(ARM_MLOG_INFO) * (SendCount + 1));
		if(!pLogs_ARM){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		int i;
		DWORD _convSlog[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 11, 1, 2, 3, 0xFF, 7, 8, 9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 12, 0xFF, 10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		for(i = 0; i < SendCount; i++){
			pLogs_ARM[i].dwSeconds = pLogs[i].dwSeconds;
			pLogs_ARM[i].wSid = pLogs[i].nManagerID;
			pLogs_ARM[i].wId = pLogs[i].nUserID;
			//pLogs_ARM[i].byAction = _convSlog[pLogs[i].byAction];
			//pLogs_ARM[i].bySubid = 0;
			pLogs_ARM[i].byAction = pLogs[i].byAction;
			pLogs_ARM[i].bySubid =pLogs[i].byResult;			
		}

		if(Com_SendBigData( (void*)pLogs_ARM, sizeof(ARM_MLOG_INFO)*SendCount ) == -1){
			free(pLogs_ARM);
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		free(pLogs_ARM);
		free(pLogs);


		DbSLogSetReadPos((pCMD->InParam + SendCount) % dbLicense.nSlogMaxCount);
		DbSetupTotalWrite();
		//	dbSetupTotal.setNoMenu.nReadMLogCount = count;   //xingfu070424
		//	DbSetupTotalWrite();                             //xingfu070424
// 		nReMLogCount = count;                            //xingfu070424
// 		nCurrentCmd = CMD_SLOG_GET;                      //xingfu070424
		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGlogGetCount(void)
{
	Com_SendExeResult( EXE_RES_TRUE, DbGLogCountAll() );
	int nGLogReadCnt = DbGLogGetReadPos();
	Com_SendData(&nGLogReadCnt, 4);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGlogGet ( CMDPKT* pCMD )
{
	DWORD count;
	int SendCount;//, nRecvSendCount;
	DWORD LogIndex;

	count = DbGLogCountAll();
	if ( pCMD->InParam == 0 )
	{
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)count );
	}
	else
	{
		if(Com_RecData(&LogIndex, 4) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		
		if ( LogIndex - 1 > count || LogIndex < 1 )
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if ( pCMD->Length + LogIndex - 1 > count )
			SendCount = count - LogIndex - 1;
		else
			SendCount = pCMD->Length;
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)SendCount );

		ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (SendCount + 1));
		if(!pLogs){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if(!DbGLogGet(pLogs, LogIndex - 1, SendCount)){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		ARM_ALOG_INFO* pLogs_ARM = (ARM_ALOG_INFO*)malloc(sizeof(ARM_ALOG_INFO) * SendCount);
		if(!pLogs_ARM){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		int i;
		DWORD _convGlog[] = {0xCF, 0xCF, 1, 0xCF, 3, 0xCF, 2, 0xCF, 0xCF, 0xCF};
		for(i = 0; i < SendCount; i++){
			pLogs_ARM[i].dwSeconds = pLogs[i].dwSeconds;
			pLogs_ARM[i].wId = (DWORD)pLogs[i].nID;
			pLogs_ARM[i].byAction = _convGlog[pLogs[i].byAction];
		}

		if(Com_SendBigData( (void*)pLogs_ARM, sizeof(ARM_ALOG_INFO)*SendCount ) == -1){
			free(pLogs_ARM);
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		free(pLogs_ARM);
		free(pLogs);

		DbGLogSetReadPos((LogIndex + SendCount) % dbLicense.nGlogMaxCount);
		//	dbSetupTotal.setNoMenu.nReadALogCount = count;  //xingfu070424
		//	DbSetupTotalWrite();                            //xingfu070424
// 		nReALogCount = count;                           //xingfu070424
// 		nCurrentCmd = CMD_GLOG_GET;                      //xingfu070424

		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSlogGetByTime ( CMDPKT* pCMD )
{
	DWORD count;
	int SendCount,pos;//, nRecvSendCount;
	DWORD LogIndex[3];

	count = DbGLogCountAll();
	if ( pCMD->InParam == 0 )
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		pos=DbSLogPosGetByTime(0,  count, LogIndex[1], LogIndex[2]);
		//Com_SendExeResult( pos, count-pos);	
		Com_SendExeResult( EXE_RES_TRUE, pos );
		Com_SendExeResult( EXE_RES_TRUE, count-pos );
	}
	else
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		if ( LogIndex[0] - 1 > count || LogIndex[0] < 1 )
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if ( pCMD->Length + LogIndex[0] - 1 > count )
			SendCount = count - LogIndex[0] - 1;
		else
			SendCount = pCMD->Length;

		MLOG_INFO *pLogs = (MLOG_INFO*)malloc(sizeof(MLOG_INFO) * (SendCount + 1));
		if(!pLogs){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if(!(SendCount=DbSLogGetByTime(pLogs,  LogIndex[0] - 1, LogIndex[0] - 1 + SendCount,LogIndex[1], LogIndex[2]))){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)SendCount );

		ARM_MLOG_INFO* pLogs_ARM = (ARM_MLOG_INFO*)malloc(sizeof(ARM_MLOG_INFO) * SendCount);
		if(!pLogs_ARM){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		int i;
		DWORD _convSlog[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 11, 1, 2, 3, 0xFF, 7, 8, 9, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 12, 0xFF, 10, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
		for(i = 0; i < SendCount; i++){
			pLogs_ARM[i].dwSeconds = pLogs[i].dwSeconds;
			pLogs_ARM[i].wSid = pLogs[i].nManagerID;
			pLogs_ARM[i].wId = pLogs[i].nUserID;
			//pLogs_ARM[i].byAction = _convSlog[pLogs[i].byAction];
			//pLogs_ARM[i].bySubid = 0;
			pLogs_ARM[i].byAction = pLogs[i].byAction;
			pLogs_ARM[i].bySubid =pLogs[i].byResult;			
		}

		if(Com_SendBigData( (void*)pLogs_ARM, sizeof(ARM_MLOG_INFO)*SendCount ) == -1){
			free(pLogs_ARM);
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		free(pLogs_ARM);
		free(pLogs);


		//DbSLogSetReadPos((LogIndex + SendCount) % dbLicense.nGlogMaxCount);
		//	dbSetupTotal.setNoMenu.nReadALogCount = count;  //xingfu070424
		//	DbSetupTotalWrite();                            //xingfu070424
// 		nReALogCount = count;                           //xingfu070424
// 		nCurrentCmd = CMD_GLOG_GET;                      //xingfu070424

		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGlogGetByTime ( CMDPKT* pCMD )
{
	DWORD count;
	int SendCount;//, nRecvSendCount;
	DWORD LogIndex[3],dwSeconds;
	int pos;

	count = DbGLogCountAll();
	if ( pCMD->InParam == 0 )
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		pos=DbGLogPosGetByTime(0,  count, LogIndex[1], LogIndex[2]);
		count=DbGLogCountGetByTime(pos,  count, LogIndex[1], LogIndex[2]);

		int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;


		uiRtcSeconds2YMDHMS(LogIndex[1],&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		uiRtcSeconds2YMDHMS(LogIndex[2],&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
           if(LogIndex[1]>=LogIndex[2]||count-pos<0)
	   	{
		    Com_SendExeResult( EXE_RES_FALSE, 0 );
	   	    return FALSE;
	   	}
		Com_SendExeResult( EXE_RES_TRUE, pos );
		Com_SendExeResult( EXE_RES_TRUE, count-pos );	

	}
	else
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		if ( LogIndex[0] - 1 > count || LogIndex[0] < 1 )
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if ( pCMD->Length + LogIndex[0] - 1 > count )
			SendCount = count - LogIndex[0] - 1;
		else
			SendCount = pCMD->Length;

		ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (SendCount + 1));
		if(!pLogs){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if(!(SendCount=DbGLogGetByTime(pLogs,  LogIndex[0] - 1, LogIndex[0] - 1 + SendCount,LogIndex[1], LogIndex[2]))){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)SendCount );

		ARM_ALOG_INFO* pLogs_ARM = (ARM_ALOG_INFO*)malloc(sizeof(ARM_ALOG_INFO) * SendCount);
		if(!pLogs_ARM){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		int i;
		DWORD _convGlog[] = {0xCF, 0xCF, 1, 0xCF, 3, 0xCF, 2, 0xCF, 0xCF, 0xCF};
		for(i = 0; i < SendCount; i++){
			pLogs_ARM[i].dwSeconds = pLogs[i].dwSeconds;
			pLogs_ARM[i].wId = (DWORD)pLogs[i].nID;
			pLogs_ARM[i].byAction = _convGlog[pLogs[i].byAction];
		}
		if(Com_SendBigData( (void*)pLogs_ARM, sizeof(ARM_ALOG_INFO)*SendCount ) == -1){
			free(pLogs_ARM);
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		free(pLogs_ARM);
		free(pLogs);
		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

int pos_allSearch=0;
DWORD fromtime=0;
DWORD totime=0;
//////////////////////////////////////////////////////////////////////////
BOOL ComGlogGetByTime_allsearch ( CMDPKT* pCMD )
{
	DWORD count;
	int SendCount;//, nRecvSendCount;
	DWORD LogIndex[3],dwSeconds;
	int pos;



	if ( pCMD->InParam == 0 )
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );

			return FALSE;
		}


   
		pos=DbGLogPosGetByTime(0,  count, LogIndex[1], LogIndex[2]);
		count=DbGLogCountGetByTimeAllSearch(LogIndex[1], LogIndex[2]);
		

		int nYear,  nMonth,  nDay, nHour, nMinute,  nSecond;


		uiRtcSeconds2YMDHMS(LogIndex[1],&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

		uiRtcSeconds2YMDHMS(LogIndex[2],&nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

           if(LogIndex[1]>=LogIndex[2]||count<0)
	   	{
		    Com_SendExeResult( EXE_RES_FALSE, 0 );
	   	    return FALSE;
	   	}
		
	   	 
		pos_allSearch=0;	
		fromtime=LogIndex[1];
		totime=LogIndex[2];
		Com_SendExeResult( EXE_RES_TRUE, pos );
		Com_SendExeResult( EXE_RES_TRUE, count);
	}
	else
	{
		if(Com_RecData(&LogIndex, 12) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}


			SendCount = pCMD->Length;
		ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (SendCount + 1));
		if(!pLogs){
			
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		

		if(!(SendCount=DbGLogGetByTimeAllSearch(pLogs ,pos_allSearch, LogIndex[0] - 1 + SendCount,fromtime,totime,SendCount)))
		{
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)SendCount );

		ARM_ALOG_INFO* pLogs_ARM = (ARM_ALOG_INFO*)malloc(sizeof(ARM_ALOG_INFO) * SendCount);
		if(!pLogs_ARM){
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		int i;
		DWORD _convGlog[] = {0xCF, 0xCF, 1, 0xCF, 3, 0xCF, 2, 0xCF, 0xCF, 0xCF};
		for(i = 0; i < SendCount; i++){
			pLogs_ARM[i].dwSeconds = pLogs[i].dwSeconds;
			pLogs_ARM[i].wId = (DWORD)pLogs[i].nID;
			pLogs_ARM[i].byAction = _convGlog[pLogs[i].byAction];
		}

		if(Com_SendBigData( (void*)pLogs_ARM, sizeof(ARM_ALOG_INFO)*SendCount ) == -1){
			free(pLogs_ARM);
			free(pLogs);
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		free(pLogs_ARM);
		free(pLogs);

		//DbGLogSetReadPos((LogIndex + SendCount) % dbLicense.nGlogMaxCount);
		//	dbSetupTotal.setNoMenu.nReadALogCount = count;  //xingfu070424
		//	DbSetupTotalWrite();                            //xingfu070424
// 		nReALogCount = count;                           //xingfu070424
// 		nCurrentCmd = CMD_GLOG_GET;                      //xingfu070424

		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComEnrollNumberHeadListGet ( CMDPKT* pCMD )
{
	DWORD count;
	int SendCount;//, nRecvSendCount;
	DWORD LogIndex;

	count = GetDbUserIdHeadListCountAll();
	//if ( pCMD->InParam == 0 )
	{
		if(count==0)
		{
		   Com_SendExeResult( EXE_RES_FALSE, 0 );
		   return FALSE;
		}

		Com_SendExeResult( EXE_RES_TRUE, (DWORD)count );

		if(Com_SendBigData( (void*)gpUserIdHeadData, sizeof(st_HeadString)*count ) == -1){

			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}
		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComEnrollNumberHeadListSet ( CMDPKT* pCMD )
{
	DWORD count;
	DWORD LogIndex;
	int i;
    
	if ( pCMD->Length<=MaxIdHeadListCount)
	{
        count=pCMD->Length;
		xprintf("count=%d \r\n", count);
		st_HeadString *pData = (st_HeadString*)malloc(sizeof(st_HeadString) * (count + 1));
		if(!pData){
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			return FALSE;
		}

		if ( Com_RecBigData((void*)pData, sizeof(st_HeadString)*count) == -1 ){   
			free(pData);
			Com_SendExeResult( EXE_RES_FALSE, -3 );
			return FALSE;
		}
		for(i=0;i<count;i++)
		   xprintf("Index=%d Letter=%s \r\n", pData[i].Index,pData[i].Letter);		
		memset(gpUserIdHeadData, 0, sizeof(st_HeadString)*MaxIdHeadListCount);
		memcpy(gpUserIdHeadData,pData,sizeof(st_HeadString)*count);
		DbUserIdHeadListSave();
		free(pData);
		Com_SendExeResult( EXE_RES_TRUE, 0);
	}
	return TRUE;
}



//////////////////////////////////////////////////////////////////////////
BOOL ComDeviceStatusGet(CMDPKT *vCMD)
{
	int nTemp;

	switch( vCMD->InParam ) 
	{
	case 1://ManagerCount
		nTemp = Db_GetManagerCountTotal();
		break;
	case 2://UserCount
		nTemp = Db_GetUserCount();
		break;
	case 3://FpCount
		nTemp = DbUserInfoGetCount(BACKUP_FINGER);
		break;
	case 4://PwdCount
		nTemp = DbUserInfoGetCount(BACKUP_PASSWORD);
		break;
	case 5://NewMLogCount
		nTemp = DbSLogCountAll() - DbSLogGetReadPos(); 
		break;
	case 6://NewALogCount
		nTemp = DbGLogCountAll() - DbGLogGetReadPos(); 
		break;
	case 7://CardCount
		nTemp = DbUserInfoGetCount(BACKUP_CARD);
		break;
	case 8://User Log Read Position
		nTemp = DbGLogCountAll();
		break;
	case 9://Manager Log Read Postion
		nTemp = DbSLogCountAll() ;
		break;
	default:
		Com_SendExeResult( EXE_RES_FALSE,  0);
		return FALSE;
	}
	
	Com_SendExeResult( EXE_RES_TRUE, nTemp);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeviceInfoGet(CMDPKT *vCMD)
{
	switch( vCMD->InParam ) 
	{
	case 1://ManagerLimit
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nManagersNumber );
		break;
	case 2://MachineID
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nMachineID);
		break;
	case 3://LanguageMode
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nLanguage);
		break;
	case 4://AutoPowerOffTime
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nIdletimeForPoweroff );
		break;
	case 5://LockMode
		Com_SendExeResult( EXE_RES_FALSE, dbSetupTotal.setSystem.nLockTime );
		break;
	case 6://ALogAlarm
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nGLogWarning);
		break;
	case 7://MLogAlarm
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nMLogWarning );
		break;
	case 8://ReverifyTime
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nReverifyTime );
		break;
	case 9://Baudrate
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nBaudrate + 3 );
		break;
	case 10://parity
		Com_SendExeResult( EXE_RES_TRUE, 0);
		break;
	case 11://Stop
		Com_SendExeResult( EXE_RES_TRUE, 8 );
		break;
	case 12://sign
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nDateFormat );
		break;
	case 13://Identification mode
		Com_SendExeResult( EXE_RES_TRUE, VERIFYMODE2INDEX(dbSetupTotal.setSystem.nVerifyMode) );
		break;
    case 14://real time space
		Com_SendExeResult( EXE_RES_TRUE, dbSetupTotal.setSystem.nRealSpaceTime );
	default:
		Com_SendExeResult( EXE_RES_FALSE,  0);
		return FALSE;
	}
	
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeviceInfoSet(CMDPKT *vCMD)
{
	int nRet = 0;

	switch( vCMD->InParam ) 
	{
	case 1://ManagerLimit
		nRet = (MAX(1, Db_GetManagerCountMax()) <= (int)vCMD->Length && vCMD->Length <= MAX_MGR_COUNT);
		if (nRet) dbSetupTotal.setSystem.nManagersNumber = vCMD->Length;
		break;
	case 2://MachineID
		Com_SendExeResult( EXE_RES_TRUE,  0);

		nRet = (1 <= vCMD->Length && vCMD->Length <= 255);
		if (nRet) dbSetupTotal.setSystem.nMachineID = vCMD->Length;

		DbSetupTotalWrite();
		return TRUE;
		break;
	case 3://LanguageMode
		nRet = (vCMD->Length < UILANG_CNT);
		if (nRet) dbSetupTotal.setSystem.nLanguage = vCMD->Length;
		break;
	case 4://AutoPowerOffTime
		nRet = (vCMD->Length < 24 * 3600);
		if (nRet) dbSetupTotal.setSystem.nIdletimeForPoweroff = vCMD->Length;
		break;
	case 5://LockMode
// 		nRet = (vCMD->Length <= 10);
// 		if (nRet) dbSetupTotal.setSystem.nLockTime = vCMD->Length;
		Com_SendExeResult( EXE_RES_FALSE,  0);
		return FALSE;
		break;
	case 6://ALogAlarm
		nRet = (vCMD->Length <= 1000);
		if (nRet) dbSetupTotal.setSystem.nGLogWarning = vCMD->Length;
		break;
	case 7://MLogAlarm
		nRet = (vCMD->Length <= 100);
		if (nRet) dbSetupTotal.setSystem.nMLogWarning = vCMD->Length;
		break;
	case 8://ReverifyTime
		nRet = (vCMD->Length <= 255);
		if (nRet) dbSetupTotal.setSystem.nReverifyTime = vCMD->Length;
		break;
	case 9://Baudrate
		nRet = (vCMD->Length - 3 <= BAUDRATE_115200);
		if (nRet) dbSetupTotal.setSystem.nBaudrate = vCMD->Length - 3;
		break;
	case 10://parity
		break;
	case 11://Stop
		break;
	case 12://Time Format
		nRet = (vCMD->Length < TIME_FORMAT_COUNT);
		if (nRet) dbSetupTotal.setSystem.nDateFormat = vCMD->Length;
		break;
	case 13://Identification mode
		nRet = INDEX2VERIFYMODE(vCMD->Length);
		if(nRet != -1){
//			dbSetupTotal.setSystem.byDefaultGVM = VM_NONE;
			dbSetupTotal.setSystem.nVerifyMode = nRet;
		}
		break;
    case 14://real time space
		nRet = (vCMD->Length <= 255);
		if (nRet) dbSetupTotal.setSystem.nRealSpaceTime = vCMD->Length;
		break;
	default:
		Com_SendExeResult( EXE_RES_FALSE,  0);
		return FALSE;
	}

	if (nRet)
	{
		DbSetupTotalWrite();
		Com_SendExeResult( EXE_RES_TRUE,  0);
	}
	else
		Com_SendExeResult( EXE_RES_FALSE, 0);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComEnableUser(CMDPKT *vCMD)
{
	int ID;
//	int nBackupNumber;
	int nRet = FALSE;

	ID = (vCMD->Length & 0xFFFFFFF);
//	nBackupNumber = (vCMD->Length >> 28);
	int nPos = DbUserInfoGetPosition(ID);
	DbUserInfoEnable(nPos, vCMD->InParam);
	Com_SendExeResult( TRUE, 0 );
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDeviceTimeGetSet ( CMDPKT* pCMD )
{
	DWORD dwSeconds;
	BOOL ret;

	if ( pCMD->Command == ARM_CMD_DEVICE_TIME_GET )
	{
		dwSeconds = uiRtcGetSeconds();

		Com_SendData( (void*)&dwSeconds, pCMD->Length );
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		return TRUE;
	}

	if ( pCMD->Command == ARM_CMD_DEVICE_TIME_SET )
	{
		ret = Com_RecData( (void*)&dwSeconds, pCMD->Length );
		
		if ( ret != 1 )
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
		}
		else
		{
			uiRtcSetSeconds(dwSeconds);
			Com_SendExeResult( EXE_RES_TRUE, 0 );
		}
	}

	return ret;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComPowerOff(void)
{
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	uiPowerSetStatus(UI_POWER_OFF, 1);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComModifyPrivilege(CMDPKT *vCMD)
{
	int ID;
	int nBackupNumber;
	int nRet = 0;

	ID = vCMD->Length;
	nBackupNumber = (vCMD->InParam>>8)&0xff;

	BYTE nUserPriv = (BYTE)comm_OCX2Machine_UserPriv(vCMD->InParam&0xff);
	if(nUserPriv == 0){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	if(	DbUserInfoSetPrivilege(ID, nUserPriv))
		 Com_SendExeResult( EXE_RES_TRUE, 0 );
	else Com_SendExeResult( EXE_RES_FALSE, 0 );
	return nRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComReadAllUserID(CMDPKT *vCMD)
{
	unsigned short count;
	int SendCount;
	EnrollUserID *EnrollUserIDBuffer = NULL;

	count = Db_GetUserCount();
	if ( vCMD->InParam == 0 ){
		Com_SendExeResult( EXE_RES_TRUE, (DWORD)count );
	}
	else {
		if ( vCMD->InParam > count || vCMD->InParam < 1 )
			return FALSE;
		if ( vCMD->Length + vCMD->InParam - 1 > count )
			SendCount = count - vCMD->InParam + 1;
		else
			SendCount = vCMD->Length;
//		Com_GetAllUserID();
		WORD i, j, k;
		USER_INFO *pUserInfo;

		EnrollUserIDBuffer = new EnrollUserID[dbLicense.nMaxEnrollCount * 3];
		if (!EnrollUserIDBuffer)
			return FALSE;

		j = 0;
		for (i=0; i<dbLicense.nMaxEnrollCount; i++)
		{
			pUserInfo = &gpUserInfoEnrollData[i];
			if (pUserInfo->ID == 0)
				continue;

			for (k=BACKUP_START; k<=BACKUP_END; k++)
			{
				if (DbUserInfoFlagEnrollStatusGet(pUserInfo, k))
				{
					EnrollUserIDBuffer[j].ID = pUserInfo->ID;
					EnrollUserIDBuffer[j].EMachineNumber = DEVID;

					EnrollUserIDBuffer[j].BackupNumber = k;
				//	EnrollUserIDBuffer[j].MachinePrivilege = comm_GetUserPriv(pUserInfo->ID);  //sb 091125
					EnrollUserIDBuffer[j].MachinePrivilege = comm_GetUserPriv(pUserInfo->ID, pUserInfo);   //sb 091125
					EnrollUserIDBuffer[j].Enable = DbUserInfoFlagDisableStatusGet(pUserInfo)/*((gpOptionData[i] & 1) == 0) ? 0 : 1*/;	//1:disable
					j++;
				}
			}
		}

		Com_SendExeResult( EXE_RES_TRUE, (DWORD)j );

		if(Com_SendBigData( (void*)&EnrollUserIDBuffer[vCMD->InParam-1], sizeof(EnrollUserID)*(j) ) == -1)
		{
			DELETE(EnrollUserIDBuffer);
			return FALSE;
		}
		DELETE(EnrollUserIDBuffer);
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSerialNumGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	Com_SendData(&dbLicense.szSerialNumber[0], sizeof(dbLicense.szSerialNumber));
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComClearKeeperData(void)
{
	Db_DeleteAllEnrollData();
	Db_DeleteAllLogData();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComBackupNumGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, dbLicense.nBackupNumber );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComProductCodeGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	Com_SendData(&dbLicense.szProductName[0], sizeof(dbLicense.szProductName));
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComEnrollDataEmpty(void)
{
	Db_DeleteAllEnrollData();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGlogEmpty(void)
{
	BOOL nRet;
	
	nRet = DbGLogDeleteAll();
	Com_SendExeResult( nRet, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComSlogEmpty(void)
{
	BOOL nRet;

	nRet = DbSLogDeleteAll();
	Com_SendExeResult( nRet, 0 );
	return TRUE;
}

////////////////xingfu070125
BOOL ComPassSerialNumGet(void)
{
	char szPassSerialNumber[32];
	int szBuffer, szBuffer1, szBuffer2;
	int i;

	memset(&szPassSerialNumber[0], 0, sizeof(szPassSerialNumber));
	for(i=0; i<6; i++)szPassSerialNumber[i]=dbLicense.szSerialNumber[i];
	szBuffer1= atoi(szPassSerialNumber);
	memset(&szPassSerialNumber[0], 0, sizeof(szPassSerialNumber));
	for(i=0; i<5; i++)szPassSerialNumber[i]=dbLicense.szSerialNumber[i+6];
	szBuffer2= atoi(szPassSerialNumber);

	memset(&szPassSerialNumber[0], 0, sizeof(szPassSerialNumber));
	szBuffer = (( szBuffer1 ^ 0xefd59) | szBuffer2 ) + (( szBuffer2 | 0x132cc) ^ szBuffer1 );
	sprintf(szPassSerialNumber,"%7d",szBuffer);

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	Com_SendData(&szPassSerialNumber[0], sizeof(szPassSerialNumber));
	return TRUE;

}

//////////////////////////////////////////////////////////////////////////
BOOL ComUserNameGet(CMDPKT *vCMD)
{
	USER_INFO	*pUInfo;
	pUInfo = (USER_INFO*)DbUserInfoGetPointer(vCMD->Length);
	if(!pUInfo){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	Com_SendExeResult( EXE_RES_TRUE, 0 );
    char szUserName[24];
	memcpy(szUserName, pUInfo->NAME, 24);      
	Com_SendData((void *)szUserName, 24); 

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////


BOOL ComUserNameSet(void)
{
	PACKED_NAME_INFO packed_name_info;

   	 if ( Com_RecBigData((void*)&packed_name_info, sizeof(packed_name_info)) == -1 )
	 {   
		Com_SendExeResult( EXE_RES_FALSE, -3 );
		return FALSE;
	 }   
	
	USER_INFO	*pUInfo;
	int nPos, nPos1;
	int NearestPos;
	pUInfo = (USER_INFO*)DbUserInfoGetPointer(packed_name_info.wId);
	if(!pUInfo){
					  
		nPos = DbUserInfoGetUnusedPosition();

		gpUserInfoEnrollData[nPos].ID = packed_name_info.wId;
              	memcpy(gpUserInfoEnrollData[nPos].NAME, packed_name_info.NameA, 24); 
			  
		DbUserInfoFlagManagerSet(&gpUserInfoEnrollData[nPos], PRIV_USER);

		DbUserInfoSaveOne(nPos);

		nPos1 = DbUserInfoGetNearestPosition(packed_name_info.wId, &NearestPos);
		if (nPos1 < 0)
		{
			for (int k=dbLicense.nMaxEnrollCount-1; k>NearestPos; k--)
				gpUIIndexData[k] = gpUIIndexData[k-1];
			gpUIIndexData[NearestPos] = nPos;
		}
		DbUIIndexSave();
	
	}
	else
	{
		memcpy(&gUserInfoTemp, pUInfo, sizeof(USER_INFO));
    		memcpy(gUserInfoTemp.NAME, packed_name_info.NameA, 24);                        

		if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_ALL, NULL))
		{
			Com_SendExeResult( EXE_RES_FALSE, -2 );
			return FALSE;
		}
	}
	////////

	Com_SendExeResult( EXE_RES_TRUE, 3 );
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComCompanyNameGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	Com_SendData(&dbSetupTotal.setNoMenu.szCompanyNamy[0],
		sizeof(dbSetupTotal.setNoMenu.szCompanyNamy));

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	WORD wCompanyNameDisplay;
	char szCompanyNamy[22];
	BYTE pbyCompanyNameData[240];
} PACKED_COMPANY_NAME;

BOOL ComCompanyNameSet(void)
{
	PACKED_COMPANY_NAME packed_company_name;

	if ( Com_RecBigData((void*)&packed_company_name, sizeof(PACKED_COMPANY_NAME)) == -1 ){
		Com_SendExeResult( EXE_RES_FALSE, -3 );
		return FALSE;
	}

	memcpy(&dbSetupTotal.setNoMenu.szCompanyNamy[0],
		(void*)&packed_company_name.szCompanyNamy[0], sizeof(dbSetupTotal.setNoMenu.szCompanyNamy));

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 3 );
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDoorStatusGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, __DOOR_STATUS[dbSetupTotal.setNoMenu.byDoorStatus] );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDoorStatusSet(CMDPKT *vCMD)
{
	int i;

	for (i=0; i<(int)ITEM_CNT(__DOOR_STATUS); i++)
	{
		if (__DOOR_STATUS[i] == (int)vCMD->InParam)
			break;
	}
	if (i == ITEM_CNT(__DOOR_STATUS))
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	dbSetupTotal.setNoMenu.byDoorStatus = i;
	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComIPSet(void)
{
       int i, nTime;
	char szBuffer[12];

	if ( Com_RecBigData((void*)&szBuffer, sizeof(szBuffer)) == -1 ){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

       if (!dbComm_ipIsDHCP)//静态IP
       {
              Com_SendExeResult( EXE_RES_TRUE, 0 );
	       dbSetupTotal.setSystem.ipAddress = UI_IP_MAKE(szBuffer[0], szBuffer[1], szBuffer[2], szBuffer[3]);
		dbSetupTotal.setSystem.ipSubnetMask = UI_IP_MAKE(szBuffer[4], szBuffer[5], szBuffer[6], szBuffer[7]);
		dbSetupTotal.setSystem.ipDefaultGateway = UI_IP_MAKE(szBuffer[8], szBuffer[9], szBuffer[10], szBuffer[11]);

		DbSetupTotalWrite();
       }
	else 
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
	}

       if (!dbComm_ipIsDHCP)//静态IP
	{
	       nTime = GetMainTickCount();
		   
	       for (i=0; i<MAX_SOCKS; i++)
		{
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE)
			{
				g_hClientSocksInfo[i] = 0;
			}
			else
			{
				if (comm_tcpcheck_close(g_hClientSocks[i]))
				{
					comm_tcpclient_close(g_hClientSocks[i]);
					g_hClientSocksInfo[i] = 0;
					g_dwClientIP[i] = 0;
				}
				else if (nTime - g_hClientSocksInfo[i] >= 5000)
				{
					comm_tcpclient_close(g_hClientSocks[i]);
					g_hClientSocksInfo[i] = 0;
				}
			}
		}
		   
		dbComm_ipAddress = dbSetupTotal.setSystem.ipAddress;
		dbComm_ipSubnetMask = dbSetupTotal.setSystem.ipSubnetMask;
		dbComm_ipDefaultGateway = dbSetupTotal.setSystem.ipDefaultGateway;
		dbComm_ipPcBackground = dbSetupTotal.setSystem.ipPCBackground;
		tcpclient_connect_start();
	}
	
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComBellTimeGet(void)
{
	int i;
	BELL_INFO *pBells = (BELL_INFO*)pTempBuffer;
	int nLen = sizeof(BELL_INFO) *BELL_INFO_COUNT;

	for (i = 0; i < BELL_INFO_COUNT; i++)
	{
		pBells[i].byBellKind = (BYTE)dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndHour;
		pBells[i].byHour = dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartHour;
		pBells[i].byMin = dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartMinute;
		pBells[i].bySec = 0;
		pBells[i].wLength = dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndMinute;
	}
	
	Com_SendData(pTempBuffer, nLen);
	Com_SendExeResult( EXE_RES_TRUE, nLen);
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
BOOL ComBellTimeSet(void)
{
	int ret, i, nRet;
	BELL_INFO *pBells = (BELL_INFO*)pTempBuffer;
	int nLen = sizeof(BELL_INFO) *BELL_INFO_COUNT;

	ret = Com_RecData( pTempBuffer, nLen );
	if ( ret != 1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, -1 );
		return FALSE;
	}

	nRet = TRUE;
	for (i = 0; i < BELL_INFO_COUNT; i++)
	{
		if (pBells[i].byBellKind >= BELL_KIND_COUNT ||		// kind
			pBells[i].byHour > 23 ||			// Hour
			pBells[i].byMin > 59 || 			// Minute
			pBells[i].bySec > 59)				// Second
		{
			nRet = FALSE; break;
		}
	}
	if (nRet)
	{
		for (i = 0; i < BELL_INFO_COUNT; i++)
		{
			dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartHour = pBells[i].byHour;
			dbSetupTotal.setTimezone.tzBell[i].RANGE.bStartMinute = pBells[i].byMin;
			dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndHour = pBells[i].byBellKind;
			dbSetupTotal.setTimezone.tzBell[i].RANGE.bEndMinute = pBells[i].wLength;
		}

		DbSetupTotalWrite();
        Com_SendExeResult( EXE_RES_TRUE, 0 );
	    return TRUE; 
	}

	Com_SendExeResult( EXE_RES_FALSE, 0 );
	return FALSE;
}

BOOL ComSystemCheck(CMDPKT *vCMD)
{
	 BOOL  bFlag = FALSE;

	 DWORD dwBuffer;
	 DWORD dwBufferSum;
	 DWORD dwSystemCheckSum;
	 int i;

     dwBuffer = vCMD->Length;
	 dwBufferSum = 0;
     for (i=0; i<8; i++)
	 {
		 if ((( dwBuffer & ( 0xf0000000 >> (i*4) )) >> (7-i)*4 ) != 0 && !bFlag)
		 {
             bFlag = TRUE;
			 dwBufferSum += (( dwBuffer & ( 0xf0000000 >> (i*4) )) >> (7-i)*4 );
		 }
         dwBufferSum += (( dwBuffer & ( 0xf0000000 >> (i*4) )) >> (7-i)*4 );
	 }
     dwSystemCheckSum = dbLicense.dwSystemCheck ^ dwBuffer ^ dwBufferSum;

	 Com_SendExeResult( EXE_RES_TRUE, dwSystemCheckSum );
	 return TRUE;

}

//////////////////////////////////////////////////////////////////////////
BOOL ComHostByNameGet(void)
{
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	Com_SendData(&dbSetupTotal.setSystem.szHostByName[0], sizeof(dbSetupTotal.setSystem.szHostByName));
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComHostByNameSet(void)
{
	char szHostByNameBuffer[32];

	if ( Com_RecBigData((void*)&szHostByNameBuffer, sizeof(szHostByNameBuffer)) == -1 ){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memcpy(&dbSetupTotal.setSystem.szHostByName[0], &szHostByNameBuffer[0], sizeof(dbSetupTotal.setSystem.szHostByName));

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComRealTimeLog(void)
{
	int nGLogReadCnt = DbGLogGetReadPos();
	DbGLogSetReadPosOnly((nGLogReadCnt+1) % dbLicense.nGlogMaxCount);
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComRealTimeSLog(void)
{
	int nSLogReadCnt = DbSLogGetReadPos();
	DbSLogSetReadPosOnly((nSLogReadCnt+1) % dbLicense.nSlogMaxCount);
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}


//////////////////////////////////////////////////////////////////////////
// BOOL ComLcdSet(CMDPKT *vCMD)
// {
// 
// 	dbLicense.nLCDCon = vCMD->InParam;
// 	DbLicenseWrite();
// 	Com_SendExeResult( EXE_RES_TRUE, 0 );
// 
// 	return TRUE;
// 
// }
//////////////////////////////////////////////////////////////////////////
BOOL ComInternalCheckPwd(CMDPKT *vCMD)
{
	if ( vCMD->InParam == 0 &&
		dbSetupTotal.setSystem.dwCommPassword != 0 &&
		dbSetupTotal.setSystem.dwCommPassword != vCMD->Length) 
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

BOOL arm_comm_tcp_get_cmd(HFILE hSock, CMDPKT* pvCMD)
{
	if (comm_sockrecv(hSock, pvCMD, CMDSIZE, TCP_RECV_CMD_TIMEOUT) == CMDSIZE)
	{
//		comm_crypt(pvCMD, STAFF_SIZE);
		if (Com_CheckCMD(pvCMD))
		{
			comm_mode = COMM_MODE_TCP;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL arm_comm_tcp_get_cmd2(HFILE hSock, CMDPKT* pvCMD)
{
	if (comm_sockrecv(hSock, pvCMD, CMDSIZE, TCP_RECV_TIMEOUT) == CMDSIZE)
	{
//		comm_crypt(pvCMD, STAFF_SIZE);
		if (Com_CheckCMD(pvCMD))
		{
			comm_mode = COMM_MODE_TCP;
			return TRUE;
		}
	}

	return FALSE;
}

BOOL arm_ComCheckPwd(CMDPKT* vCMD)
{
// 	DWORD	dwCommPwd;
// 
// 	if (!comm_recv_data(&dwCommPwd, 4)) return FALSE;
// 	return comm_send_ack(dbSetupTotal.setSystem.dwCommPassword == dwCommPwd ? CMD_ACK : CMD_NAK, 0);

	if ( vCMD->InParam == 0 &&
		dbSetupTotal.setSystem.dwCommPassword != 0 &&
		dbSetupTotal.setSystem.dwCommPassword != vCMD->Length) 
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}




/************************************************************************/
/* Additional Timezone et...                                            */
/************************************************************************/

//////////////////////////////////////////////////////////////////////////
BOOL ComPassTimeSet(void)
{
	DB_TIMESECTION_A tzHigh[TIMEZONE_COUNT];
	int ret;


	ret = Com_RecBigData((void*)&tzHigh[0], sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT);

	if ( ret != 1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}


	memcpy(&dbSetupTotal.setTimezone.tzHighTIME[0], (void*)&tzHigh, sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT);

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComPassTimeGet(void)
{
	Com_SendData((void*)&dbSetupTotal.setTimezone.tzHighTIME[0], sizeof(DB_TIMESECTION_A) * TIMEZONE_COUNT);
	Com_SendExeResult( EXE_RES_TRUE, 0);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGroupSet(void)
{
	BYTE  byGroupTimeInfo[TIMEGROUP_COUNT][TIMECOUNT_PER_TG];
	int ret;

	ret = Com_RecBigData((void*)&byGroupTimeInfo[0], TIMEGROUP_COUNT * TIMECOUNT_PER_TG);
	if ( ret != 1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memcpy((void *)&dbSetupTotal.setTimezone.tzHighTG[0], (void*)byGroupTimeInfo, TIMEGROUP_COUNT * TIMECOUNT_PER_TG);

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComGroupGet(void)
{
	Com_SendData((void*)&dbSetupTotal.setTimezone.tzHighTG[0], TIMEGROUP_COUNT * TIMECOUNT_PER_TG);
	Com_SendExeResult( EXE_RES_TRUE, 0);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
// BOOL ComLockGroupSet(void)
// {
// 	DWORD  dwLockGroupInfo[10];
// 	int ret, i;
// 	BYTE tzLockGroup[MULTI_IDENT_SET_COUNT];
// 
// 	ret = Com_RecBigData((void*)&dwLockGroupInfo[0], 40);
// 	if ( ret != 1 )
// 	{
// 		Com_SendExeResult( EXE_RES_FALSE, 0 );
// 		return FALSE;
// 	}
// 
// 	for(i = 0; i < 10; i++){
// 		tzLockGroup[i] = NUMBER2LOCKGROUP(dwLockGroupInfo[i]);
// 		if(LOCKGROUP_VALIDCHECK(dbSetupTotal.setTimezone.tzLockGroup, tzLockGroup[i]))
// 			dbSetupTotal.setTimezone.tzLockGroup[i] = tzLockGroup[i];
// 		else{
// 			Com_SendExeResult( EXE_RES_FALSE, 0 );
// 			return FALSE;
// 		}
// 	}
// 	
// 	DbSetupTotalWrite();
// 	Com_SendExeResult( EXE_RES_TRUE, 0 );
// 	return TRUE;
// }
// 
// //////////////////////////////////////////////////////////////////////////
// BOOL ComLockGroupGet(void)
// {
// 	DWORD  dwLockGroupInfo[10];
// 	int i;
// 
// 	for(i = 0; i < 10; i++){
// 		dwLockGroupInfo[i] = LOCKGROUP2NUMBER(dbSetupTotal.setTimezone.tzLockGroup[i]);
// 	}
// 	Com_SendData((void*)&dwLockGroupInfo[0], 40);
// 	Com_SendExeResult( EXE_RES_TRUE, 0);
// 	return TRUE;
// }

//////////////////////////////////////////////////////////////////////////
BOOL ComTimeZoneSet(void)
{
	BYTE  byTimeZoneInfo[ACCESS_TIME_SET_COUNT_HIGH][7];
	int ret;

	ret = Com_RecBigData((void*)byTimeZoneInfo, ACCESS_TIME_SET_COUNT_HIGH * 7);
	if ( ret != 1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memcpy((void *)dbSetupTotal.setTimezone.tzHighAccess, (void*)byTimeZoneInfo, ACCESS_TIME_SET_COUNT_HIGH * 7);

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComTimeZoneGet(void)
{
	Com_SendData((void*)&dbSetupTotal.setTimezone.tzHighAccess[0], ACCESS_TIME_SET_COUNT_HIGH * 7);
	Com_SendExeResult( EXE_RES_TRUE, 0);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	WORD	wId;
	WORD	wZoneID;
	DWORD   dwStartDataSec;
	DWORD   dwEndDataSec;
	WORD    wUserCtrl;
} PACKED PACKED_USER_CTRL_INFO;

BOOL ComUserCtrlSet(void)
{
	PACKED_USER_CTRL_INFO PackeUserCtrlInfo;

	if ( Com_RecBigData((void*)&PackeUserCtrlInfo, sizeof(PACKED_USER_CTRL_INFO)) == -1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, -3 );
		return FALSE;
	}

	if((/*PackeUserCtrlInfo.wZoneID < 0 && */PackeUserCtrlInfo.wZoneID > 32) && (PackeUserCtrlInfo.wUserCtrl < 1 && PackeUserCtrlInfo.wUserCtrl > 5)){
		Com_SendExeResult( EXE_RES_FALSE, -3 );
		return FALSE;
	}

	USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(PackeUserCtrlInfo.wId);
	if (!pUserInfo){
		Com_SendExeResult( EXE_RES_FALSE, -2 );
		return FALSE;
	}

	pUserInfo->UserTZ[0] = (BYTE)PackeUserCtrlInfo.wZoneID;
	pUserInfo->UserTZ[1] = 0;
	pUserInfo->UserTZ[2] = 0;

	pUserInfo->TIMEGROUP = (BYTE)PackeUserCtrlInfo.wUserCtrl;

	if(!DbUserInfoEnroll(pUserInfo, BACKUP_ALL, NULL))
	{
		Com_SendExeResult( EXE_RES_FALSE, -1 );
		return FALSE;
	}

	Com_SendExeResult( EXE_RES_TRUE, 3 );
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComUserCtrlGet(CMDPKT* pCMD)
{
	PACKED_USER_CTRL_INFO UserCtrlInfo;

	if (pCMD->Length == 0 || pCMD->Length > 999999999)
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(pCMD->Length);
	if (!pUserInfo){
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	UserCtrlInfo.wId = (WORD)pUserInfo->ID;
	UserCtrlInfo.wZoneID = pUserInfo->UserTZ[0];
	UserCtrlInfo.dwStartDataSec = 0;
	UserCtrlInfo.dwEndDataSec = 0;
	UserCtrlInfo.wUserCtrl = pUserInfo->TIMEGROUP;

	Com_SendData(&UserCtrlInfo, sizeof(PACKED_USER_CTRL_INFO));

	Com_SendExeResult( EXE_RES_TRUE, 0 );

	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	DWORD dwODDelay;
	DWORD dwODOvertimeWrn;
	DWORD dwODIllegalWrn;
	BYTE  bySignalCtrl;
	BYTE   byIsLockGroup;
	BYTE  byThreatWarn;
	BYTE  byThreatAct;
	BYTE  byVerifyKind;
	BOOL  bValidData;
	BYTE  byWgFormat;
	BYTE  byHiddenBack;
} PACKED_DBSETUP_LOCK_INFO;

BOOL ComDoorKeyParamSet(void)
{
	PACKED_DBSETUP_LOCK_INFO  dbSetupLockInfo;
	int ret;

	ret = Com_RecBigData((void*)&dbSetupLockInfo, sizeof(PACKED_DBSETUP_LOCK_INFO));
	if ( ret != 1 )
	{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	if(dbSetupLockInfo.byVerifyKind == 0)
		dbSetupTotal.setSystem.nVerifyMode = INDEX2VERIFYMODE(VM_ANY);
	else if(dbSetupLockInfo.byVerifyKind == 1)
		dbSetupTotal.setSystem.nVerifyMode = INDEX2VERIFYMODE(VM_FPPW);
	else if(dbSetupLockInfo.byVerifyKind == 2)
		dbSetupTotal.setSystem.nVerifyMode = INDEX2VERIFYMODE(VM_RFFP);
	else if(dbSetupLockInfo.byVerifyKind == 3)
		dbSetupTotal.setSystem.nVerifyMode = INDEX2VERIFYMODE(VM_RFPW);
	else if(dbSetupLockInfo.byVerifyKind == 4)
		dbSetupTotal.setSystem.nVerifyMode = INDEX2VERIFYMODE(VM_FPRFPW);
	else{
		Com_SendExeResult( EXE_RES_FALSE, 0 );
		return FALSE;
	}
	dbSetupTotal.setSystem.nLockTime = dbSetupLockInfo.dwODDelay;
	dbSetupTotal.setSystem.nIllegalVerifyWarning = dbSetupLockInfo.dwODIllegalWrn;
	dbSetupTotal.setSystem.nDoorOpenTime = dbSetupLockInfo.dwODOvertimeWrn;
	dbSetupTotal.setSystem.byWiegandFormat = dbSetupLockInfo.byWgFormat;
// 	if(dbSetupLockInfo.byHiddenBack == 0)
// 		dbSetupTotal.setSystem.byAntipassStatus = 0;
// 	else
// 		dbSetupTotal.setSystem.byAntipassStatus = 1;

	DbSetupTotalWrite();
	Com_SendExeResult( EXE_RES_TRUE, 0 );
	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
BOOL ComDoorKeyParamGet(void)
{	
	PACKED_DBSETUP_LOCK_INFO  dbSetupLockInfo;

	dbSetupLockInfo.dwODDelay = dbSetupTotal.setSystem.nLockTime;
	dbSetupLockInfo.dwODIllegalWrn = dbSetupTotal.setSystem.nIllegalVerifyWarning;
	dbSetupLockInfo.dwODOvertimeWrn = dbSetupTotal.setSystem.nDoorOpenTime;
	dbSetupLockInfo.byWgFormat = dbSetupTotal.setSystem.byWiegandFormat;
// 	if(dbSetupTotal.setSystem.byAntipassStatus == ANTIPASS_NO)
// 		dbSetupLockInfo.byHiddenBack=0;
// 	else
// 		dbSetupLockInfo.byHiddenBack=1;

	
	if(dbSetupTotal.setSystem.nVerifyMode == VERIFYMODE2INDEX(VM_ANY))
		dbSetupLockInfo.byVerifyKind = 0;
	else if(dbSetupTotal.setSystem.nVerifyMode == VERIFYMODE2INDEX(VM_FPPW))
		dbSetupLockInfo.byVerifyKind = 1;
	else if(dbSetupTotal.setSystem.nVerifyMode == VERIFYMODE2INDEX(VM_RFFP))
		dbSetupLockInfo.byVerifyKind = 2;
	else if(dbSetupTotal.setSystem.nVerifyMode == VERIFYMODE2INDEX(VM_RFPW))
		dbSetupLockInfo.byVerifyKind = 3;
	else if(dbSetupTotal.setSystem.nVerifyMode == VERIFYMODE2INDEX(VM_FPRFPW))
		dbSetupLockInfo.byVerifyKind = 4;

	dbSetupLockInfo.bySignalCtrl = 0;
	dbSetupLockInfo.byThreatWarn = 0;
	dbSetupLockInfo.byThreatAct = 0;
	dbSetupLockInfo.bValidData = 0;	
	dbSetupLockInfo.byIsLockGroup=0;

	Com_SendData((void *)&dbSetupLockInfo, sizeof(PACKED_DBSETUP_LOCK_INFO));

	Com_SendExeResult( EXE_RES_TRUE, 0 );

	return TRUE;	
}

//////////////////////////////////////////////////////////////////////////
typedef struct
{
	DWORD	dwSeconds;
	WORD	wId;
	BYTE	byAction;
	BYTE    byType;
	int     DoorState;
} PACKED_ALOG_INFO;

BOOL ComLogWatchGet(CMDPKT* pCMD)
{
	PACKED_ALOG_INFO AlogInfo;
	int count = 0; 

	int nAlogcount = DbGLogCountAll();
	int nGLogReadCnt = DbGLogGetReadPos();

	if (pCMD->InParam == 0)
	{
		if (nGLogReadCnt > nAlogcount)
		{
			nGLogReadCnt = nAlogcount;
			//DbSetupTotalWrite();
		}

		if (nGLogReadCnt != nAlogcount)
		{
			count = nGLogReadCnt; 

			ALOG_INFO ALog;

			if(!DbGLogGet(&ALog, count, 1)){
				Com_SendData((void *)&AlogInfo, sizeof(PACKED_ALOG_INFO));	
				Com_SendExeResult( EXE_RES_FALSE, 0 );
				return FALSE;
			}
			AlogInfo.wId = ALog.nID;
			AlogInfo.dwSeconds = ALog.dwSeconds;
			AlogInfo.byType=0;
			AlogInfo.byAction = ALog.byAction;
			AlogInfo.DoorState = __DOOR_STATUS[dbSetupTotal.setNoMenu.byDoorStatus];
		}
		else
		{
			memset((void *)&AlogInfo, 0 , sizeof(PACKED_ALOG_INFO) - sizeof(int));
			AlogInfo.DoorState = __DOOR_STATUS[dbSetupTotal.setNoMenu.byDoorStatus];
		}
		Com_SendData((void *)&AlogInfo, sizeof(PACKED_ALOG_INFO));	
		Com_SendExeResult( EXE_RES_TRUE, nGLogReadCnt );					
	} 
	else if(pCMD->InParam == 1) 
	{
		if (pCMD->Length == (DWORD)nGLogReadCnt)
		{
			DbGLogSetReadPos((nGLogReadCnt+1) % dbLicense.nGlogMaxCount);
			Com_SendExeResult( EXE_RES_TRUE, 0 );
		}
		else
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
		}
	}
	return TRUE;
}
/*
//////////////////////////////////////////////////////////////////////////
BOOL ComLogtimeSet(CMDPKT* pCMD)
{
	LOG_CTIME  LogTimeInfo[10];
	int ret;

	ret = Com_RecBigData((void*)LogTimeInfo, sizeof(LOG_CTIME) * 10);

	if ( ret != 1 )
	{
		arm_comm_send_result( EXE_RES_FALSE, 0 );
		return FALSE;
	}

	memcpy(dbSetupTotal.setSystem.t_LOG_TIME, (void*)LogTimeInfo, sizeof(LOG_CTIME) * 10);

	DbSetupTotalWrite();
	arm_comm_send_result( EXE_RES_TRUE, 0 );
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComLogtimeGet(CMDPKT* pCMD)
{
	Com_SendData((void*)dbSetupTotal.setSystem.t_LOG_TIME, sizeof(LOG_CTIME) * 10);
	arm_comm_send_result( EXE_RES_TRUE, 0);
	return TRUE;
}
*/
/************************************************************************/
/*																		*/
/************************************************************************/
BOOL Com_CommanProc2(CMDPKT* vCMD,int nFP)
{
	int  nRet = TRUE;	

	dwRealTime = uiTimeGetTickCount();
	//dwTimeSynTime=dwRealTime;
	bSendAckTimeout=0;

	if (!Com_SendCmdAck(CMD_ACK))
	{
	    xprintf("%s", "Com_SendCmdAck err \r\n"); 
		return FALSE;
	}

	//if (g_uiWorkingDisplay)
	//	uiProcDrawStatus();

	g_uiCommandProc = TRUE;

	//	Com_DispCmd(nCMD);

	xprintf("vCMD->Command=%d \r\n", vCMD->Command); 

	bSendAckTimeout=0;
	
	switch (vCMD->Command)
	{
	case ARM_CMD_REALTIME_LOG:		
		bSendAckTimeout=0;
		nRet = ComRealTimeLog();
		return 100;
		break;
	case ARM_CMD_REALTIME_SLOG:		
		bSendAckTimeout=0;
		nRet = ComRealTimeSLog();
		return 100;
		break;		
	case ARM_CMD_REALTIME_HEART:
		bSendAckTimeout=0;
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		return 100;
		break;	
	case EVENT_ENROLL_GET_NAME:
		xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_NAME ..."); 
		if(vCMD->InParam==0 && vCMD->Length==0)
		{
			return	3; //服务器无此ID
		}
		bzero(&packed_name_info, sizeof(packed_name_info));
		if ( Com_RecBigData((void*)&packed_name_info, sizeof(packed_name_info)) == -1)
		{
			 xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_NAME err"); 
			 return	0;
		}
		return 2;//传输结束
		break;
	case EVENT_ENROLL_GET_FINGER_DATA:
		xprintf("%s", "Com_Send EVENT_ENROLL_GET_FINGER_DATA ..."); 

		if(TCPCLIENT_SEND_DATA)
		{
		   TCPCLIENT_SEND_DATA=0;
		   if(nFP==10)
		   {	
			  if ( Com_SendBigData(gFpPacket, 4)== -1)
			  {
				   xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_FINGER_DATA err"); 
				   return 0;
			  }
			  return 2;//传输结束
		   }
		   else if(nFP==11)
		   {	
			  if ( Com_SendBigData(gFpPacket, 4)== -1)
			  {
				   xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_FINGER_DATA err"); 
				   return 0;
			  }
			  return 2;//传输结束
		   }
		   else
		   {	
			  if ( Com_SendBigData(gFpPacket, sizeof(FPINFO) + 12)== -1)
			  {
				   xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_FINGER_DATA err"); 
				   return 0;
			  }
			  return 2;//传输结束
		   }		   

		}

		break;
	case EVENT_ENROLL_GET_FINGER_IMAGE:
		xprintf("%s", "Com_Send EVENT_ENROLL_GET_FINGER_IMAGE ..."); 

		if(TCPCLIENT_SEND_DATA)
		{
		        TCPCLIENT_SEND_DATA=0;

			  if ( Com_SendBigData(gFpImage, 256*256 + 12)== -1)
			  {
				   xprintf("%s \r\n", "Com_Send EVENT_ENROLL_GET_FINGER_IMAGE err"); 
				   return 0;
			  }
			  return 2;//传输结束

		}

		break;
	case EVENT_VERIFY_GET_DATA: 
		xprintf("%s \r\n", "Com_Send EVENT_VERIFY_GET_DATA ..."); 
		if(vCMD->InParam==0 && vCMD->Length==0)
		{
			return	3; //服务器无此ID
		}
		else if(vCMD->InParam==0 && vCMD->Length)
		{
			return 2;//传输结束
		}
		else if(vCMD->InParam==2 && vCMD->Length)
		{
			return 4;//有ID 没有批文信息
		}
		else if(vCMD->InParam==1 && vCMD->Length)
		{
        bzero(&UserData, sizeof(UserData));
		if ( Com_RecBigData((void*)&UserData, sizeof(UserData)) == -1 )
		{
			 xprintf("%s \r\n", "Com_Send EVENT_VERIFY_GET_DATA err"); 
			 return 0;
		}
			return 100;//
		}
		break;		
	default:
		return	0;
		break;
		//////////////////////////////////////////////////////////////////////////
	}

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_MakeFpData(BYTE *data)
{
	DWORD dwChkSum;
	DWORD* pdwBuf = (DWORD*)&data[8];

	if(data[0] != (BYTE)'S')
		return FALSE;
	if(data[1] != (BYTE)'m')
		return FALSE;
	if(data[2] != (BYTE)'a')
		return FALSE;
	if(data[3] != (BYTE)'c')
		return FALSE;
	if(data[4] != (BYTE)'k')
		return FALSE;
	if(data[5] != (BYTE)'B')
		return FALSE;
	if(data[6] != (BYTE)'i')
		return FALSE;
	if(data[7] != (BYTE)'o')
		return FALSE;

	dwChkSum = Com_MakeCheckSum(pdwBuf, 1404/4);
	if(dwChkSum != *((DWORD*)&data[8+1404]))
		return FALSE;

	memcpy(gFpData, &data[8], 1404);
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL Com_CheckFpData(BYTE *data)
{
	DWORD dwChkSum;
	DWORD* pdwBuf = (DWORD*)&data[8];

	if(data[0] != (BYTE)'S')
		return FALSE;
	if(data[1] != (BYTE)'m')
		return FALSE;
	if(data[2] != (BYTE)'a')
		return FALSE;
	if(data[3] != (BYTE)'c')
		return FALSE;
	if(data[4] != (BYTE)'k')
		return FALSE;
	if(data[5] != (BYTE)'B')
		return FALSE;
	if(data[6] != (BYTE)'i')
		return FALSE;
	if(data[7] != (BYTE)'o')
		return FALSE;

	dwChkSum = Com_MakeCheckSum(pdwBuf, 1404/4);
	if(dwChkSum != *((DWORD*)&data[8+1404]))
		return FALSE;

	//memcpy(gFpData, &data[8], 1404);
	return TRUE;
}

extern BOOL uiEnrollUserInfo2(USER_INFO *pUserInfo);

int  ComClientGetVerifydata_web2(UINT64 ID)
{
	int nRet;
	nRet=UIENROLL_RET_FALSE;
	nRet =HttpClient_main(DEVID,ID,0,0,HTTP_DEPTPUNCH,TRUE);
	return nRet;
}

int  ComClientGetVerifydata(UINT64 ID)
{
	int i;
	int  nRet;
	
	nRet=UIENROLL_RET_FALSE;

	//上传登记号码到设备服务器
	if( comm_send_event(EVENT_VERIFY_GET_DATA, &ID, 8 ) == 0 ) 
	{
		//if(comm_tcpclient_connect()==0)
		//{
		//}
		return  nRet;
	}
	else
	{
		CMDPKT vCMD;		
		BOOL  bResult;
		void* pData;
			
		for (i=0; i<MAX_SOCKS; i++)
		{  
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE && dbLicense.byTcpipMode == TCPIP_SERVER)	
				return  UIENROLL_RET_FALSE;	
			comm_sub_mode = i;
			
			DWORD dwTime = 0;
			dwTime = uiTimeGetTickCount();
			while((uiTimeGetTickCount()-dwTime)<10000) //有数据时 InParam == 1 Length == enrollid
			{
				bzero(&vCMD, sizeof(vCMD));
				if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
				{					
					xprintf("vCMD.InParamr=%d vCMD.Lengthr=%d \r\n", vCMD.InParam,vCMD.Length); 

                    			bResult=Com_CommanProc2(&vCMD,0);
					if(bResult==0)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						xprintf("%s", "EVENT_VERIFY_GET_DATA ERR"); 
						nRet=UIENROLL_RET_FALSE;
						return  nRet;				
					}
					else if(bResult==2)					
						{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						nRet=UIENROLL_RET_TRUE;
						return  nRet;									     
						}
					else if(bResult==4)					
						{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						nRet=UIENROLL_NO_ENROLL_FP;
						return  nRet;									     
						}
					

					else if(bResult==3)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						nRet=UIENROLL_NO_ENROLL_ID;
						return  nRet;					
					}

					xprintf("UserData.dwEnrollNumber=%d \r\n", UserData.dwEnrollNumber); 
					xprintf("UserData.dwBackupNumber=%d \r\n", UserData.dwBackupNumber); 
					xprintf("UserData.UserName=%s \r\n", UserData.UserName); 
					
					//xprintf("UserData.UserName=%s", UserData.UserName); 
                    //int j;
					//for(j=8; j<sizeof(FPINFO)+12; j++)
					//{
					//	xprintf("%x", UserData.FingerData[j]); 
					//}					
					//xprintf("UserData.dwPrivilege=%d \r\n", UserData.dwPrivilege); 
					memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
					
					gUserInfoTemp.ID=UserData.dwEnrollNumber;
					//gUserInfoTemp.FP=UserData.dwBackupNumber;
					gUserInfoTemp.VERIFYMODE=UserData.dwVerifymode;
					gUserInfoTemp.FLAG.members.byMgr=UserData.dwPrivilege;
					//strncpy((char *)gUserInfoTemp.NAME,(char *)UserData.UserName,24);					
                    			QString str =G2U((char *)UserData.UserName);
					STRING2UNICODE(str,(WORD*)gUserInfoTemp.NAME, USERNAME_LENGTH); 

					if(UserData.dwBackupNumber >= BACKUP_FINGER0 && UserData.dwBackupNumber <= BACKUP_FINGER9)
					{
						if(Com_CheckFpData(&UserData.FingerData[0])==0)
						   break;	

						if (SB_FP_IDENTIFYFPDATA((FPINFO*)&UserData.FingerData[8], NULL) >= 0)  
						{						
	                       				 g_hClientSocksInfo[i] = uiTimeGetTickCount();
							comm_mode = COMM_MODE_NONE;
							comm_sub_mode = -1;							
							return  UIENROLL_RET_DUPLICATE;	
						}
						pData=&UserData.FingerData[8];
					}
					else if(UserData.dwBackupNumber==10)
					{
						char buf[16];
						sprintf(buf, "%d", UserData.Password);
					    gUserInfoTemp.PWD=STRING2PWD(buf);
						pData=&gUserInfoTemp.PWD;
					}
					else if(UserData.dwBackupNumber==11)
					{
						char buf[16];
						sprintf(buf, "%d", UserData.CardID);
					    gUserInfoTemp.CARD=STRING2PWD(buf);
					    pData=&gUserInfoTemp.CARD;
					}
					else
					{
	                        				g_hClientSocksInfo[i] = uiTimeGetTickCount();
							comm_mode = COMM_MODE_NONE;
							comm_sub_mode = -1;							
							return  UIENROLL_RET_FALSE;						
					}
                	              		DbUserInfoEnroll(&gUserInfoTemp, UserData.dwBackupNumber, pData, TRUE, FALSE);
					if(DbUserTimeDataWrite(gUserInfoTemp.ID)==0)
						DbUserTimeDataNew(gUserInfoTemp.ID);
					dwTime = uiTimeGetTickCount();

					 if(bResult==100)	
					{
					   dwTime = uiTimeGetTickCount();
					   continue;
					}
					g_hClientSocksInfo[i] = uiTimeGetTickCount();
					comm_mode = COMM_MODE_NONE;
					comm_sub_mode = -1;
					nRet = UIENROLL_RET_TRUE;
					return  nRet;
					}
			}		
		lexit:	
			g_hClientSocksInfo[i] = uiTimeGetTickCount();
			comm_mode = COMM_MODE_NONE;
			comm_sub_mode = -1;
			nRet = UIENROLL_RET_FALSE;
			return  nRet;
		}		
	}
	return  nRet;
}


BOOL ComClientSendCardPasswordData(UINT64 ID ,int card ,BOOL iscard)
{
	int i;
    mUserIDInfo data;
   
    if ( ID < 1 || ID > MAX_ID)
    {
	   return FALSE;
    }	
	if(iscard)
	  data.BackupNumber=11;	
	else
	  data.BackupNumber=10;
	data.EnrollNumber=ID;	
	data.Privilege=gUserInfoTemp.FLAG.members.byMgr;
	data.VerifyMode=gUserInfoTemp.VERIFYMODE;

	
	//上传登记号码到设备服务器
	if( comm_send_event(EVENT_ENROLL_GET_FINGER_DATA , &data,sizeof(data) ) == 0 ) 
	{
		//if(comm_tcpclient_connect()==0)
		//{
		//}
		return  FALSE;
	}
	else
	{
		CMDPKT vCMD;		
			
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE && dbLicense.byTcpipMode == TCPIP_SERVER)	
				return FALSE;	

			if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
			{
				Com_MakePacket((BYTE*)card, sizeof(card));
				comm_sub_mode = i;
				TCPCLIENT_SEND_DATA=1;
				if(Com_CommanProc2(&vCMD,0)==0)
				{
					TCPCLIENT_SEND_DATA=0;
					g_hClientSocksInfo[i] = uiTimeGetTickCount();
					comm_mode = COMM_MODE_NONE;
					comm_sub_mode = -1;
					return  FALSE;			
				}
				TCPCLIENT_SEND_DATA=0;
				g_hClientSocksInfo[i] = uiTimeGetTickCount();
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;				
			}
		}
		
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
			{
				comm_sub_mode = i;
				if(vCMD.Command==EVENT_ENROLL_GET_FINGER_DATA )
				{	   
					   g_hClientSocksInfo[i] = uiTimeGetTickCount();
					   comm_mode = COMM_MODE_NONE;
					   comm_sub_mode = -1;
					   return TRUE;
	
				}
				g_hClientSocksInfo[i] = uiTimeGetTickCount();
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
			}
		}
		
	}
	return  FALSE;
}



BOOL ComClientSendFingerData(UINT64 ID ,int nFP,BYTE* pData)
{
	int i;
	BOOL  bResult;
	int  nRet;

    mUserIDInfo data;
   
   // if ( ID < 1 || ID > MAX_ID || nFP < BACKUP_FINGER0 || nFP > BACKUP_FINGER9)
  //  {
	//   return FALSE;
  //  }

	data.EnrollNumber=ID;
	data.BackupNumber=nFP;
	data.Privilege=gUserInfoTemp.FLAG.members.byMgr;
	data.VerifyMode=gUserInfoTemp.VERIFYMODE;

	
	//上传登记号码到设备服务器
	if( comm_send_event(EVENT_ENROLL_GET_FINGER_DATA , &data, sizeof(data) ) == 0 ) 
	{
		//if(comm_tcpclient_connect()==0)
		//{
		//}
		return  FALSE;
	}
	else
	{
		CMDPKT vCMD;	
		typedef struct DataPak{
			union{
				BYTE Data[4]; //用户指纹模板
				DWORD Password;
				DWORD CardID;
			};
			
		}st_Data;	
		st_Data num;
			
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE && dbLicense.byTcpipMode == TCPIP_SERVER)	
				return FALSE;	
			DWORD dwTime = 0;
			dwTime = uiTimeGetTickCount();
			while((uiTimeGetTickCount()-dwTime) < 5000) //有数据时 InParam == 1 Length == enrollid
			{
				if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
				{
	                if(nFP==10)
	            	{
						char buf[16];
						memcpy(&num.Data, (BYTE*)pData, 4);
						sprintf(buf, "%x", num.Password);
						DWORD tmp=STRING2ID(buf);
						xprintf("Password=%d \r\n", tmp); 

						memcpy(&gFpPacket[0], (BYTE*)&tmp, 4);
	            	}
					else if(nFP==11)
	            	{
						char buf[16];
						memcpy(&num.Data, (BYTE*)pData, 4);
						sprintf(buf, "%d", num.Password);
						DWORD tmp=STRING2PWD(buf);
						memcpy(&gFpPacket[0], (BYTE*)&tmp, 4);
	            	}					
					else if(nFP >= BACKUP_FINGER0 && nFP <= BACKUP_FINGER9)
	            	{
	            	   Com_MakePacket((BYTE*)pData, sizeof(FPINFO));
	            	}						
					else
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						return  FALSE;				
					}

					comm_sub_mode = i;
					TCPCLIENT_SEND_DATA=1;
	                bResult=Com_CommanProc2(&vCMD,nFP);
					if(bResult==0)
					{
						TCPCLIENT_SEND_DATA=0;
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						return  FALSE;				
					}
					else if(bResult==100)	
					{
					   dwTime = uiTimeGetTickCount();
					   	g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
					   continue;
					}
					else if(bResult==2)					
						goto lexit;
					else if(bResult==3)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						nRet=3;
						return  nRet;					
					}
						
					TCPCLIENT_SEND_DATA=0;
					g_hClientSocksInfo[i] = uiTimeGetTickCount();
					comm_mode = COMM_MODE_NONE;
					comm_sub_mode = -1;
				    dwTime = uiTimeGetTickCount();	
				}
			}	
		}
		TCPCLIENT_SEND_DATA=0;
		g_hClientSocksInfo[i] = uiTimeGetTickCount();
		comm_mode = COMM_MODE_NONE;
		comm_sub_mode = -1;
		return  FALSE;			
  lexit:		
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
			{
				comm_sub_mode = i;
				if(vCMD.Command==EVENT_ENROLL_GET_FINGER_DATA )
				{	   
					   g_hClientSocksInfo[i] = uiTimeGetTickCount();
					   comm_mode = COMM_MODE_NONE;
					   comm_sub_mode = -1;
					   return TRUE;
	
				}
				g_hClientSocksInfo[i] = uiTimeGetTickCount();
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
			}
		}
		
	}
	return  FALSE;
}

BOOL ComClientSendFingerImage(UINT64 ID ,int nFP, void* pData)
{
	int i;
	BOOL  bResult;
	int  nRet;

        mUserIDInfo data;
   
	data.EnrollNumber=ID;
	data.BackupNumber=nFP;
	data.Privilege=gUserInfoTemp.FLAG.members.byMgr;
	data.VerifyMode=gUserInfoTemp.VERIFYMODE;

	
	//上传登记号码到设备服务器
	if( comm_send_event(EVENT_ENROLL_GET_FINGER_IMAGE , &data, sizeof(data) ) == 0 ) 
	//if( comm_send_event(EVENT_ENROLL_GET_FINGER_IMAGE, &ID, 8 ) == 0 ) 
	{
		return  FALSE;
	}
	else
	{		   
		CMDPKT vCMD;	

		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE && dbLicense.byTcpipMode == TCPIP_SERVER)	
				return FALSE;	
			DWORD dwTime = 0;
			dwTime = uiTimeGetTickCount();
			while((uiTimeGetTickCount()-dwTime)<5000) //有数据时 InParam == 1 Length == enrollid
			{
				if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
				{
				   
				      Com_MakeImage((BYTE*)pData, 256*256);

					comm_sub_mode = i;
					TCPCLIENT_SEND_DATA=1;
			              bResult=Com_CommanProc2(&vCMD,0);
					if(bResult==0)
					{
						TCPCLIENT_SEND_DATA=0;
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						return  FALSE;				
					}
					else if(bResult==100)	
					{
					   dwTime = uiTimeGetTickCount();
					   	g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
					   continue;
					}
					else if(bResult==2)					
						goto lexit;
					else if(bResult==3)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						nRet=3;
						return  nRet;					
					}
						
					TCPCLIENT_SEND_DATA=0;
					g_hClientSocksInfo[i] = uiTimeGetTickCount();
					comm_mode = COMM_MODE_NONE;
					comm_sub_mode = -1;
				    dwTime = uiTimeGetTickCount();	
				}
			}	
		}
		TCPCLIENT_SEND_DATA=0;
		g_hClientSocksInfo[i] = uiTimeGetTickCount();
		comm_mode = COMM_MODE_NONE;
		comm_sub_mode = -1;
		return  FALSE;			
  lexit:		
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
			{
				comm_sub_mode = i;
				if(vCMD.Command==EVENT_ENROLL_GET_FINGER_IMAGE )
				{	   
					   g_hClientSocksInfo[i] = uiTimeGetTickCount();
					   comm_mode = COMM_MODE_NONE;
					   comm_sub_mode = -1;
					   return TRUE;
	
				}
				g_hClientSocksInfo[i] = uiTimeGetTickCount();
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;
			}
		}
		
	}
	return  FALSE;
}


BOOL ComClientGetName(UINT64 ID ,WORD *Name,int len)
{

	//上传登记号码到设备服务器
	if( comm_send_event(EVENT_ENROLL_GET_NAME, &ID, 8 ) == 0 ) 
	{
		//if(comm_tcpclient_connect()==0)
		//{
		//}
		return  FALSE;
	}
	else
	{
		CMDPKT vCMD;
		int i;
        BOOL  bResult;
	
		bzero(&vCMD, sizeof(vCMD));
		comm_tcpclient_accept();	 
		for (i=0; i<MAX_SOCKS; i++)
		{						   
			
			if (g_hClientSocks[i] == INVALID_SOCK_HANDLE && dbLicense.byTcpipMode == TCPIP_SERVER)	
				return FALSE;
			DWORD dwTime = 0;
			dwTime = uiTimeGetTickCount();
			while((uiTimeGetTickCount()-dwTime)<5000) //有数据时 InParam == 1 Length == enrollid
			{		
				//xprintf("%s \r\n", "arm_comm_tcp_get_cmd");
				if (arm_comm_tcp_get_cmd2(g_hClientSocks[i], &vCMD))
				{
					comm_sub_mode = i;
					bResult=Com_CommanProc2(&vCMD,0);
					if(bResult==2)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						xprintf("NameA=%s \r\n", packed_name_info.NameA);
						
						//QString str = QWidget::tr((char *)packed_name_info.NameA);
	                    QString str =G2U((char *)packed_name_info.NameA);
	                    bzero(Name, len*2);
						STRING2UNICODE(str,(WORD*)Name, USERNAME_LENGTH); 
						//UNICODE2STRING((WORD*)packed_name_info.NameA,12);
						//strncpy((char*)Name,packed_name_info.NameA,len*2);
						//memcpy((char*)Name,packed_name_info.NameA,len*2);
						xprintf("Name=%s \r\n", Name);
						return 1;				
					}
					else if(bResult==100)	
					{
					   dwTime = uiTimeGetTickCount();
					   continue;
					}					
					else if(bResult==3)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						return  3;					
					}
					else if(bResult==0)
					{
						g_hClientSocksInfo[i] = uiTimeGetTickCount();
						comm_mode = COMM_MODE_NONE;
						comm_sub_mode = -1;
						return  FALSE;				
					}					
					g_hClientSocksInfo[i] = uiTimeGetTickCount();
					comm_mode = COMM_MODE_NONE;
					comm_sub_mode = -1;
					dwTime = uiTimeGetTickCount();		
				}
			}		
			g_hClientSocksInfo[i] = uiTimeGetTickCount();
			comm_mode = COMM_MODE_NONE;
			comm_sub_mode = -1;
			return  FALSE;				
		}
	}
	return  FALSE;
}

//////////////////////////////////////////////////////////////////////////
BOOL ComClientFpDataUpLoad ( void )
{
	UINT64 nID;
	int nFP;
	FPINFO* pFPinfo;
    	int backup_num;
	
	if (dbLicense.byTcpipMode != TCPIP_CLIENT)
		return FALSE;
	if(DbFpUploadDataGet(&nID,&nFP)==0)
		return FALSE;

	if ( nID < 1 || nID > MAX_ID) 
	{
		DbFpUploadDataClear(nID);
		return FALSE;
	}
	backup_num = BACKUP_FINGER0;
	while(backup_num <= BACKUP_CARD)
	{
        		if(nFP & (1 << backup_num))
        		{
			pFPinfo = (FPINFO*)DbUserInfoGetPointer(nID, backup_num);	
			if ( pFPinfo )
			{
				int nUserPriv = comm_GetUserPriv(nID);
				if(nUserPriv == -1){
					return FALSE;
				}
				//下面是我改变的，功能是离线注册后没上传的等在线时上传
				//if(ComClientSendFingerData(nID,backup_num,(BYTE*)pFPinfo))
				if(web2_send_finger( nID,backup_num,nUserPriv,(u8 *)pFPinfo))	
				{
				    	DbFpUploadDataSave(nID,backup_num,1);				
				   	 return TRUE;
				}
				else
				{
				   	tcpclient_connect_start();
				   	return TRUE;
				}
			}
			else
			{
			   	DbFpUploadDataSave(nID,backup_num,1);
			}
        		}
		backup_num++;
	}
	return FALSE;
}


/*
BOOL  Com_VerifyLoop(int Key)
{
	int nKey;
	USER_INFO UserInfo;
	BOOL bResult;
	UINT64	nID;
	BYTE bDisabled;

	CInputUserID w(this); w.show();
	nID = w.DoProcess(FALSE);
	w.close();
	if (((int)nID == -1))
	{
		//VerifySManager0();
		return 0;
	}
	bResult = uiIDVerify(nID, &UserInfo, &bDisabled);
    if(!bResult)
    {
		CMessageBox msgBox(NULL);
		uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
		msgBox.SetIcon(QString(GUI_RESOURCE_PATH) + QString("icon-question.png"));
		msgBox.SetText(QString(UISTR(UISTR_PRESS_VERIFY_GET_DATA)));
		msgBox.show();
		msgBox.SetType(UI_MSG_QUESTION);

		if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
			LCD_BLANK(FBINFO_BLANK_RESUME);

		while (uiTimeIsTimeout(10000) == FALSE)
		{
			POST_EVENTS();

			nKey = uiKeyGetKey(TRUE);
			if (nKey == UIKEY_ESC)
				return 0;
			else if (nKey == UIKEY_OK)
				break;
		}
	    if(nKey == UIKEY_OK)
	    {
			if(ComClientGetVerifydata(nID))
				uiLcdMessageBox(UI_MSG_OK, UISTR_VERIFY_GET_DATA_SUCCESS, UI_MSGTIMEOUT);
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_GET_DATA_FAIL, UI_MSGTIMEOUT);
	    }
    }
	return 1;
}
*/

BOOL  Com_VerifyLoop(UINT64	nID)
{
	int nKey;
	xprintf("nIDxxxxx==%d\r\n",nID);

	CMessageBox msgBox(NULL);
	uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
	msgBox.SetIcon(QString(GUI_RESOURCE_PATH) + QString("icon-question.png"));
	msgBox.SetText(QString(UISTR(UISTR_PRESS_VERIFY_GET_DATA)));
	msgBox.show();
	msgBox.SetType(UI_MSG_QUESTION);

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	while (uiTimeIsTimeout(10000) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			return 0;
		else if (nKey == UIKEY_OK)
			break;
	}
	xprintf("nIDxxxxx1==%d\r\n",nID);
	if(QApplication::focusWidget()==(QWidget*)pMessageBoxbtnOK)
	{
        		int  nRet;
		
		//nRet=ComClientGetVerifydata(nID);//这里是从服务器获取信息的函数
		nRet=ComClientGetVerifydata_web2(nID);//这个是我添加的从服务器获取信息的函数add by loveywm 2012.10.25
		xprintf("nRet==%d\r\n",nRet);
		if(nRet==UIENROLL_RET_DUPLICATE)
		{
			xprintf("%d\r\n",UIENROLL_RET_DUPLICATE);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLFP_FPDOUBLED, 5000);
		}
		else if(nRet==UIENROLL_RET_TRUE)
		{
			xprintf("%d\r\n",UIENROLL_RET_TRUE);
			uiLcdMessageBox(UI_MSG_OK, UISTR_VERIFY_GET_DATA_SUCCESS, 5000);
		}
		else if(nRet==UIENROLL_NO_ENROLL_FP)
		{
			xprintf("%d\r\n",UIENROLL_NO_ENROLL_FP);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SERVER_NO_ENROLL_FP, 5000);
		}
		else if(nRet==UIENROLL_NO_ENROLL_ID)
		{
			xprintf("%d\r\n",UIENROLL_NO_ENROLL_ID);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SERVER_NO_ENROLL_ID, 5000);
		}		
		else
		{
			xprintf("no \r\n");
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_GET_DATA_FAIL, 5000);
		}
	}
	return 1;
}

//static volatile int __tcpclient_connect_status = 0;//0:没有连接1:已连接2:正在连接


void* tcpclient_connect_thread(void*/* arg*/)
{
// 	long* param = (long*)arg;
// 	__ENGINE_STATUS = fnSB_fp((int)param[0], param[1], param[2], param[3], param[4], param[5]);
	BOOL bRet = 0;
	//PACK	gPACK;//web2.0
	
	while (1)
	{
		//xprintf("__tcpclient==%d\r\n",__tcpclient_connect_status);
		if (__tcpclient_connect_status == 0)
		{
			if(Net_LinkIsOk())
			{
				__tcpclient_connect_status = 2;//表示正在连接服务器。。。  
				bRet = comm_tcpclient_connect();
				if(bRet==0)
				{
				  //comm_sendtime();
				  //xprintf("%s","comm_tcpclient_connect fail\n");
				  //DM9000_Reset();
				   __tcpclient_connect_status = 0;
				}
				else
				{
				  __tcpclient_connect_status = 1;	
				}
			}	
		}
/*		bzero(&gPACK, sizeof(gPACK));//web2.0
		if(__tcpclient_connect_status == 1 )
		{
			if (arm_comm_tcp_get_cmd3(Client_Sock, &gPACK))
			{						
				Com_CommanProc1(&gPACK);
			}			
		}
*/		//get_cmd();
		//sleep(2);  //10秒
	}	
}		
void  tcpclient_connect_start(void)
{
	if (dbLicense.byTcpipMode != TCPIP_CLIENT)
         	return ;
//xprintf("i am in tcpclient-connect_start!!\r\n");	
	if(Net_LinkIsOk() && __tcpclient_connect_status!=2)
	{
		//tcpclient_connect_threadStop();
		__tcpclient_connect_status = 0;
		//tcpclient_connect_Creatthread();
	}
}

void  tcpclient_connect_Set(BOOL data)
{
	__tcpclient_connect_status = data;
}

BOOL  tcpclient_connect_isok(void)
{
	if (dbLicense.byTcpipMode != TCPIP_CLIENT)
		return 1;
    if (__tcpclient_connect_status==1)
	    return 1;
	else 
		return 0;
}

pthread_t   tcpclient_connect_thread_id=0;

void  tcpclient_connect_Creatthread(void)
{
#if 0
	static struct task_struct * _task; 
	_task = kthread_run(tcpclient_connect_thread, NULL, "tcpclient_connect_thread");   
	if (!IS_ERR(_task))   
	{	
			printf("kthread_create done\n");   
			tcpclient_connect_thread_id=1;
	}	
	else  
	{	
			printf("kthread_create error\n");	
	}	
#endif

	pthread_attr_t attr;
	sched_param param;
	
	int newprio=100;

	if(tcpclient_connect_thread_id)
		return ;
	pthread_attr_init(&attr);
	pthread_attr_getschedparam(&attr, &param);
	param.sched_priority=newprio;
	pthread_attr_setschedparam(&attr, &param);	
	
	if (pthread_create(&tcpclient_connect_thread_id, &attr, tcpclient_connect_thread, NULL))
	{
		printf("Can't create engine thread\r\n");
	}
	pthread_attr_destroy(&attr);
}

void  tcpclient_connect_threadStop(void)
{
	if(tcpclient_connect_thread_id==0)
		return;
	pthread_detach(tcpclient_connect_thread_id);
	tcpclient_connect_thread_id=0;

	 if (Client_Sock)
	{
      		SOCKET_CLOSE(Client_Sock);   
 	}
	 __tcpclient_connect_status=1;
}


/************************************************************************/
#define IOCTL_WRITE_PHYADDR    0
#define IOCTL_READ_PHYADDR   1
#define IOCTL_OPEN_PHYADDR    2
#define IOCTL_CLOSE_PHYADDR   3
#define IOCTL_DM9000INDEX_READ   4
#define IOCTL_DM9000INDEX_WRITE   5
#define IOCTL_DM9000DATA_READ   6
#define IOCTL_DM9000DATA_WRITE   7
#define IOCTL_DM9000_INIT        8
#define IOCTL_LOCK_ON   9
#define IOCTL_LOCK_OFF        10




void OtherDev_Test(void)
{
    int addr,key,data;

	if (g_hOther != INVALID_HANDLE_VALUE)
	{	
        key=uiKeyGetKey();
		if (key == UIKEY_ESC)
		{
           ioctl(g_hOther, IOCTL_LOCK_ON, 0);
		}
		else if(key == UIKEY_OK)
		{
			ioctl(g_hOther, IOCTL_LOCK_OFF, 0);
		}
	}
}


void DM9000_Reset(void)
{
	ioctl(g_hOther, IOCTL_DM9000_INIT, 0);
    comm_sendtime();
    xprintf("%s", "dm9000 reset\n");	
    sleep(0.5);  //延时0.5秒
}


BOOL   LINK_LOST=1;

BOOL Net_LinkIsOk(void)
{
	DM9000_Check();
   if(LINK_LOST)
   	  return 0;
   else if(LINK_LOST==0)
      return 1;
}
extern BOOL http_WEB_CONNECT;
//u8 WEB_CONNECT_SIGN;

void DM9000_Check(void)
{
    //hiway del
/*
	if ((g_hOther != INVALID_HANDLE_VALUE) && dbLicense.bUseEthernet && dbSetupTotal.setSystem.bEthernetUse)
	{
        ioctl(g_hOther, IOCTL_DM9000INDEX_WRITE, 0x01);
		if((ioctl(g_hOther, IOCTL_DM9000DATA_READ, 0)&(1<<6))==0)//连接失败,网线断开
		{
			LINK_LOST=1;
			http_WEB_CONNECT=0;
			WEB_CONNECT_SIGN = 0;
		}	
		else
		{
			LINK_LOST=0;
		}

	}
*/
}

extern DWORD	dwGlogIndex;
/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL Com_CommanProc(CMDPKT* vCMD)
{
	int  nRet = TRUE;	

	dwRealTime = uiTimeGetTickCount();
	//dwTimeSynTime=dwRealTime;
	bSendAckTimeout=0;

	if(vCMD->Command!=ARM_CMD_REALTIME_LOG&&vCMD->Command!=ARM_CMD_REALTIME_SLOG&&vCMD->Command!=ARM_CMD_REALTIME_HEART)
	{
		if (!Com_SendCmdAck(CMD_ACK))
		{
			return FALSE;
		}
	}
	if (g_uiWorkingDisplay)
		uiProcDrawStatus();

	g_uiCommandProc = TRUE;

/*	if (vCMD->Command != ARM_CMD_REALTIME_HEART)
	{

		if (!g_bDisableDevice && vCMD->Command >= ARM_CMD_GET_ENROLL_DATA)
		{
	//		uiBuzzerAlarm();
			BUZZER_ALARM();
		}
		else
		{
			if (vCMD->Command >= CMD_DOWN_DOWNLOADER_WRITE && vCMD->Command != CMD_TEST_GET_IMAGE_ORG)
				BUZZER_ALARM();
		}
	}  */////1.34

//	Com_DispCmd(nCMD);

	switch (vCMD->Command)
	{
	case ARM_CMD_GET_OCX_KEY:
		Com_SendData((void*)"{D6EC2D9B-34E0-4ebf-BB2C-5DC0765392CF}", 38);
		break;
	case ARM_CMD_GET_ENROLL_DATA:
		if ( (vCMD->InParam&0x0f) == DATA_TYPE_FP )
			nRet = ComGetEnrollDataFP( vCMD );
		else if ( (vCMD->InParam&0x0f) == DATA_TYPE_PWD )
			nRet = ComGetEnrollDataPWD( vCMD );
		else if ( (vCMD->InParam&0x0f) == DATA_TYPE_CARD )
			nRet = ComGetEnrollDataCARD( vCMD );
		else
			nRet = FALSE;
		break;
	case ARM_CMD_SET_ENROLL_DATA:
		if ( (vCMD->InParam & 0xF) == DATA_TYPE_FP )
			nRet = ComSetEnrollDataFP( vCMD );
		else if ( (vCMD->InParam & 0xF) == DATA_TYPE_PWD )
			nRet = ComSetEnrollDataPWD( vCMD );
		else if ( (vCMD->InParam & 0xF) == DATA_TYPE_CARD )
			nRet = ComSetEnrollDataCARD( vCMD );
		else
			nRet = FALSE;
		break;
	case ARM_CMD_DELETE_ENROLL_DATA:		
		if ( (vCMD->InParam&0x0f) == DATA_TYPE_FP )
			nRet = ComDeleteEnrollDataFP( vCMD );
		else if ( (vCMD->InParam&0x0f) == DATA_TYPE_PWD )
			nRet = ComDeleteEnrollDataPWD( vCMD );
		else if ( (vCMD->InParam&0x0f)== DATA_TYPE_CARD )
			nRet = ComDeleteEnrollDataCARD( vCMD );
		else if ( (vCMD->InParam&0x0f) == DATA_TYPE_FP_ALL )
			nRet = ComDeleteEnrollDataAllFP( vCMD );
		else if ( (vCMD->InParam&0x0f) == DATA_TYPE_ALL )
			nRet = ComDeleteEnrollDataAll( vCMD );
		else
			nRet = FALSE;

//		if ( nRet == TRUE )
//			Com_SendExeResult( EXE_RES_TRUE, 0 );
//		else
//			Com_SendExeResult( EXE_RES_FALSE, 0 );
		break;
	case ARM_CMD_SLOG_GET_COUNT:  
		nRet = ComSlogGetCount();
		break;
	case ARM_CMD_SLOG_GET:
		nRet = ComSlogGet ( vCMD );
		break;
	case ARM_CMD_GLOG_GET_COUNT:  
		nRet = ComGlogGetCount();
		break;
	case ARM_CMD_GLOG_GET:
		nRet = ComGlogGet ( vCMD );
		break;
	case ARM_CMD_GLOG_GET_BYTIME:
		nRet = ComGlogGetByTime ( vCMD );
		break;
	case ARM_CMD_GLOG_GET_BYTIME_ALLSEARCH:
		nRet = ComGlogGetByTime_allsearch ( vCMD );
		break;
	case ARM_CMD_SLOG_GET_BYTIME:
		nRet = ComSlogGetByTime ( vCMD );
		break;
	case ARM_CMD_GET_ENROLLNUMBER_HEAD_LIST:
		nRet = ComEnrollNumberHeadListGet ( vCMD );
		break;	
	case ARM_CMD_SET_ENROLLNUMBER_HEAD_LIST:
		nRet = ComEnrollNumberHeadListSet ( vCMD );
		break;			
	case ARM_CMD_DEVICE_STATUS_GET: 
		nRet = ComDeviceStatusGet(vCMD);
		break;
	case ARM_CMD_DEVICE_INFO_GET:
		nRet = ComDeviceInfoGet(vCMD);
		break;
	case ARM_CMD_DEVICE_INFO_SET:
		nRet = ComDeviceInfoSet(vCMD);
		break;
	case ARM_CMD_DISABLE_DEVICE:
		g_bDisableDevice = comm_get_disabledevice();  
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		nRet = TRUE;
		break;
	case ARM_CMD_ENABLE_DEVICE:
		g_bDisableDevice = DISABLE_MODE_NONE;
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		nRet = TRUE;
		break;
	case ARM_CMD_ENABLE_USER:	  
		nRet = ComEnableUser(vCMD);
		break;
	case ARM_CMD_DEVICE_TIME_GET:
	case ARM_CMD_DEVICE_TIME_SET:
		nRet = ComDeviceTimeGetSet ( vCMD );
		break;
	case ARM_CMD_POWER_OFF:		  
		nRet = ComPowerOff();
		break;
	case ARM_CMD_MODIFY_PRIVILIGE:  ////////////////////////////
		nRet = ComModifyPrivilege(vCMD);
		break;
	case ARM_CMD_READ_ALL_USERID:///////////////////////////////////////
		nRet = ComReadAllUserID(vCMD);
		break;
	case ARM_CMD_SERIAL_NUM_GET:	  
		nRet = ComSerialNumGet();
		break;
	case ARM_CMD_CLEAR_KEEPER_DATA:		  
		nRet = ComClearKeeperData();
		break;
	case ARM_CMD_BACKUP_NUM_GET:	  
		nRet = ComBackupNumGet();
		break;
	case ARM_CMD_PRODUCT_CODE_GET:  
		nRet = ComProductCodeGet();
		break;
	case ARM_CMD_ENROLL_DATA_EMPTY:	  
		nRet = ComEnrollDataEmpty();
		break;
	case ARM_CMD_GLOG_EMPTY:	 
		nRet = ComGlogEmpty();
		break; 
	case ARM_CMD_SLOG_EMPTY:	 
		nRet = ComSlogEmpty();
		break;
	case ARM_CMD_USER_NAME_GET:	  
		nRet = ComUserNameGet(vCMD);
		break;
	case ARM_CMD_USER_NAME_SET:
		nRet = ComUserNameSet();
		break;
	case ARM_CMD_USER_NAME_GET_FOR:	  
		nRet = ComUserNameGet(vCMD);
		break;
	case ARM_CMD_USER_NAME_SET_FOR:
		nRet = ComUserNameSet();
		break;
	case ARM_CMD_COMPANY_NAME_GET:
		nRet = ComCompanyNameGet();
		break;
	case ARM_CMD_COMPANY_NAME_SET:  
		nRet = ComCompanyNameSet();
		break;
	case ARM_CMD_DOOR_STATUS_GET:	 
		nRet = ComDoorStatusGet();
		break;
	case ARM_CMD_DOOR_STATUS_SET:	 
		nRet = ComDoorStatusSet(vCMD);
		break;
	case ARM_CMD_BELLTIME_GET:  
		nRet = ComBellTimeGet();
		break;
	case ARM_CMD_BELLTIME_SET:  
		nRet = ComBellTimeSet();
		break;
 	case ARM_CMD_BACKUP_SERIAL_NUM_GET:	  
 		nRet = ComPassSerialNumGet();
 		break;
	case CMD_INTERNAL_CHECK_LIVE:  
		nRet = 1;
		break;
	case ARM_CMD_INTERNAL_CHECK_PWD:  
		nRet = arm_ComCheckPwd(vCMD);
		break;
	case ARM_CMD_PASS_TIME_SET:
		nRet = ComPassTimeSet();
		break;
	case ARM_CMD_PASS_TIME_GET:
		nRet = ComPassTimeGet();
		break;
	case  ARM_CMD_GROUP_SET:
		nRet = ComGroupSet();
		break;
	case ARM_CMD_GROUP_GET:
		nRet = ComGroupGet();
		break;
// 	case  ARM_CMD_LOCKGROUP_SET:                ///////////
// 		nRet = ComLockGroupSet();
// 		break;
// 	case ARM_CMD_LOCKGROUP_GET:               ///////////////
// 		nRet = ComLockGroupGet();
// 		break;
	case ARM_CMD_TIME_ZONE_SET:
		nRet = ComTimeZoneSet();
		break;
	case ARM_CMD_TIME_ZONE_GET:
		nRet = ComTimeZoneGet();
		break;
	case ARM_CMD_USER_CTRL_SET:
		nRet = ComUserCtrlSet();
		break;
	case ARM_CMD_USER_CTRL_GET:
		nRet = ComUserCtrlGet(vCMD);
		break;
	case ARM_CMD_DOOR_KEY_SET:
		nRet = ComDoorKeyParamSet();
		break;
	case ARM_CMD_DOOR_KEY_GET:
		nRet = ComDoorKeyParamGet();
		break;
	case ARM_CMD_LOG_WATCH:
		nRet = ComLogWatchGet(vCMD);
		g_uiCommandProc = FALSE;
		break;
// 	case ARM_CMD_LOGTIME_SET:
// 		nRet = ComLogtimeSet(vCMD);
// 		break;
// 	case ARM_CMD_LOGTIME_GET:
// 		nRet = ComLogtimeGet(vCMD);
// 		break;
	case ARM_CMD_SYSTEMNO_CHECK:
		nRet = ComSystemCheck(vCMD);
	    break;
	case ARM_CMD_SET_HOST_BY_NAME:
		nRet = ComHostByNameSet();
		break;
	case ARM_CMD_GET_HOST_BY_NAME:
		nRet = ComHostByNameGet();
		break;
	case ARM_CMD_REALTIME_LOG:		
		//bSendAckTimeout=0;
		if(dwGlogIndex==vCMD->Length)
		{
		    nRet = ComRealTimeLog();
		    dwGlogIndex++;
		}
		break;
	case ARM_CMD_REALTIME_SLOG:		
		//bSendAckTimeout=0;
		nRet = ComRealTimeSLog();
		break;		
	case ARM_CMD_IP_SET:  
		nRet = ComIPSet();
		break;
	case ARM_CMD_REALTIME_HEART:
		//bSendAckTimeout=0;
		Com_SendExeResult( EXE_RES_TRUE, 0 );
		break;

	case ARM_CMD_HTTP_ROMUPDATE:
		nRet = HttpGetRomFileName(vCMD);
		break;
    default:
		return  0;
		break;
		//////////////////////////////////////////////////////////////////////////
	}

	return TRUE;
}

static int HttpRomSocket=0;
DWORD DNS_SDDR_HttpRom=0;

struct sockaddr_in serverip_HttpRom;

struct sockaddr_in peer_HttpRom;

#define BUFSIZE                             (8192)


int HttpRomReceive(BYTE *_data,int _data_size)
{

	
	int nETime;
	int nReqSize = _data_size;
	int nReadSize = 0;
	BYTE * pBufIdx = _data;
	static bool b_readhead = true;
	int nTimeout;
	int nCurrentReadSize; 

	nTimeout=25000;
	nETime = GetMainTickCount() + nTimeout;
	
         wdog_app_alive();//added by hym
	while (GetMainTickCount() < nETime)	
	{

		nCurrentReadSize =BUFSIZ - 1;

		nCurrentReadSize = recv_timeout(HttpRomSocket, pBufIdx, nCurrentReadSize, 0,25);  
            wdog_app_alive();//added by hym
		if (nCurrentReadSize > 0)
		{	wdog_app_alive();//added by hym	
			pBufIdx += nCurrentReadSize;
			nReadSize += nCurrentReadSize;
			nETime = GetMainTickCount() + nTimeout;
			continue;
		}
		else if (nCurrentReadSize < 0)
		{
			if (errno == EWOULDBLOCK)
			{
				continue;
			}
		}
		break;
	} 
         wdog_app_alive();//added by hym

	xprintf("nReadsize==%d\r\n",nReadSize);
	return nReadSize;
}


bool HttpRomSend(string msg)
{

	int rc;

	if((rc = send_timeout(HttpRomSocket, msg.c_str(), msg.size(), 0,4)) == -1)
	{
		if((errno != EWOULDBLOCK) && (errno != EAGAIN))
		{
			close(HttpRomSocket);
			return false;
		}
	}
	return true;
}



DWORD			HTTPROMFtp_ip;														//4

char* Http_CfgstrGetFILELEN(char *buff,char *dest1,char *dest2,char *ret);
/*
int atoi(char *nptr)
{
	int j;
	j=0;
	for(int i = 0;nptr[i]!='/0';i++)
	{
		j=j*10+nptr[i];
	}
	return j;
}
*/

bool HttpRomConnect(string hostname)
{



	xprintf("%s\r\n","connect start"); 
	int fd;
	int a,b,c,d;
	struct timeval timeo;
	char str_data[64];
	char str_port[6];
	WORD  whttpPortNum;
       	whttpPortNum=0;

       if(HttpRomSocket)
		close( HttpRomSocket );		

	   
	fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( fd < 0 )
	{
		xprintf("%s\r\n","socket call failed");
		return false;
	}
/*
	用 strcpy

char cstr1[80];
string str2;
strcpy( cstr1, str2.c_str() );

这样子就可以了。
*/
	//strcpy(dbSetupTotal.setSystem.szHttpRomFileName,hostname.c_str());
	//const char *Hostname = hostname.c_str();
	//const char *Hostname = hostname;

	//strcpy(dbSetupTotal.setSystem.szHttpRomFileName,Hostname);
	//memcpy(dbSetupTotal.setSystem.szHttpRomFileName,Hostname,sizeof(Hostname));
	
       	xprintf(" hostname=%s\r\n",hostname.c_str());
	xprintf(" dbSetupTotal.setSystem.szHttpRomFileName=%s\r\n",dbSetupTotal.setSystem.szHttpRomFileName);	  
	memset(str_data,0,sizeof(str_data));
	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName,"//",":",str_data)==0) 
	{

		   	xprintf("%s\r\n","2222");

		    	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName,"//","/",str_data)==0) 
			{
				  xprintf("%s\r\n","Http_CfgstrGet2");
	 			  return 0;   
			}
	}
	else
	{
                      	xprintf("str_data=%s\r\n",str_data);
		     	xprintf("%s\r\n","555");
			memset(str_port,0,sizeof(str_port));
                   	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName+10,":","/",str_port)==0) 
                   	{
                   		     xprintf("%s\r\n","str_port  err");
	 			     return 0;   
                   	}
			xprintf("str_port=%s\r\n",str_port);	
			whttpPortNum=atoi(str_port);
	}
	if(whttpPortNum==0)
		whttpPortNum=80;
		 xprintf("whttpPortNum=%d\r\n",whttpPortNum);		
	



    	xprintf("str_data=%s\r\n",str_data);
     	HTTPROMFtp_ip= ntohl( inet_addr(str_data)); 

	 UI_IP_UNMAKE(HTTPROMFtp_ip, a, b, c, d);
	 
    	 xprintf("HTTPROMFtp_ip=%d.%d.%d.%d\r\n",a,b,c,d);

	bzero( &peer_HttpRom, sizeof(peer_HttpRom) );
	peer_HttpRom.sin_family = AF_INET;
	if (dbSetupTotal.setSystem.szHostByName[0]==0)
	{
            	peer_HttpRom.sin_addr.s_addr = htonl(HTTPROMFtp_ip);
		peer_HttpRom.sin_port	= htons(whttpPortNum);		
		xprintf("dbSetupTotal.setSystem.szHostByName[0]==0\n");
	}
	else
 	{
 	         if(DNS_SDDR_HttpRom==0)
 	         	{
 				xprintf("host name:%s\r\n",hostname.c_str());
 				
 		     		wdog_app_alive();//added by hym
 			      DNS_SDDR_HttpRom=gngethostbyname((char *)hostname.c_str(),1);
 				 xprintf("DNS_SDDR=%d\r\n",DNS_SDDR_HttpRom);
 			     if(DNS_SDDR_HttpRom==0)
 			      {
 				     xprintf("unknow host:%s\r\n",hostname.c_str());
 				     memset(&serverip_HttpRom,0,sizeof(serverip_HttpRom));
 				     close(fd);
 				     return false;
 			       }
 	         	}
 			       peer_HttpRom.sin_addr.s_addr = htonl(DNS_SDDR_HttpRom);
 			       peer_HttpRom.sin_port	= htons(80);
 			       serverip_HttpRom=peer_HttpRom;
 
 	}

	//if( connect( fd, (struct sockaddr *)&peer, sizeof( peer ) ) )
	xprintf("%s\n","connect...");
	if( connect_timeout( fd, (struct sockaddr *)&peer_HttpRom, sizeof( struct sockaddr ) ,20) )
	{
		//cout << errno << "connect failed" << endl;
		xprintf("%s\n","connect failed");
		DNS_SDDR_HttpRom=0;
		close( fd );		
		return false;
	}
	HttpRomSocket = fd;    
	return true;
}
bool HttpRomConnect1(string hostname)
{
	xprintf("%s\r\n","connect start"); 
	int fd;
	int a,b,c,d;
	struct timeval timeo;
	char str_data[64];
	char str_port[6];
	WORD  whttpPortNum;
       	whttpPortNum=0;

       if(HttpRomSocket)
		close( HttpRomSocket );		

	   
	fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( fd < 0 )
	{
		xprintf("%s\r\n","socket call failed");
		return false;
	}
/*
	用 strcpy

char cstr1[80];
string str2;
strcpy( cstr1, str2.c_str() );

这样子就可以了。
*/

	memset(dbSetupTotal.setSystem.szHttpRomFileName,0,sizeof(dbSetupTotal.setSystem.szHttpRomFileName));
	strcpy(dbSetupTotal.setSystem.szHttpRomFileName,hostname.c_str());
	//const char *Hostname = hostname.c_str();
	//const char *Hostname = hostname;

	//strcpy(dbSetupTotal.setSystem.szHttpRomFileName,Hostname);
	//memcpy(dbSetupTotal.setSystem.szHttpRomFileName,Hostname,sizeof(Hostname));
	
       xprintf(" hostname=%s\r\n",hostname.c_str());
	xprintf(" dbSetupTotal.setSystem.szHttpRomFileName=%s\r\n",dbSetupTotal.setSystem.szHttpRomFileName);	  
	memset(str_data,0,sizeof(str_data));
	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName,"//",":",str_data)==0) 
	{

		   	xprintf("%s\r\n","2222");

		    	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName,"//","/",str_data)==0) 
			{
				  xprintf("%s\r\n","Http_CfgstrGet2");
	 			  return 0;   
			}
	}
	else
	{
                    xprintf("str_data=%s\r\n",str_data);
		     	xprintf("%s\r\n","555");
			memset(str_port,0,sizeof(str_port));
                   	if(Http_CfgstrGetFILELEN((char *)dbSetupTotal.setSystem.szHttpRomFileName+10,":","/",str_port)==0) 
                   	{
                   		     xprintf("%s\r\n","str_port  err");
	 			     return 0;   
                   	}
			xprintf("str_port=%s\r\n",str_port);	
			whttpPortNum=atoi(str_port);
	}
	if(whttpPortNum==0)
		whttpPortNum=80;
	xprintf("whttpPortNum=%d\r\n",whttpPortNum);		
	



    	xprintf("str_data=%s\r\n",str_data);
     	HTTPROMFtp_ip= ntohl( inet_addr(str_data)); 

	 UI_IP_UNMAKE(HTTPROMFtp_ip, a, b, c, d);
	 
    	 xprintf("HTTPROMFtp_ip=%d.%d.%d.%d\r\n",a,b,c,d);

	bzero( &peer_HttpRom, sizeof(peer_HttpRom) );
	peer_HttpRom.sin_family = AF_INET;
	if (dbSetupTotal.setSystem.szHostByName[0]==0)
	{
            	peer_HttpRom.sin_addr.s_addr = htonl(HTTPROMFtp_ip);
		peer_HttpRom.sin_port	= htons(whttpPortNum);		
		xprintf("dbSetupTotal.setSystem.szHostByName[0]==0\n");
	}
	else
 	{
 	         if(DNS_SDDR_HttpRom==0)
 	         	{
 				xprintf("host name:%s\r\n",hostname.c_str());
 				
 		     		wdog_app_alive();//added by hym
 			      DNS_SDDR_HttpRom=gngethostbyname((char *)hostname.c_str(),1);
 				 xprintf("DNS_SDDR=%d\r\n",DNS_SDDR_HttpRom);
 			     if(DNS_SDDR_HttpRom==0)
 			      {
 				     xprintf("unknow host:%s\r\n",hostname.c_str());
 				     memset(&serverip_HttpRom,0,sizeof(serverip_HttpRom));
 				     close(fd);
 				     return false;
 			       }
 	         	}
 			       peer_HttpRom.sin_addr.s_addr = htonl(DNS_SDDR_HttpRom);
 			       peer_HttpRom.sin_port	= htons(80);
 			       serverip_HttpRom=peer_HttpRom;
 
 	}

	//if( connect( fd, (struct sockaddr *)&peer, sizeof( peer ) ) )
	xprintf("%s\n","connect...");
	if( connect_timeout( fd, (struct sockaddr *)&peer_HttpRom, sizeof( struct sockaddr ) ,20) )
	{
		//cout << errno << "connect failed" << endl;
		xprintf("%s\n","connect failed");
		DNS_SDDR_HttpRom=0;
		close( fd );		
		return false;
	}
	HttpRomSocket = fd;    
	return true;
}

char* Http_CfgstrGetFILELEN(char *buff,char *dest1,char *dest2,char *ret)
{
	int dest_len;
	char *pos1 = 0;
	char *pos2 = 0;	
	//char str_out[30]; 

	dest_len=strlen(dest1);	
	pos1 = mystrstr(buff, dest1);
	if(pos1)
	   pos2 = mystrstr(pos1+2,dest2);	
	if(pos1 && pos2 && (pos1!=pos2))
	{
	    strncpy(ret,pos1+dest_len,pos2-pos1-dest_len); 
	}
	else
	{
		return 0;
	}

	return (pos2);

}

//////////////////////////////////////////////////////////////////////////
UINT64 STRING2FILESIZE(char* strID)
{
	int nLength, i;
	UINT64 nID = 0;
	BYTE number;

	if ((nLength = strlen(strID)) > 8)
		return 0;

	for (i=0; i<nLength; i++)
	{
	      nID *= 10;

		if (strID[i] >= '0' && strID[i] <= '9')
			number = strID[i] - '0';
		else
			number = 0;
		nID += number;
	}

	return nID;
}

BOOL HttpGetRomFileName(CMDPKT* pCMD)
{

	char  HttpFileName[256];


      memset(HttpFileName,'\0',sizeof(HttpFileName));
	if ( pCMD->InParam == 0 )
	{
		if(Com_RecData(&HttpFileName, 256) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("1 HttpGetRomFileName=%s\r\n",HttpFileName);
			return FALSE;
		}
	      memcpy(dbSetupTotal.setSystem.szHttpRomFileName, HttpFileName, sizeof(HttpFileName)); 
		Com_SendExeResult( EXE_RES_TRUE, 1 );
		xprintf("5dbSetupTotal.setSystem.szHttpRomFileName=%s\r\n",dbSetupTotal.setSystem.szHttpRomFileName);
		DbSetupTotalSave();
	}
	else
	{
	   	if(Com_RecData(&HttpFileName, 256) != 1)
		{
			Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("1 HttpGetRomFileName=%s\r\n",HttpFileName);
			return FALSE;
		}
	      memcpy(dbSetupTotal.setSystem.szHttpRomFileName, HttpFileName, sizeof(HttpFileName)); 
		Com_SendExeResult( EXE_RES_TRUE, 1 );
		DbSetupTotalSave();
	   xprintf("2 HttpGetRomFileName=%s\r\n",dbSetupTotal.setSystem.szHttpRomFileName);
	   HttpRomWrite(dbSetupTotal.setSystem.szHttpRomFileName);
	   system("reboot");
	}
	


}

BOOL HttpRomWrite1(string word)
{
	BOOL bRet = TRUE;
	BYTE* pRomImage;
	BYTE * pRomImage2;

	//string filename;
	string hostname;
	//string pin;
	//string dept;
	int pos1 = 0;
	int pos2 = 0;	
	char temp[64];
	char str_data[64];
	char str_FILESIZE[10]; 
   	 int len,len2;
	
/*	if(tcpclient_connect_isok()==0)
		return 0;
	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
		return 0;
*/
	tcpclient_connect_threadStop();
	
	//bulid the query for http
	string quest = "GET ";
	quest += word;
	quest += " HTTP/1.0\r\n";
	quest += "User-agent:Mozilla/4.0\r\n";
	quest += "Accept-language:zh-cn\r\n\r\n";

	//get the hostname and filename from the word
	//string substr(int pos = 0,int n = npos) const;//返回pos开始的n个字符组成的字符串
	//int find_first_of(char c, int pos = 0) const;//从pos开始查找字符c第一次出现的位置
	//http://192.168.10.47/wcfclient/update/SB3300-5Kv1.35.1536.61.bin
	xprintf("\r\nword:%s\r\n",word.c_str());
	string str_http = "http://";
	pos1 = word.find_first_of (str_http, 0);
	pos2 = word.find_first_of ("/", pos1+7);
	hostname = word.substr( pos1+7, pos2-pos1-7 );
	pos1 = word.find_last_of( "/", word.size() );
	
	xprintf("\r\nhostname:%s\r\n",hostname.c_str());
	xprintf("\r\nquest:%s\r\n",quest.c_str());
	
	pRomImage = (BYTE *)malloc(17*1024*1024);
	if (!pRomImage)
	{
		xprintf("%s\r\n","malloc error");
		return 0;
	}

      if(!HttpRomConnect1(word))
      	{
      	    	xprintf("%s\r\n","HttpRomConnect error");
      	   	FREE(pRomImage);
	   	return 0;
      	}

	  if(!HttpRomSend(quest))
	  	{
	  	     xprintf("%s\r\n","HttpRomSend error");
	      	       FREE(pRomImage);
	 		  return 0;  	
	  	}

	CMessageBox *msgBox; 
      	msgBox	= new CMessageBox; 
	//msgBox->MsgBoxProc_Message("Wait for moment ...");
	msgBox->MsgBoxProc_Message3(UISTR(UISTR_WAIT_FOR_COMMUNICATING));
	//msgBox->MsgBoxProc_Message((char *)UISTR(UISTR_WAIT_FOR_COMMUNICATING));

	//uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	int datalen=HttpRomReceive(pRomImage,17*1024*1024);
	
	//uiLcdProgressEnd();
	if(msgBox)
          delete msgBox;    
   
	   
         xprintf("datalen =%d\r\n",datalen);
	//xprintf("%s\r\n",(const char *)pRomImage); 
    	if(datalen==0)
	{
	      xprintf("%s\r\n","atalen==0");
	   	FREE(pRomImage);
	   	return 0;
	}

	
	memset(str_data,0,sizeof(str_data));
	if(Http_CfgstrGet2((char *)pRomImage,"Content-Length: ","w",str_data)==0) 
	{
	   	xprintf("%s\r\n","Http_CfgstrGet2");
	   
	  	FREE(pRomImage);
	  	return 0;   
	}
	xprintf("\r\n%s\r\n",str_data);	
	xprintf("\r\n%x\r\n",str_data);	
	len2=datalen-AsciiToDec(str_data); 
	len=AsciiToDec(str_data); 
	xprintf("len=%d\r\n",len); 
	xprintf("len2=%d\r\n",len2); 

	
	POST_EVENTS();
	
	pRomImage2=&pRomImage[len2];
	xprintf("pRomImage2[0]=%x\r\n",*(pRomImage2+0)); 
	xprintf("pRomImage2[1]=%x\r\n",*(pRomImage2+1)); 
	xprintf("pRomImage2[2]=%x\r\n",*(pRomImage2+2)); 
	xprintf("pRomImage2[3]=%x\r\n",*(pRomImage2+3));
	xprintf("before uiLcdProgressDlgShow1\r\n");
	// g_bProgress = TRUE;
	 //xprintf("before uiLcdProgressDlgShow2\r\n");
	//uiLcdProgressDlgShow(UISTR_FILEWRITE);	
	bRet = _Db_FWWriteToFlash((unsigned char *)&pRomImage[len2], len);	
	//uiLcdProgressDlgExit(); 
	//g_bProgress = FALSE;

	xprintf("bRet=%d\r\n",bRet);
	
	FREE(pRomImage);

	/*	g_params.ipAddress = dbSetupTotal.setSystem.ipAddress;
		g_params.ipSubnetMask = dbSetupTotal.setSystem.ipSubnetMask;
		g_params.ipDefaultGateway =  dbSetupTotal.setSystem.ipDefaultGateway;
		g_params.dwCommPassword = dbSetupTotal.setSystem.dwCommPassword;
		g_params.wPortNum = dbSetupTotal.setSystem.wPortNumBack;
           	g_params.nBaudrate=dbSetupTotal.setSystem.nBaudrate;
		memcpy( g_params.byMACaddr, dbLicense.byMACaddr, 6);
		g_params.nMachineID= dbSetupTotal.setSystem.nMachineID;
		DbParamInfoSave();
  	*/	//SB_EXEC("reboot"); 
  		//system("reboot");
  		

	return bRet;
}



BOOL HttpRomWrite(string word)
{
	BOOL bRet = TRUE;
	BYTE* pRomImage;
	BYTE * pRomImage2;

	//string filename;
	string hostname;
	//string pin;
	//string dept;
	int pos1 = 0;
	int pos2 = 0;	
	char temp[64];
	char str_data[64];
	char str_FILESIZE[10]; 
   	 int len,len2;
	
/*	if(tcpclient_connect_isok()==0)
		return 0;
	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
		return 0;
*/
	tcpclient_connect_threadStop();
	
	//bulid the query for http
	string quest = "GET ";
	quest += word;
	quest += " HTTP/1.0\r\n";
	quest += "User-agent:Mozilla/4.0\r\n";
	quest += "Accept-language:zh-cn\r\n\r\n";

	//get the hostname and filename from the word
	//string substr(int pos = 0,int n = npos) const;//返回pos开始的n个字符组成的字符串
	//int find_first_of(char c, int pos = 0) const;//从pos开始查找字符c第一次出现的位置
	//http://192.168.10.47/wcfclient/update/SB3300-5Kv1.35.1536.61.bin
	xprintf("\r\nword:%s\r\n",word.c_str());
	string str_http = "http://";
	pos1 = word.find_first_of (str_http, 0);
	pos2 = word.find_first_of ("/", pos1+7);
	hostname = word.substr( pos1+7, pos2-pos1-7 );
	pos1 = word.find_last_of( "/", word.size() );
	
	xprintf("\r\nhostname:%s\r\n",hostname.c_str());
	xprintf("\r\nquest:%s\r\n",quest.c_str());
	
	pRomImage = (BYTE *)malloc(17*1024*1024);
	if (!pRomImage)
	{
		xprintf("%s\r\n","malloc error");
		return 0;
	}

      if(!HttpRomConnect(word))
      	{
      	    	xprintf("%s\r\n","HttpRomConnect error");
      	   	FREE(pRomImage);
	   	return 0;
      	}

	  if(!HttpRomSend(quest))
	  	{
	  	     xprintf("%s\r\n","HttpRomSend error");
	      	       FREE(pRomImage);
	 		  return 0;  	
	  	}

	CMessageBox *msgBox; 
      	msgBox	= new CMessageBox; 
	//msgBox->MsgBoxProc_Message("Wait for moment ...");	
	msgBox->MsgBoxProc_Message3(UISTR(UISTR_WAIT_FOR_COMMUNICATING));
       	int datalen=HttpRomReceive(pRomImage,17*1024*1024);

	if(msgBox)
          delete msgBox;    
   
	   
         xprintf("datalen =%d\r\n",datalen);
	xprintf("%s\r\n",(const char *)pRomImage); 
    	if(datalen==0)
	{
	      xprintf("%s\r\n","atalen==0");
	   FREE(pRomImage);
	   return 0;
	}


	memset(str_data,0,sizeof(str_data));
	if(Http_CfgstrGet2((char *)pRomImage,"Content-Length: ","w",str_data)==0) 
	{
	   xprintf("%s\r\n","Http_CfgstrGet2");
	   
	  FREE(pRomImage);
	  return 0;   
	}
	xprintf("\r\nywm==%s\r\n",str_data);	
	xprintf("\r\nywm1==%x\r\n",str_data);	
	len2=datalen-AsciiToDec(str_data); 
	len=AsciiToDec(str_data); 
	xprintf("len=%d\r\n",len); 
	xprintf("len2=%d\r\n",len2); 

	
	POST_EVENTS();
	
	pRomImage2=&pRomImage[len2];
	xprintf("pRomImage2[0]=%x\r\n",*(pRomImage2+0)); 
	xprintf("pRomImage2[1]=%x\r\n",*(pRomImage2+1)); 
	xprintf("pRomImage2[2]=%x\r\n",*(pRomImage2+2)); 
	xprintf("pRomImage2[3]=%x\r\n",*(pRomImage2+3)); 
	 g_bProgress = TRUE;
	uiLcdProgressDlgShow(UISTR_FILEWRITE);	
	bRet = _Db_FWWriteToFlash((unsigned char *)&pRomImage[len2], len);	
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	  xprintf("bRet=%d\r\n",bRet);
	
	FREE(pRomImage);

		g_params.ipAddress = dbSetupTotal.setSystem.ipAddress;
		g_params.ipSubnetMask = dbSetupTotal.setSystem.ipSubnetMask;
		g_params.ipDefaultGateway =  dbSetupTotal.setSystem.ipDefaultGateway;
		g_params.dwCommPassword = dbSetupTotal.setSystem.dwCommPassword;
		g_params.wPortNum = dbSetupTotal.setSystem.wPortNumBack;
            g_params.nBaudrate=dbSetupTotal.setSystem.nBaudrate;
		memcpy( g_params.byMACaddr, dbLicense.byMACaddr, 6);
		g_params.nMachineID= dbSetupTotal.setSystem.nMachineID;
		DbParamInfoSave();
  		SB_EXEC("reboot"); 

	return bRet;
}

/*
*下面是为web2.0增加 的内容，供移植时复制
*
*/
//制作发送头
void web_make_packhead(PACK_HEAD *packhead,u32 head,u32 cmd,u32 datalen)
{
	packhead->Head = (head);
	packhead->Cmd  = (cmd);
	packhead->Cmd_Serial = 0;
	packhead->Cmd_Step = 0;
	packhead->DeviceID = (DEVID);
	packhead->Datalen = (datalen);
}
//校验和输出函数
u32 comm_csum1(void* pbuf, int nsize)
{
	u32 csum = 0;
	int i;
	
	for(i=0;i<nsize;i++)
		csum += ((BYTE*)pbuf)[i];
	
	return csum;
}

//制作连接发送包，并发送出去
void make_connect(void)
{
	PACK_HEAD 	packhead;	
	st_connectInfo	connectinfo;

	bzero(&connectinfo, sizeof(st_connectInfo));
	static u8 buf[SEND_CONNECT_SIZE];
	u32 *checksum = (u32 *)&buf[SEND_CONNECT_SIZE - 4];
	//制作头
	web_make_packhead(&packhead, SEND_HEAD, CMD_CONNECT, sizeof(st_connectInfo));
	//制作发送内容
	memcpy(connectinfo.mVersion,LNSC_FIRMWAREVERSION,sizeof(LNSC_FIRMWAREVERSION));
	connectinfo.DeviceId = DEVID;
	connectinfo.xxx.loveywm.ip = dbComm_ipAddress; 
	connectinfo.xxx.loveywm.sm = dbComm_ipSubnetMask;
	connectinfo.xxx.loveywm.gw = dbComm_ipDefaultGateway;
	connectinfo.xxx.loveywm.dhcp = dbComm_ipIsDHCP;
	//memcpy(connectinfo.xxx.loveywm.MAC,g_byMACaddr_default,6);
	memcpy(connectinfo.xxx.loveywm.MAC,g_params.byMACaddr,6);
	
	//分别填入发送的数组
	memcpy(buf,&packhead,PACK_HEAD_SIZE);
	memcpy(buf + PACK_HEAD_SIZE,&connectinfo,sizeof(st_connectInfo));

	//在此加入加密算法,只加密数据
	ks(buf + PACK_HEAD_SIZE ,sizeof(st_connectInfo));

	
	//制作发送检验和
	u32 sum = SEND_CONNECT_SIZE - 4;
	*checksum = comm_csum1(buf, sum);

	
	//发送
	comm_tcpclient_send(buf,SEND_CONNECT_SIZE);

	web2_recv_data(1000);

/*
	int nETime;
	int nTimeout = 1000;//这个时间待定
	nETime = GetMainTickCount() + nTimeout;
	while(GetMainTickCount() < nETime)
	{
		if(__tcpclient_connect_status == 1)//首先确定连接到服务端
		{
			
			//xprintf("111111111111111\r\n");
			PACK_HEAD gPACK;//web2.0
			bzero(&gPACK, sizeof(gPACK));//web2.0
			if (web2_get_cmd(Client_Sock, &gPACK))
			{					
				web2_run_cmd(Client_Sock,&gPACK);
				comm_mode = COMM_MODE_NONE;
				comm_sub_mode = -1;			
			}
			//xprintf("yyyyyyyy==%d\r\n",WEB_CONNECT_SIGN);
			if(WEB_CONNECT_SIGN == FALSE)
			{
				continue;
			}
		}
		xprintf("WEB_CONNECT_SIGN==%d\r\n",WEB_CONNECT_SIGN);
				if(WEB_CONNECT_SIGN == TRUE)
				{
					goto ywm1;
				}
				if(WEB_CONNECT_SIGN == FALSE)
				{
					goto ywm0;
				}
	}
	
ywm0:
	xprintf("i am in ywm000\r\n");
	//sleep(2);
	WEB_CONNECT_SIGN = FALSE;
	connect_count++;
	if(connect_count == 2)//递归3次发送
	{
		connect_count = 0;
		goto ywm1;
	}
	//make_connect();//这里存在递归问题，时间很长的话，回出现内存问题，这个要注意

ywm1:	
	xprintf("i am in ywm111\r\n");*/	
}

BOOL web2_get_cmd(HFILE hSock, PACK_HEAD* pvCMD)
{

	//xprintf("22222\r\n");
	if (comm_sockrecv(hSock, pvCMD, CMDWEBSIZE, TCP_RECV_CMD_TIMEOUT) <= CMDWEBSIZE)
	{
		//解密算法
		//ks_f((u8 *)pvCMD,CMDWEBSIZE);


		//这个只是为了打印信息的	
		if(pvCMD->Head != NULL)
		{
			xprintf("###########################################\r\n");
			xprintf(" head=%p\r\n",pvCMD->Head);
			xprintf(" cmd=%p\r\n",pvCMD->Cmd);
			xprintf(" cmd_serial=%p\r\n",pvCMD->Cmd_Serial);
			xprintf(" cmd_step=%p\r\n",pvCMD->Cmd_Step);
			xprintf(" deviceid=%p\r\n",pvCMD->DeviceID);
			xprintf(" datalen=%d\r\n",pvCMD->Datalen);
			//xprintf("checksum=%d\r\n",pvCMD->CheckSum);
			xprintf("###########################################\r\n");
		}
		if(pvCMD->Head == NULL)
		{		
			return 	CMD_WEB_NAK;
		}

		if((pvCMD->Head  !=  SEND_HEAD) && (pvCMD->Head)  !=  RECV_HEAD)
		{
			xprintf("the head is wrong!!\r\n");
			xprintf("head==%p\r\n",pvCMD->Head);
			return 	CMD_WEB_NAK;
		}
		//这个设备号检测可以暂时不要
		if((pvCMD->DeviceID) != DEVID)
		{
			xprintf("no this deviceid!!\r\n");
			xprintf("deviceid=%p\r\n",pvCMD->DeviceID);
			return 	CMD_WEB_NAK;
		}
		
		return TRUE;
		
	}

	xprintf("55555\r\n");

	return FALSE;

}

//这个函数主要是接受头后，
//分析头代表的意思，进行switch
//然后再分开进行数据接受，
//最后开始运行命令的含义
//extern DWORD	dwGlogIndex;
u8 web2_run_cmd(HFILE hSock, PACK_HEAD* vCMD)
{
	u8 nRet;
	u32 checksum;
	//处理头部校验和
	u32 checksum_head = comm_csum1(vCMD,PACK_HEAD_SIZE);
	xprintf("checksum_head==%d\r\n",checksum_head);

	//接受剩余没有被接受的数据
	u32 datalen = vCMD->Datalen + sizeof(u32);
	u8  *recvdatabuf = (u8 *)malloc(datalen);
	while(recvdatabuf == NULL)//循环，直到分配到空间
	{
		recvdatabuf = (u8 *)malloc(datalen);
	}	
	if (comm_sockrecv(hSock,recvdatabuf, datalen, TCP_RECV_CMD_TIMEOUT) <= datalen)
	{
		

		////////////////////////////////////////////////////
		dwRealTime = uiTimeGetTickCount();
		bSendAckTimeout=0;	
		if (g_uiWorkingDisplay)
			uiProcDrawStatus();
		g_uiCommandProc = TRUE;
		////////////////////////////////////////////////////
		//处理总校验和
		u32 checksum_data = comm_csum1(recvdatabuf,vCMD->Datalen);
		xprintf("checksum_data==%d\r\n",checksum_data);
		memcpy(&checksum,recvdatabuf + vCMD->Datalen,4);
		xprintf("checksum==%d\r\n",checksum);
		xprintf("checksum_data + checksum_head==%d\r\n",checksum_data + checksum_head);
		if(checksum != (checksum_data + checksum_head))
		{
			xprintf("checksum wrong!!\r\n");
			//send_ack(0, vCMD->Pack_Head.Cmd, CHECKSUM_ERROR, vCMD);
			free(recvdatabuf);
			return FALSE;
		}
		
		//解密算法
		ks_f(recvdatabuf,datalen - 4);
		
		switch(vCMD->Cmd)
		{
			case CMD_CONNECT: //确认连接			
				nRet = web2_cmd_connect(vCMD,recvdatabuf);
				break;
			case	CMD_REALTIME_LOG:   //确认主动上传记录成功
				nRet = web2_realtime_log(vCMD,recvdatabuf);
				break;
			case	CMD_UPLOAD_FINGER:   //确认上传指纹成功
				nRet = web2_upload_finger(vCMD,recvdatabuf);
				break;	
			case CMD_GET_LOG:   //PC获取记录
				nRet = web2_cmd_get_log(vCMD,recvdatabuf);
				//sleep(3);
				break;
			case CMD_GET_USER_REG:   //PC获取用户注册信息
				nRet = web2_cmd_get_user_reg(vCMD,recvdatabuf);
				break;
			case CMD_SET_USER_REG:	//PC下发用户注册信息//	
				nRet = web2_cmd_set_user_reg(vCMD,recvdatabuf);
				break;
			case CMD_DEL_USER_REG:	//PC用户删除	
				nRet = web2_cmd_del_user_reg(vCMD,recvdatabuf);
				break;
			case CMD_MOD_PRVILEGE:	//PC下发权限设置
				nRet = web2_cmd_mod_prvilege(vCMD,recvdatabuf);
				break;
			case CMD_GET_ALL_USERID:   //PC 获取用户列表//
				nRet = web2_cmd_get_all_userid(vCMD);
				break;
			case CMD_DEL_DATA:	//PC 删除数据记录
				nRet = web2_cmd_del_data(vCMD,recvdatabuf);
				break;
			case CMD_UPGRADE_ADDR:	//PC 下发升级地址
				nRet = web2_cmd_upgrade_addr(vCMD,recvdatabuf);
				break;
			case CMD_SET_TIME:    //PC 设置时间
				nRet = web2_cmd_set_time(vCMD,recvdatabuf);
				break;
			case CMD_GET_TIME:   //PC 获取时间
				nRet = web2_cmd_get_time(vCMD);
				xprintf("send_data is ok!!\r\n");
				break;
			case CMD_SET_MAC://设置mac地址
				nRet = web2_cmd_set_mac(vCMD,recvdatabuf);
				SystemReset();
				break;
			default:
				break;
		
		}	
	}
	xprintf("*************************************************\r\n");
	free(recvdatabuf);
	return nRet;
}

u8 web2_cmd_connect( PACK_HEAD* vCMD,u8 *recvdata)
{
				
	if(*recvdata == 1)
	{
		xprintf("connected is ok!!\r\n");						
		http_WEB_CONNECT=TRUE;
		WEB_CONNECT_SIGN = TRUE;
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-ok.png"));
		g_MainWindow->ui.lblNet->show();
	}
	else
	{
		xprintf("connected is failed!!\r\n");   		
		http_WEB_CONNECT=FALSE;
		WEB_CONNECT_SIGN = FALSE;
		g_MainWindow->ui.lblNet->setPixmap(QPixmap(GUI_RESOURCE_PATH"net-err.png"));
		g_MainWindow->ui.lblNet->show();
	}
	return true;
}

u8 web2_upload_finger( PACK_HEAD* vCMD,u8 *recvdata)
{
	if(*recvdata == 1)
	{
		xprintf("realtime_log is ok!!\r\n");
				
	}
	else
	{
		xprintf("realtime_log is failed!!\r\n");
	}
	return true;

}

u8 web2_realtime_log( PACK_HEAD* vCMD,u8 *recvdata)
{
	if(*recvdata == 1)
	{
		//只有返回索引与上传的对应才加1 modify:2013.03.29
		if(vCMD->Cmd_Serial == DbGLogGetReadPos())
		{	
			xprintf("realtime_log is ok!!\r\n");
			int nGLogReadCnt = DbGLogGetReadPos();
			DbGLogSetReadPosOnly((nGLogReadCnt+1) % dbLicense.nGlogMaxCount);
			//dwGlogIndex++;
		}
	}
	else
	{
		xprintf("realtime_log is failed!!\r\n");
		return FALSE;
	}
	return true;
}


u8 web2_glog_get_bytime(PACK_HEAD* vCMD, GetGLogCondition *pCMD)
{
	DWORD count;
	int SendCount;
	DWORD LogIndex[3],dwSeconds,ret=0;
	int pos;
	//u32 loveywm = (u32)-1;
	count = DbGLogCountAll();
	LogIndex[1] = pCMD->BeginDatetime;
	LogIndex[2] = pCMD->EndDatetime;

	xprintf("pCMD->UserID==%d\r\n",pCMD->UserID);
	xprintf("pCMD->BeginDatetime==%d\r\n",pCMD->BeginDatetime);
	xprintf("pCMD->EndDatetime==%d\r\n",pCMD->EndDatetime);
	xprintf("pCMD->Index==%d\r\n",pCMD->Index);

	
	
	if ( pCMD->UserID == 0 )//全部用户
	{
		
		pos=DbGLogPosGetByTime(0,  count, LogIndex[1], LogIndex[2]);//确定logindex[1]位置
		count=DbGLogCountGetByTime(pos,  count, LogIndex[1], LogIndex[2]);//确定logindex[2]位置
		ret = DbGLogCountGetByTimeAllSearch(LogIndex[1], LogIndex[2]);
		if(ret == 0)
		{
			//send_count(ret,vCMD);
			web2_send_data(vCMD,&ret,sizeof(u32));
			xprintf("courn==%d\r\n",ret);
			return true;
		}
		ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (ret));
		if(!pLogs)
		{
			//Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("loveywm1212\r\n");
			//send_count((u32)-1,vCMD);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		xprintf("LogIndex[1]0==%d\r\n",LogIndex[1]);
		xprintf("LogIndex[2]0==%d\r\n",LogIndex[2]);
		memset(pLogs, 0, sizeof(ALOG_INFO) * ret);
		if(!(SendCount=DbGLogGetByTime(pLogs,  pos, count,LogIndex[1], LogIndex[2]))){
			free(pLogs);
			//Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("loveywm3434\r\n");
			//send_count((u32)-1,vCMD);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		xprintf("sendcount==%d\r\n",SendCount);
		xprintf("count==%d\r\n",count);
		xprintf("pos==%d\r\n",pos);
		xprintf("count-pos==%d\r\n",count - pos);
		xprintf("ret==%d\r\n",ret);
		GLog *glog = (GLog *)malloc(sizeof(GLog) * ret);
		if(!glog){
			free(pLogs);
			//send_count((u32)-1,vCMD);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		int i;
		for(i = 0;i < ret;i++){
			glog[i].Datetime = pLogs[i].dwSeconds;
			glog[i].UserID = pLogs[i].nID;
			glog[i].VerifyMode = (u32)pLogs[i].byAction;
			glog[i].Index = i;
		}
		//先发共多少个
		//send_count(ret,vCMD);
		web2_send_data(vCMD,&ret,sizeof(u32));
		//后发数据
		web2_send_data(vCMD,glog,sizeof(GLog) * ret);	
		free(pLogs);
		free(glog);
	}
	else
	{
		if(!DbUserInfoIsUsedID(pCMD->UserID))
		{	
			xprintf("no used in\r\n");
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		ret = DbGLogCountGetByTimeAllSearch_and_byid( LogIndex[1],LogIndex[2],pCMD->UserID);	
		ALOG_INFO *pLogs1 = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (ret));
		if(!pLogs1)
		{
			//Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("loveywm5656\r\n");
			return FALSE;
		}
		xprintf("ret==%d\r\n",ret);
		xprintf("LogIndex[1]1==%d\r\n",LogIndex[1]);
		xprintf("LogIndex[2]1==%d\r\n",LogIndex[2]);
		memset(pLogs1, 0, sizeof(ALOG_INFO) * ret);
		if(!(SendCount=DbGLogGetByTime_and_byID(pLogs1, 0, count,LogIndex[1], LogIndex[2],pCMD->UserID)))
		{
			free(pLogs1);
			//Com_SendExeResult( EXE_RES_FALSE, 0 );
			xprintf("loveywm7878\r\n");
			return FALSE;
		}
		xprintf("sendcount==%d\r\n",SendCount);
		xprintf("count==%d\r\n",count);
		xprintf("ret==%d\r\n",ret);

		GLog *glog1 = (GLog *)malloc(sizeof(GLog) * ret);
		if(!glog1){
			free(pLogs1);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}

		int j;
		for(j= 0;j < ret;j++){
			glog1[j].Datetime = pLogs1[j].dwSeconds;
			glog1[j].UserID = pLogs1[j].nID;
			glog1[j].VerifyMode = (u32)pLogs1[j].byAction;
			glog1[j].Index = j;
		}

		//先发共多少个
		web2_send_data(vCMD,&ret,sizeof(u32));

		//后发数据
		web2_send_data(vCMD,glog1,sizeof(GLog) * ret);
		free(pLogs1);
		free(glog1);		
	}
	xprintf("the glog is ok by time!!!\r\n");
	return TRUE;
}

u8 web2_glog_get_byindex(PACK_HEAD* vCMD, GetGLogConditionEx *glogconditionex)
{
	u64 ret;
	//u32 loveywm = (u32)-1;
	int SendCount;
	ret = glogconditionex->EndIndex - glogconditionex->BeginIndex ;
	ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (ret));
	if(!pLogs)
	{
		//Com_SendExeResult( EXE_RES_FALSE, 0 );
		xprintf("loveywm9090\r\n");
		//web2_send_data(vCMD,&loveywm,sizeof(u32));
		//send_count((u32)-1,vCMD);
		return FALSE;
	}
	if(!(SendCount=DbGLogGetByindex(pLogs, (int )glogconditionex->BeginIndex, (int)glogconditionex->EndIndex)))
	{
		free(pLogs);
		//Com_SendExeResult( EXE_RES_FALSE, 0 );
		xprintf("loveywm-=-=\r\n");
		//send_count((u32)-1,vCMD);
		//web2_send_data(vCMD,&loveywm,sizeof(u32));
		return FALSE;
	}

		GLog *glog = (GLog *)malloc(sizeof(GLog) * ret);
		if(!glog){
			free(pLogs);
			//send_count((u32)-1,vCMD);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		int i;
		for(i = 0;i < ret;i++){
			glog[i].Datetime = pLogs[i].dwSeconds;
			glog[i].UserID = pLogs[i].nID;
			glog[i].VerifyMode = (u32)pLogs[i].byAction;
			glog[i].Index = i;
		}
		//先发共多少个
		web2_send_data(vCMD,&ret,sizeof(u32));
		//后发数据
		web2_send_data(vCMD,glog,sizeof(GLog) * ret);
		free(glog);
		free(pLogs);
		xprintf("the glog is ok by index!!!\r\n");
		return true;
}

u8 web2_glog_get_byall( PACK_HEAD* vCMD)
{
		//u32 loveywm = (u32)-1;
		DWORD count;
		count = DbGLogCountAll();
		if(count == 0)
		{
			web2_send_data(vCMD,&count,sizeof(u32));
			xprintf("courn==%d\r\n",count);
			return true;
		}
		ALOG_INFO *pLogs = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * (count));
		if(!pLogs)
		{
			xprintf("plogs is wrong\r\n");
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}

		if(!DbGLogGet(pLogs, 0, count)){//这里存在是从0还是从1开始的问题
			free(pLogs);
			xprintf("dbglogget is wrong\r\n");
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}
		
		GLog *glog = (GLog *)malloc(sizeof(GLog) * count);
		if(!glog){
			free(pLogs);
			//web2_send_data(vCMD,&loveywm,sizeof(u32));
			return FALSE;
		}

		int i;
		for(i = 0;i < count;i++){
			glog[i].Datetime = pLogs[i].dwSeconds;
			glog[i].UserID = pLogs[i].nID;
			glog[i].VerifyMode = (u32)pLogs[i].byAction;
			glog[i].Index = i;
		}

/*		if(count >50000)
		{
			int sendfirst;
			sendfirst = count - 50000;
			web2_send_data(vCMD,&count,sizeof(u32));
			web2_send_data(vCMD,glog,sizeof(GLog) * 50000);
			//sleep(1);			
			//web2_send_data(vCMD,&sendfirst,sizeof(u32));
			web2_send_data(vCMD,glog+50000,sizeof(GLog) * sendfirst);
		}
		else 
		{
			//先发共多少个
			//send_count(count,vCMD);
			web2_send_data(vCMD,&count,sizeof(u32));	
			//后发数据
			web2_send_data(vCMD,glog,sizeof(GLog) * count);
		}
*/		
		int loveywm1,loveywm2,xh;
		int count_num = 5000;
		loveywm1 = count/count_num;
		loveywm2 = count%count_num;
		xprintf("loveywm1==%d\r\n",loveywm1);
		xprintf("loveywm==%d\r\n",loveywm2);
		
		//先发共多少个
		web2_send_data(vCMD,&count,sizeof(u32));
		
		for(xh=0;xh<loveywm1;xh++)
		{
			web2_send_data(vCMD,glog+count_num*xh,sizeof(GLog) * count_num);
		}
		
		web2_send_data(vCMD,glog+count_num*loveywm1,sizeof(GLog) * loveywm2);


		//先发共多少个	
		//web2_send_data(vCMD,&count,sizeof(u32));	
		//后发数据
		//web2_send_data(vCMD,glog,sizeof(GLog) * count);
		free(glog);
		free(pLogs);
		xprintf("the glog is ok by all!!!\r\n");
		return true;
}
u8 web2_cmd_get_log( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("004\r\n");
	xprintf("recvdata==%d\r\n",*recvdata);
	u8 ret;
	u32 loveywm = (u32)-1;
	if((vCMD->Datalen) == 1)//全采集0//新采集1
	{
		xprintf("quan cai ji\r\n");
		ret = web2_glog_get_byall(vCMD);
	}
	else if(((vCMD->Datalen) == (1 + sizeof(GetGLogCondition))) && *recvdata == 2)
	{
		xprintf("by time\r\n");
		//下面被修改过2013.02.01
		//GetGLogCondition *glogcondition = NULL;
		//glogcondition = (GetGLogCondition *)(recvdata + sizeof(u8));
		GetGLogCondition glogcondition;
		memcpy(&glogcondition,recvdata+1,sizeof(GetGLogCondition));
		xprintf("recvdata==%d\r\n",*recvdata);
		xprintf("glogcondition.UserID==%d\r\n",glogcondition.UserID);
		xprintf("glogcondition.BeginDatetime==%d\r\n",glogcondition.BeginDatetime);
		xprintf("glogcondition.EndDatetime==%d\r\n",glogcondition.EndDatetime);
		xprintf("glogcondition.Index==%d\r\n",glogcondition.Index);
		ret = web2_glog_get_bytime(vCMD, &glogcondition);
	}
	else if(((vCMD->Datalen) == (1 + sizeof(GetGLogConditionEx))) && *recvdata == 3)
	{
		xprintf("by index\r\n");
		//下面被修改过2013.02.01
		//GetGLogConditionEx *glogconditionex = NULL;
		//glogconditionex = (GetGLogConditionEx*)(recvdata + sizeof(u8));
		GetGLogConditionEx glogconditionex;
		memcpy(&glogconditionex,recvdata+1,sizeof(GetGLogConditionEx));
		ret = web2_glog_get_byindex(vCMD, &glogconditionex);
	}
	else
	{
		//u32 loveywm = (u32)-1;
		web2_send_data(vCMD,&loveywm,sizeof(u32));
		return FALSE;
	}
	if(ret)
	{
		xprintf("the glog is ok!!!\r\n");
		return true;
	}
	else
	{
		xprintf("the glog is failed!!!\r\n");
		web2_send_data(vCMD,&loveywm,sizeof(u32));
		return FALSE;
	}
	

	
	//xprintf("the glog is ok!!!\r\n");
	//return true;
}	


u8 web2_cmd_get_user_reg(PACK_HEAD *vCMD,u8 *recvdata)
{
	xprintf("005\r\n");
	
	GetUser *getuser = (GetUser *)recvdata;
	xprintf("i am in web_get_user_info\r\n");
	xprintf("getuser->UserID==%d\r\n",getuser->UserID);
	xprintf("getuser->BackupNumber==%d\r\n",getuser->BackupNumber);
	u8 *sendbuf = NULL;
	FPINFO *fpinfo = NULL;
	//u32 len = sizeof(UserInfo);
	//u32 len1 = sizeof(FPINFO);
	//判断用户是否存在
	if(!DbUserInfoIsUsedID(getuser->UserID))
	{
		UserInfo user_info1;
		user_info1.UserID = getuser->UserID;
		user_info1.BackupNumber = 0;	
		web2_send_data(vCMD,&user_info1,sizeof(UserInfo));	
		return true;
	}
	//通过ID 获取用户全部信息
	USER_INFO	*pUInfo;
	pUInfo = (USER_INFO*)DbUserInfoGetPointer(getuser->UserID);
	if(pUInfo == NULL)
	{
		xprintf("no this fpinfo\r\n");
		return FALSE;
	}
	//填充st_UserInfo数据结构
	UserInfo user_info;
	user_info.UserID = getuser->UserID;
	user_info.Card = pUInfo->CARD;
	user_info.Password = pUInfo->PWD;
	
	u32 pri = (u32)DbUserInfoGetPrivilege(getuser->UserID);
	if(pri == 1)
	{
		user_info.Privilege = 0;
	}
	else if(pri == 6)
	{
		user_info.Privilege = 2;
	}
	else if(pri == 7)
	{
		user_info.Privilege = 1;
	}
	else 
	{
		user_info.Privilege = 0;
	}
	QString str1;
	QByteArray str2;

	str1 = UNICODE2STRING(pUInfo->NAME,24);//2014.04.19 modify
	str2 = U2G(str1);
	memcpy(user_info.UserName,str2,24);
	
	//memcpy(user_info.UserName,pUInfo->NAME,24);
	xprintf("pUinfo->name==%s\r\n",pUInfo->NAME);	
	xprintf("pUInfo->CARD==%d\r\n",pUInfo->CARD);
	xprintf("pUInfo->ID==%d\r\n",pUInfo->ID);
	xprintf("pUInfo->PWD==%d\r\n",pUInfo->PWD);
	xprintf("pUInfo->FP==%d\r\n",pUInfo->FP);
	//通过ID获取指纹模板信息
	xprintf("getuser->backnumber1==%d\r\n",getuser->BackupNumber);
	xprintf("getuser->backnumber2==%p\r\n",getuser->BackupNumber);
	//xprintf("getuser->backnumber3==%b\r\n",getuser->BackupNumber);
	if(getuser->BackupNumber == 12)//获取姓名
	{
		//下面三行修改于2013.01.22，用于协议整改bug
		//user_info.BackupNumber = getuser->BackupNumber;
		user_info.BackupNumber = 0;//清零
		user_info.BackupNumber |= (1 << 12);
		web2_send_data(vCMD,&user_info,sizeof(UserInfo));
	}
	else if(getuser->BackupNumber == -1)//获取全部指纹模板
	{
		xprintf("i love ywm3333\r\n");
		user_info.BackupNumber = 0;//清零
		sendbuf = (u8 *)malloc(sizeof(UserInfo) + 10 * sizeof(FPINFO));
		while(sendbuf == NULL)//循环，直到分配到空间
		{
			sendbuf = (u8 *)malloc(sizeof(UserInfo) + 10 * sizeof(FPINFO));
		}
		int i,num = 0;
		for(i = BACKUP_FINGER0;i <= BACKUP_FINGER9;i++)
		{
			fpinfo = (FPINFO *)DbUserInfoGetPointer(getuser->UserID, i);
			if(fpinfo == NULL)
			{
				xprintf("the end of pfinfo\r\n");		
				continue;
			}
			user_info.BackupNumber |=  (1 << i);
			num =  num + 1;
			memcpy(sendbuf+sizeof(UserInfo) + (num - 1) * sizeof(FPINFO),fpinfo,sizeof(FPINFO));
		}
		//判断密码位置
		if(user_info.Password  != 0)
		{
			user_info.BackupNumber |=  (1 << 10);
		}
		//判断卡位置
		if(user_info.Card != 0)
		{
			user_info.BackupNumber |=  (1 << 11);
		}
	/*	int xxx;
		xprintf("num==%d\r\n",num);
		xprintf("the data is :\r\n");
		
		for(xxx=0;xxx<sizeof(UserInfo) + sizeof(FPINFO) * num;xxx++)
		{
			xprintf("%x",sendbuf[xxx]);
		}
		xprintf("\r\n*****************************************************\r\n");
		for(xxx=0;xxx<sizeof(FPINFO) * num;xxx++)
		{
			xprintf("%x",*(sendbuf+xxx+sizeof(UserInfo)));
		}
*/		xprintf("\r\nthe data is over:\r\n");
		xprintf("user_info.UserName==%s\r\n",user_info.UserName);
		xprintf("user_info.BackupNumber1==%d\r\n",user_info.BackupNumber);
		xprintf("user_info.BackupNumber2==%x\r\n",user_info.BackupNumber);
		xprintf("user_info.BackupNumber3==%p\r\n",user_info.BackupNumber);
		xprintf("user_info.Card==%d\r\n",user_info.Card);
		xprintf("user_info.Password==%d\r\n",user_info.Password);
		xprintf("user_info.Privilege==%d\r\n",user_info.Privilege);
		xprintf("user_info.UserID==%d\r\n",user_info.UserID);
		
		//20130103添加了下面这个语句
		memcpy(sendbuf,&user_info,sizeof(UserInfo));
		
		web2_send_data(vCMD,sendbuf,sizeof(UserInfo) + sizeof(FPINFO) * num);
		
	}
	else//获取指定指纹模板
	{
		xprintf("i love ywm1111\r\n");
		user_info.BackupNumber = 0;//清零
		user_info.BackupNumber |=  (1 << (getuser->BackupNumber));
		//判断密码位置
		if(user_info.Password  != 0)
		{
			user_info.BackupNumber |=  (1 << 10);
		}
		//判断卡位置
		if(user_info.Card != 0)
		{
			user_info.BackupNumber |=  (1 << 11);
		}
		fpinfo = (FPINFO *)DbUserInfoGetPointer(getuser->UserID, getuser->BackupNumber);
		if(fpinfo == NULL)
		{
			
			xprintf("no this fpinfo\r\n");
			return FALSE;
		}
		//申请发送数据空间
		sendbuf = (u8 *)malloc(sizeof(UserInfo) + sizeof(FPINFO));
		while(sendbuf == NULL)//循环，直到分配到空间
		{
			sendbuf = (u8 *)malloc(sizeof(UserInfo) + sizeof(FPINFO));
		}
		memcpy(sendbuf,&user_info,sizeof(UserInfo));
		memcpy(sendbuf+sizeof(UserInfo),fpinfo,sizeof(FPINFO));
		web2_send_data(vCMD,sendbuf,sizeof(UserInfo) + sizeof(FPINFO));
		//web2_send_data(vCMD,&user_info,sizeof(UserInfo));//先发用户信息
		//web2_send_data(vCMD, fpinfo,sizeof(FPINFO));//再发指纹数据
	}
	free(sendbuf);
	return TRUE;
}


u8 web2_cmd_set_user_reg( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("006\r\n");
	int  nFP;
	BYTE nUserPriv;
	u32 pwd;
	u32 card;
	//UserInfo uInfo;
	//FPINFO   uFp;
	//UserInfo *info = (UserInfo *)malloc(sizeof(UserInfo));//小心没分配到
	//FPINFO *fp = NULL;
	UserInfo *info = NULL;
	FPINFO *fp = NULL;
	//排除接受信息中可能增加其他数据，方便兼容2013.04.18
/*	
	if(vCMD->Datalen == (sizeof(UserInfo) + sizeof(FPINFO)) )
	{
		info = (UserInfo *)recvdata;
		fp = (FPINFO *)(recvdata + sizeof(UserInfo));
	}
	else if(vCMD->Datalen == sizeof(UserInfo))
	{
		info = (UserInfo *)recvdata;
	}
	else
	{
		web2_send_ack(0,ERROR_OK,vCMD);
		xprintf("vCMD->Datalen==%d\r\n",vCMD->Datalen);
		return FALSE;
	}
*/	
	info = (UserInfo *)recvdata;
	//fp = (FPINFO *)(recvdata + sizeof(UserInfo));
	
	nFP = ((info->BackupNumber) & 0xff);//取低位给BackNumber

	//if(nFP != 12)
	//{
		//fp = (FPINFO *)(recvdata + sizeof(UserInfo));
	//}
	
	//只改姓名
	if(nFP== 12)
	{	
		USER_INFO	*pUInfo;
		int nPos, nPos1;
		int NearestPos;
		pUInfo = (USER_INFO*)DbUserInfoGetPointer(info->UserID);
		if(!pUInfo)
		{			  
			nPos = DbUserInfoGetUnusedPosition();

			gpUserInfoEnrollData[nPos].ID = info->UserID;	
		
              		memcpy(gpUserInfoEnrollData[nPos].NAME, info->UserName, 24); 
			QString str =G2U((char *)gpUserInfoEnrollData[nPos].NAME);
			bzero(gpUserInfoEnrollData[nPos].NAME, USERNAME_LENGTH * 2);
			STRING2UNICODE(str,(WORD*)gpUserInfoEnrollData[nPos].NAME, USERNAME_LENGTH); 		
			  
			DbUserInfoFlagManagerSet(&gpUserInfoEnrollData[nPos], PRIV_USER);

			DbUserInfoSaveOne(nPos);

			nPos1 = DbUserInfoGetNearestPosition(info->UserID, &NearestPos);
			if (nPos1 < 0)
			{
				for (int k=dbLicense.nMaxEnrollCount-1; k>NearestPos; k--)
				gpUIIndexData[k] = gpUIIndexData[k-1];
				gpUIIndexData[NearestPos] = nPos;
			}
			DbUIIndexSave();
		}
		else
		{
			memcpy(&gUserInfoTemp, pUInfo, sizeof(USER_INFO));
    			memcpy(gUserInfoTemp.NAME, info->UserName, 24); 
			QString str =G2U((char *)gUserInfoTemp.NAME);

			bzero(gUserInfoTemp.NAME, USERNAME_LENGTH * 2);
			STRING2UNICODE(str,(WORD*)gUserInfoTemp.NAME, USERNAME_LENGTH); 
			if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_ALL, NULL))
			{
				web2_send_ack(0,ERROR_OK,vCMD);
				return FALSE;
			}
		}
		web2_send_ack(1,0,vCMD);
		return true;
	}

	fp = (FPINFO *)(recvdata + sizeof(UserInfo));//当取指纹时，加入
	
	xprintf("nId==%d\r\n",info->UserID);
	xprintf("nfp==%d\r\n",nFP);
	if ( info->UserID < 1 || info->UserID > MAX_ID || nFP < BACKUP_FINGER0 || nFP > BACKUP_END )
	{
		web2_send_ack(0,BACKNUMBER_ID_ERROR,vCMD);
		xprintf("nfp failed\r\n");
		return FALSE;
	}
	//删除用户信息
	int nback = ((info->BackupNumber)  & 0x80000000);//去最高位作为判断依据
	if(nback != 0)//当最高位置1时，先删除用户在注册
	{
		DbUserInfoDelete(info->UserID,0xFFFF);
	}
	
	if((info->Privilege)== 0)
	{
		 nUserPriv = PRIV_USER;
	}
	else if((info->Privilege)== 1)	
	{
		nUserPriv = PRIV_SMGR;
	}
	else if((info->Privilege)== 2)	
	{
		nUserPriv = PRIV_MGR;
	}
	else
	{
		nUserPriv = PRIV_USER;
	}
	xprintf("info->Privilege==%d\r\n",info->Privilege);
	xprintf("nUserPriv==%d\r\n",nUserPriv);
	
	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	gUserInfoTemp.ID = info->UserID;
	gUserInfoTemp.CARD = info->Card;
	gUserInfoTemp.PWD = info->Password;
	pwd =  info->Password;
	card =   info->Card;
	gUserInfoTemp.FLAG.members.byMgr = nUserPriv;
	//对名字数据的处理
	//char name[24];
	memcpy(gUserInfoTemp.NAME,info->UserName,USERNAME_LENGTH * 2);
	
	xprintf("gUserinfotemp.name==%s\r\n",gUserInfoTemp.NAME);
	xprintf("info->UserName==%s\r\n",info->UserName);
	
	//QString str =G2U((char *)packed_name_info.NameA);	
	QString str =G2U((char *)gUserInfoTemp.NAME);

	bzero(gUserInfoTemp.NAME, USERNAME_LENGTH * 2);
	STRING2UNICODE(str,(WORD*)gUserInfoTemp.NAME, USERNAME_LENGTH); 
	
	xprintf("zzzzzgUserInfoTemp.NAME=%s \r\n", gUserInfoTemp.NAME);
	xprintf("guserinfogtemp.id==%d\r\n",gUserInfoTemp.ID);
	xprintf("guserinfogtemp.Fp==%d\r\n",gUserInfoTemp.FP);
	xprintf("guserinfogtemp.card==%d\r\n",gUserInfoTemp.CARD);
	xprintf("guserinfogtemp.userpriv==%d\r\n",gUserInfoTemp.FLAG.members.byMgr);
	xprintf("guserinfogtemp.pwd==%d\r\n",gUserInfoTemp.PWD);	
	//这里是为一个问题而设的，
	//下面的DbUserInfoEnroll函数不恩能够直接传指纹指针，
	//需要转换数组才可以，很蛋疼!!
	if(nFP == BACKUP_PASSWORD)
	{
		if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_PASSWORD,&pwd))
		{
			web2_send_ack(0,ENRALL_PASSWD_ERROR,vCMD);
			xprintf("DBuserinfoenroll failed pwd\r\n");	
			return FALSE;
		}
	}
	else if(nFP == BACKUP_CARD)//2013.05.06增加下面的卡注册
	{
			
		if (!DbUserInfoEnroll(&gUserInfoTemp, BACKUP_CARD,&card))
		{
			web2_send_ack(0,ENRALL_CARD_ERROR,vCMD);
			xprintf("DBuserinfoenroll failed card\r\n");	
			return FALSE;
		}
	}
	else
	{
		char gbfb[1404];
		memcpy(gbfb,fp,sizeof(FPINFO));	
		if (!DbUserInfoEnroll(&gUserInfoTemp, nFP, &gbfb[0], TRUE, FALSE))
		{
			web2_send_ack(0,ENRALL_PP_ERROR,vCMD);
			xprintf("DBuserinfoenroll failed\r\n");	
			return FALSE;
		}
	}
	//每次都根据下发的权限改这个用户的权限
	DbUserInfoSetPrivilege(info->UserID,nUserPriv);
	
	web2_send_ack(1,0,vCMD);
	xprintf("DBuserinfoenroll ok\r\n");
	return true;
}


u8 web2_cmd_del_user_reg( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("007\r\n");
	u64 web_userID;
	u8 nRet;
	memcpy(&web_userID,recvdata,sizeof(u64));
	xprintf("11111id==%d\r\n",web_userID);
	if(web_userID == 0)
	{
		//循环删除
		u32 i;
		for(i=1;i<= dbLicense.nMaxEnrollCount;i++)
		{
			nRet = DbUserInfoDelete(i,0xFFFF);
			xprintf("delete the %d user!!\r\n",i);
			if(nRet == 0)
			{
				i = dbLicense.nMaxEnrollCount + 1;
				nRet = 1;
			}
		}
		//直接删除文件
		nRet = DbUserInfoDeleteAll();
		nRet = DbFpDeleteAll() && nRet;//20130130修改
		xprintf("DbUserInfoDeleteAll\r\n");
	}
	else
	{
		int j;
		for(j=0;j<(vCMD->Datalen/8);j++)
		{
			//memcpy(&web_userID,&RecvData[24 + 8 * j],sizeof(u64));
			memcpy(&web_userID,(recvdata+8*j),sizeof(u64));
			xprintf("web_userid==%d\r\n",web_userID);
			if(DbUserInfoIsUsedID(web_userID))
			{
				nRet =DbUserInfoDelete(web_userID, 0xFFFF);
			}
			else
			{
				nRet = 1;
			}
		}
		//nRet = DbUserInfoDelete(web_userID, 0xFFFF);
		xprintf("DbUserInfoDelete(web_userID, 0xFFFF);\r\n");
	}
	if(nRet)
	{
		web2_send_ack(1,0,vCMD);
		xprintf("delete ok\r\n");
	}
	else
	{
		web2_send_ack(0,DEL_USER_REG_ERROR,vCMD);
		xprintf("delete failed\r\n");
	}
	return true;
}


u8 web2_cmd_mod_prvilege( PACK_HEAD* vCMD,u8 *recvdata)
{
	u64 ID;
	BYTE nUserPriv;
	USER_INFO *pUserInfo;
	UserPrvilege *prvilege = (UserPrvilege *)recvdata;
	int i;
	//把所有用户都设为普通用户
	if((prvilege->Prvilege)== 0xffffffff)
	{
		nUserPriv = PRIV_USER;
		int count = Db_GetUserCount();
		xprintf("count==%d\r\n",count);
		for(i = 0;i < count ;i++)
		{
			pUserInfo = &gpUserInfoEnrollData[i];
			if (pUserInfo->ID == 0)
				continue;
			if(DbUserInfoSetPrivilege(pUserInfo->ID, nUserPriv))
			{
				//send_ack(1,CMD_MOD_PRVILEGE,0,vCMD);
				xprintf(" ok\r\n");
			}
			else
			{
				//send_ack(0,CMD_MOD_PRVILEGE,0,vCMD);
				xprintf(" failed\r\n");
			}
		}
		web2_send_ack(1,0,vCMD);
		return true;
	}
	//判断用户是否存在
	if(!DbUserInfoIsUsedID(prvilege->UserID))
	{
		web2_send_ack(0,NO_USER_ERROR,vCMD);
		xprintf("no this userid\r\n");
		return FALSE;
	}
	if((prvilege->Prvilege)== 0)
	{
		 nUserPriv = PRIV_USER;
	}
	else if((prvilege->Prvilege)== 1)	
	{
		nUserPriv = PRIV_SMGR;
	}
	else if((prvilege->Prvilege)== 2)	
	{
		nUserPriv = PRIV_MGR;
	}
	else
	{
		xprintf("no this prvlige\r\n");
		nUserPriv = PRIV_USER;
	}
	xprintf("prvilege->Prvilege==%d\r\n",(prvilege->Prvilege));
	xprintf("nUserPriv==%d\r\n",nUserPriv);
	xprintf("prvilege->UserID==%d\r\n",prvilege->UserID);
	
	if(DbUserInfoSetPrivilege(prvilege->UserID, nUserPriv))
	{
		web2_send_ack(1,0,vCMD);
		xprintf("modify prvilege ok\r\n");
	}
	else
	{
		web2_send_ack(0,MOD_PRVILEGE_ERROR,vCMD);
		xprintf("modify prvilege failed\r\n");
		return FALSE;
	}
	return true;
}


u8 web2_cmd_get_all_userid( PACK_HEAD* vCMD)
{
	u32 count;
	UserID *EnrollUserIDBuffer = NULL;
	
	QString str1;//2014.04.19 modify
	QByteArray str2;
	
	count = Db_GetUserCount();
	xprintf("count==%d\r\n",count);
	if(count == 0)
	{
		//send_count(count,vCMD);
		web2_send_data(vCMD,&count,sizeof(u32));
		xprintf("courn==%d\r\n",count);
		return true;
	}
	
	WORD i, k,usernum,sign = 0;
	USER_INFO *pUserInfo = NULL;

	EnrollUserIDBuffer = (UserID *)malloc(count * sizeof(UserID));
	if (!EnrollUserIDBuffer)
	{
		//send_count((u32)-1,vCMD);
		u32 loveywm = (u32)-1;
		web2_send_data(vCMD,&loveywm,sizeof(u32));
		xprintf("EnrollUserIDBuffer wrong\r\n");
		return FALSE;
	}	
	memset(EnrollUserIDBuffer,0,count * sizeof(UserID));
	
	u32 j = 0;
	usernum = 0;
	for (i=0; i<count; i++)
	{
		pUserInfo = &gpUserInfoEnrollData[i];
		if (pUserInfo->ID == 0)
			continue;
		
		sign = 1;
		u8 noinfo_sign = 0;//只要他等于1，说明他就不只是有name
		for (k=BACKUP_START; k<=BACKUP_END; k++)
		{
			
			if (DbUserInfoFlagEnrollStatusGet(pUserInfo, k))
			{				
				if(sign ==  1)
				{				
					EnrollUserIDBuffer[j].UserID = pUserInfo->ID;
					//EnrollUserIDBuffer[j].EMachineNumber = DEVID;
					str1 = UNICODE2STRING(pUserInfo->NAME,24);//2014.04.19 modify
					str2 = U2G(str1);
					memcpy(EnrollUserIDBuffer[j].name,str2,24);
					
					//memcpy(EnrollUserIDBuffer[j].name,pUserInfo->NAME,24);
					EnrollUserIDBuffer[j].Prvilege = (u16)comm_GetUserPriv((int)(pUserInfo->ID), pUserInfo);   //sb 091125
					//EnrollUserIDBuffer[j].Enable = DbUserInfoFlagDisableStatusGet(pUserInfo)/*((gpOptionData[i] & 1) == 0) ? 0 : 1*/;	//1:disable
					j++;//用户数
					xprintf("j==%d\r\n",j);
					usernum = j -1;
					
					noinfo_sign = 1;
					sign = 0;
				}
				EnrollUserIDBuffer[usernum].BackupNumber |= (1 << k);
				//EnrollUserIDBuffer[j].MachinePrivilege = comm_GetUserPriv(pUserInfo->ID);  //sb 091125		
			}	
			//continue;//当此用户完了后，就进行下一个
		}
		if(noinfo_sign == 1)
		{
			noinfo_sign = 0;
			continue;//当此用户完了后，就进行下一个
		}
		
		//下面是只有姓名的用户处理
		EnrollUserIDBuffer[j].UserID = pUserInfo->ID;
		//QString str1;//2014.04.19 modify
		//QByteArray str2;

		str1 = UNICODE2STRING(pUserInfo->NAME,24);//2014.04.19 modify
		str2 = U2G(str1);
		memcpy(EnrollUserIDBuffer[j].name,str2,24);
		//EnrollUserIDBuffer[j].name = U2G(str1);
		
		//memcpy(EnrollUserIDBuffer[j].name,pUserInfo->NAME,24);
		EnrollUserIDBuffer[j].Prvilege = (u16)comm_GetUserPriv((int)(pUserInfo->ID), pUserInfo);  
		EnrollUserIDBuffer[j].BackupNumber = 0;
		//xprintf("j==%d\r\n",j);
		//xprintf("noinfo_sign==%d\r\n",noinfo_sign);
		j++;//用户数
		xprintf("jxx==%d\r\n",j);
		xprintf("noinfo_sign==%d\r\n",noinfo_sign);
		//sign = 0;
	}
/*	for(i =0 ;i<j;i++)
	{
		xprintf("EnrollUserIDBuffer[%d].UserID==%d\r\n",i,EnrollUserIDBuffer[i].UserID);
		xprintf("EnrollUserIDBuffer[%d].Prvilege==%d\r\n",i,EnrollUserIDBuffer[i].Prvilege);
		xprintf("EnrollUserIDBuffer[%d].BackupNumber==%d\r\n",i,EnrollUserIDBuffer[i].BackupNumber);
		xprintf("EnrollUserIDBuffer[%d].BackupNumber_p==%p\r\n",i,EnrollUserIDBuffer[i].BackupNumber);
	}
*/
	//send_count(j,vCMD);
	web2_send_data(vCMD,&j,sizeof(u32));

	if(j  != 0)
	{
		//send_userID_data(j,EnrollUserIDBuffer,vCMD);
		//u32 len = sizeof(UserID) * j;
		web2_send_data(vCMD,EnrollUserIDBuffer,sizeof(UserID) * j);
	}
	DELETE(EnrollUserIDBuffer);	
	return TRUE;
}


u8 web2_cmd_del_data( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("010\r\n");
	u8 nret1,nret2,nRet;
	if(*recvdata == 0)
	{
		//删除全部数据
		nret1=Db_DeleteAllEnrollData();
		nret2=Db_DeleteAllLogData();
		nRet = nret1 && nret2;
		if(nRet)
		{
			web2_send_ack(1,0,vCMD);
			xprintf("delete data_quanbu\r\n");
		}
		else
		{
			web2_send_ack(0,DEL_ALL_DATA_ERROR,vCMD);	
		}
						
	}
	else if(*recvdata == 1)	
	{
		//删除记录数据
		nRet = DbGLogDeleteAll();
		if(nRet)
		{
			web2_send_ack(1,0,vCMD);
			xprintf("delete data_jilu\r\n");
		}
		else
		{
			web2_send_ack(0,DEL_GLOG_DATA_ERROR,vCMD);	
		}
						
	}
	else if(*recvdata == 2)	
	{
		//删除管理记录数据
		nRet = DbSLogDeleteAll();
		if(nRet)
		{
				web2_send_ack(1,0,vCMD);
				xprintf("delete data_guanli\r\n");
		}
		else
		{
			web2_send_ack(0,DEL_SLOG_DATA_ERROR,vCMD);	
		}				
	}				
	return nRet;
}


u8 web2_cmd_upgrade_addr( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("011\r\n");
					
	//u8 buff[vCMD->Pack_Head.Datalen];    //////////原先是这个，导致了接受命令后就死机的bug
	char buf[256];//存放下载地址
	
	xprintf("vCMD->Pack_Head.Datalen==%d\r\n",vCMD->Datalen);					
	if(vCMD->Datalen != 0 )
	{
		memset(buf,0,sizeof(buf));
		memcpy(buf,recvdata,vCMD->Datalen);
		//buf中存放是下载地址
		xprintf("buf==%s\r\n",buf);
		//CMessageBox *msgBox = new CMessageBox; 
  		//msgBox->MsgBoxProc_Message("UpdateFirmware ...");
	
		Db_FreeAllData();   
		//接受完成后，给服务端发送接受成功
		web2_send_ack(1, 0,vCMD);

		//buf==http://192.168.10.47/wcfclient/update/SB3300-5Kv1.35.1536.61.bin	
		HttpRomWrite1(buf);

		//if(msgBox)
	  		//delete msgBox;
	
		Db_LoadAllData(TRUE);
		xprintf("the addr is ok!!\r\n");
		SB_EXEC("reboot"); 
		//web2_send_ack(0,0,vCMD);
		
		return TRUE;
						
	}
	else
	{
		web2_send_ack(0,0,vCMD);
		xprintf("the addr is wrong\r\n");
		return FALSE;
	}
			
}

u8 web2_cmd_set_mac(PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("013\r\n");
	//u32 timedata;
	//u8  mac[8];
	//memcpy(mac,recvdata,vCMD->Datalen);
	xprintf("%x\r\n",*recvdata);
	xprintf("%x\r\n",*(recvdata+1));
	xprintf("%x\r\n",*(recvdata+2));
	xprintf("%x\r\n",*(recvdata+3));
	xprintf("%x\r\n",*(recvdata+4));
	xprintf("%x\r\n",*(recvdata+5));
	//xprintf("%x\r\n",*recvdata);

	
	memset(g_params.byMACaddr,0,8);
	memcpy(g_params.byMACaddr, recvdata, vCMD->Datalen);	

	DbParamInfoSave();

	//memcpy(dbLicense.byMACaddr,recvdata, vCMD->Datalen);
	//DbLicenseWrite();
	//DbSetupTotalWrite();

	//g_uiLicenseChanged = g_uiBuildMenu = TRUE;
	
	web2_send_ack(1, 0,vCMD);
	xprintf("set  mac\r\n");
	return true;

}

u8 web2_cmd_set_time( PACK_HEAD* vCMD,u8 *recvdata)
{
	xprintf("012\r\n");
	u32 timedata;
	memcpy(&timedata,recvdata,vCMD->Datalen);
	uiRtcSetSeconds(timedata);
	web2_send_ack(1, 0,vCMD);
	xprintf("811 set  time\r\n");
	return true;
}

u8 web2_cmd_get_time( PACK_HEAD* vCMD)
{
	xprintf("013\r\n");
	u32 get_time;
	//u32 len = sizeof(u32);
	get_time = uiRtcGetSeconds();
	//send_time(vCMD,get_time);
	web2_send_data(vCMD,&get_time,sizeof(u32));
	xprintf("get_time is ok!!\r\n");
	return true;
}

//设备回复pc的信息
void web2_send_ack(u8 oksign,u8 errorsign,PACK_HEAD* vCMD)
{

	static u32 buf[8];//此时回复共32字节
	u8 *ack = (u8 *)&buf[6];//这四个位分别表示不同含义
	
	buf[0] = RECV_HEAD;
	buf[1] = vCMD->Cmd;
	buf[2] = vCMD->Cmd_Serial;//命令字序列号
	buf[3] = vCMD->Cmd_Step;//当前步骤
	buf[4] = vCMD->DeviceID;

	xprintf("buf[1]==%p\r\n",buf[1]);
	xprintf("vCMD->Pack_Head.Cmd==%p\r\n",vCMD->Cmd);

	if(vCMD->Cmd  !=  CMD_DEL_USER_REG)
	{
		buf[5] = 4;//数据长度	

		*ack = oksign;
		*(ack+1) = errorsign;

		
		//加密数据
		ks(ack,4);

		
		buf[7] = comm_csum1(buf, 28);//和校验
		//发送
		comm_tcpclient_send(buf,sizeof(buf));	
	}
	else
	{
		xprintf("loveywm here \r\n");	
		buf[5] = 1;
		*ack  = oksign;
		
		//加密数据
		ks(ack,1);

		
		buf[7] = comm_csum1(buf,25);
		u32 sum = buf[7];
		memcpy(ack + 1,&sum,sizeof(sum));
		//发送
		comm_tcpclient_send(buf,sizeof(buf) - 3);			
	}	
}

u8 web2_send_data(PACK_HEAD* vCMD,void *data,u32 datalen)
{
	int nRet;
	u32 len = datalen;
	xprintf("len==%d\r\n",len);
	u8 *sendbuf = NULL;
	sendbuf = (u8 *)malloc(PACK_HEAD_SIZE + len + sizeof(u32));
	
	while(sendbuf == NULL)//循环，直到分配到空间
	{
		sendbuf = (u8 *)malloc(PACK_HEAD_SIZE+ len + sizeof(u32));
	}
	
	PACK_HEAD ppackhead;
	web2_make_packhead(&ppackhead,len,vCMD);
	memcpy(sendbuf,&ppackhead,PACK_HEAD_SIZE);
	memcpy(sendbuf + PACK_HEAD_SIZE,data,len);

	

	//在此加入加密算法
	//加密方式
	//第一步：高低四位对调！
	//第二步：对调后低四位按位取反！	
	ks(sendbuf + PACK_HEAD_SIZE,len);


	u32 checksum = comm_csum1(sendbuf,PACK_HEAD_SIZE+len);
	memcpy(sendbuf+PACK_HEAD_SIZE+len,&checksum,4);

	nRet = comm_tcpclient_send(sendbuf,PACK_HEAD_SIZE + len + 4);
	if(nRet > 0)
	{
		nRet = 1;
	}
	else
	{
		nRet = 0;
	}
	//xprintf("send_data is ok111!!\r\n");
	free(sendbuf);
	xprintf("send_data is ok!!\r\n");
	return nRet;
}

void web2_make_packhead(PACK_HEAD *packhead,u32 datalen,PACK_HEAD *vCMD)
{
	if(vCMD->Head == SEND_HEAD)
	{
		//packhead->Head = (vCMD->Head);
		packhead->Head =  RECV_HEAD;
	}
	else
	{
		//packhead->Head =  RECV_HEAD;
		packhead->Head = SEND_HEAD;
	}
	packhead->Cmd  = (vCMD->Cmd);
	packhead->Cmd_Serial	= (vCMD->Cmd_Serial);
	packhead->Cmd_Step = (vCMD->Cmd_Step);
	packhead->DeviceID = (DEVID);
	packhead->Datalen = (datalen);
}

u8 web2_send_glog(ALOG_INFO *pLogData)
{
	BOOL  bRet = TRUE;
	u8 ret;
	ALOG_INFO *aloginfo = pLogData;
	
	GLog glog;
	comm_sendtime();
	xprintf("sendlog_web\r\n");
	glog.Datetime = pLogData->dwSeconds;
	glog.UserID = pLogData->nID;
	glog.VerifyMode = pLogData->byAction;
	//glog.Index = dwGlogIndex;
	//修复索引重启就从0开始的bug，add by loveywm 2013.02.21
	glog.Index = DbGLogGetReadPos();//上传完后，接受回复后会加1
	//dwGlogIndex++;
	
	xprintf("glog.Datetime==%d\r\n",glog.Datetime);
	xprintf("glog.UserID==%d\r\n",glog.UserID);
	xprintf("glog.VerifyMode==%d\r\n",glog.VerifyMode);
	xprintf("glog.Index==%d\r\n",glog.Index);

	PACK_HEAD  packhead;
	//这里用RECV_HEAD，是因为后面有个转换，为了后面，这里就委屈下
	web_make_packhead(&packhead, RECV_HEAD, CMD_REALTIME_LOG, sizeof(GLog));

	packhead.Cmd_Serial = glog.Index ;

	ret = web2_send_data(&packhead,&glog,sizeof(GLog));
	xprintf("the glog is send ok!!\r\n");

	//发完就得等待1000接受
	ret = web2_recv_data(1000);//add by l;oveywm 2013.02.21
	xprintf("the glog is recv ok!!\r\n");

/*	xprintf("ret=%d\n\r",ret);
	if(ret > 0){
		bRet = 1;
	}else{
		bRet = 0;
	}	
	xprintf("bret=%d\n\r",bRet);
	
      	if(bRet==0)
	{
		xprintf("the bret is 0!!\r\n");
		tcpclient_connect_start();
	}
	xprintf("the glog is send ok!!\r\n");
    	http_WEB_CONNECT=bRet;
*/	return ret;
}

u8 web2_send_finger(u64 ID,int backupnumber,u32 prilege,u8 *pdata)
{
	DM9000_Check();
		
   if(__tcpclient_connect_status == 1 && LINK_LOST == 0)
   {	
	FingerData finger;
	PACK_HEAD  packhead;
	memset(&finger,0,sizeof(FingerData));
	web_make_packhead(&packhead, RECV_HEAD, CMD_UPLOAD_FINGER, sizeof(FingerData));
	finger.UserID = ID;
	finger.BackupNumber = backupnumber;
	finger.priege = prilege;
	if(backupnumber == BACKUP_PASSWORD || backupnumber ==BACKUP_CARD)
	{
		memcpy(finger.data,pdata,4);//密码是四字节
		int pwd;
		memcpy(&pwd,pdata,4);
		xprintf("pwd==%d\r\n",pwd);
		//xprintf("num==%d\r\n",num);
		//xprintf("buf==%s\r\n",buf);
		//xprintf("tmp==%d\r\n",tmp);
	}
	else
	{
		memcpy(finger.data,pdata,sizeof(FPINFO));
	}
	web2_send_data(&packhead,&finger,sizeof(FingerData));
	xprintf("the finger is send ok!!\r\n");
	//发完就得等待1000接受
	web2_recv_data(1000);//add by l;oveywm 2013.02.21
	xprintf("the finger is recv ok!!\r\n");
	return true;
   }
   else
   {
	tcpclient_connect_start();
   }
   return FALSE;
}

u8 web2_recv_data(int timeout)
{
	//u8 nRet;
	int  nETime = GetMainTickCount() + timeout;		
	while (GetMainTickCount() < nETime)
	{	
		PACK_HEAD gPACK;//web2.0
		//comm_mode = COMM_MODE_NONE;
		bzero(&gPACK, sizeof(gPACK));//web2.0
		if(dbLicense.bUseEthernet && dbSetupTotal.setSystem.bEthernetUse &&
			(!g_bDisableDevice || g_bDisableDevice == DISABLE_MODE_TCP)) //TCPIP
		{
				if (web2_get_cmd(Client_Sock, &gPACK))
				{						
				/*	nRet = web2_run_cmd(Client_Sock,&gPACK);
					//comm_mode = COMM_MODE_NONE;
					//comm_sub_mode = -1;
					if(nRet == true)
					{
						break;
					}*/
					if(web2_run_cmd(Client_Sock,&gPACK))
					{
						xprintf("web2_run_cmd!!\r\n");
						return true;
					}
				}			
		}
	}
	return FALSE;
}

//加密方式
//第一步：高低四位对调！
//第二步：对调后低四位按位取反！
//加密代码
void ks(u8 *sendbuf,int buflen)
{
    int i;
    int len = buflen;
    //u8 buf[len];
    u8 ch;
        
    for(i=0;i<len;i++)
    {        
        //printf("b ch x= %x\n",sendbuf[i]);
        ch = 0;
        ch |= (sendbuf[i] & 0x0f) << 4;
        ch |= (~((sendbuf[i] & 0xf0) >> 4)) & 0x0f;
        sendbuf[i] = ch;     
    }
    return;    
}
//解密代码
void ks_f(u8 *sendbuf,int buflen)
{
    int i;
    int len = buflen;
    //u8 buf[len];
    u8 ch;
        
    for(i=0;i<len;i++)
    {        
        //printf("b ch x= %x\n",sendbuf[i]);
        ch = 0;
        ch |= (sendbuf[i] & 0xf0) >> 4;
        ch |= (~((sendbuf[i] & 0x0f) << 4)) & 0xf0;
        sendbuf[i] = ch;     
    }
    return;    
}

///////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
//下面是http服务加入的
static unsigned char HttpLinking=0;

////////////////////csocket.cpp中的内容拷贝//////////////////////

unsigned char Http_MsgEn=0;
DWORD gngethostbyname(char *HostName, int timeout);

#define UI_IP_MAKE(a,b,c,d) (((a)<<24) | ((b)<<16) | ((c)<<8) | (d))
extern  int GetMainTickCount(void);
// TCP/IP
extern BOOL				dbComm_ipIsDHCP;
extern BOOL				dbComm_dhcpSuccess;
extern BYTE				dbComm_macAddress[6];
extern WORD				dbComm_wPortNum;
extern DWORD			dbComm_ipAddress;
extern DWORD			dbComm_ipSubnetMask;
extern DWORD			dbComm_ipDefaultGateway;
extern DWORD			dbComm_ipPcBackground;
extern DBSETUP_TOTAL    dbSetupTotal;	

//extern int comm_uartsend2(int iUART, void *pBuffer, int len);

#define  PrintfDbugEn1 1

void SOCKET_printf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
)
{
#if (PrintfDbugEn1==1)

	va_list ap;
    char string[10*1024];

    va_start(ap,str);
    vsprintf(string,str,ap);
	//comm_uartsend2(0, &string, strlen(string)) ;
    va_end(ap);
#endif
}

//#define xprintf  httpprintf
#define httpprintf xprintf


#if 0
Sock_instance::Sock_instance(string hostname, unsigned port, s_type type,int size)
	: _hostname( hostname ), 
	 _port( port ),
	 _fd( 0 ),
	 _state( CONN_ERROR ),
	 _type( type )
{
	_datalen = 0;
	_data = new unsigned char[size];
	_data_size=size;
}
#endif

Sock_instance::Sock_instance(string hostname, unsigned char *dat,int size)
	: _hostname( hostname ), 
	 _port( 80 ),
	 _fd( 0 ),
	 _state( CONN_ERROR ),
	 _type( CLIENT_TYPE )
{
	_datalen = 0;
	if(dat)
	    _data = dat;
	//else
	//	_data = new unsigned char[size];
	_data_size=size;
}

Sock_instance::~Sock_instance()
{
	//delete[] _data;
}

//Sock_instance *s_clientp; 

struct sockaddr_in serverip_http;
//DWORD DNS_SDDR=0;
struct sockaddr_in peer;

void DnsServerIpSet_bak(DWORD ipPcBackground)
{
	int a, b, c, d;
	BYTE			macAddress[6];														//6
	DWORD			ipAddress;															//4
	DWORD			ipSubnetMask;														//4
	DWORD			ipDefaultGateway;													//4
	char *szCommand = (char*)malloc(1024);

	if (dbSetupTotal.setSystem.bDHCPUse==0)
		return ;
	COMMAND_EXE("cp  /usr/resolv.conf /enrolldata/resolv.conf");

    //UI_IP_UNMAKE(dbSetupTotal.setSystem.ipPCBackground, a, b, c, d); 
	UI_IP_UNMAKE(ipPcBackground, a, b, c, d); 
	     d=1;
		 
	if (!szCommand)
		return ;
	sprintf(szCommand, "echo \"nameserver %d.%d.%d.%d \">> /etc/resolv.conf", a,b,c,d);
	xprintf("set bak dns==%s\r\n", szCommand);	

	SB_EXEC(szCommand);
	FREE(szCommand);	
}
void DnsServerIpSet_main(DWORD ipPcBackground)
{
	int a, b, c, d;
	BYTE			macAddress[6];														//6
	DWORD			ipAddress;															//4
	DWORD			ipSubnetMask;														//4
	DWORD			ipDefaultGateway;													//4
	char *szCommand = (char*)malloc(1024);

	if (dbSetupTotal.setSystem.bDHCPUse==0)
		return ;
	COMMAND_EXE("cp  /usr/resolv.conf /enrolldata/resolv.conf");

    //UI_IP_UNMAKE(dbSetupTotal.setSystem.ipPCBackground, a, b, c, d); 
	UI_IP_UNMAKE(ipPcBackground, a, b, c, d); 
	if (!szCommand)
		return ;
	sprintf(szCommand, "echo \"nameserver %d.%d.%d.%d \">> /etc/resolv.conf", a,b,c,d);
	xprintf("set main dns==%s\r\n", szCommand);	

	SB_EXEC(szCommand);
	FREE(szCommand);	
}
bool Sock_instance::Connect()
{



	httpprintf("%s\r\n","connect start");

	if( _type == SERVER_TYPE )
	{
		httpprintf("%s\r\n","The socket is a server, don't use conncet!");
		return false;
	}
	

	int fd;
	struct timeval timeo;

	fd = socket( AF_INET, SOCK_STREAM, 0 );
	if ( fd < 0 )
	{
		httpprintf("%s\r\n","socket call failed");
		return false;
	}


	bzero( &peer, sizeof(peer) );
	peer.sin_family = AF_INET;
	
	httpprintf("dbSetupTotal.setSystem.szHostByName[0]==%s\r\n",dbSetupTotal.setSystem.szHostByName);
	if (dbSetupTotal.setSystem.szHostByName[0]==0)
	{
            	peer.sin_addr.s_addr = htonl(dbComm_ipPcBackground);
		//peer.sin_port	= htons(dbSetupTotal.setSystem.wPortNumBack);
		peer.sin_port	= htons(8001);//这个是http写死的
		httpprintf("dbSetupTotal.setSystem.szHostByName[0]==0\n");
	}
	else
	{
	         if(DNS_SDDR==0)
	         	{
				httpprintf("host name:%s\r\n",_hostname.c_str());
				
		     		wdog_app_alive();//added by hym
			      DNS_SDDR=gngethostbyname((char *)_hostname.c_str(),1);
				 httpprintf("DNS_SDDR=%d\r\n",DNS_SDDR);				 
			     if(DNS_SDDR==0)
			      {
								 		 httpprintf("unknow host:%s\r\n",_hostname.c_str());
				    						 memset(&serverip_http,0,sizeof(serverip_http));
				     						close(fd);
				     						return false;
			     	}

	         	}
			       peer.sin_addr.s_addr = htonl(DNS_SDDR);
			       peer.sin_port	= htons(_port);
			       serverip_http=peer;

	}

	//if( connect( fd, (struct sockaddr *)&peer, sizeof( peer ) ) )
	httpprintf("%s\n","connect...");
	if( connect_timeout( fd, (struct sockaddr *)&peer, sizeof( struct sockaddr ) ,4) )
	{
		//cout << errno << "connect failed" << endl;
		httpprintf("%s\n","connect failed");
		DNS_SDDR=0;
		_state = CONN_ERROR;
		close( fd );		
		return false;
	}
	httpprintf("%s\n","connect ok");
	_state = CONN_OK;
	_fd = fd;    
	return true;
}

s_state Sock_instance::state()
{
	return _state;
}

int Sock_instance::fd()
{
	return _fd;
}

bool Sock_instance::Send(string msg)
{

	int rc;

	if((rc = send_timeout(_fd, msg.c_str(), msg.size(), 0,5)) == -1)
	{
		if((errno != EWOULDBLOCK) && (errno != EAGAIN))
		{
			_state = CONN_ERROR;
			close(_fd);
			return false;
		}
	}
	return true;
}

//////////////////////////////////////////////////////////////////////////
int recv_timeout(HFILE hSock,char *data,int len,int tiemout)
{
	fd_set rdFD;
	struct timeval tv;
	char temp;
	int rc;

	tv.tv_sec = tiemout;
	tv.tv_usec = 0;

	FD_ZERO(&rdFD);
	FD_SET(hSock, &rdFD);

	if (select(hSock + 1, &rdFD, 0, 0, &tv) == 1)
	{
		rc=recv(hSock, data, len, MSG_PEEK);
		return rc;
	}
	return -1;
}


int Sock_instance::Receive()
{
	CMessageBox *msgBox; 
      	msgBox	= new CMessageBox; 
	//msgBox->MsgBoxProc_Message("Wait for moment ...");	
	msgBox->MsgBoxProc_Message3(UISTR(UISTR_WAIT_FOR_COMMUNICATING));
	
	int nETime;
	int nReqSize = _data_size;
	int nReadSize = 0;
	BYTE* pBufIdx = (BYTE*)_data;
	static bool b_readhead = true;
	char buf[BUFSIZ];
  	char *p_buf = buf;
	int nTimeout;

	nTimeout=25000;

	nETime = GetMainTickCount() + nTimeout;


	wdog_app_alive();//added by hym
	while (GetMainTickCount() < nETime)	
	{
		int nCurrentReadSize =BUFSIZ - 1;
		wdog_app_alive();//added by hym
		
		nCurrentReadSize = recv_timeout(_fd, pBufIdx, nCurrentReadSize, 0,8);  
		wdog_app_alive();//added by hym
		if (nCurrentReadSize > 0)
		{
			wdog_app_alive();//added by hym
			
			httpprintf("read HTTP data %d\r\n",nCurrentReadSize);
			pBufIdx += nCurrentReadSize;
			nReadSize += nCurrentReadSize;
			nETime = GetMainTickCount() + nTimeout;
			continue;
		}
		else if (nCurrentReadSize < 0)
		{
			if (errno == EWOULDBLOCK)
			{
				continue;
			}
			_state = CONN_WAIT;
			httpprintf("read HTTP data err\r\n");
		}
		else 
		{
			_state = CONN_WAIT;		
		}
		break;

	} 
	wdog_app_alive();//added by hym

	_datalen = nReadSize;	
	if(msgBox)
          delete msgBox;    
	return nReadSize;
}

#if 0

int Sock_instance::Receive()
{
	int nETime;
	fd_set rdFD;
	struct timeval tv;
	int rc;
	char buf[1024];
	char *p_buf = buf;

	static bool b_readhead = true;

	bzero(buf, 1024);
	
	tv.tv_sec = 10;
	tv.tv_usec = 0;

	FD_ZERO(&rdFD);
	FD_SET(_fd, &rdFD);
	if (select(_fd + 1, &rdFD, 0, 0, &tv) != 1)
	{
		return -1;
	}

	nETime = GetMainTickCount() + 10000;
	httpprintf("%s\r\n","recive ...");
	while (GetMainTickCount() < nETime)
	{
		if((rc = recv( _fd, buf, 1024, 0 )) < 0 )  //MSG_PEEK
		{
			//cout << "recive error" << endl;
			httpprintf("%s\n","recive timeout");
			_state = CONN_WAIT;
			Close();
			break;
		}
		else if( rc == 0 )
		{
			//cout << "server teminated" << endl;
			httpprintf("%s\r\n","server teminated");
			_state = CONN_WAIT;
			Close();
			break;
		}
		else
		{
			//read HTTP head
			httpprintf("%s\r\n","read HTTP data");
			wdog_app_alive();
			
			int ix = 0;
			while( b_readhead )
			{
				// 2 0D 0A just for head end
				if( ix >= rc )
					break;
				if( buf[ix] == 13 && buf[ix+1] == 10 && buf[ix+2] == 13 && buf[ix+3] == 10 )
				{
					b_readhead = false;
					char *p = new char[ix+5];
					memset( p, 0, ix+5 );
					memcpy( p, buf, ix+5 );
					p_buf += ix + 5;
					_http_head = p;
					delete[] p;
					//cout << _http_head << endl;
					httpprintf("%s\n",_http_head.c_str());
					break;
				}
				ix ++;
			}
			
			ix = 0;

			//copy data to _data
			if( ix != 0 && ix < rc )
			{
				//this buf has head so data begin with buf+ix+4
				memcpy( _data+_datalen, buf+ix+4, rc-ix-4 );
				_datalen += rc-ix-4;
			}
			else
			{
				memcpy( _data+_datalen, buf, rc );
				_datalen += rc;	
			}
			nETime = GetMainTickCount() + 10000;
		}
	}
	if(rc<0)
	  httpprintf("%s\r\n","recive error");
	return rc;
}
#endif

inline void Sock_instance::Close()
{    
	close( _fd );
}

//string Sock_instance::data() const
char * Sock_instance::data() const
{
	return (char *)_data;
}

int Sock_instance::datalen() const
{
	return _datalen;
}

string Sock_instance::http_head() const
{
	return _http_head;
}


int Sock_Receive(string hostname, string quest,unsigned char *dat,int size)
{
    int len;
	
	//Sock_instance *s_client=new Sock_instance( hostname, 80, CLIENT_TYPE,15*1024*1024);
	Sock_instance s_client( hostname, dat,size );
	
	if( !s_client.Connect() )
	{
		httpprintf("%s\n","connect error"); 
		return 0;
	}

	//send the http query to the host
	httpprintf("%s\n","connect is ok!");
	if( !s_client.Send(quest) )
	{
		httpprintf("%s\n","send is error!");
		return 0;
	}

	httpprintf("%s\n","Receive data...!");
	//recieve all the file from the hsot
	if(s_client.Receive() < 0)
	{
		return 0;
	}
	wdog_app_alive();//added by hym
	len=s_client.datalen();	
	httpprintf("datalen=%d\r\n",len);  
	//delete  s_client;
	return len;
}



///////////////////////////////////////////

int HttpClient_Connecting(void)
{
	return HttpLinking;
}
void HttpClient_SetConnecting(unsigned char states)
{
	HttpLinking=states;
}

int HttpClient_Connect(string domain_name,int deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType)
{
	string word;
	string hostname;
	BYTE* pdatabuf;
	int nRet;
	char temp[64];//用来存放传入的数据
	 if(PunchType == HTTP_DEPTPUNCH)
	 {
		sprintf(temp, "%d", nId);
	 }
	 xprintf("temp==%s\r\n",temp);
	 
	xprintf("link_lost===%d\r\n",LINK_LOST);
	if( LINK_LOST == 1)
	{
	 	httpprintf(" LINK_LOST=1\r\n");	
		return 0;
	}
	
	 xprintf("i am in httpclien_connect!!!deviceid===%d!!!\r\n",deviceid);
	 httpprintf("nId=%d\n",nId);	
	 httpprintf("nPin=%d\n",nPin);	
	 httpprintf("nDept=%d\n",nDept);
	 httpprintf("PunchType=%d\n",PunchType);

	if (dbSetupTotal.setSystem.bDHCPUse && dbComm_dhcpSuccess==0)
	{
	 	 httpprintf("dbComm_dhcpSuccess=%d\r\n",dbComm_dhcpSuccess);	
	 	 httpprintf("dbSetupTotal.setSystem.bDHCPUse=%d\r\n",dbSetupTotal.setSystem.bDHCPUse);	
		 return 0;
	}
	nRet=1;

	//此时是post格式的请求，不能用get
/*

POST /WcfEquServiceLibrary/EquService/ HTTP/1.1
Content-Type: application/soap+xml;charset=utf-8
Host: 192.168.10.2:8001
Content-Length: 651
Expect: 100-continue
Accept-Encoding: gzip,deflate
Connection: Keep-Alive

<s:Envelope xmlns:a="http://www.w3.org/2005/08/addressing" xmlns:s="http://www.w3.org/2003/05/soap-envelope">
  <s:Header>
    <a:Action s:mustUnderstand="1">http://tempuri.org/IEquHttpService/UpDownTime</a:Action>
    <a:MessageID>urn:uuid:3c7a424b-d554-4a95-87a8-161cac4142cd</a:MessageID>
    <a:ReplyTo>
      <a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address>
    </a:ReplyTo>
    <a:To s:mustUnderstand="1">http://192.168.10.2:8001/WcfEquServiceLibrary/EquService/</a:To>
  </s:Header>
  <s:Body>
    <UpDownTime xmlns="http://tempuri.org/">
      <EquCode>1</EquCode>
    </UpDownTime>
  </s:Body>
</s:Envelope>

*/

/*
QString与string相互转换函数
QString s2q(const string &s); 
string q2s(const QString &s); 

*/
	char buf[128],buf1[24];
	string ywm,ywm1,Device;
	//u16 port = dbSetupSystemNew.wPortNumBack;
	u16 port = 8001;//此处是http后台端口，写死在此


	//制作ip
	QString str;
	int a, b, c, d;
	UI_IP_UNMAKE(dbSetupTotal.setSystem.szHostByName[0] == 0 ? dbSetupSystemNew.ipPCBackground : dbComm_ipPcBackground, a, b, c, d);  
	str = QString("%1.%2.%3.%4").arg(a).arg(b).arg(c).arg(d);
	string iptext =q2s(str);
	
	//制作端口号
	sprintf(buf1,"%d",port);
	ywm1 = buf1;

	//制作设备号
	sprintf(buf1,"%d",deviceid);
	Device = buf1;
	
	//制作数据
	string context;
	context  ="<s:Envelope xmlns:a=\"http://www.w3.org/2005/08/addressing\" xmlns:s=\"http://www.w3.org/2003/05/soap-envelope\">";
	context  +="    <s:Header>";
	context  +="         <a:Action s:mustUnderstand=\"1\">http://tempuri.org/IEquHttpService/";
	if(PunchType == HTTP_TIMESET)
	{
		context += "UpDownTime";
	}
	else if(PunchType == HTTP_UPDATA_FIRMWARE)
	{
		context += "UpDownUpgradeFile";
	}
	else if(PunchType == HTTP_DEPTPUNCH)
	{
		context += "UpDownReg";
	}
	context += "</a:Action>";
	context  +="         <a:MessageID>urn:uuid:15ce9bcc-9997-4ca6-a20c-2effa4c6b358</a:MessageID>";
	context  +="         <a:ReplyTo>";
	context  +="              <a:Address>http://www.w3.org/2005/08/addressing/anonymous</a:Address>";
	context  +="         </a:ReplyTo>";
	
	//context  +="         <a:To s:mustUnderstand=\"1\">http://192.168.10.2:8001/WcfEquServiceLibrary/EquService/</a:To>";
	context  +="         <a:To s:mustUnderstand=\"1\">http://";
	context  += iptext;//192.168.10.2
	context +=":";
	context +=ywm1;//8001
	context +="/WcfEquServiceLibrary/EquService/</a:To>";			
	context  +="    </s:Header>";
	
	if(PunchType == HTTP_TIMESET)
	{
		context  +="    <s:Body>";
		context  +="        <UpDownTime xmlns=\"http://tempuri.org/\">";
		//设备号	
		context  +="             <EquCode>";
		context  += Device;
		context  +="</EquCode>";
		
		context  +="        </UpDownTime>";
		context  +="    </s:Body>";
		context +="</s:Envelope>";
		
	}
	else if(PunchType == HTTP_UPDATA_FIRMWARE)
	{
		context  +="    <s:Body>";
		context  +="        <UpDownUpgradeFile xmlns=\"http://tempuri.org/\">";
		//设备类型	
		context  +="            	<Tid>";
		context  += tid;
		context  +="</Tid>"; 
		//设备号	
		context  +="             <EquCode>";
		context  += Device;
		context  +="</EquCode>";
		//硬件版本
		context  +="             <Hid>";
		context  += LNSC_PRODUCTNAME;
		context  +="</Hid>";
		//软件版本
		context  +="             <Sid>";
		context  += LNSC_FIRMWAREVERSION;
		context  +="</Sid>";
		
		context  +="        </UpDownUpgradeFile>";
		context  +="    </s:Body>";
		context +="</s:Envelope>";
	}
	else if(PunchType == HTTP_DEPTPUNCH)
	{
		context  +="    <s:Body>";
		context  +="        <UpDownReg xmlns=\"http://tempuri.org/\">";
		//设备类型	
		context  +="            	<Tid>";
		context  += tid;
		context  +="</Tid>"; 
		//设备号	
		context  +="             <EquCode>";
		context  += Device;
		context  +="</EquCode>";
		//登记号
		context  +="             <RegCode>";
		context  += temp;
		context  +="</RegCode>";
			
		context  +="        </UpDownReg>";
		context  +="    </s:Body>";
		context +="</s:Envelope>";
	}

	int len = strlen(context.c_str());
	xprintf("len==%d\r\n",len);
	
	//请求行
	string quest = "POST /WcfEquServiceLibrary/EquService/ HTTP/1.1\r\n";
	//请求头部
	quest += "Content-Type: application/soap+xml; charset=utf-8\r\n";
	
	//quest += "Host: 192.168.10.2:8001\r\n";
	quest += "Host: ";
	quest += iptext;
	quest +=":";
	quest +=ywm1;
	quest +="\r\n";

	//制作发送长度
	//quest += "Content-Length: 679\r\n";
	sprintf(buf,"Content-Length: %d",len);
	ywm = buf;
	quest += ywm;
	quest +="\r\n";
	
	quest += "Expect: 100-continue\r\n";
	quest += "Accept-Encoding: gzip,deflate\r\n";
	quest += "Connection: Keep-Alive\r\n\r\n";//在这里多加一行空格，这是格式需要

	//请求数据
	quest += context;

	httpprintf("ywm:%s\r\n",ywm.c_str());
	httpprintf("iptext:%s\r\n",iptext.c_str());
	httpprintf("ywm1port:%s\r\n",ywm1.c_str());
	//httpprintf("quest:%s\r\n",quest.c_str());
	httpprintf("Device:%s\r\n",Device.c_str());
	httpprintf("device==%d\r\n",deviceid);


	

	
	//发送并接受	
	int bufsize;	
	bufsize=3*1024*1024;
    	pdatabuf = (BYTE*)malloc(bufsize);
	if (!pdatabuf)
	{
		httpprintf("%s\r\n","malloc error");
		return 0;
	}
	xprintf("==================send http=====================================\r\n");
         char * TTMP=(char *)quest.c_str();
         int len1=quest.length();
	int i;
        for(i=0;i<len1;i++)
        {
            xprintf("%c",TTMP[i]);
        }
         xprintf("\r\n");
         //wdog_app_alive();
         xprintf("==================send http=====================================\r\n");
	int datalen=Sock_Receive(hostname, quest,pdatabuf,bufsize);
    	if(datalen==0)
	{
	   httpprintf("datalen is zero\r\n");	
	   FREE(pdatabuf);
	   return 0;
	}
	xprintf(" loveywm datalen===%d\r\n",datalen);	
	//这里需要处理接受的数据函数
/*	int i;
	for(i=0;i<datalen;i++){
		xprintf("%c",pdatabuf[i]);
	}
*/	
	//判断接受的是否是真确的信息
	if(!mystrstr((char *)pdatabuf,"HTTP/1.1 200 OK"))
	{
		xprintf("HTTP/1.1 400 Bad Request\r\n");
		return  0;
	}

	
	if(PunchType == HTTP_TIMESET)
	{
		nRet = http_time_set((char *)pdatabuf);
	}
	else if(PunchType == HTTP_UPDATA_FIRMWARE)
	{
		nRet = http_updata_firmware((char *)pdatabuf);
	}
	else if(PunchType == HTTP_DEPTPUNCH)
	{
		xprintf("\r\nPunchType == HTTP_DEPTPUNCH\r\n");
		xprintf("npin1==%d\r\n",nPin);
		if(nPin == 0)
		{
			nRet = http_down_reg((char *)pdatabuf);
		}		
		else if(nPin == 1)
		{
			xprintf("npin2==%d\r\n",nPin);
			nRet = http_down_name((char *)pdatabuf);
		}
		
		//nRet = 1;
	}
	else
 	{
		nRet=0;
    	}
	
	httpprintf("\r\nHttpClient_Connect exit\r\n");
	FREE(pdatabuf);
	return nRet;
}


//int HttpClient_main(string deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType,unsigned char MsgEn)
int HttpClient_main(u32 deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType,unsigned char MsgEn)	
{
      	xprintf("i am in httpclien_main!!!\r\n");	
 	 HttpLinking=1;
	 //return 1; 
	 int ret;

	if(ret = HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
	{
	      HttpLinking=1;
	      xprintf("i am in httpclien_main!!!HttpLinking111===%d!!!\r\n",HttpLinking);
	      return ret;
	}
	//else
	//{
		//再一次试试
		//if(ret = HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
		//{
	   			//HttpLinking=1;
				//xprintf("i am in httpclien_main!!!HttpLinking222===%d!!!\r\n",HttpLinking);
			        //return ret;
		//}
/*		else
		{
			if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
			{
	   			HttpLinking=1;	
				xprintf("i am in httpclien_main!!!HttpLinking333===%d!!!\r\n",HttpLinking);
			   	return 1;
			}	
			else
			{
				if(HttpClient_Connect((const char *)&dbSetupTotal.setSystem.szHostByName[0],deviceid,nId,nPin,nDept,PunchType))
				{
	   					HttpLinking=1;
						xprintf("i am in httpclien_main!!!HttpLinking444===%d!!!\r\n",HttpLinking);
			   			 return 1;
				  }		
			}
		}*/
	//}
        HttpLinking=0;
        //xprintf("i am in httpclien_main!!!HttpLinking555===%d!!!\r\n",HttpLinking);
        return 0;
        
}

//这两个是转换函数
QString s2q(const string &s)
{
    return QString(QString::fromLocal8Bit(s.c_str()));
}
string q2s(const QString &s)
{
    return string((const char *)s.toLocal8Bit());
 }



//下面是http处理函数

char *Http_DeptStrGet(int n,unsigned char type)
{
	if(type==1)
	{
	  return http_department_str[n].idstr;
	}
	else if(type==2)
	{
	  return http_department_str[n].namestr;
	}	
	else
	  return 0;
}
int Http_DeptStrCNTGet(void)
{
	return http_department_str_Num;
}

int TIMESTRING2ID(char* strID,int *pnID)
{
	int nLength, i;
	int nID = 0;
	unsigned char number;

	//if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
	//	return 0;

    nLength = strlen(strID);
	
	for (i=0; i<nLength; i++)
	{		

		if (strID[i] >= '0' && strID[i] <= '9')
		{
		   nID *= 10;
		   number = strID[i] - '0';
		   nID += number;
		}
// 		else if (strID[i] >= 'A' && strID[i] <= 'Z')
// 			number = 10 + strID[i] - 'A';
// 		else if (strID[i] >= 'a' && strID[i] <= 'z')
// 			number = 10 + strID[i] -'a';
		else
			break;

	}
    *pnID=nID;
	return i;
}

//String格式"2010-12-19 19:45:28"
void TimeStringGet(char* strTime,int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond)
{
	int  i=0;
	//int nID = 0;
	//int nYear,nMonth,nDay,nHour,nMinute,nSecond;
	char* pstrTime;
	
	//if ((nLength = strlen(strID)) > IDNUMBER_LENGTH)
	//	return 0;
	pstrTime=&strTime[2];
	i=TIMESTRING2ID(pstrTime,pnYear);
    pstrTime+=(i+1);
	i=TIMESTRING2ID(pstrTime,pnMonth);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnDay);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnHour);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnMinute);
    pstrTime+=(i+1);	
	i=TIMESTRING2ID(pstrTime,pnSecond);

}

//时间更新
u8 http_time_set(char *pdatabuf)
{
//处理下面的东西，获取时间
/*
HTTP/1.1 200 OK
Content-Length: 452
Content-Type: application/soap+xml; charset=utf-8
Server: Microsoft-HTTPAPI/1.0
Date: Fri, 19 Oct 2012 08:37:21 GMT

<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope" xmlns:a="http://www.w3.org/2005/08/addressing">
<s:Header>
<a:Action s:mustUnderstand="1">http://tempuri.org/IEquHttpService/UpDownTimeResponse</a:Action>
<a:RelatesTo>urn:uuid:15ce9bcc-9997-4ca6-a20c-2effa4c6b358</a:RelatesTo>
</s:Header>
<s:Body>
<UpDownTimeResponse xmlns="http://tempuri.org/">
<UpDownTimeResult>2012-10-19 16:37:21</UpDownTimeResult>
</UpDownTimeResponse>
</s:Body>
</s:Envelope>
*/	
	char *timetext;
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
	char buf[strlen("2012-10-19 16:37:21")];
	memset(buf,0,strlen("2012-10-19 16:37:21"));
	if(timetext = mystrstr(pdatabuf,"<UpDownTimeResult>"))
	{
		xprintf("\r\ntimetext==%s\r\n",timetext);
		memcpy(buf,timetext + strlen("<UpDownTimeResult>"),strlen("2012-10-19 16:37:21"));
		xprintf("buf==%s\r\n",buf);
		TimeStringGet(buf,&nYear,&nMonth, &nDay, &nHour, &nMinute, &nSecond);
		Rtc1Set(nYear, nMonth, nDay, uiRtcGetWeekDay(nYear, nMonth, nDay), nHour, nMinute, nSecond);

		xprintf("\r\ngggggggggggggggggggggggg\r\n");
		
		if (nYear < 0 || nYear > 99 ||
		nMonth < 1 || nMonth > 12 ||
		nDay < 1 || nDay > uiRtcGetDaysForMonth(nYear, nMonth) ||
		nHour < 0 || nHour > 23 ||
		nMinute < 0 || nMinute > 59 ||
		nSecond < 0 || nSecond > 59)
		{
			nYear = 0;
			nMonth = 1;
			nDay = 1;
			nHour = 0;
			nMinute = 0;
			nSecond = 0;		
			Rtc1Set(nYear, nMonth, nDay, uiRtcGetWeekDay(nYear, nMonth, nDay), nHour, nMinute, nSecond);
		}
		xprintf("%04d-%02d-%02d %02d:%02d:%02d\n", nYear, nMonth, nDay, nHour, nMinute, nSecond);
		RtcSet(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
		g_MainWindow->DrawClock(TRUE);
		return 1;
	}
	else
	{
		xprintf("\r\nxxxxxxxxxxxxxxxxxxxxxxxxxx\r\n");
		return 0;
	}
         
	return 1;
}

//固件升级
u8 http_updata_firmware(char *pdatabuf)
{
	//处理下面的东西，获取升级信息
/*
HTTP/1.1 200 OK
Content-Length: 532
Content-Type: application/soap+xml; charset=utf-8
Server: Microsoft-HTTPAPI/1.0
Date: Mon, 22 Oct 2012 03:20:34 GMT

<s:Envelope xmlns:s="http://www.w3.org/2003/05/soap-envelope" xmlns:a="http://www.w3.org/2005/08/addressing">
	<s:Header>
		<a:Action s:mustUnderstand="1">http://tempuri.org/IEquHttpService/UpDownUpgradeFileResponse</a:Action>
		<a:RelatesTo>urn:uuid:15ce9bcc-9997-4ca6-a20c-2effa4c6b358</a:RelatesTo>
	</s:Header>
	<s:Body>
		<UpDownUpgradeFileResponse xmlns="http://tempuri.org/">
			<UpDownUpgradeFileResult>http://192.168.10.47/wcfclient/update/SB3300-5Kv1.35.1536.61.bin</UpDownUpgradeFileResult>
		</UpDownUpgradeFileResponse>
	</s:Body>
</s:Envelope>
*/
	char buf[256];
	char *pos;
	BOOL bRet = TRUE;
	
	memset(buf,0,sizeof(buf));
	xprintf("i am in http_updata_firmware\r\n");
	pos =Http_CfgstrGet2(pdatabuf,"<UpDownUpgradeFileResult>","</UpDownUpgradeFileResult>",buf);
	if(pos == NULL)
	{
		xprintf("pos is null!!\r\n");
		return 0;
	}
	xprintf("22222buf==%s\r\n",buf);

	CMessageBox *msgBox = new CMessageBox; 
  	//msgBox->MsgBoxProc_Message("UpdateFirmware ...");
	msgBox->MsgBoxProc_Message3(UISTR(UISTR_WAIT_FOR_COMMUNICATING));
	Db_FreeAllData();   
	//buf==http://192.168.10.47/wcfclient/update/SB3300-5Kv1.35.1536.61.bin	
	bRet =HttpRomWrite1(buf);

	if(msgBox)
	  	delete msgBox;
	
	Db_LoadAllData(TRUE);
    	//SB_EXEC("reboot"); 
	//while(1);
	uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	xprintf("httpclient_main is ok\r\n");
	system("reboot");
   	return bRet;
	
}

//更新用户信息
u8 http_down_reg(char *pdatabuf)
{
//格式如下:
/*

*/
	char *buf= (char *)malloc(1024 * 10);
	char *pos=NULL;
	char *pos1=NULL,*pos2=NULL;
	char name[24];
	char  buf3[10]= {0};
	char buf2[2014];
	char buf4[1024 * 5];
	char buf5[1404];
	//char
	u8 ret = 1;
	u32 kahao;
	int nback;
	int nfp,card,passwd,sign=0,mima,ka;
	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	
	memset(buf,0,sizeof(buf));
	xprintf("i am in http_down_reg\r\n");
	pos = Http_CfgstrGet2(pdatabuf,"<UpDownRegResult>","</UpDownRegResult>",buf);
	if(pos == NULL)
	{
		//当这两者之间无数据时，说明无此id
		xprintf("1pos is null!!\r\n");
		xprintf("no this id!!\r\n");
		return UIENROLL_NO_ENROLL_ID;
	}	
	int i;
	xprintf("\r\nywm==\r\n");
	//for(i=0;i<strlen(buf);i++){
		//xprintf("%c",buf[i]);
	//}	
	//数据格式
	//NM=鏉庢槑;NL=;W=1;B=10,P=0,D=123;B=11,P=0,D=0123456;
	
	//对名字数据的处理
	pos1 = Http_CfgstrGet2(buf,"NM=",";",name);
	memcpy(gUserInfoTemp.NAME,name,USERNAME_LENGTH * 2);
	
	xprintf("gUserinfotemp.name==%s\r\n",gUserInfoTemp.NAME);
	xprintf("Name==%s\r\n",name);

	QString str = QString::fromUtf8(name,-1);//接受的是utf8编码，需要转换
	
	
	//QString str =G2U((char *)packed_name_info.NameA);	
	//QString str =G2U((char *)gUserInfoTemp.NAME);
	xprintf("ywm2\r\n");
	bzero(gUserInfoTemp.NAME, USERNAME_LENGTH * 2);
	xprintf("ywm3\r\n");
	STRING2UNICODE(str,(WORD*)gUserInfoTemp.NAME, USERNAME_LENGTH); 

	//取ID
	pos1 = Http_CfgstrGet2(pos1,"W=",";",buf3);
	xprintf("ywm5\r\n");		
	//xprintf("kahao1==%d\n",kahao);
	gUserInfoTemp.ID = kahao;

	kahao = AsciiToDec(buf3);
	gUserInfoTemp.ID = kahao;
	xprintf("gUserInfoTemp.ID ==%d\n",gUserInfoTemp.ID );
	xprintf("kahao==%d\n",kahao);

	//数据格式
	//NM=鏉庢槑;NL=;W=1;B=10,P=0,D=123;B=11,P=0,D=0123456;
	while(pos1 != NULL)
	{
		memset(buf2,0,sizeof(buf2));
		memset(buf3,0,sizeof(buf3));
		pos1 = Http_CfgstrGet2(pos1,"B",";",buf2);
		if(pos1 == NULL)
		{
			xprintf("break1\r\n");
			goto break_ok;
		}
		pos2 = Http_CfgstrGet2(buf2,"=",",",buf3);
		nback = AsciiToDec(buf3);
		xprintf("nback===%d\r\n",nback);
		
		if(nback == 10)
		{
			xprintf("card\r\n");
			passwd = nback;
			
			memset(buf3,0,sizeof(buf3));
			//pos2 = Http_CfgstrGet2(pos2,"D=",";",buf3);
			pos2 = mystrstr(buf2,"D=");
			memcpy(buf3,&pos2[2],strlen(pos2)-2);
			mima = AsciiToDec(buf3);
			gUserInfoTemp.PWD = mima;
			xprintf("mima==%d\n",mima);
			xprintf("gUserInfoTemp.PWD==%d\n",gUserInfoTemp.PWD);

			//
			if (!DbUserInfoEnroll(&gUserInfoTemp, passwd, &mima))
			{
				xprintf("DBuserinfoenroll failed\r\n");	
				return FALSE;
			}   
			ret = 1;
			
			
		}
		else if(nback == 11)
		{
			xprintf("ywm\r\n");
			card = nback;

			memset(buf3,0,sizeof(buf3));
			//pos2 = Http_CfgstrGet2(buf2,"D=",";",buf3);
			pos2 = mystrstr(buf2,"D=");
			memcpy(buf3,&pos2[2],strlen(pos2)-2);
			ka = AsciiToDec(buf3);
			gUserInfoTemp.CARD = ka;
			xprintf("ka==%d\n",ka);
			xprintf("gUserInfoTemp.CARD==%d\n",gUserInfoTemp.CARD);

			//
			if (!DbUserInfoEnroll(&gUserInfoTemp, card, &ka))
			{
				xprintf("DBuserinfoenroll failed\r\n");	
				return FALSE;
			}   
			ret = 1;
		}
		else
		{
			xprintf("fp\r\n");
			nfp = nback;
			sign = 1;

			memset(buf4,0,sizeof(buf4));
			//pos2 = Http_CfgstrGet2(buf2,"D=",";",buf4);
			pos2 = mystrstr(buf2,"D=");
			memcpy(buf4,&pos2[2],strlen(pos2)-2);
			
			//从buf4[8]开始，每两个算一个字节，取1404个
			char tmpbuf[2]={0};
			int k;
			BYTE bdata;
			for(k = 0;k<1404;k++)
			{
				memcpy(tmpbuf, &buf4[16+k*2],2);
				buf5[k] = (BYTE)strtoul(tmpbuf,NULL,16);
			}

			//
			if (!DbUserInfoEnroll(&gUserInfoTemp, nfp, &buf5[0], TRUE, FALSE))
			{
				xprintf("DBuserinfoenroll failed\r\n");
				return UIENROLL_NO_ENROLL_FP;
			}   
			ret = 1;			
		}
	}
	
break_ok:
/*	xprintf("sign==%d\n",sign);
	xprintf("card==%d\n",card);
	xprintf("passwd==%d\n",passwd);
	
	if(sign == 1)//指纹注册标志
	{
		if (!DbUserInfoEnroll(&gUserInfoTemp, nfp, &buf5[0], TRUE, FALSE))
		{
			xprintf("DBuserinfoenroll failed\r\n");
			return UIENROLL_NO_ENROLL_FP;
		}   
		ret = 1;
	}
	else if(passwd == 10)//密码注册BACKUP_CARD
	{
		if (!DbUserInfoEnroll(&gUserInfoTemp, passwd, &mima))
		{
			xprintf("DBuserinfoenroll failed\r\n");	
			return FALSE;
		}   
		ret = 1;
	}
	else if(card == 11)//卡号注册
	{
		if (!DbUserInfoEnroll(&gUserInfoTemp, card, &ka))
		{
			xprintf("DBuserinfoenroll failed\r\n");	
			return FALSE;
		}   
		ret = 1;
	}
	else
	{
		ret = 0;
	}
	sign = 0;
*/
	//if(ret == 0)
	//{
		//DbUserInfoDelete((u64)kahao, 0xFFFF);	
	//}
	free(buf);
	return ret;
}

//更新用户信息
u8 http_down_name(char *pdatabuf)
{
//格式如下:
/*

*/
	char *buf= (char *)malloc(1024 * 10);
	if(buf ==  NULL)
	{
		xprintf("malloc buf error\r\n");
		return 0;
	}
	char *pos=NULL;
	char *pos1=NULL;
	char name[24];
	int ret = 1;
	memset(buf,0,1024 * 10);
	memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
	xprintf("i am in http_down_name\r\n");
	pos = Http_CfgstrGet2(pdatabuf,"<UpDownRegResult>","</UpDownRegResult>",buf);
	if(pos == NULL)
	{
		//当这两者之间无数据时，说明无此id
		xprintf("1pos is null!!\r\n");
		xprintf("no this id!!\r\n");
		return 0;
	}	
	//int i;
	//xprintf("\r\nywm==\r\n");
	//for(i=0;i<strlen(buf);i++){
		//xprintf("%c",buf[i]);
	//}	
	//数据格式
	//NM=鏉庢槑;NL=;W=1;B=10,P=0,D=123;B=11,P=0,D=0123456;
	
	//对名字数据的处理
	pos1 = Http_CfgstrGet2(buf,"NM=",";",name);
	if(pos1 == NULL)
	{
		xprintf("no name\r\n");
		return 0;
	}
	memcpy(gUserInfoTemp.NAME,name,USERNAME_LENGTH * 2);
	
	xprintf("gUserinfotemp.name==%s\r\n",gUserInfoTemp.NAME);
	xprintf("Name==%s\r\n",name);

	QString str = QString::fromUtf8(name,-1);//接受的是utf8编码，需要转换
	
	
	//QString str =G2U((char *)packed_name_info.NameA);	
	//QString str =G2U((char *)gUserInfoTemp.NAME);
	xprintf("ywm2\r\n");
	bzero(gUserInfoTemp.NAME, USERNAME_LENGTH * 2);
	xprintf("ywm3\r\n");
	STRING2UNICODE(str,(WORD*)gUserInfoTemp.NAME, USERNAME_LENGTH); 
	free(buf);
	return ret;
}





