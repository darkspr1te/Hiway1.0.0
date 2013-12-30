#include "precomp.h"

//Device Handles
HFILE		g_hRtcClock = INVALID_HANDLE_VALUE;												//4
HFILE		g_hRtc1Clock = INVALID_HANDLE_VALUE;											//4
HFILE		g_hUart[2] = {INVALID_HANDLE_VALUE, INVALID_HANDLE_VALUE};						//4
HFILE		g_hKeyboard = INVALID_HANDLE_VALUE;												//4
HFILE		g_hBuzzer = INVALID_HANDLE_VALUE;												//4
HFILE		g_hMonoLcd = INVALID_HANDLE_VALUE;												//4
HFILE		g_hTftLcd = INVALID_HANDLE_VALUE;												//4
HFILE		g_hWiegand = INVALID_HANDLE_VALUE;												//4
HFILE		g_hWatchdogP = INVALID_HANDLE_VALUE, g_hWatchdog = INVALID_HANDLE_VALUE;		//4
HFILE		g_hRfmod = INVALID_HANDLE_VALUE;												//4
HFILE		g_hSdmod = INVALID_HANDLE_VALUE;												//4
HFILE		g_hCammod = INVALID_HANDLE_VALUE;												//4
HFILE		g_hPort = INVALID_HANDLE_VALUE;													//4
HFILE		g_hSensor = INVALID_HANDLE_VALUE;												//4
HFILE		g_hUSBDevice = INVALID_HANDLE_VALUE;	
HFILE		g_hOther = INVALID_HANDLE_VALUE; //zwh 2010.10.14

//4
void*		g_hFpLibrary = NULL;															//4
T_VIDEOIN	g_VideoIn;																		//4

//Various Status Parameters
int		g_nSignal = -1;																	//4
int		gCMOSType;																		//4
BOOL		gbIsCMOS;																		//1
BOOL		g_bProgress = FALSE;															//1	
BOOL		g_bHostCommandCheckEnable = FALSE;												//1
BOOL		g_bCmosCaptureEnable = FALSE;													//1
BOOL		g_bCardCaptureEnable = FALSE;													//1
BYTE		g_bDisableDevice = DISABLE_MODE_NONE;											//1
BOOL		g_bDeviceBusy = FALSE;															//1
T_CTRL_ITEM*    g_CtrlList = NULL;																//4
BOOL		g_bPoweroffFlag = TRUE;															//1

DWORD		g_uiTimeLastAction = 0;															//4
BOOL		g_uiCommandProc = FALSE;														//1
BOOL		g_uiWorkingDisplay = FALSE;														//1
BOOL		g_uiBuildMenu = FALSE;															//1
BOOL		g_uiLicenseChanged = FALSE;														//1
BOOL		g_uiPowerOffFlag = FALSE;														//1
BOOL		g_uiClearForLogWrn = FALSE;														//1
BOOL		g_uiViewSecond = FALSE;															//1
int		g_uiHelpStr = -1;																//4
struct termios  g_ttyConsoleStatus[2];														//

//
BYTE            gFpData[1404];																			//1404
USER_INFO       gUserInfoTemp;																	//56

DBLICENSE       dbLicense;																		//140
DBSETUP_TOTAL   dbSetupTotal;																	//3332
DBSETUP_TOTAL   dbSetupTotalTemp;																//3332
DBSETUP_SYSTEM  dbSetupSystemNew;															//156
DBSETUP_TIMEZONE dbSetupTimezoneNew;														//3108
T_PARAMETER_INFO g_params;																	//64
BYTE			gpSplash[65536];															//65536

USER_INFO*		gpUserInfoEnrollData = NULL;	
USER_TIME*		gpUserTimeData = NULL;//4
st_HeadString*		gpUserIdHeadData = NULL;//4
st_FpUploadData*		gpFpUploadData = NULL;//4

P_FPINFO		gpFingerEnrollData = NULL;													//4	

WORD*			gpUIIndexData = NULL;														//4
BYTE*			gpIndexData = NULL;															//4
BYTE*			gpAntipassData = NULL;														//4	

// TCP/IP
BOOL			dbComm_ipIsDHCP = FALSE;													//1
BOOL			dbComm_dhcpSuccess = FALSE;													//1	
DWORD			dbComm_machineID;															//4
BYTE			dbComm_macAddress[6];														//6
WORD			dbComm_wPortNum;															//4
DWORD			dbComm_ipAddress;															//4
DWORD			dbComm_ipSubnetMask;														//4
DWORD			dbComm_ipDefaultGateway;													//4
DWORD			dbComm_ipPcBackground;														//4
DWORD			dbComm_dnsserverip;	

// Performance Check
DWORD			g_dwPerfCaptureTime;														//4
DWORD			g_dwPerfVerifySuccessTime;													//4
DWORD			g_dwPerfVerifyFailureTime;													//4
DWORD			g_dwVerifyCountFP;															//4
DWORD			g_dwVerifyCountCD;															//4
DWORD			g_dwVerifyCountPW;															//4

int			g_nCurrentTheme;															//4
QRgb			g_rgbForeColor;																//4
QRgb			g_rgbForeColor1;															//4
QRgb			g_rgbBackgroundColor;														//4
char*			g_bgImageFilename;															//4
char*			g_inputboxImageFilename;													//4
char*			g_titleImageFilename;														//4
char*			g_bottomImageFilename;														//4
char*			g_clockImageFilename;														//4

//Total = 77323
