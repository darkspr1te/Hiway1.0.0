#ifndef __SB3000LIB_H__
#define __SB3000LIB_H__

#define TICKCOUNT_START 0
#define TICKCOUNT_STOP  1
#define TICKCOUNT_CALC  2

typedef enum
{
	DEVERR_SUCCESS,
	DEVERR_RTC,
	DEVERR_UART0,
	DEVERR_UART1,
	DEVERR_KEYBOARD,
	DEVERR_BUZZER,
	DEVERR_LCD,
	DEVERR_WIEGAND,
	DEVERR_WATCHDOG,
	DEVERR_RFMOD,
	DEVERR_SDMOD,
	DEVERR_CAMMOD,
	DEVERR_GPIO,
	DEVERR_SBUM,
	DEVERR_SENSOR,
	DEVERR_ENGINE0,
	DEVERR_ENGINE1,
	DEVERR_CAMERA
} T_DEVICE_ERROR;

//////////////////////////////////////////////////////////////////////////
#define DEVNAME_RTCCLOCK		"/dev/rtc"
#define DEVNAME_RTC1CLOCK		"/dev/rtc1"
#define DEVNAME_UART0			"/dev/ttySAC0"
#define DEVNAME_UART1			"/dev/ttySAC1"
//#define DEVNAME_KEYBOARD		"/dev/keyboard"
//hiway add
#define DEVNAME_KEYBOARD                "/dev/input/event1"
#define DEVNAME_BUZZER			"/dev/buzzer"
#define DEVNAME_MONOLCD			"/dev/monochrome"
#define DEVNAME_TFTLCD			"/dev/fb0"
#define DEVNAME_WIEGAND			"/dev/wiegand"
#define DEVNAME_WATCHDOG		"/dev/watchdog"
#define DEVNAME_PWATCHDOG		"/dev/p_watchdog"
#define DEVNAME_RFMODULE		"/dev/rfmod"
#define DEVNAME_SDMODULE		"/dev/sdmod"
#define DEVNAME_CAMMODULE		"/dev/cammod"
#define DEVNAME_GPIO			"/dev/gpio"
#define DEVNAME_SENSOR			"/dev/SB3000TSensor"
#define DEVNAME_SBUM			"/dev/sbum"
#define FPLIB_FILENAME			"/sb3000t/fp.so"
//////////////////////////////////////////////////////////////////////////
int check_wave(int thefd, int* pspeed, int* pbits, int* pstereo, int* pTotalCount);
int check_wave_buf(BYTE* pbyBuf, int* pspeed, int* pbits, int* pstereo, int* pTotalCount);
//////////////////////////////////////////////////////////////////////////

int SB3000DEV_INIT1();
int SB3000DEV_INIT2();
void SB30000DEV_DEINIT(BOOL bPoweroff);
BOOL InitCameraDevice(void);
void CloseCameraDevice(void);

//////////////////////////////////////////////////////////////////////////
int  GetMainTickCount(void);
DWORD GetTickCount(int nType);
void DelayMicroSecond(DWORD dwMicrosecond);
void DelayMiliSecond(DWORD dwMilisecond);
int  GetLastError(void);
WORD CRC16Checksum(void* p, int blen);
void free_spaces(DWORD *pdwImageLimit, DWORD *pdwmallocPt, DWORD *pdwHEAPEND, DWORD *pdwfree);
DWORD free_spaces1(void);
DWORD free_spaces2(void);
DWORD free_spaces3(void);
DWORD free_spaces4(void);
int free_space_flash();
int total_flash_size();
int total_ram_size();
int free_space_ram();

//////////////////////////////////////////////////////////////////////////
void BUZZER_START(void);
void BUZZER_STOP(void);
void BUZZER_OK(void);
void BUZZER_ERROR(void);
void BUZZER_ALARM(void);
void BUZZER_ALARM_ASYNC(void);
void BUZZER_BELL(void);

//////////////////////////////////////////////////////////////////////////
BYTE GETKEY(BOOL bLong = FALSE);
BOOL KEYBOARD_SLEEP(BOOL bStatus, BOOL bPoweroff);

//////////////////////////////////////////////////////////////////////////
void RtcGet(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond);
void RtcSet(int nYear, int nMonth, int nDay, int nWeekday, int nHour, int nMinute, int nSecond);
void Rtc1Get(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond);
void Rtc1Set(int nYear, int nMonth, int nDay, int nWeekday, int nHour, int nMinute, int nSecond);
void RtcGetAlam(int* pnHour, int* pnMinute, int* pnSecond);
void RtcSetAlam(int nHour, int nMinute, int nSecond);
void RtcAlarmDisable();
//////////////////////////////////////////////////////////////////////////
BOOL xifconfig(const char *devname, BYTE *mac_addr, DWORD *ip_addr, DWORD *mask_addr, DWORD *gw_addr, BOOL bSet);
BOOL xifconfig_speed(const char *devname, int nSpeed);
BOOL xdhcpconfigure(int nTimeout, BOOL bForce = TRUE);
void xsignal(int sig);
BOOL xuartconfig(HFILE s_handle, speed_t s_baud, tcflag_t s_data_bits, int s_parity_bit);
BOOL xuarttxempty(HFILE s_handle);
BOOL xwiegandconfig(struct _wiegand_type *wiegand_type);
BOOL xrtcalarmconfig(DWORD dwTime);
void xwatchdogconfig(HFILE s_handle);
void fp_setlivecheck(BOOL bCheck);
void wdog_restart(void);
void wdog_app_alive(void);
void SystemReset(void);

