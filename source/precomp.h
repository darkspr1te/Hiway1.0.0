#ifndef __PRECOMP_H__
#define __PRECOMP_H__
#include <QtCore/QTextCodec>

//////////////////////////////////////////////////////////////////////////
typedef int						HFILE;

typedef char					CHAR;
typedef short					SHORT;
typedef int						INT;

typedef unsigned char			BYTE, u8, uchar;
typedef unsigned char			BOOL;
typedef unsigned short			WORD, UINT16,u16;
typedef unsigned int			DWORD, UINT32, u32;
typedef long					LONG;
typedef unsigned long long		UINT64, u64;

typedef unsigned short			WPARAM;
typedef unsigned long			LPARAM;

typedef enum
{
	CTRL_TEXTBOX,
	CTRL_COMBOBOX,
	CTRL_CHECKBOX,
	CTRL_PUSHBUTTON,
	CTRL_DIALOG,
	CTRL_NONE
}T_CTRL_TYPE;

//////////////////////////////////////////////////////////////////////////
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

//////////////////////////////////////////////////////////////////////////
#define MAX(_a_, _b_)			((_a_) > (_b_) ? (_a_) : (_b_))
#define MIN(_a_, _b_)			((_a_) < (_b_) ? (_a_) : (_b_))
#define MAKEWORD(a, b)			((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)			((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)				((WORD)(l))
#define HIWORD(l)				((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)				((BYTE)(w))
#define HIBYTE(w)				((BYTE)(((WORD)(w) >> 8) & 0xFF))
#define PACKED					__attribute__((packed))
#define STR2ASCII(_str_)		((_str_).toAscii().data())

#define UI_IP_MAKE(a,b,c,d) (((a)<<24) | ((b)<<16) | ((c)<<8) | (d))
#define UI_IP_UNMAKE(ip, a,b,c,d) { (a)=((ip)>>24)&0xFF; (b)=((ip)>>16)&0xFF; (c)=((ip)>>8)&0xFF; (d)=(ip)&0xFF; }

#define POST_EVENTS()			{QApplication::processEvents(); ioctl(g_hTftLcd, FBIOBLANK, FBINFO_ROTATE);}
#define ITEM_CNT(_x_)			(sizeof((_x_)) / sizeof((_x_)[0]))
#define WAIT_EVENT(_e_)			{while((_e_)) { POST_EVENTS(); }}

#define FD_CLOSE(_fd_)	{if ((_fd_) != INVALID_HANDLE_VALUE) close((_fd_)); (_fd_) = INVALID_HANDLE_VALUE;}
#define FREE(_p_)		{if ((_p_) != NULL) free((_p_)); (_p_) = NULL;}
#define DELETE(_p_)		{if ((_p_) != NULL) delete((_p_)); (_p_) = NULL;}

#define WM_USER					(QEvent::User)
#define WM_T9INPUT				((QEvent::Type)(WM_USER + 1))

#define FP_GET_NEXTPOS(_f_)		LOWORD(((FPINFO*)(_f_))->lParam)
#define FP_SET_NEXTPOS(_f_,_v_)	(((FPINFO*)(_f_))->lParam = MAKELONG((_v_), HIWORD(((FPINFO*)(_f_))->lParam)))
#define FP_GET_UIPOS(_f_)		HIWORD(((FPINFO*)(_f_))->lParam)
#define FP_SET_UIPOS(_f_,_v_)	(((FPINFO*)(_f_))->lParam = MAKELONG(LOWORD(((FPINFO*)(_f_))->lParam), (_v_)))

#define WM_USER					(QEvent::User)
#define WM_T9INPUT				((QEvent::Type)(WM_USER + 1))

#define TIMER_RTCCLOCK			0x1001
#define TIMER_LED_ON			0x1002
#define TIMER_MANAGERREQUEST	0x1003
#define TIMER_DATETIME_SETUP	0x1004
#define TIMER_ALARM				0x1005
#define TIMER_SYSMONITOR		0x1006
#define TIMER_SMSG				0x1007
#define TIMER_ACCACHE_FLUSH		0x1008
#define TIMER_DURESS_ALARM		0x1009
#define TIMER_SOSKEY_RELEASE	0x100A
#define TIMER_KEYPAD_BACKGROUND	0x100B
#define TIMER_LOCK_RESTORE		0x100C
#define TIMER_LOGOUT_ALARM		0x100D

