#ifndef __COM_H__
#define __COM_H__
//#loveywm 2013.02.22 ssss
#include "gui/MainWindow.h"
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
extern CMainWindow *g_MainWindow;



//////////////////////////////////
#include <QString> 
#include <vector> 
//#include <iostream> 
//#include <string> 
//using namespace std; 
QString s2q(const string &s); 
string q2s(const QString &s); 


//////////////////////////////////////////////////////////////////////////
#define COMM_DEF_TIMEOUT 5000

typedef enum
{
	COMM_MODE_NONE = -1,
	COMM_MODE_SERIAL,
	COMM_MODE_USB,
	COMM_MODE_TCP,
	COMM_MODE_UDP,
}T_COMM_MODE;

typedef enum
{
	DISABLE_MODE_NONE,
	DISABLE_MODE_UART0,
	DISABLE_MODE_UART1,
	DISABLE_MODE_UART2,
	DISABLE_MODE_USB,
	DISABLE_MODE_TCP,
	DISABLE_MODE_UDP,
}T_DISABLE_MODE;

/************************************************************************/
/*                                                                      */
/************************************************************************/
enum
{
	CMD_INTERNAL_CHECK_LIVE = 0x51,
	CMD_INTERNAL_CHECK_PWD
};

enum
{
	CMD_GET_ALLID = 0x801,
	CMD_GET_ONEID,
	CMD_GET_UINFO,
	CMD_SET_UINFO,
	CMD_GET_LOG_COUNT,
	CMD_GET_SLOG,
	CMD_GET_GLOG,
	CMD_GET_DEVICE_STATUS,
	CMD_GET_DEVICE_INFO,
	CMD_SET_DEVICE_INFO,
	CMD_GET_DATA_FILE,
	CMD_SET_DATA_FILE,
	CMD_ENABLE_DEVICE,
	CMD_POWER_CONTROL,
	CMD_EMPTY_DATA,
	CMD_FW_UPGRADE,
	CMD_GET_PHOTOLIST,
	
	CMD_GET_DATA_FILE_WS = 0x201,	//for web server
	CMD_SET_DATA_FILE_WS,
	CMD_FW_UPGRADE_WS,
};

enum
{
	CMD_DOWN_DOWNLOADER_WRITE = 0x501,
	CMD_DOWN_RESTART,
	CMD_DOWN_INIT_GET,
	CMD_DOWN_INIT_SET,
	CMD_DOWN_KERNEL_WRITE,
	CMD_DOWN_ROOTFS_WRITE,
	CMD_DOWN_ROMWRITE,
	CMD_DOWN_FLASHINIT,
	CMD_DOWN_BOOTSPLASH,
	CMD_TEST_BIG_ENROLL,
	CMD_TEST_BIG_SLOG,
	CMD_TEST_BIG_GLOG,
	CMD_TEST_GET_IMAGE_TRIGGER,
	CMD_TEST_GET_IMAGE_ORG,
	CMD_TEST_GET_IMAGE,
};

enum
{
	CMD_ANTIPASS_SEND = 0x701,
};


//////////////////////////////////////////////////////////////////////////
BOOL comm_tcpserver_init(void);
void comm_tcpserver_close(void);
void comm_tcpclient_accept(void);
void comm_tcpclient_close(HFILE hSock);
BOOL comm_tcpcheck_close(HFILE hSock);
BOOL comm_send_event(int nEvent, void *data, int len);
BOOL comm_tcpclient_connect(void);     

BYTE hcProcMain(void);
BOOL Com_AntipassSend(int nVerifyMode, void *pTemplate, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber);

BOOL comm_send_data(void* pbuf, int nsize);  
int comm_uartsend(int iUART, void *pBuffer, int len); 
/************************************************************************/
/* Arm.app Communication Command Enumeration                              */
/************************************************************************/

typedef struct
{
	WORD	wId;
	BYTE	byMgr;
	WORD	wPwd;
} PASSWORD_DATA;

typedef struct
{
	WORD	wId;
	BYTE	byMgr;
	DWORD	dwData;
} CARD_DATA;

#define CMD_ANS_ACK			1
#define CMD_ANS_NAK			0

#define EXE_RES_TRUE		1
#define EXE_RES_FALSE		0

#define CMDSIZE	        16
#define ACKSIZE	        8
#define EXERETSIZE	    14

enum
{
	DATA_TYPE_FP = 1,
	DATA_TYPE_PWD,
	DATA_TYPE_CARD,
	DATA_TYPE_FP_ALL,
	DATA_TYPE_ALL
};

