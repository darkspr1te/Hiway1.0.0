#ifndef __HTTPMAIN_H__
#define __HTTPMAIN_H__

#include "../precomp.h"
#include "../_fp.h"
#include "CSocket.h"
#include <fstream>


enum
{
  HTTP_BADGEPUNCH=1,
  HTTP_DEPTPUNCH ,
  HTTP_TIMESET,
  HTTP_FINGERPUNCH,
  HTTP_FINGERDEPTPUNCH ,
  HTTP_PINDEPTPUNCH,
  HTTP_UPLOAD_FPTEMPLATE,
  HTTP_DOWNLOAD_FPTEMPLATE,
  HTTP_UPLOAD_LOGO,
  HTTP_UPDATA_FIRMWARE ,
  HTTP_FETCH_DEPARTMENT,
  HTTP_TRANSFER_DEPARTMENT,
  HTTP_FINGERPUNCH2,
  HTTP_PINPUNCH2,
    HTTP_SYNC_ACK,

};


extern unsigned char Http_BadgePunch_IsOk(void);
extern const char* Http_CfgstrGet(char *buff,char *dest);
extern unsigned char Http_DeviceId_IsOk(void);

extern char str_PunchedIn[40]; 
extern char str_PunchedOut[40]; 
extern char str_EmployeeName[40]; 
extern char str_DepartmentName[40]; 
extern char str_LastPunch[40];
extern char str_CurrentTime[40]; 
extern char str_UTCOffset[40]; 
extern char str_AccountName[40]; 



extern void Http_BadgePunchDataRead(char *Client_Datap);
extern void Http_DepPunchDataRead(char *Client_Datap);
//extern  int HttpClient_main(string deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType,unsigned char MsgEn);
extern 	int HttpClient_main(u32 deviceid,unsigned long long nId,unsigned long long nPin,unsigned long long nDept,int PunchType,unsigned char MsgEn);
extern void TimeStringGet(char* strTime,int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond);
char *Http_DeptStrGet(int n,unsigned char type);
int Http_DeptStrCNTGet(void);
void  Http_FpTemplateSet(FPINFO  *pData);
int HttpClient_Connecting(void);
void HttpClient_SetConnecting(unsigned char states);
BOOL  PingIp(unsigned char a,unsigned char b,unsigned char c,unsigned char d);

#endif 


