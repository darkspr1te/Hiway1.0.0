#include <setjmp.h> 
#include <time.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#if 0
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


#define TZNAME_LENGTH				16
#define ACCESS_TIME_SET_COUNT		50
#define ACCESS_USER_GROUP_COUNT		5
#define LOG_TZONE_COUNT				10
#define MULTI_IDENT_SET_COUNT		10

//only for highlevel timezone function
#define TIMEZONE_COUNT				32
#define TIMEGROUP_COUNT				32
#define TIMECOUNT_PER_TG			10
#define ACCESS_TIME_SET_COUNT_HIGH	32

#define BELL_INFO_COUNT				10
#define MSG_INFO_COUNT				10
#define MSG_LEN						60
#define EVENT_LENGTH				64

typedef struct _wiegand_type{
	unsigned char byOEM_len;	// length of OEM code
	unsigned char byFC_len;		// length of the machine no field
	unsigned char byCC_len;		// length of the ID field
	unsigned char byRes;		// reserved
	unsigned int  dwTpw;		// pulse width (micro second)
	unsigned int  dwTpi;		// pulse interval (micro second)
} WIEGAND_TYPE;

typedef struct _dbsetup_nomenu
{
	char	szCompanyNamy[32];		//32
	int		nReadMLogPos;			//4
	int		nReadALogPos;			//4
	DWORD	dwMechanical;			//4
	DWORD	dwExpose;				//4
	BOOL	bDisableDevice;			//1
	BYTE	byDoorStatus;			//1, 0:Off, 1:On, 2:Auto
	BOOL	bSummertimeUpdated;		//1
	BYTE	res[1];					//1
	WIEGAND_TYPE wiegand_type;		//12
} DBSETUP_NOMENU;					//Total = 64

typedef struct _dbsetup_system
{
	int		nTimeFormat;			//4
	int		nDateFormat;			//4
	int		nLanguage;				//4
	int		nVolume;				//4
	BOOL	bVoiceOut;				//1
	BOOL	bKeyTones;				//1
	BYTE	res[2];					//2
	int		nDaylightOffset;		//4
	DWORD	dwDaylightChangeTime;	//4
	DWORD	dwDaylightRestoreTime;	//4
	BYTE	byF1Status;				//1
	BYTE	byF2Status;				//1
	BYTE	byF3Status;				//1
	BYTE	byF4Status;				//1
	BYTE	byF5Status;				//1
	BYTE	byF6Status;				//1
	BYTE	byF7Status;				//1
	BYTE	byF8Status;				//1
	int		nIdletimeForPoweroff;	//4
	int		nIdletimeForSleep;		//4
	int		nIdletimeForLcdswitch;	//4
	DWORD	dwAutoPoweroffTime;		//4
	DWORD	dwAutoPoweronTime;		//4
	DWORD	dwAutoSleepTime;		//4
	BOOL	bPowerkeyLock;			//1
	BOOL	bRS232Use;				//1
	BOOL	bRS485Use;				//1
	BOOL	bUSBSlaveUse;			//1
	int		nMachineID;				//4
	int		nBaudrate;				//4
	DWORD	ipAddress;				//4
	DWORD	ipSubnetMask;			//4
	DWORD	ipDefaultGateway;		//4
	DWORD	ipPCBackground;			//4
	DWORD	dwCommPassword;			//4
	int		nMLogWarning;			//4
	int		nGLogWarning;			//4
	int		nReverifyTime;			//4
	int		nLockTime;				//4
	int		nDoorOpenTime;			//4
	int		nDoorSensorStatus;		//4
	int		nIllegalVerifyWarning;	//4
	int		nManagersNumber;		//4
	int		nVerifyMode;			//4
	DWORD	dwSManagerPwd;			//4
	BOOL	bDHCPUse;				//1
	BOOL	byAntipassStatus;		//1
	BOOL	bPwdAlarmUse;			//1
	BOOL	bSOSKeyUse;				//1
	int		nAlarmDelay;			//4
	int		nLockGroupMain;			//4
	DWORD	dwBindingID;			//4
	BOOL	bEthernetUse;			//1
	BYTE	byNetworkSpeed;			//1
	BYTE	byTheme;				//1
	BYTE	byWiegandFormat;		//1
	BYTE	byDefaultGVM;			//1
	BOOL	bCameraShow;			//1
	BOOL	bPhotoShow;				//1
	BOOL	bFPShow;				//1
	BOOL	bCameraSave;			//1
	BYTE	byCameraRateForFP;		//1
	BYTE	byCameraRateForCard;	//1
	BYTE	byCameraRateForPWD;		//1
	int     nBackgroupIconFile;         
	WORD    wPortNumBack;               
	CHAR	szHostByName[32];		    
	int		nRealSpaceTime;	
	CHAR	nHttpMachineID[20];
	
} DBSETUP_SYSTEM;					//Total = 164