typedef struct {
	BYTE 	Head1;		// 55=STX1
	BYTE 	Head2;		// AA=STX2
	WORD    MachineID;
	WORD    Reserved;
	WORD 	Command;
	DWORD	Length;		//SettingValue
	WORD	InParam;
	WORD 	ChkSum;
} CMDPKT;               // 14BYTE  

typedef struct {
	BYTE 	Head1;		// 5A=STX1
	BYTE 	Head2;		// A5=STX2
	WORD    MachineID;
	WORD	Response;
	WORD 	ChkSum;
} ACKPKT;               // 8Byte  


typedef struct UserDataPak{
	int UserExist; //用户是否存在
	UINT64 dwEnrollNumber; //用户id
	DWORD dwBackupNumber; //用户id
	DWORD dwPrivilege;
	DWORD dwVerifymode;
	BYTE UserName[24]; //用户姓名
	union{
		BYTE FingerData[1404+12]; //用户指纹模板
		DWORD Password;
		DWORD CardID;
	};
	
}st_UserData;

typedef struct UserIDInfo
	{
		UINT64 EnrollNumber; 
		DWORD BackupNumber;
		DWORD Privilege;
		DWORD VerifyMode;
	} mUserIDInfo;

typedef struct {
	DWORD Index;    //最大支持2位数。
	char Letter[16]; //字母	
}st_HeadString;

typedef struct {
	UINT64 nID; 
	DWORD nFP;
	DWORD Avail;
}st_FpUploadData;


#define MaxIdHeadListCount  99

//Response = 0x02  (NAK)
//           0x03  (ACK)

typedef struct {
	BYTE 	Head1;		// AA=STX1
	BYTE 	Head2;		// 55=STX2
	WORD    MachineID;
	WORD    Reserved;
	WORD	Ret;		// 1: OK 0: Error
	DWORD	OutParam;	// Result or ErrorCode
	WORD 	ChkSum;
} RESULTPKT;            // 12Byte

typedef struct 
{
	unsigned int	ID;
	unsigned char	EMachineNumber;
	unsigned char	BackupNumber;
	unsigned char	MachinePrivilege;
	unsigned char	Enable;
} EnrollUserID;

typedef struct
{
	DWORD	dwSeconds;
	DWORD	wSid;
	DWORD	wId;
	BYTE	bySubid;
	BYTE	byAction;
} ARM_MLOG_INFO;

typedef struct
{
	DWORD	dwSeconds;
	DWORD	wId;
	BYTE	byAction;
} ARM_ALOG_INFO;

enum
{
	ARM_CMD_INTERNAL_CHECK_LIVE = 0x51,
	ARM_CMD_INTERNAL_CHECK_PWD
};

