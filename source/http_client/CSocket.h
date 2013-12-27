#ifndef __CSOCKET_H__
#define __CSOCKET_H__
/*
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
*/
//extern void SOCKET_printf (
//	const char*	str,	/* Pointer to the format string */
//	...					/* Optional arguments */
//);

/*
#define httpprintf SOCKET_printf
//#define httpprintf 


using namespace std;

typedef enum socket_type { SERVER_TYPE = 0, CLIENT_TYPE } s_type;
typedef enum socket_state{ CONN_ERROR = -1, CONN_OK = 0, CONN_WAIT = 1 } s_state;

class Sock_instance
{
public:
	Sock_instance(string hostname, unsigned char *dat,int size);	//Sock_instance(string hostname, unsigned port, s_type type,int size);	
	~Sock_instance();
	bool Connect();
	int fd();
	s_state state();
	bool Send(string msg);
	int Receive();
	void Close();
	char* data() const;
	int datalen() const;
	string http_head() const;
private:
	string	_hostname;
	unsigned	_port;
	int		_fd;
	s_state	 _state;
	s_type	_type;
	unsigned char *_data;
	int _data_size;
	int _datalen;
	string _http_head;
};

extern struct sockaddr_in serverip_http;
int Sock_Receive(string hostname, string quest,unsigned char *dat,int size);
extern unsigned char Http_MsgEn;
*/
#endif