//////////////////////////////////////////////////////////////////////////
void ALARM_ON(void);
void ALARM_OFF(void);
void POWER_OFF(void);
int  POWER_KEY(void);
void BELL_ON(void);
void BELL_OFF(void);
void DOOR_OPEN(void);
void DOOR_CLOSE(void);
int  DOOR_ISNOT_EXIT(void);
int  DOOR_IS_OPENED(void);
void RS485_ENABLE(void);
void RS485_DISABLE(void);
int  TAMPER_IS_OFF(void);
void LED_R_ON();
void LED_R_OFF();
void LED_G_ON();
void LED_G_OFF();
void LED_K_ON();
void LED_K_OFF();
void LCD_BG_ON();
void LCD_BG_OFF();
void APLUS_SOUND_BELL();
void APLUS_SOUND_PRESSNEW();
void APLUS_SOUND_OK();
void APLUS_SOUND_REVERIFY();

//////////////////////////////////////////////////////////////////////////
#define FBIOBLANK			0x4611
typedef enum
{
	/* screen: unblanked, hsync: on,  vsync: on */
	FB_BLANK_UNBLANK,

	/* screen: blanked,   hsync: on,  vsync: on */
	FB_BLANK_NORMAL,

	/* screen: blanked,   hsync: on,  vsync: off */
	FB_BLANK_VSYNC_SUSPEND,

	/* screen: blanked,   hsync: off, vsync: on */
	FB_BLANK_HSYNC_SUSPEND,

	/* screen: blanked,   hsync: off, vsync: off */
	FB_BLANK_POWERDOWN
}T_BLANK_MODE;

#define FBINFO_BLANK_PAUSE		0x400
#define FBINFO_BLANK_RESUME		0x401
#define FBINFO_ROTATE			0x402

void LCD_BLANK(int nBlankMode);
int LCD_BLANK_STATUS();

class QString;
class QWidget;
//////////////////////////////////////////////////////////////////////////
BOOL Save256Image(char *szFilename, BYTE *pData, int length);
void DrawFingerprint(void *pWindow, void *pOrgPixmap = NULL);
void DrawCamera(void *pWindow, void *pOrgPixmap, void *pNewPixmap);
UINT64 STRING2ID(char* strID);
char* ID2STRING(UINT64 nID);
DWORD STRING2PWD(char* strPassword);
char* PWD2STRING(DWORD dwPassword);
BOOL PWD2STRING(DWORD dwPassword, char *szPWD,int len);
QString UNICODE2STRING(WORD* szUnicodeStr, int nSize);
BOOL STRING2UNICODE(QString str, WORD* szUnicodeBuffer, int nBufferSize);
int LOCKGROUP2NUMBER(int nLockGroup);
char* LOCKGROUP2STRING(int nLockGroup);
int NUMBER2LOCKGROUP(int nNumber);
BOOL LOCKGROUP_VALIDCHECK(BYTE *pLockGroupList, BYTE byLockGroup);
int VERIFYMODE2INDEX(int nVerifyMode);
int INDEX2VERIFYMODE(int nIndex);
DWORD VERIFYMODE2MASK(int nVerifyMode);
void EDITBOX_2_T9InputBox(QWidget* w);
void CLEAR_ALL(QWidget *w);
void SET_DLG_ITEM_COLOR(QWidget *w,int colorFlag = 0);
int FILEOPEN(const char *szFilename, int flags);
BOOL SET_LANGUAGE(int nLanguage);
void SET_GUITHEME(int nTheme);
BOOL STRING2HM(QString szTime, BYTE & bHour, BYTE & bMinute);
char* MAKE_FULLPATH(const char *szDir, const char *szFile, const char *szExtension);
BOOL FILE_EXIST(const char *szFile);
int FILE_SIZE(const char *szFile);
BOOL MKDIR(const char *szDirName);
BOOL DIR_CHECK_AND_MAKE(const char *szFullPath);
BOOL RMDIR(const char *szDirName);
BOOL COPYDIR(const char *szSrc, char *szDst);
BOOL SAVE_FILE(const char *szFullPath, BYTE *pData, int nSize);
BOOL COPY_FILE(const char *szFilename, const char *szNewFilename);
BOOL DELETE_FILE(const char *szFullPath);
BOOL RENAME_FILE(const char *oldpath, const char *newpath);
int FREE_SPACE(const char *szFilesystem);
int SB_EXEC(const char *command, DWORD dwTimeout = -1UL);
BOOL WEBSERVER_START();
BOOL WEBSERVER_STOP();
int WEBSERVER_GETPID();
BOOL WEBSERVER_ISALIVE();
BOOL TCPIP_ON();
BOOL UDISK_ON();
BOOL CAMERA_ON();
BOOL CAMERA_CAPTURE();
BOOL SDCARD_ISMOUNT(void);
BOOL SDCARD_DETECT(void);
BOOL SDCARD_MOUNT(void);
BOOL SDCARD_LOCKED(void);
BOOL SDCARD_RESET(void);
BOOL SDCARD_MAKESPACE(int nSize);

BOOL SBUM_SUSPEND();
BOOL SBUM_RESUME();

#endif /*__SB3000LIB_H__*/