enum
{
	ARM_CMD_GET_OCX_KEY = 0x100,
	ARM_CMD_GET_ENROLL_DATA = 0x101,//i need it
	ARM_CMD_SET_ENROLL_DATA,//i need it
	ARM_CMD_DELETE_ENROLL_DATA,
	ARM_CMD_SLOG_GET_COUNT,
	ARM_CMD_SLOG_GET,
	ARM_CMD_GLOG_GET_COUNT,
	ARM_CMD_GLOG_GET,
	ARM_CMD_DEVICE_STATUS_GET,
	ARM_CMD_DEVICE_INFO_GET,
	ARM_CMD_DEVICE_INFO_SET,
	ARM_CMD_DISABLE_DEVICE,
	ARM_CMD_ENABLE_DEVICE,
	ARM_CMD_ENABLE_USER,
	ARM_CMD_DEVICE_TIME_GET,
	ARM_CMD_DEVICE_TIME_SET,
	ARM_CMD_POWER_OFF,
	ARM_CMD_MODIFY_PRIVILIGE,//i need it
	ARM_CMD_READ_ALL_USERID,//i need it
	ARM_CMD_SERIAL_NUM_GET,
	ARM_CMD_CLEAR_KEEPER_DATA,//i need it
	ARM_CMD_BACKUP_NUM_GET,
	ARM_CMD_PRODUCT_CODE_GET,
	ARM_CMD_ENROLL_DATA_EMPTY,
	ARM_CMD_GLOG_EMPTY,//i need it
	ARM_CMD_SLOG_EMPTY,//i need it
	ARM_CMD_USER_NAME_GET,
	ARM_CMD_USER_NAME_SET,
	ARM_CMD_COMPANY_NAME_GET,
	ARM_CMD_COMPANY_NAME_SET,
	ARM_CMD_DOOR_STATUS_GET,
	ARM_CMD_DOOR_STATUS_SET,
	ARM_CMD_BELLTIME_GET,
	ARM_CMD_BELLTIME_SET,
	//xfu 
	ARM_CMD_BACKUP_SERIAL_NUM_GET,
	//xfu  2007-04-29
	ARM_CMD_GBK_SET,				
	//add by cjuan 5-9
	ARM_CMD_VALID_PERIOD_SET,     
	ARM_CMD_HOLIDAY_SET,          
	ARM_CMD_PERIOD_SET,           
	ARM_CMD_USER_PERIOD_SET,      
	ARM_CMD_VALID_PERIOD_GET,     
	ARM_CMD_HOLIDAY_GET,          
	ARM_CMD_PERIOD_GET,           
	ARM_CMD_USER_PERIOD_GET,      
	ARM_CMD_USER_PERIOD_DELETE,   
	ARM_CMD_DOOR_DELAY_SET,       
	ARM_CMD_LOCK_TYPE_SET,        
	ARM_CMD_OPEN_OVERTIME_SET,    
	ARM_CMD_ILLEGAL_OPEN_TIME_SET,
	ARM_CMD_DOOR_RSTATUS_GET,	
	//lt 2007-10-16
	ARM_CMD_USER_GET_COUNT,       
	ARM_CMD_USER_GET,             
	ARM_CMD_GET_USER_DATA ,       
	ARM_CMD_SET_USER_DATA,        
	ARM_CMD_USER_NAME_GET_FOR,   
	ARM_CMD_USER_NAME_SET_FOR,
	ARM_CMD_GLOG_GET_BYTIME,
	ARM_CMD_SLOG_GET_BYTIME,
	ARM_CMD_GET_ENROLLNUMBER_HEAD_LIST,
	ARM_CMD_SET_ENROLLNUMBER_HEAD_LIST,
	//xf 2011-12-13
	ARM_CMD_IP_SET,
	ARM_CMD_GLOG_GET_BYTIME_ALLSEARCH,

};

enum
{
	ARM_CMD_SYSTEMNO_CHECK = 0x401,				
	ARM_CMD_SET_HOST_BY_NAME,                  
	ARM_CMD_GET_HOST_BY_NAME,                   
	ARM_CMD_REALTIME_LOG,  
	ARM_CMD_REALTIME_HEART,
	ARM_CMD_REALTIME_SLOG, 
	ARM_CMD_HTTP_ROMUPDATE, //HYM
};

enum
{
	ARM_CMD_PASS_TIME_SET = 0x601,
	ARM_CMD_PASS_TIME_GET,
	ARM_CMD_GROUP_SET,
	ARM_CMD_GROUP_GET,
	ARM_CMD_TIME_ZONE_SET,
	ARM_CMD_TIME_ZONE_GET,
	ARM_CMD_USER_CTRL_SET,
	ARM_CMD_USER_CTRL_GET,
	ARM_CMD_DOOR_KEY_SET,
	ARM_CMD_DOOR_KEY_GET,
	ARM_CMD_LOG_WATCH,
//	ARM_CMD_LOGTIME_SET,
//	ARM_CMD_LOGTIME_GET,
// 	ARM_CMD_LOCKGROUP_SET,
// 	ARM_CMD_LOCKGROUP_GET,
};

enum
{
	ARM_CMD_SB_FIRMWARE_WRITE = 0x501,
	ARM_CMD_SB_INIT_GET,
	ARM_CMD_SB_INIT_SET,
	ARM_CMD_SB_BIG_ENROLL,
	ARM_CMD_SB_BIG_SLOG,
	ARM_CMD_SB_BIG_GLOG,
	ARM_CMD_SB_ENROLL_ONE_FILE,
	ARM_CMD_SB_GET_IMAGE_TRIGGER,
	ARM_CMD_SB_GET_IMAGE_ORG,
	ARM_CMD_SB_GET_IMAGE,
	ARM_CMD_SB_SET_IMAGE,
	ARM_CMD_SB_ENROLL_ONE_IMAGE,
	ARM_CMD_SB_IDENTIFY_ONE_IMAGE
};

BOOL	ComGetEnrollDataFP ( CMDPKT* pCMD );
BOOL	ComGetEnrollDataPWD ( CMDPKT* pCMD );
BOOL	ComGetEnrollDataCARD ( CMDPKT* pCMD );

