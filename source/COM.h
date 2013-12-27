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
	int UserExist; //�û��Ƿ����
	UINT64 dwEnrollNumber; //�û�id
	DWORD dwBackupNumber; //�û�id
	DWORD dwPrivilege;
	DWORD dwVerifymode;
	BYTE UserName[24]; //�û�����
	union{
		BYTE FingerData[1404+12]; //�û�ָ��ģ��
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
	DWORD Index;    //���֧��2λ����
	char Letter[16]; //��ĸ	
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
*	������Ϊweb2.0Э�����ӵ���������ݽṹ����غ���
*	��������
*/

#define SEND_CONNECT_SIZE  (sizeof(PACK_HEAD)+sizeof(st_connectInfo)+4)//��������ʱ�����ֳ�
#define 	SEND_HEAD 	0x1a2b3c4d      //�������ͱ�־	
#define	RECV_HEAD	0x4d3c2b1a	//���ܳɹ��󷵻ر�־
#define    PACK_HEAD_SIZE	(sizeof(PACK_HEAD))//ͷ�ļ��Ĵ�С
#define CMD_WEB_ACK			1
#define CMD_WEB_NAK			0
#define 	CMDWEBSIZE	        24//��һ��ֻ��������ͷ��24���ֽ�


//�����ֵ�ö������
enum{

	CMD_CONNECT = 0x01,                  		//��������
	CMD_REALTIME_LOG,					//�����ϴ���¼
	CMD_UPLOAD_FINGER,					//�ϴ�ָ��
	CMD_GET_LOG,						//PC��ȡ��¼
	CMD_GET_USER_REG,					//PC��ȡ�û�ע����Ϣ
	CMD_SET_USER_REG,					//PC�·��û�ע����Ϣ
	CMD_DEL_USER_REG,					//PC�û�ɾ��
	CMD_MOD_PRVILEGE,					//PC�·�Ȩ������
	CMD_GET_ALL_USERID,					//PC ��ȡ�û��б�
	CMD_DEL_DATA,						//PC ɾ�����ݼ�¼
	CMD_UPGRADE_ADDR,					//PC �·�������ַ
	CMD_SET_TIME,                  				//PC ����ʱ��
	CMD_GET_TIME,						//PC��ȡʱ��	
	//�Ž�����
	CMD_GET_PASSTIME,						//PC ��ȡ�Ž�PASSTIME
	CMD_SET_PASSTIME,						//PC �����Ž�PASSTIME
	CMD_GET_GROUPTIME,					//PC ��ȡ�Ž�GROUPTIME
	CMD_SET_GROUPTIME,					//PC ��ȡ�Ž�GROUPTIME
	CMD_GET_USERCTRL,						//PC ��ȡ�û�����
	CMD_SET_USERCTRL,						//PC �����û�����
	CMD_GET_DOOR_KEY,						//PC ��ȡ�Ž����Ʋ���
	CMD_SET_DOOR_KEY,						//PC �����Ž����Ʋ���
	CMD_GET_SOFTKEY,						//PC ��ȡ��ݼ�
	CMD_SET_SOFTKEY,						//PC ���ÿ�ݼ�
	CMD_GET_DEVICE_STATUS1,				//PC ��ȡ�豸״̬
	CMD_GET_DOOR_STATE,					//PC ��ȡ��״̬
	CMD_SET_DOOR_STATE	,				//PC ������״̬
	CMD_GET_BELL,							//PC ��ȡ����
	CMD_SET_BELL,							//PC ���õ���
	CMD_GET_TASK_TIME_RANGE,				//PC ��ȡ��ʱ����ʱ�䷶Χ
	CMD_SET_TASK_TIME_RANGE,				//PC ���ö�ʱ����ʱ�䷶Χ
	CMD_GET_TASK_DAY,						//PC ��ȡ��ʱ��������
	CMD_SET_TASK_DAY,						//PC ���ö�ʱ��������
	CMD_GET_TASK_WEEK,					//PC ��ȡ��ʱ��������
	CMD_SET_TASK_WEEK,					//PC ���ö�ʱ��������
	CMD_GET_DEVICE_INFO1,					//PC ��ȡ�豸��Ϣ
	CMD_SET_DEVICE_INFO1	,				//PC �����豸��Ϣ

	//����������Ҫ������
	CMD_SET_MAC,							//����MAC��ַ

};

//�������־
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



//Э���ͷ
typedef struct 
{
	u32		Head;
	u32		Cmd;
	u32		Cmd_Serial;
	u32		Cmd_Step;
	u32		DeviceID;
	u32		Datalen;
}PACK_HEAD;				//24byte

//CMD_CONNECT�����ֵ����ݰ�
typedef	struct ConnectInfo
{
	u8		mVersion[32];//�汾��
	u32		DeviceId;//�豸Ψһ��
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

//�޸�Ȩ����Ҫ�����ݽṹ
typedef struct UserPrvilege
{
	u64  	UserID;
	u32		Prvilege;  //0����ͨ 1:��������Ա 2:ע�����Ա 
}st_UserPrvilege;

//��ȡ���·��û�ע����Ϣ�����ݽṹ
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

//��ȡ�û�ID���ݽṹ
typedef struct UserID
{
	u64 	UserID;
	u16	BackupNumber;
	u16	Prvilege;
	u8    name[24];
}st_UserID;

//pc��ȡ��¼���ݽṹ
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

//��¼�ṹ
typedef struct GLog
{
	u64	UserID;
	u32	Datetime;
	u16	VerifyMode;
	u16  Event;
	u32  Index;
}st_GLog;

//ָ�ƽṹ
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

//���ڷ��ͺ�͵ȴ����ܵĺ������������ڴ�ѭ����
//ȥ�ȴ����ܣ����ٷ��ͳ�ͻ
u8 web2_recv_data(int timeout);//ʱ�䵥λ��ms
void ks(u8 *sendbuf,int buflen);
void ks_f(u8 *sendbuf,int buflen);

///////////////////////////////////////////////////////////////
//������http�Ķ���
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
