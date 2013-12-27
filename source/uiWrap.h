#ifndef __UI_WRAP_H__
#define __UI_WRAP_H__

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	UIKEY_0,
	UIKEY_1,
	UIKEY_2,
	UIKEY_3,
	UIKEY_4,
	UIKEY_5,
	UIKEY_6,
	UIKEY_7,
	UIKEY_8,
	UIKEY_9,
	UIKEY_MENU,
	UIKEY_UP,
	UIKEY_DOWN,
	UIKEY_OK,
	UIKEY_ESC,
	UIKEY_POWER,
	UIKEY_NONE = 0xFF
} T_UI_KEY;

#define UITIME_OUT 120000
#define UITIME_VOICE 5000

//////////////////////////////////////////////////////////////////////////
void uiTimeDelay(DWORD dwMilisecs);
DWORD uiTimeGetTickCount(void);
void uiTimeSetLastActionTime(DWORD dwTime = -1UL);
DWORD uiTimeGetIdleTime(void);
BOOL uiTimeIsTimeout(DWORD dwTimeout = UITIME_OUT);

//////////////////////////////////////////////////////////////////////////
int uiRtcYMD2Days(int nYear, int nMonth, int nDay);
void uiRtcDays2YMD(int nDays, int* pnYear, int* pnMonth, int* pnDay);
void uiRtcSeconds2YMDHMS(DWORD dwSeconds, int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond);
int uiRtcGetWeekDay(int nYear, int nMonth, int nDay);
int uiRtcGetDaysForMonth(int nYear, int nMonth);
DWORD uiRtcGetSeconds(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond);
void uiRtcGet(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond);
DWORD uiRtcGetSeconds(void);
void uiRtcSetSeconds(DWORD dwSeconds);
void uiRtcSynchronize();
void uiRtcSetDate(DWORD dwSeconds);
void uiRtcSetTime(DWORD dwSeconds);
QString uiRtcGetDate(DWORD dwSeconds = -1UL, BOOL bWithYear = TRUE);
char* uiRtcSeconds2LogStringForDownload(DWORD dwSeconds);  
QString uiRtcGetTime(DWORD dwSeconds = -1UL, BOOL bShowSecond = TRUE);
int uiRtcDiffSecond(int nSecCur, int nSecPrev);
BOOL uiRtcIsToday(DWORD dwSeconds);
char* uiRtcSeconds2LogString(DWORD dwSeconds);
char* uiRtcSeconds2Summertime(DWORD dwSeconds);
char* uiRtcSeconds2LogStringForCamera(DWORD dwSeconds = -1UL);

//////////////////////////////////////////////////////////////////////////
int uiKeyGetKey(int bPostKeyEvent = FALSE);   
int uiKeyGetKeyLong(DWORD dwTimeout = -1UL);
BOOL uiKeyIsDigit(T_UI_KEY nKey);
BOOL uiKeyIsPower(void);
int DetermineControlType(QObject *w);
void PostKeyEvent(int nKey, void *receiver, int bPostKeyEvent);  

//////////////////////////////////////////////////////////////////////////

typedef enum
{
	UI_BUZZER_NONE,
	UI_BUZZER_OK,
	UI_BUZZER_ERROR,
	UI_BUZZER_ALARM,
	UI_BUZZER_BELL,
	UI_BUZZER_ON
}T_BUZZER_TYPE;

void uiBuzzerOn(int nBuzzerType);
void uiBuzzerOff(void);
void uiBuzzerOk(void);
void uiBuzzerError(void);
void uiBuzzerAlarm(void);
void uiBuzzerKey(void);
void uiBuzzerBell(void);
void uiSoundOut(int nSoundNumber, int nBuzzer, int nTimeout = 0, BOOL bFirstGUIProcess = FALSE);

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	UI_LED_NONE,
	UI_LED_NORMAL,
	UI_LED_ABNORMAL,
	UI_LED_SUCCESS,
	UI_LED_FAIL,
	UI_LED_BUSY
}T_LED_TYPE;

void uiLedNormal();
void uiLedAbnormal();
void uiLedOK();
void uiLedFail();
void uiLedBusy();
void uiLedOff();
void uiLedKeyBackground(BOOL bStatus);

//////////////////////////////////////////////////////////////////////////
void uiCMOSCheck(void);
BOOL uiCMOSCaptureFP(void);
BOOL uiCMOSIsPressFP(void);
BOOL uiCMOSAdjustBrightness(DWORD* pdwMechanical, DWORD* pdwExposure);
BOOL uiCMOSPower(BOOL bPower);

//////////////////////////////////////////////////////////////////////////
void uiDoorOpen(UINT64 nID);
void uiDoorClose();
BOOL uiDoorSensorStatus();
void uiLockProc(void);
void uiLogSlogAdd2(UINT64 nManagerID, BYTE byAction, UINT64 nUserID, BYTE byResult);

//////////////////////////////////////////////////////////////////////////
void uiWiegandSend(UINT64 nId);

//////////////////////////////////////////////////////////////////////////
BOOL uiPcCmdProc(BOOL bWorkingDisplay);

//////////////////////////////////////////////////////////////////////////
enum
{
	UIENROLL_RET_FALSE=0,
	UIENROLL_RET_TRUE,
	UIENROLL_RET_DUPLICATE,
	UIENROLL_NO_ENROLL_FP,
	UIENROLL_NO_ENROLL_ID
};

typedef enum
{
	UI_VERIFY_START,
	UI_VERIFY_NONE = UI_VERIFY_START,
	UI_VERIFY_PW,
	UI_VERIFY_FP,
	UI_VERIFY_RF,
	UI_VERIFY_ID,
	UI_VERIFY_END = UI_VERIFY_ID
} T_UI_VERIFY_MODE;