BOOL	ComSetEnrollDataFP( CMDPKT* pCMD );
BOOL	ComSetEnrollDataPWD ( CMDPKT* pCMD );
BOOL	ComSetEnrollDataCARD ( CMDPKT* pCMD );

BOOL	ComDeleteEnrollDataFP ( CMDPKT* pCMD );
BOOL	ComDeleteEnrollDataPWD ( CMDPKT* pCMD );
BOOL	ComDeleteEnrollDataCARD ( CMDPKT* pCMD );
BOOL	ComDeleteEnrollDataAllFP ( CMDPKT* pCMD );
BOOL	ComDeleteEnrollDataAll ( CMDPKT* pCMD );

BOOL	ComReadAllUserID(CMDPKT *vCMD);

BOOL	ComSlogGetCount(void);
BOOL	ComSlogGet ( CMDPKT* pCMD );
BOOL	ComGlogGetCount(void);
BOOL	ComGlogGet ( CMDPKT* pCMD );

BOOL	ComEnrollDataEmpty(void);
BOOL	ComGlogEmpty(void);
BOOL	ComSlogEmpty(void);

BOOL	ComDeviceStatusGet(CMDPKT *vCMD);
BOOL	ComDeviceInfoGet(CMDPKT *vCMD);
BOOL	ComDeviceInfoSet(CMDPKT *vCMD);

BOOL	ComEnableUser(CMDPKT *vCMD);
BOOL	ComDeviceTimeGetSet ( CMDPKT* pCMD );
BOOL	ComPowerOff(void);
BOOL	ComModifyPrivilege(CMDPKT *vCMD);
BOOL	ComSerialNumGet(void);
BOOL	ComClearKeeperData(void);
BOOL	ComPassSerialNumGet(void);
BOOL	ComBackupNumGet(void);
BOOL	ComProductCodeGet(void);
BOOL	ComUserNameGet(CMDPKT *vCMD);
BOOL	ComUserNameSet(void);
BOOL	ComCompanyNameGet(void);
BOOL	ComCompanyNameSet(void);
BOOL	ComDoorStatusGet(void);
BOOL	ComDoorStatusSet(CMDPKT *vCMD);
 BOOL	ComBellTimeGet(void);
// BOOL	ComLcdSet(CMDPKT *vCMD);
 BOOL	ComBellTimeSet(void);
 BOOL ComSystemCheck(CMDPKT *vCMD);       
BOOL	ComInternalCheckPwd(CMDPKT *vCMD);



BOOL	Com_MakePacket(BYTE* pFpData, int nSize);
DWORD	Com_MakeCheckSum(DWORD* pdwBuf, int nSize);
BOOL	Com_MakeFpData(void);
int		Com_SendBigData(void* pData, DWORD dwSize );
int		Com_RecBigData(void* pData, DWORD dwSize );

BOOL ComPassTimeSet(void);
BOOL ComPassTimeGet(void);
BOOL ComGroupSet(void);
BOOL ComGroupGet(void);
// BOOL ComLockGroupSet(void);
// BOOL ComLockGroupGet(void);
BOOL ComTimeZoneSet(void);
BOOL ComTimeZoneGet(void);
BOOL ComUserCtrlSet(void);
BOOL ComUserCtrlGet(CMDPKT* pCMD);
BOOL ComDoorKeyParamSet(void);
BOOL ComDoorKeyParamGet(void);
BOOL ComLogWatchGet(CMDPKT* pCMD);

int  ComClientGetVerifydata(UINT64 ID);
BOOL ComClientSendCardPasswordData(UINT64 ID ,int card ,BOOL iscard);
BOOL ComClientSendFingerData(UINT64 ID ,int nFP,BYTE* pData);
BOOL ComClientSendFingerImage(UINT64 ID, int nFP, void* pData);
BOOL ComClientGetName(UINT64 ID ,WORD *Name,int len);
BOOL  Com_VerifyLoop(UINT64	nID);

void  tcpclient_connect_start(void);
void  tcpclient_connect_Creatthread(void);
BOOL  tcpclient_connect_isok(void);
void  tcpclient_connect_threadStop(void);
void DM9000_Reset(void);
BOOL Net_LinkIsOk(void);
void DM9000_Check(void);


BOOL ComSlogGetByTime ( CMDPKT* pCMD );
BOOL ComGlogGetByTime ( CMDPKT* pCMD );

