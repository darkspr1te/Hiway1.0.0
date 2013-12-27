#include "CSocket.h"
#include "../precomp.h"
#include "../dns.c"
#include "../gui/MessageBox.h"


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

extern int comm_uartsend2(int iUART, void *pBuffer, int len);

#define  PrintfDbugEn1 0

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
	comm_uartsend2(0, &string, strlen(string)) ;
    va_end(ap);
#endif
}


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
DWORD DNS_SDDR=0;
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
	if (dbSetupTotal.setSystem.szHostByName[0]==0)
	{
            	peer.sin_addr.s_addr = htonl(dbComm_ipPcBackground);
		peer.sin_port	= htons(dbSetupTotal.setSystem.wPortNumBack);		
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

	xprintf("wait for recv!!\r\n");
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
		httpprintf("Receive data is error!\r\n");
		return 0;
	}
	wdog_app_alive();//added by hym
	len=s_client.datalen();	
	httpprintf("datalen=%d\r\n",len);  
	//delete  s_client;
	return len;
}