#define SETUP_TIMER(_timerid_, _timeout_, _param_, _callback_)	{if (g_MainWindow) g_MainWindow->SetTimer((_timerid_), (_timeout_), (_param_), (_callback_));}
#define STOP_TIMER(_timerid_)	{if (g_MainWindow) g_MainWindow->StopTimer((_timerid_));}

#define PERF_CHECK(_X_)		//_X_

#define G2U(s) ( QTextCodec::codecForName("GBK")->toUnicode(s) )
#define U2G(s) ( QTextCodec::codecForName("GBK")->fromUnicode(s) )


//////////////////////////////////////////////////////////////////////////
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
//hiway add
#include<linux/input.h>//按键输出


#include <QtCore/QString>
#include <QtGui/QApplication>
#include <QtGui/QRgb>
#include <QtGui/QPainter>
#include <QtGui/QLabel>
#include <QtGui/QColor>

#include "../include/s3c2410addr.h"
#include "../include/rtc.h"
#include "../include/ownrtc.h"
#include "../include/portctl.h"
#include "../include/buzzer.h"
#include "../include/keyboard.h"
#include "../include/monochrome.h"
#include "../include/wdog.h"

#include "SB3000LIB.h"
#include "md5_hash.h"
#include "_fp.h"
#include "uiFont.h"
#include "uiLcd.h"
#include "Database.h"
#include "uiWrap.h"
// #include "uiProcs.h"
#include "COM.h"
#include "Wiegand.h"
#include "Lock.h"
#include "camera/spcav4l.h"
//#include "mp3/mp3_main.h"
#include "./http_client/http_main.h"


#define DEVID		(dbComm_machineID)

//////////////////////////////////////////////////////////////////////////
typedef struct _ctrl_item
{
	DWORD dwID;
	T_CTRL_TYPE ctrlType;
	struct _ctrl_item *next;
}T_CTRL_ITEM;

typedef struct _proc_status
{
	BOOL	bReqManager;
	BOOL	bMenuRequested;
	BOOL	bMenuProcessing;
	BOOL	bVerifying;
	DWORD	dwReqManagerTime;
	BOOL	bManagerVerifyOK;
	UINT64	nIDCurrentMgr;
	BYTE	byMgr;
	int		nTrType;
	int		nVerifyFail;
	DWORD	dwLastVerifyFailTime;
	BOOL	bAlarming;
	BOOL	bAlarmPrevStatus;
	BOOL	bControllerCommError;
	BOOL	bControllerCommError1;
	volatile int nAlarmStatusFromController;
	DWORD	dwMsgStartTime;
	BOOL	bLcdSwitching;
	BOOL	bSleeping;
	DWORD	dwRtcSyncTime;
	BYTE	bDisableDevice;
	BOOL	bCameraStatus;
	BOOL	bSDCardStatus;
	BOOL	bNetworkStatus;
	BOOL	bUSBStatus;
	BOOL	bSOSKeyPressed;
	DWORD	dwTimeDisableDevice;
	DWORD	dwCurrentSecond;
	int		nPrevLanguage;
	int		nLedCurrStatus;
	DWORD	dwTimeLedStart;
	BOOL	bPrevDhcpConfigStatus;
	BOOL	bDuressFlag;
	BOOL	bDrawClock;
	BOOL	bDrawClockPrevStatus;
	UINT64  nLastVerifiedUser;
	BOOL	bExistRFMod;
	BYTE	byPrevTheme;
	BOOL    bAlarmStatus;
}T_UI_PROCSTATUS;


//////////////////////////////////////////////////////////////////////////
//extern int			errno;

//Device Handles
extern HFILE		g_hRtcClock;
extern HFILE		g_hRtc1Clock;
extern HFILE		g_hUart[2];
extern HFILE		g_hKeyboard;
extern HFILE		g_hBuzzer;
extern HFILE		g_hMonoLcd;
extern HFILE		g_hTftLcd;
extern HFILE		g_hWiegand;
extern HFILE		g_hWatchdogP, g_hWatchdog;
extern HFILE		g_hRfmod;
extern HFILE		g_hSdmod;
extern HFILE		g_hCammod;
extern HFILE		g_hPort;
extern HFILE		g_hSensor;
extern HFILE		g_hUSBDevice;
extern HFILE		g_hOther ; //zwh 2010.10.14

extern void*		g_hFpLibrary;
extern T_VIDEOIN	g_VideoIn;