char* UserId_BCDtoSTR(UINT64 nID);
UINT64 UserId_STRtoBCD(char* strID);
BOOL ComEnrollNumberHeadListGet ( CMDPKT* pCMD );
BOOL ComEnrollNumberHeadListSet ( CMDPKT* pCMD );
BOOL UserId_isOk(void);
BOOL ComClientFpDataUpLoad ( void );
BOOL HttpRomWrite(string word);
BOOL HttpGetRomFileName(CMDPKT* pCMD);
DWORD	DbGLogCountGetByTimeAllSearch( int fromsecond, int tosecond);


extern void DispDeviceState(void);


/*
*	下面是为web2.0协议增加的命令和数据结构与相关函数
*	的声明。
*/

#define SEND_CONNECT_SIZE  (sizeof(PACK_HEAD)+sizeof(st_connectInfo)+4)//建立连接时发送字长
#define 	SEND_HEAD 	0x1a2b3c4d      //主动发送标志	
#define	RECV_HEAD	0x4d3c2b1a	//接受成功后返回标志
#define    PACK_HEAD_SIZE	(sizeof(PACK_HEAD))//头文件的大小
#define CMD_WEB_ACK			1
#define CMD_WEB_NAK			0
#define 	CMDWEBSIZE	        24//第一次只接受数据头的24个字节


//命令字的枚举声明
enum{

	CMD_CONNECT = 0x01,                  		//连接命令
	CMD_REALTIME_LOG,					//主动上传记录
	CMD_UPLOAD_FINGER,					//上传指纹
	CMD_GET_LOG,						//PC获取记录
	CMD_GET_USER_REG,					//PC获取用户注册信息
	CMD_SET_USER_REG,					//PC下发用户注册信息
	CMD_DEL_USER_REG,					//PC用户删除
	CMD_MOD_PRVILEGE,					//PC下发权限设置
	CMD_GET_ALL_USERID,					//PC 获取用户列表
	CMD_DEL_DATA,						//PC 删除数据记录
	CMD_UPGRADE_ADDR,					//PC 下发升级地址
	CMD_SET_TIME,                  				//PC 设置时间
	CMD_GET_TIME,						//PC获取时间	
	//门禁功能
	CMD_GET_PASSTIME,						//PC 获取门禁PASSTIME
	CMD_SET_PASSTIME,						//PC 设置门禁PASSTIME
	CMD_GET_GROUPTIME,					//PC 获取门禁GROUPTIME
	CMD_SET_GROUPTIME,					//PC 获取门禁GROUPTIME
	CMD_GET_USERCTRL,						//PC 获取用户控制
	CMD_SET_USERCTRL,						//PC 设置用户控制
	CMD_GET_DOOR_KEY,						//PC 获取门禁控制参数
	CMD_SET_DOOR_KEY,						//PC 设置门禁控制参数
	CMD_GET_SOFTKEY,						//PC 获取快捷键
	CMD_SET_SOFTKEY,						//PC 设置快捷键
	CMD_GET_DEVICE_STATUS1,				//PC 获取设备状态
	CMD_GET_DOOR_STATE,					//PC 获取门状态
	CMD_SET_DOOR_STATE	,				//PC 设置门状态
	CMD_GET_BELL,							//PC 获取电铃
	CMD_SET_BELL,							//PC 设置电铃
	CMD_GET_TASK_TIME_RANGE,				//PC 获取定时任务时间范围
	CMD_SET_TASK_TIME_RANGE,				//PC 设置定时任务时间范围
	CMD_GET_TASK_DAY,						//PC 获取定时任务日期
	CMD_SET_TASK_DAY,						//PC 设置定时任务日期
	CMD_GET_TASK_WEEK,					//PC 获取定时任务星期
	CMD_SET_TASK_WEEK,					//PC 设置定时任务星期
	CMD_GET_DEVICE_INFO1,					//PC 获取设备信息
	CMD_SET_DEVICE_INFO1	,				//PC 设置设备信息

	//下面是我需要的设置
	CMD_SET_MAC,							//设置MAC地址

};

//错误码标志
enum{
		ERROR_OK,
		DEL_ALL_DATA_ERROR,	
		DEL_GLOG_DATA_ERROR,
		DEL_SLOG_DATA_ERROR,
		NO_USER_ERROR,
		MOD_PRVILEGE_ERROR,
		DEL_USER_REG_ERROR,
		BACKNUMBER_ID_ERROR,
		ENRALL_PASSWD_ERROR,
		ENRALL_CARD_ERROR,
		ENRALL_PP_ERROR,
};