typedef struct _db_timesection_a
{
	BYTE	bStartHour;				//1
	BYTE	bStartMinute;			//1
	BYTE	bEndHour;				//1, In the case of bell, bell-type
	BYTE	bEndMinute;				//1, In the case of bell, bell-length
}DB_TIMESECTION_A;					//Total = 4;

typedef struct _db_tz_normal
{
	WORD NAME[TZNAME_LENGTH];	//32
	DB_TIMESECTION_A RANGE;		//4
	DWORD STATUS;				//4
}DB_TZ_NORMAL;					//Total = 40;

typedef struct _db_tz_access
{
	DB_TIMESECTION_A RANGE[7];	//28
	DWORD STATUS;
}DB_TZACCESS;					//Total = 32

typedef struct _db_tzgroup
{
	BYTE	bGroupA;				//1
	BYTE	bGroupB;				//1
	BYTE	bGroupC;				//1
	BYTE	bGroupD;				//1(reserved)
}DB_TZGROUP_A;						//Total = 4

typedef DB_TZGROUP_A DB_TZGROUP[ACCESS_USER_GROUP_COUNT]; //4 * 5 = 20

typedef struct {
	WORD	SMSID;				// 2, message ID
	BYTE	Valid;				// 1, valid
	BYTE	Tag;				// 1, message type: 0-general, 1-user, 2-group
	WORD	Belong;				// 2, user or group ID or 0(general)
	WORD	ValidMinutes;		// 2, valid period
	DWORD	StartTime;			// 4, valid period
	char	Contents[MSG_LEN];	// 60,displayed message
} MSG_INFO;						// Total = 72

typedef struct 
{
	DB_TZ_NORMAL tzTr[LOG_TZONE_COUNT];			//40
	DB_TZ_NORMAL tzBell[BELL_INFO_COUNT];		//40
	DB_TZACCESS  tzAccess[ACCESS_TIME_SET_COUNT];//1600
	DB_TZGROUP   tzGroup;						//20
	BYTE		 tzLockGroup[MULTI_IDENT_SET_COUNT];//10
	BYTE		 tzGrupVM[ACCESS_USER_GROUP_COUNT];//5
	BYTE		 tzRes;							//1
	MSG_INFO	 tzMsg[MSG_INFO_COUNT];			//720
	//only for highlevel timezone function
	DB_TIMESECTION_A	tzHighTIME[TIMEZONE_COUNT];					//128
	BYTE				tzHighTG[TIMEGROUP_COUNT][TIMECOUNT_PER_TG];//320
	BYTE				tzHighAccess[ACCESS_TIME_SET_COUNT_HIGH][7];//224
}DBSETUP_TIMEZONE;								//Total = 3108

typedef struct 
{
	DWORD					dwCheckSum;	//4
	DBSETUP_NOMENU			setNoMenu;	//64
	DBSETUP_SYSTEM			setSystem;	//156
	DBSETUP_TIMEZONE		setTimezone;//3108
} DBSETUP_TOTAL;						//Total = 3332
#endif
DWORD gngethostbyname(char *HostName, int timeout);
extern BOOL DnsIpRead(void);
extern void DnsIpSet(DWORD ipPcBackground);
extern void ClearConfFile(void);
extern void UdhcpcInit(void);
void ClearConfFile(void);