void uiFpEnrollStart(void);
int uiFpEnrollNth(int nStep, int *pResult = NULL);
int uiFpEnrollEnd(FPINFO *pTemplate);
void uiFpEnrollDelete(UINT64 nID, int nFP);
BOOL uiFpVerifyO2N(FPINFO *pFP, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber);
BOOL uiFpVerifyByMaster(FPINFO *pFP, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber);
BOOL uiFpVerifyO2O(FPINFO *pFP, UINT64 nID, BOOL *pbAdapted, BYTE *pbFingerNumber);

//////////////////////////////////////////////////////////////////////////
DWORD uiCardCapture(void);
BOOL uiCardEnroll(USER_INFO *pUserInfo, DWORD dwCardNumber);
void uiCardEnrollDelete(UINT64 nID);
BOOL uiCardVerify(DWORD dwCardNumber, USER_INFO *pUserInfo, BYTE *pbDisabled);
BOOL uiCardVerifyByMaster(DWORD dwCardNumber, USER_INFO *pUserInfo, BYTE *pbDisabled);
void uiCardCaptureInit(void);

//////////////////////////////////////////////////////////////////////////
BOOL uiPwdEnroll(USER_INFO *pUserInfo, char* pcPwd);
void uiPwdEnrollDelete(UINT64 nID);
BOOL uiPwdVerify(UINT64 nID, char* pcPwd, USER_INFO *pUserInfo, BYTE *pbDisabled);
BOOL uiIDVerify(UINT64 nID, USER_INFO *pUserInfo, BYTE *pbDisabled);

//////////////////////////////////////////////////////////////////////////
typedef enum
{
	UI_ENABLED,
	UI_DISABLED,
	UI_NOT_ACCESS_TIME
}T_UI_DISABLE_TYPE;

void uiLogSlogAdd(UINT64 nManagerID, BYTE byAction, UINT64 nUserID = 0, BYTE byResult = 0);
int uiLogSlogGetCountPerMgr(UINT64 nIDMgr);

void uiLogGlogAdd(UINT64 nID, BYTE byAction, BYTE byTrStatus = 0, BOOL bAntipassOut = FALSE);

enum
{
	UI_SUMMER_NONE,
	UI_SUMMER_UPDATE,
	UI_SUMMER_RESTORE,
};

enum
{
	UI_POWER_ON,
	UI_POWER_OFF,
	UI_POWER_SLEEP,
	UI_POWER_LCDSWITCH
};

enum
{
	UI_ALARM_START,
	UI_ALARM_NOCLOSE = UI_ALARM_START,
	UI_ALARM_TAMPER,
	UI_ALARM_DURESS,
	UI_ALARM_ILGVERIFY,
	UI_ALARM_ILGOPEN,
	UI_ALARM_LOGOVERFLOW,
	UI_ALARM_PCCMD,
	UI_ALARM_NOCOMM,
	UI_ALARM_END = UI_ALARM_NOCOMM
};

//////////////////////////////////////////////////////////////////////////
int uiGetCurrentTR();
int uiBellGetStatus();
void uiBellOn(BOOL bOn);
QString uiMsgGetCurrentString(UINT64 nID, int nGroup);
void uiMsgStart(QString szMessage, BOOL bPersonalMessage);
void uiMsgDrawCurrentStatus();
BOOL uiMsgPersonalIsFlowing();
void uiMsgStop();
BOOL uiAlarmStart(int nType, BOOL bBuzzerOnly = FALSE);
BOOL uiAlarmStop(int nType = -1);
void uiAlarmDuress(UINT64 nID);
int uiPowerGetStatus();
void uiPowerSetStatus(int nStatus, DWORD dwParam);
void uiPowerEnterSleep(BOOL bPoweroff);
void uiPowerReboot();

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_IsExist(void);
BOOL uiSL811_IsDetected(void);
BOOL uiSL811_DownloadGlog(BOOL* pbEmpty);
BOOL uiSL811_DownloadAllGlog(BOOL* pbEmpty);
BOOL uiSL811_DownloadSlog(BOOL* pbEmpty);
BOOL uiSL811_DownloadAllSlog(BOOL* pbEmpty);
BOOL uiSL811_DownloadAllEnroll(void);
void uiSL811_UploadAllEnrollDraw(void);
void uiSL811_UploadAllEnrollResultDraw(BOOL bRet);
BOOL uiSL811_UploadAllEnroll(void);
BOOL uiSL811_MsgUpload(void);
BOOL uiSL811_MP3Upload(void);
void uiSL811_FirmwareUpgradeDraw(void);
void uiSL811_FirmwareUpgradeResultDraw(BOOL bRet);
BOOL uiSL811_FirmwareUpgrade(void);
BOOL uiSL811_SetImage();

//////////////////////////////////////////////////////////////////////////
BOOL uiEventSend_HEART(void);   
BOOL uiEventSend_SLOG(MLOG_INFO *pLogData);
BOOL uiEventSend_GLOG(ALOG_INFO *pLogData);  
void uiEventSend_PRESS_FP(void);
void uiEventSend_VERIFY_SUCCESS(int nVerifyMode, UINT64 ID);
void uiEventSend_VERIFY_FAIL(int nVerifyMode);
void uiEventSend_ALARM_ON(int nAlarmType, UINT64 ID);
void uiEventSend_ALARM_OFF(int nAlarmType, int nAlarmReleaseType, UINT64 ID);
BOOL uiEventSend_TIMESYN(void);

#endif /*__UI_WRAP_H__*/