//协议包头
typedef struct 
{
	u32		Head;
	u32		Cmd;
	u32		Cmd_Serial;
	u32		Cmd_Step;
	u32		DeviceID;
	u32		Datalen;
}PACK_HEAD;				//24byte

//CMD_CONNECT命令字的数据包
typedef	struct ConnectInfo
{
	u8		mVersion[32];//版本号
	u32		DeviceId;//设备唯一号
	union{
			u8		mReserved[32];
			struct DeviceConnectInfo
			{
				u32 ip;
				u32 sm;
				u32 gw;
				u8  dhcp;
				u8  MAC[6];
			}loveywm;
		}xxx;
}st_connectInfo;

//修改权限需要的数据结构
typedef struct UserPrvilege
{
	u64  	UserID;
	u32		Prvilege;  //0：普通 1:超级管理员 2:注册管理员 
}st_UserPrvilege;

//获取和下发用户注册信息的数据结构
typedef struct GetUser
{
	u64 	UserID;
	int 	BackupNumber;
}st_GetUser;//12

typedef struct UserInfo
{
	u64	UserID;
	u32	BackupNumber;
	u32	Card;
	u32	Password;
	u32  Privilege;
	char 	UserName[24];
}st_UserInfo;  //8+4+4+4+4+24=48

//获取用户ID数据结构
typedef struct UserID
{
	u64 	UserID;
	u16	BackupNumber;
	u16	Prvilege;
	u8    name[24];
}st_UserID;

//pc获取记录数据结构
typedef struct GetGLogCondition
{
	u64	UserID;
	u32	BeginDatetime;
	u32	EndDatetime;
	u64	Index;
}st_GetGLogCondition;//24

typedef struct GetGLogConditionEx
{
	u64 	BeginIndex;
	u64	EndIndex;
}st_GetGLogConditionEx;//16

//记录结构
typedef struct GLog
{
	u64	UserID;
	u32	Datetime;
	u16	VerifyMode;
	u16  Event;
	u32  Index;
}st_GLog;

//指纹结构
typedef struct FingerData
{
	u64	UserID;
	u32	BackupNumber;
	u32  priege;
	u8	data[1404];
}st_FingerData;



void make_connect(void);
BOOL web2_get_cmd(HFILE hSock, PACK_HEAD* pvCMD);
int comm_socksend(HFILE hSock, void *pBuffer, int len);
u8 web2_run_cmd(HFILE hSock, PACK_HEAD* vCMD);
void web2_send_ack(u8 oksign,u8 errorsign,PACK_HEAD* vCMD);
u8 web2_cmd_connect( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_set_mac(PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_get_time( PACK_HEAD* vCMD);
u8 web2_cmd_set_time( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_upgrade_addr( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_del_data( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_get_all_userid( PACK_HEAD* vCMD);
u8 web2_cmd_mod_prvilege( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_del_user_reg( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_set_user_reg( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_get_user_reg( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_cmd_get_log( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_glog_get_byall( PACK_HEAD* vCMD);
u8 web2_glog_get_bytime(PACK_HEAD* vCMD, GetGLogCondition *pCMD);
u8 web2_glog_get_byindex(PACK_HEAD* vCMD, GetGLogConditionEx *pCMD);
u8 web2_realtime_log( PACK_HEAD* vCMD,u8 *recvdata);
u8 web2_upload_finger( PACK_HEAD* vCMD,u8 *recvdata);

u8 web2_send_finger(u64 ID,int backupnumber,u32 prilege,u8 *pdata);
u8 web2_send_glog(ALOG_INFO *pLogData);
u8 web2_send_data(PACK_HEAD* vCMD,void *data,u32 datalen);
void web2_make_packhead(PACK_HEAD *packhead,u32 datalen,PACK_HEAD* vCMD);

//用于发送后就等待接受的函数，而不是在大循环中
//去等待接受，减少发送冲突
u8 web2_recv_data(int timeout);//时间单位是ms
void ks(u8 *sendbuf,int buflen);
void ks_f(u8 *sendbuf,int buflen);

///////////////////////////////////////////////////////////////
//下面是http的东西
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



 
u8 http_time_set(char *pdatabuf);
u8 http_updata_firmware(char *pdatabuf);
u8 http_down_reg(char *pdatabuf);
u8 http_down_name(char *pdatabuf);
char *Http_DeptStrGet(int n,unsigned char type);
int Http_DeptStrCNTGet(void);

BOOL HttpRomWrite1(string word);

int comm_socksend(HFILE hSock, void *pBuffer, int len);



#endif /*__COM_H__*/