//Various Status Parameters
extern int			g_nSignal;
extern int			gCMOSType;
extern BOOL			gbIsCMOS;
extern BOOL			g_bProgress;
extern BOOL			g_bHostCommandCheckEnable;
extern BOOL			g_bCmosCaptureEnable;
extern BOOL			g_bCardCaptureEnable;
extern BYTE			g_bDisableDevice;
extern BOOL			g_bDeviceBusy;
extern T_CTRL_ITEM* g_CtrlList;
extern BOOL			g_bPoweroffFlag;

extern DWORD		g_uiTimeLastAction;
extern BOOL			g_uiCommandProc;
extern BOOL			g_uiWorkingDisplay;
extern BOOL			g_uiBuildMenu;
extern BOOL			g_uiLicenseChanged;
extern BOOL			g_uiPowerOffFlag;
extern BOOL			g_uiClearForLogWrn;
extern BOOL			g_uiViewSecond;
extern int			g_uiHelpStr;
extern struct termios g_ttyConsoleStatus[2];
extern T_UI_PROCSTATUS g_uiProcStatus;

//
extern BYTE gFpData[1404];
extern USER_INFO gUserInfoTemp;

extern DBLICENSE dbLicense;
extern DBSETUP_TOTAL dbSetupTotal;
extern DBSETUP_TOTAL dbSetupTotalTemp;
extern DBSETUP_SYSTEM dbSetupSystemNew;
extern DBSETUP_TIMEZONE dbSetupTimezoneNew;
extern T_PARAMETER_INFO g_params;
extern BYTE				gpSplash[65536];

extern USER_INFO*		gpUserInfoEnrollData;
extern USER_TIME*		gpUserTimeData;
extern st_HeadString*		gpUserIdHeadData;

extern P_FPINFO			gpFingerEnrollData;

extern WORD*			gpUIIndexData;
extern BYTE*			gpIndexData;
extern BYTE*			gpAntipassData;

// TCP/IP
extern BOOL				dbComm_ipIsDHCP;
extern BOOL				dbComm_dhcpSuccess;
extern DWORD			dbComm_machineID;
extern BYTE				dbComm_macAddress[6];
extern WORD				dbComm_wPortNum;
extern DWORD			dbComm_ipAddress;
extern DWORD			dbComm_ipSubnetMask;
extern DWORD			dbComm_ipDefaultGateway;
extern DWORD			dbComm_ipPcBackground;
extern DWORD			dbComm_dnsserverip;	

// Performance Check
extern DWORD			g_dwPerfCaptureTime;
extern DWORD			g_dwPerfVerifySuccessTime;
extern DWORD			g_dwPerfVerifyFailureTime;
extern DWORD			g_dwVerifyCountFP;
extern DWORD			g_dwVerifyCountCD;
extern DWORD			g_dwVerifyCountPW;

// Style
extern int				g_nCurrentTheme;
extern QRgb				g_rgbForeColor;

extern QRgb				g_rgbBackgroundColor;
extern char*			g_bgImageFilename;
extern char*			g_inputboxImageFilename;
extern char*			g_titleImageFilename;
extern char*			g_bottomImageFilename;
extern char*			g_clockImageFilename;

extern st_FpUploadData*		gpFpUploadData;
#define  PrintfDbugEn   	0
#define PRODUCT_AB 	0

#define USE_FP 		0    	//是否使用指纹验证/记得改main,cpp下面的一个参数gbIsCMOS = FALSE;
#define USE_CARD		0	//是否使用打卡验证
#define AE_375X		1	//使用375的特性，一些是372所不用的	
#define AE_372X              0      //使用372的特性，一些是375所不用的


extern void xprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
);

extern void xfprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
);

extern void COMMAND_EXE(	
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
);

extern void DnsIpSet(void);
extern int connect_nonb(int sockfd, struct sockaddr *saptr, socklen_t salen, int nsec);
extern void DnsInit(void);
extern BOOL DnsIpRead(void);
extern char WiegandCardType;
extern BOOL   LINK_LOST;

extern void DnsIpSet(DWORD ipPcBackgrdound);
extern void DnsInit(void);
extern BOOL HttpLink_OK;
extern void SystemReset(void);
extern void   StartDhchclient(void);
extern unsigned char  StopDhchclient(int pid);
extern BOOL Net_LinkIsOk(void);
extern char* Http_CfgstrGet2(char *buff,char *dest1,char *dest2,char *ret);
extern unsigned int AsciiToInt(char *str);
unsigned int AsciiToDec(char *str);
void DM9000_Check(void);
char *mystrstr(char *haystack, char *needle);

#endif /*__PRECOMP_H__*/

