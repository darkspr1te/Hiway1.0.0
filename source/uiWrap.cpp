#include "precomp.h"
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QPushButton>
#include <QtGui/QComboBox>
#include <QtGui/QCheckBox>
#include <QtGui/QKeyEvent>
#include "t9/t9_main.h"
#include "gui/MainWindow.h"
#include "gui/SystemManage.h"
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QTextCodec>
#include <QtGui/QPainter>
#include <QtGui/QDialog>
#include "./http_client/http_main.h"

#include <QDebug>

extern void comm_sendtime (void);	
extern void DM9000_Reset(void);



extern T_UI_PROCSTATUS g_uiProcStatus;
extern CMainWindow *g_MainWindow;
extern CVerify *g_VerifyWindow;


void uiProcDrawMsgArea(BOOL bStart);
int uiProcBoxSelect(QWidget *pWnd, int x, int y, int w, int h, BOOL *pbRet, int nValue, int from, int to, QStringList *pStrList = NULL, BOOL bResize = TRUE);

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiTimeDelay(DWORD dwMilisecs)
{
	DWORD dwTimeout = GetMainTickCount() + dwMilisecs;
	WAIT_EVENT((GetMainTickCount() < (int)dwTimeout));
}

DWORD uiTimeGetTickCount(void)
{
	return GetMainTickCount();
}

void uiTimeSetLastActionTime(DWORD dwTime/* = -1UL*/)
{
	g_uiProcStatus.bLcdSwitching = FALSE;
	g_uiProcStatus.bSleeping = FALSE;
	if (dwTime == -1UL)
		g_uiTimeLastAction = uiTimeGetTickCount();//这个时间是注册时间
	else
		g_uiTimeLastAction = dwTime;
}

DWORD uiTimeGetIdleTime(void)
{
	return uiTimeGetTickCount() - g_uiTimeLastAction;
}

BOOL uiTimeIsTimeout(DWORD dwTimeout)
{
	BOOL bRet;
	bRet = (uiPowerGetStatus() != -1);
	bRet = (bRet || uiTimeGetIdleTime() >= dwTimeout);
	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static int rtcDaysPerMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

//////////////////////////////////////////////////////////////////////////
int uiRtcYMD2Days(int nYear, int nMonth, int nDay)
{
	int i;
	int nDays = 0;

	if (nYear > 0)
		nDays = nYear * 365 + ((nYear - 1) / 4 + 1);

	for ( i = 1; i < nMonth; i++ )
		nDays += rtcDaysPerMonth[i-1];

	if ( nYear % 4 == 0 )
	{
		if (nMonth > 2)
			nDays += 1;
	}

	nDays += nDay;

	return nDays;
}

//////////////////////////////////////////////////////////////////////////
void uiRtcDays2YMD(int nDays, int* pnYear, int* pnMonth, int* pnDay)
{
	int nDaysTemp;
	*pnYear = 0;
	*pnMonth = 1;

	while (1)
	{
		nDaysTemp = 365;
		if (*pnYear % 4 == 0)
			nDaysTemp++;

		if (nDays <= nDaysTemp)
			break;

		nDays -= nDaysTemp;
		(*pnYear)++;
	}

	while (1)
	{
		nDaysTemp = rtcDaysPerMonth[*pnMonth - 1];
		if (*pnMonth == 2 && *pnYear % 4 == 0)
			nDaysTemp++;

		if (nDays <= nDaysTemp)
			break;

		nDays -= nDaysTemp;
		(*pnMonth)++;
	}

	*pnDay = nDays;
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSeconds2YMDHMS(DWORD dwSeconds, int* pnYear, int* pnMonth, int* pnDay, int* pnHour, int* pnMinute, int* pnSecond)
{
	DWORD dwSeconds2 = dwSeconds % (3600 * 24);

	*pnHour = dwSeconds2 / 3600; dwSeconds2 %= 3600;
	*pnMinute = dwSeconds2 / 60;
	*pnSecond = dwSeconds2 % 60;

	uiRtcDays2YMD(dwSeconds / 3600 / 24 + 1, pnYear, pnMonth, pnDay);
	*pnYear += 2000;
}

//////////////////////////////////////////////////////////////////////////
int uiRtcGetWeekDay(int nYear, int nMonth, int nDay)
{
	return (uiRtcYMD2Days(nYear, nMonth, nDay) + 5) % 7 + 1;
}

//////////////////////////////////////////////////////////////////////////
int uiRtcGetDaysForMonth(int nYear, int nMonth)
{
	int nret;
	
	nret = rtcDaysPerMonth[nMonth - 1];
	if (nMonth == 2 && nYear % 4 == 0)
		nret++;

	return nret;
}

//////////////////////////////////////////////////////////////////////////
DWORD uiRtcGetSeconds(int nYear, int nMonth, int nDay, int nHour, int nMinute, int nSecond)
{
	DWORD dwSeconds;

	nYear -= 2000;

	dwSeconds = (DWORD)(uiRtcYMD2Days(nYear, nMonth, nDay) - 1) * 24 * 3600;
	dwSeconds += nHour * 3600;
	dwSeconds += nMinute * 60;
	dwSeconds += nSecond;

	return dwSeconds;
}

//////////////////////////////////////////////////////////////////////////
void uiRtcGet(int* pnYear, int* pnMonth, int* pnDay, int* pnWeekday, int* pnHour, int* pnMinute, int* pnSecond)
{
	RtcGet(pnYear, pnMonth, pnDay, pnWeekday, pnHour, pnMinute, pnSecond);
	*pnYear += 2000;

	if (dbSetupTotal.setSystem.nDaylightOffset)
	{
		DWORD dwSeconds = uiRtcGetSeconds(*pnYear, *pnMonth, *pnDay, *pnHour, *pnMinute, *pnSecond);
		DWORD dwFrom = dbSetupTotal.setSystem.dwDaylightChangeTime;
		DWORD dwTo = dbSetupTotal.setSystem.dwDaylightRestoreTime;
		int nYear, nMonth, nDay, nHour, nMinute, nSecond;

		uiRtcSeconds2YMDHMS(dwFrom, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		nYear = *pnYear;
		dwFrom = uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		uiRtcSeconds2YMDHMS(dwTo, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		nYear = *pnYear;
		dwTo = uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);

		if ((dwSeconds >= dwFrom) &&
			(dwSeconds <= dwTo))
		{
			dwSeconds += 3600 * dbSetupTotal.setSystem.nDaylightOffset;
			uiRtcSeconds2YMDHMS(dwSeconds, pnYear, pnMonth, pnDay, pnHour, pnMinute, pnSecond);
		}
	}
	*pnWeekday = uiRtcGetWeekDay(*pnYear-2000, *pnMonth, *pnDay);
}

//////////////////////////////////////////////////////////////////////////
DWORD uiRtcGetSeconds(void)
{
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
	uiRtcGet(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
	return uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetSeconds(DWORD dwSeconds)
{
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;

	if ((dwSeconds >= dbSetupTotal.setSystem.dwDaylightChangeTime) &&
		(dwSeconds <= dbSetupTotal.setSystem.dwDaylightRestoreTime))
		dwSeconds -= 3600 * dbSetupTotal.setSystem.nDaylightOffset;

	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	nYear -= 2000;

	nWeekday = uiRtcGetWeekDay(nYear, nMonth, nDay);

	RtcSet(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
	Rtc1Set(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
	g_MainWindow->DrawClock(TRUE);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSynchronize()
{
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;

	Rtc1Get(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
	if (nYear < 0 || nYear > 99 ||
		nMonth < 1 || nMonth > 12 ||
		nDay < 1 || nDay > uiRtcGetDaysForMonth(nYear, nMonth) ||
		nHour < 0 || nHour > 23 ||
		nMinute < 0 || nMinute > 59 ||
		nSecond < 0 || nSecond > 59)
	{
		nYear = 0;
		nMonth = 1;
		nDay = 1;
		nHour = 0;
		nMinute = 0;
		nSecond = 0;
		Rtc1Set(nYear, nMonth, nDay, uiRtcGetWeekDay(nYear, nMonth, nDay), nHour, nMinute, nSecond);
	}
//	printf("%04d-%02d-%02d %02d:%02d:%02d\n", nYear, nMonth, nDay, nHour, nMinute, nSecond);
	RtcSet(nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond);
	g_MainWindow->DrawClock(TRUE);
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetDate(DWORD dwSeconds)
{
	int nYear1, nMonth1, nDay1, nHour1, nMinute1, nSecond1;
	int nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2;

	uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear1, &nMonth1, &nDay1, &nHour1, &nMinute1, &nSecond1);
	uiRtcSeconds2YMDHMS(dwSeconds, &nYear2, &nMonth2, &nDay2, &nHour2, &nMinute2, &nSecond2);

	nHour2 = nHour1; nMinute2 = nMinute1; nSecond2 = nSecond1;
	uiRtcSetSeconds(uiRtcGetSeconds(nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2));
}

//////////////////////////////////////////////////////////////////////////
void uiRtcSetTime(DWORD dwSeconds)
{
	int nYear1, nMonth1, nDay1, nHour1, nMinute1, nSecond1;
	int nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2;

	uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear1, &nMonth1, &nDay1, &nHour1, &nMinute1, &nSecond1);
	uiRtcSeconds2YMDHMS(dwSeconds, &nYear2, &nMonth2, &nDay2, &nHour2, &nMinute2, &nSecond2);

	nYear2 = nYear1; nMonth2 = nMonth1; nDay2 = nDay1;
	uiRtcSetSeconds(uiRtcGetSeconds(nYear2, nMonth2, nDay2, nHour2, nMinute2, nSecond2));
}

//////////////////////////////////////////////////////////////////////////
QString uiRtcGetDate(DWORD dwSeconds, BOOL bWithYear)
{
	char strDate[16];
	char *strDateWithoutYear = &strDate[3];  
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	if (dwSeconds == -1UL)
		dwSeconds = uiRtcGetSeconds();

	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	nYear -= 2000;

	switch (dbSetupTotal.setSystem.nDateFormat + UISTR_DATEFMT_START)
	{
	case UISTR_DATEFMT_1:
		sprintf(strDate, "%02d-%02d-%02d", nYear, nMonth, nDay);
		break;
	case UISTR_DATEFMT_2:
		sprintf(strDate, "%02d/%02d/%02d", nYear, nMonth, nDay);
		break;
	case UISTR_DATEFMT_3:
		sprintf(strDate, "%02d.%02d.%02d", nYear, nMonth, nDay);
		break;
	case UISTR_DATEFMT_4:
		sprintf(strDate, "%02d-%02d-%02d", nMonth, nDay, nYear);
		break;
	case UISTR_DATEFMT_5:
		sprintf(strDate, "%02d/%02d/%02d", nMonth, nDay, nYear);
		break;
	case UISTR_DATEFMT_6:
		sprintf(strDate, "%02d.%02d.%02d", nMonth, nDay, nYear);
		break;
	case UISTR_DATEFMT_7:
		sprintf(strDate, "%02d-%02d-%02d", nDay, nMonth, nYear);
		break;
	case UISTR_DATEFMT_8:
		sprintf(strDate, "%02d/%02d/%02d", nDay, nMonth, nYear);
		break;
	case UISTR_DATEFMT_9:
		sprintf(strDate, "%02d.%02d.%02d", nDay, nMonth, nYear);
		break;
	case UISTR_DATEFMT_10:
		sprintf(strDate, "%04d%02d%02d", 2000 + nYear, nMonth, nDay);
		strDateWithoutYear = &strDate[4];   
		break;
	}

	if (bWithYear)
		return QString(strDate);
	else
		return QString(strDateWithoutYear);
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogStringForDownload(DWORD dwSeconds)
{
	static char strDate[32];
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;


	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

	sprintf(strDate,  "%04d/%02d/%02d  %02d:%02d:%02d", nYear, nMonth, nDay, nHour, nMinute, nSecond);

	return strDate;

}

//////////////////////////////////////////////////////////////////////////
QString uiRtcGetTime(DWORD dwSeconds, BOOL bShowSecond)
{
	char strTime[16];
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	if (dwSeconds == -1UL)
		dwSeconds = uiRtcGetSeconds();
	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
// 	switch (dbSetupSystemNew)
// 	{
// 
// 	}
	if (bShowSecond)
		sprintf(strTime, "%02d:%02d:%02d", nHour, nMinute, nSecond);
	else
		sprintf(strTime, "%02d:%02d", nHour, nMinute);
	return QString(strTime);
}

//////////////////////////////////////////////////////////////////////////
int uiRtcDiffSecond(int nSecCur, int nSecPrev)
{
	nSecCur = nSecCur % (3600 * 24);
	nSecPrev = nSecPrev % (3600 * 24);
	int nSecDiff = nSecCur - nSecPrev;

	if (nSecDiff < 0)
		nSecDiff += (24 * 3600);

	return nSecDiff;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiRtcIsToday(DWORD dwSeconds)
{
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	nHour = 23;
	nMinute = 59;
	nSecond = 59;

	return (uiRtcDiffSecond(uiRtcGetSeconds(nYear, nMonth, nDay, nHour, nMinute, nSecond), dwSeconds) < 24 * 3600);
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogString(DWORD dwSeconds)
{
	char strDate[16];           
	static char buf[16];
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

	switch (dbSetupTotal.setSystem.nDateFormat + UISTR_DATEFMT_START)
	{
		case UISTR_DATEFMT_1:
		case UISTR_DATEFMT_4:
			sprintf(strDate, "%02d-%02d", nMonth, nDay);
			break;
		case UISTR_DATEFMT_2:
		case UISTR_DATEFMT_5:
			sprintf(strDate, "%02d/%02d", nMonth, nDay);
			break;
		case UISTR_DATEFMT_3:
		case UISTR_DATEFMT_6:
			sprintf(strDate, "%02d.%02d", nMonth, nDay);
			break;
		case UISTR_DATEFMT_7:
			sprintf(strDate, "%02d-%02d", nDay, nMonth);
			break;
		case UISTR_DATEFMT_8:
			sprintf(strDate, "%02d/%02d", nDay, nMonth);
			break;
		case UISTR_DATEFMT_9:
			sprintf(strDate, "%02d.%02d", nDay, nMonth);
			break;
		case UISTR_DATEFMT_10:
			sprintf(strDate, "%02d%02d", nMonth, nDay);  
			break;
	}
    sprintf(buf, "%s %02d:%02d", STR2ASCII(QString(strDate)), nHour, nMinute); 

	return buf;
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2LogStringForCamera(DWORD dwSeconds)
{
	static char buf[32];
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	if (dwSeconds == -1UL)
		dwSeconds = uiRtcGetSeconds();
	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	sprintf(buf, "%02d%02d%02d-%02d%02d%02d", nYear - 2000, nMonth, nDay, nHour, nMinute, nSecond);
	return buf;
}

//////////////////////////////////////////////////////////////////////////
char* uiRtcSeconds2Summertime(DWORD dwSeconds)
{
	static char buf[16];
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;

	uiRtcSeconds2YMDHMS(dwSeconds, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

	sprintf(buf, "%02d-%02d %02d:%02d", nMonth, nDay, nHour, nMinute);
	return buf;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
typedef struct 
{
	const char *szClassName;
	const char *szObjectName;
	int nHelpStr;
}T_WINDOW_LIST;
T_WINDOW_LIST HELP_WINDOW_LIST[] = 
{
	{"CEnrollStep1",		NULL,				UISTR_HELP_ENROLLSTEP1},
	{"CEnrollStep2",		NULL,				UISTR_HELP_ENROLLSTEP2},
	{"CEnrollFP",			"EnrollFP",			UISTR_HELP_ENROLLFP},
	{"CEnrollFP",			"EnrollDuress",		UISTR_HELP_ENROLLDURESS},
	{"CEnrollCard",			NULL,				UISTR_HELP_ENROLLCARD},
	{"CEnrollVoice",		NULL,				UISTR_HELP_ENROLLVOICE},
	{"CEnrollPhoto",		NULL,				UISTR_HELP_ENROLLPHOTO},
	{"CEnrollDelete",		NULL,				UISTR_HELP_ENROLLDELETE},
	{"CDuressFP",			"DuressFPSet",		UISTR_HELP_DURESSFPSET},
	{"CDuressFP",			"DuressFPRemove",	UISTR_HELP_DURESSFPREMOVE},
	{"CInputUserID",		"UserIDInput",		UISTR_HELP_INPUTID},
	{"CInputUserID",		"UserPWDInput",		UISTR_HELP_INPUTPWD},
	{"CSearchUser",			NULL,				UISTR_HELP_SEARCHUSER},
//	{"CMenu",				NULL,				UISTR_HELP_MENU},
	{"CBellSetup",			NULL,				UISTR_HELP_BELLSETUP},
	{"CBellSetOne",			NULL,				UISTR_HELP_BELLSETONE},
	{"CTrSetup",			NULL,				UISTR_HELP_TRSETUP},
	{"CTrSetOne",			NULL,				UISTR_HELP_TRSETONE},
	{"CTimezoneSetup",		NULL,				UISTR_HELP_TIMEZONESETUP},
	{"CMp3Upload",			NULL,				UISTR_HELP_MP3UPLOAD},
	{"CSystemUpgrade",		NULL,				UISTR_HELP_SYSTEMUPGRADE},
	{"CSelftestKeyboard",	NULL,				UISTR_HELP_SELFTESTKEYBOARD},
	{"CSelftestMemory",		NULL,				UISTR_HELP_SELFTESTMEMORY},
	{"CSelftestRtc",		NULL,				UISTR_HELP_SELFTESTRTC},
	{"CSelftestSensor",		NULL,				UISTR_HELP_SELFTESTSENSOR},
	{"CSelftestSound",		NULL,				UISTR_HELP_SELFTESTSOUND},
//	{"CSelftestAll",		NULL,				UISTR_HELP_SELFTESTALL},
	{"CUserList",			NULL,				UISTR_HELP_USERLIST},
	{"CSearchLog",			NULL,				UISTR_HELP_SEARCHLOG},
	{"CSLogList",			NULL,				UISTR_HELP_SLOGLIST},
	{"CGLogList",			NULL,				UISTR_HELP_GLOGLIST},
};

//////////////////////////////////////////////////////////////////////////
int uiHelpFind(QObject *pDlg)
{
	int i, k;
	QObject *obj;

	for (i=0; i<(int)ITEM_CNT(HELP_WINDOW_LIST); i++)
	{
		obj = pDlg;
		for (k=0; k<5; k++)
		{
			if (!obj)
				break;
			if (strcmp(obj->metaObject()->className(), HELP_WINDOW_LIST[i].szClassName) == 0)
			{
				if (!HELP_WINDOW_LIST[i].szObjectName || obj->objectName() == HELP_WINDOW_LIST[i].szObjectName)
					return HELP_WINDOW_LIST[i].nHelpStr;
			}
			if (g_uiHelpStr >= 0 && strcmp(obj->metaObject()->className(), "CMenu") == 0)
				return g_uiHelpStr;
			obj = obj->parent();
		}
	}
	return -1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
const int __KEYMAP_TEXTBOX[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Backspace,		//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
    Qt::Key_Tab,			//UIKEY_OK    
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};
const int __KEYMAP_COMBOBOX[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Meta,			//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
    Qt::Key_Tab,			//UIKEY_OK  
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};
const int __KEYMAP_CHECKBOX[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Meta,			//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
	Qt::Key_Space,			//UIKEY_OK
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};
const int __KEYMAP_PUSHBUTTON[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Meta,			//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
	Qt::Key_Space,			//UIKEY_OK
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};
const int __KEYMAP_DIALOG[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Meta,			//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
	Qt::Key_Enter,			//UIKEY_OK
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};
static const int* __KEYMAP[] = 
{
	__KEYMAP_TEXTBOX,
	__KEYMAP_COMBOBOX,
	__KEYMAP_CHECKBOX,
	__KEYMAP_PUSHBUTTON,
	__KEYMAP_DIALOG
};

const int __KEYMAP_TEXTBOX_BK[] = 
{
	Qt::Key_0,				//UIKEY_0
	Qt::Key_1,				//UIKEY_1
	Qt::Key_2,				//UIKEY_2
	Qt::Key_3,				//UIKEY_3
	Qt::Key_4,				//UIKEY_4
	Qt::Key_5,				//UIKEY_5
	Qt::Key_6,				//UIKEY_6
	Qt::Key_7,				//UIKEY_7
	Qt::Key_8,				//UIKEY_8
	Qt::Key_9,				//UIKEY_9
	Qt::Key_Backspace,		//UIKEY_MENU
	Qt::Key_Backtab,		//UIKEY_UP
	Qt::Key_Tab,			//UIKEY_DOWN
	Qt::Key_Enter,			//UIKEY_OK    
	Qt::Key_Escape,			//UIKEY_ESC
	Qt::Key_Control,		//UIKEY_POWER
};

static const int* __KEYMAP_BK[] = 
{
	__KEYMAP_TEXTBOX_BK,
	__KEYMAP_COMBOBOX,
	__KEYMAP_CHECKBOX,
	__KEYMAP_PUSHBUTTON,
	__KEYMAP_DIALOG
};

int uiKeyGetKey(int bPostKeyEvent)     
{

	int nKey = (int)GETKEY();
        switch(nKey)
        {
        case UIKEY_OK://13
            qDebug() << "keycode==ok"<<13;
            //OnKeyPressOk(nPopupMenuTitle);
            //this->hide();
            break;
        case UIKEY_MENU:
            qDebug() << "keycode==menu"<<19;
            //this->show();
            break;
        case UIKEY_UP://14
            qDebug() << "keycode==up"<<14;
            //OnKeyPressArrow(nKey,nPopupMenuTitle);
            break;
        case UIKEY_DOWN://15
            qDebug() << "keycode==down"<<15;
            //OnKeyPressArrow(nKey,nPopupMenuTitle);
            break;
        case UIKEY_ESC://UIKEY_ESC
            qDebug() << "keycode==esc"<<1;
            //goto _Exit;
            break;
        case UIKEY_2:
            qDebug() << "keycode==right"<<2;
            break;
        default:
            break;
        }

	if (nKey != UIKEY_NONE)
	{
                //if (g_MainWindow)
                        //uiLedKeyBackground(TRUE);
                //SETUP_TIMER(TIMER_KEYPAD_BACKGROUND, 15000, 0, NULL);
                uiTimeSetLastActionTime();

                //hiway del
                //if(dbSetupTotal.setSystem.bKeyTones)
                        //uiBuzzerKey();
		if (bPostKeyEvent)                
		    PostKeyEvent(nKey, NULL, bPostKeyEvent);   
	}	
	return nKey;
}

int uiKeyGetKeyLong(DWORD dwTimeout)
{
	int nKey = GETKEY(TRUE);

	dwTimeout = uiTimeGetTickCount() + dwTimeout;

	while (uiTimeGetTickCount() < dwTimeout)
	{
		if (nKey != GETKEY(TRUE))
			return UIKEY_NONE;
		uiTimeDelay(50);
	}
	return nKey;
}

BOOL uiKeyIsDigit(T_UI_KEY nKey)
{
	return (UIKEY_0 <= nKey && nKey <= UIKEY_9);
}

BOOL uiKeyIsPower(void)
{
	return ( (POWER_KEY() && !dbSetupTotal.setSystem.bPowerkeyLock) || g_uiPowerOffFlag);
}

//////////////////////////////////////////////////////////////////////////
int DetermineControlType(QObject *w)
{
	const char* __ctrl_list[] = {"QLineEdit", "QComboBox", "QCheckBox", "QPushButton", "QDialog"};

	for (int i=0; i<(int)ITEM_CNT(__ctrl_list); i++)
	{
		if (strcmp(((QObject*)w)->metaObject()->className(), __ctrl_list[i]) == 0)
			return i;
	}
	return CTRL_NONE;
}

void PostKeyEvent(int nKey, void *receiver, int bPostKeyEvent)  
{
	QWidget *w = (QWidget*)receiver;

	if (nKey == UIKEY_NONE)
		goto _lExit;
	
	if (!w)
		w = QApplication::focusWidget();

	if (w)
	{
		int ctrlType = DetermineControlType((QObject*)w);

		if (ctrlType != CTRL_NONE)
		{
			if(bPostKeyEvent == KEY_BK)
				 nKey = __KEYMAP_BK[ctrlType][nKey];
			else nKey = __KEYMAP[ctrlType][nKey]; 
		}
		else
		{
			goto _lExit;
		}

		if (ctrlType == CTRL_COMBOBOX)
		{
			QComboBox *wCombo = (QComboBox*)w;

			if (nKey == Qt::Key_Control)        
			{                              
				BOOL bResult;
				QStringList* pStringList = new QStringList();
				for(int i = 0; i<wCombo->count();i++)
				pStringList->append(wCombo->itemText(i));
				int nValue = uiProcBoxSelect(w,0,0, wCombo->width(), wCombo->height(), &bResult,wCombo->currentIndex(),0,wCombo->count()-1,pStringList,FALSE); 
				if(bResult)
				{
					wCombo->setCurrentIndex(nValue);
				}
				DELETE(pStringList);  
				goto _lExit;
			}  
		}   

		if (nKey == Qt::Key_Control && w->objectName().contains("useT9") == TRUE)      
		{
			w = w->parentWidget();
			if (!w)
				goto _lExit;

			QEvent *e = new QEvent(WM_T9INPUT);  
			QApplication::postEvent(w, e);       
			goto _lExit;
		}

	    if (ctrlType == CTRL_TEXTBOX && (nKey == Qt::Key_Backspace) ) 
		{
			if (w)
			{
				((QLineEdit*)w)->clear();
				((QLineEdit*)w)->setText("");
				goto _lExit;
			}
		}

		QString szString = ((nKey >= Qt::Key_0 && nKey <= Qt::Key_9) ? QString(nKey) : QString(0));
		QKeyEvent *keyEvent = new QKeyEvent(QEvent::KeyPress, nKey, Qt::NoModifier, szString);  
		QApplication::postEvent(w, keyEvent);    

		if (nKey != Qt::Key_Escape)
		{
			keyEvent = new QKeyEvent(QEvent::KeyRelease, nKey, Qt::NoModifier, QString(nKey));
			QApplication::postEvent(w, keyEvent);  
		}    
	}

_lExit:
	return;
}

//////////////////////////////////////////////////////////////////////////

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
void uiBuzzerOn(int nBuzzerType)
{
	switch(nBuzzerType)
	{
	case UI_BUZZER_OK:
		uiBuzzerOk();
		break;
	case UI_BUZZER_ERROR:
		uiBuzzerError();
		break;
	case UI_BUZZER_ALARM:
		uiBuzzerAlarm();
		break;
	case UI_BUZZER_BELL:
		uiBuzzerBell();
		break;
	case UI_BUZZER_ON:
		BUZZER_START();
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerOff(void)
{
	BUZZER_STOP();
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerOk(void)
{
	BUZZER_OK();
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerError(void)
{
	BUZZER_ERROR();
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerAlarm(void)
{
	BUZZER_ALARM_ASYNC();
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerKey(void)
{
	uiSoundOut(SOUND_KEYTONES, UI_BUZZER_ALARM);
//	uiBuzzerAlarm();
}

//////////////////////////////////////////////////////////////////////////
void uiBuzzerBell(void)
{
	BUZZER_BELL();
}

//////////////////////////////////////////////////////////////////////////
void uiSoundOut(int nSoundNumber, int nBuzzer, int nTimeout/* = 0*/, BOOL bFirstGUIProcess /*= FALSE*/)
{
    //hiway
/*	if (bFirstGUIProcess)
		POST_EVENTS();

	if (!dbSetupTotal.setSystem.bVoiceOut)
	{
		uiBuzzerOn(nBuzzer);
		return;
	}

	if (dbLicense.bUseMP3)
	{
		char *szMP3File = MP3_GetFileName(dbSetupTotal.setSystem.nLanguage, nSoundNumber);

		if (!FILE_EXIST(szMP3File))
			return;

		if((nSoundNumber >= SOUND_DIGIT0 && nSoundNumber <= SOUND_DIGIT9) ||
			(nSoundNumber == SOUND_CAMERA_TONE)	||
			(nSoundNumber == SOUND_KEYTONES)	||
			(nSoundNumber == SOUND_MENUSELECT)	||
			(nSoundNumber == SOUND_ENTERMENU)	||
			(nSoundNumber == SOUND_ERROR)		||
			(nSoundNumber == SOUND_QUESTION)	||
			(nSoundNumber == SOUND_OK)			||
			(nSoundNumber == SOUND_BELL1)		||
			(nSoundNumber == SOUND_BELL2)		||
			(nSoundNumber == SOUND_BELL3)		||
			(nSoundNumber == SOUND_BELL4)		||
			(nSoundNumber == SOUND_BELL5))
		{
			MP3_PLAY(szMP3File, nTimeout);
		}
		else
		{
			if (COPY_FILE(szMP3File, "/tmp/tmp.mp3"))
				MP3_PLAY("/tmp/tmp.mp3", nTimeout);
		}
	}
	else
	{
		if ((nSoundNumber == SOUND_BELL1) ||
			(nSoundNumber == SOUND_BELL2) ||
			(nSoundNumber == SOUND_BELL3) ||
			(nSoundNumber == SOUND_BELL4) ||
			(nSoundNumber == SOUND_BELL5))
			APLUS_SOUND_BELL();
		else if (nSoundNumber == SOUND_VERIFY_FAIL)
			APLUS_SOUND_PRESSNEW();
		else if (nSoundNumber == APLUS_OK)
			APLUS_SOUND_OK();
		else if (nSoundNumber == APLUS_REVERIFY)
			APLUS_SOUND_REVERIFY();
		else 
			uiBuzzerOn(nBuzzer);
        }*/
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiLedNormal()
{
	g_uiProcStatus.nLedCurrStatus = UI_LED_NORMAL;
}

void uiLedAbnormal()
{
	g_uiProcStatus.nLedCurrStatus = UI_LED_ABNORMAL;
}

void uiLedOK()
{
	if (g_uiProcStatus.nLedCurrStatus != UI_LED_NORMAL)
		return;
	g_uiProcStatus.nLedCurrStatus = UI_LED_SUCCESS;
	g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
	LED_G_ON();
	LED_R_OFF();
}

void uiLedFail()
{
	if (g_uiProcStatus.nLedCurrStatus != UI_LED_NORMAL)
		return;
	g_uiProcStatus.nLedCurrStatus = UI_LED_FAIL;
	g_uiProcStatus.dwTimeLedStart = uiTimeGetTickCount();
	LED_G_OFF();
	LED_R_ON();
}

void uiLedBusy()
{
	if (g_uiProcStatus.nLedCurrStatus != UI_LED_NORMAL)
		return;
	g_uiProcStatus.nLedCurrStatus = UI_LED_BUSY;
}

void uiLedOff()
{
	LED_R_OFF();
	LED_G_OFF();
}

void uiLedKeyBackground(BOOL bStatus)
{
	bStatus ? LED_K_ON() : LED_K_OFF();
}


/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiCMOSCheck(void)
{
	gbIsCMOS = gbIsCMOS && (SB_FP_CMOSINIT(dbSetupTotal.setNoMenu.dwMechanical, dbSetupTotal.setNoMenu.dwExpose) == FP_ERR_SUCCESS);

	if (!gbIsCMOS)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_CHECK_SENSOR, UITIME_OUT);
	}
}

BOOL uiCMOSCaptureFP(void)
{
	BOOL bRet = FALSE;
//	DWORD dwSTime = uiTimeGetTickCount();
//	return FALSE;
	if (!gbIsCMOS)
		return FALSE;
	
	PERF_CHECK((GetTickCount(TICKCOUNT_START)));
	
	bRet = (SB_FP_CAPTUREFINGER() == FP_ERR_SUCCESS);
	if (bRet)
	{
		xprintf("the send is press_fp\r\n");
		uiEventSend_PRESS_FP();//发送数据
		uiTimeSetLastActionTime();//设置时间
	}
	
	PERF_CHECK((g_dwPerfCaptureTime = GetTickCount(TICKCOUNT_STOP)));
	//printf("Capture: Result = %d, Elapsed=%dms\n", bRet, uiTimeGetTickCount() - dwSTime);
	
	return bRet;
}

BOOL uiCMOSIsPressFP(void)
{
	BOOL bRet;
	if (!gbIsCMOS)
		return FALSE;
	
	bRet = (SB_FP_ISPRESSFINGER() == FP_ERR_SUCCESS);
	if (bRet)
		uiTimeSetLastActionTime();
	
	return bRet;
}

BOOL uiCMOSAdjustBrightness(DWORD* pdwMechanical, DWORD* pdwExposure)
{
	BOOL bRet;
	if (!gbIsCMOS)
		return FALSE;
	
	fp_setlivecheck(FALSE);
	uiLcdProgressDlgShow(UISTR_MENU_ADVANCEDSETTING_BRIGHT_ADJUST); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_MENU_ADVANCEDSETTING_BRIGHT_ADJUST);
	uiLcdProgress(10);
	bRet = (SB_FP_CMOSCHECKADJUST(pdwMechanical, pdwExposure) == FP_ERR_SUCCESS);
	if (bRet)
		uiLcdProgress(100);
	uiLcdProgressDlgExit(); g_bProgress = FALSE;
// 	if (bRet)
// 	 	*pdwBrightness = engCmosInitResult->br_last;
	fp_setlivecheck(TRUE);
	return bRet;
}

BOOL uiCMOSPower(BOOL bPower)
{
	SB_FP_SENSORPOWER(bPower);
	if (bPower)
		uiCMOSCheck();

	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiDoorOpen(UINT64 nID)
{
	if(dbLicense.bLockControl)
	{
// 		if (dbSetupTotal.setNoMenu.byDoorStatus)
// 		{
// 			dbSetupTotal.setNoMenu.byDoorStatus = 2;
// 			DbSetupTotalWrite();
// 		}

		if (dbSetupTotal.setSystem.dwBindingID)
			LOCK_DOOR_CONTROL(T_LOCK_DOOR_OPEN);
		else
		{
			LockStatus(T_DOOR_UNLOCK);
//			SETUP_TIMER(TIMER_LOCK_RESTORE, dbSetupTotal.setSystem.nLockTime * 1000, 0, NULL);
		}
		if (uiAlarmStop(UI_ALARM_NOCLOSE))
			uiEventSend_ALARM_OFF(UI_ALARM_NOCLOSE, ALARMRELEASE_USER, nID);
		if (uiAlarmStop(UI_ALARM_ILGOPEN))
			uiEventSend_ALARM_OFF(UI_ALARM_ILGOPEN, ALARMRELEASE_USER, nID);
		if (uiAlarmStop(UI_ALARM_ILGVERIFY))
			uiEventSend_ALARM_OFF(UI_ALARM_ILGVERIFY, ALARMRELEASE_USER, nID);
		if (VERIFY_DURESS_AUTOSTOP())
			uiEventSend_ALARM_OFF(UI_ALARM_DURESS, ALARMRELEASE_USER, nID);
	}
}

void uiDoorClose()
{
	if (dbLicense.bLockControl)
	{
		if (!dbSetupTotal.setSystem.dwBindingID)
		{
			LockStatus(T_DOOR_CLOSE);
		}
	}
}

BOOL uiDoorSensorStatus()
{
	BOOL bStatus;

	if (dbSetupTotal.setSystem.dwBindingID)
		bStatus = LOCK_DOOR_STATUS();
	else
		bStatus = IsDoorOpened();
	return bStatus;
}

void uiLockProc(void)
{
	if(dbLicense.bLockControl)
	{
		if (dbSetupTotal.setSystem.dwBindingID)
		{
			if (TAMPER_IS_OFF())
			{
				if (uiAlarmStart(UI_ALARM_TAMPER))
					uiEventSend_ALARM_ON(UI_ALARM_TAMPER, 0);
			}
		}
		else
			LockProc();
	}
}

void uiWiegandSend(UINT64 nId)
{
	Wiegand_Send(0, (DWORD)dbSetupTotal.setSystem.nMachineID, (DWORD)nId);
}

//////////////////////////////////////////////////////////////////////////
//
//
BOOL uiPcCmdProc(BOOL bWorkingDisplay)
{
	g_uiCommandProc = FALSE;
	g_uiWorkingDisplay = bWorkingDisplay;
	
	hcProcMain();
	
	g_uiWorkingDisplay = FALSE;
	
	return g_uiCommandProc;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiFpEnrollStart(void)
{
	SB_FP_ENROLLSTART();
}

int uiFpEnrollNth(int nStep, int *pResult)
{
	int nRet;

	nRet = SB_FP_ENROLLNTH256(nStep);

	if (nRet == 0)
		nRet = UIENROLL_RET_TRUE;
	else if (nRet < 0)
		nRet = UIENROLL_RET_FALSE;
	else
	{
		if (pResult)
			*pResult = nRet - 1;
		nRet = UIENROLL_RET_DUPLICATE;
	}
	
	return nRet;
}

int uiFpEnrollEnd(FPINFO *pTemplate)
{
	if(SB_FP_ENROLLMERGE(pTemplate) == FP_ERR_SUCCESS)
		return UIENROLL_RET_TRUE;
	else
		return UIENROLL_RET_FALSE;
}

void uiFpEnrollDelete(UINT64 nID, int nFP)
{
	DbUserInfoDelete(nID, 0x01 << nFP);
}

BOOL uiFpVerifyO2N(FPINFO *pFP, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber)
{
	BOOL bRet = TRUE;
	int nPosFP, nPosUI;
//	DWORD dwSTime = uiTimeGetTickCount();

	*pbDisabled = FALSE;

	PERF_CHECK((GetTickCount(TICKCOUNT_START)));

	if (pFP)
		nPosFP = SB_FP_IDENTIFYFPDATA(pFP, pbAdapted);
	else
		nPosFP = SB_FP_IDENTIFYIMAGE256(pbAdapted);

	if (nPosFP < 0 || nPosFP >= dbLicense.nMaxEnrollCount)
	{
		PERF_CHECK((g_dwPerfVerifyFailureTime = GetTickCount(TICKCOUNT_STOP)));
		bRet = FALSE;
		goto _lExit;
	}

	PERF_CHECK((g_dwPerfVerifySuccessTime = GetTickCount(TICKCOUNT_STOP)));

	nPosUI = FP_GET_UIPOS(&gpFingerEnrollData[nPosFP]);
	memcpy(pUserInfo, &gpUserInfoEnrollData[nPosUI], sizeof(USER_INFO));
	*pbFingerNumber = gpFingerEnrollData[nPosFP].wParam;

	if (*pbAdapted)
	{
	 /*
		if(!DbFpSaveOne(nPosFP))
		{
			bRet = FALSE;
			goto _lExit;
		}
		*/
		DbFpSaveOne(nPosFP);
	}

	if (!DbUserInfoIsAble(nPosUI))
	{
		*pbDisabled = UI_DISABLED;
		bRet = FALSE;
	}

_lExit:
//	printf("Verfiy Time: Result=%d, Elapsed=%dms\n", bRet, uiTimeGetTickCount() - dwSTime);

	return bRet;
}

BOOL uiFpVerifyByMaster(FPINFO *pFP, USER_INFO *pUserInfo, BOOL *pbDisabled, BOOL *pbAdapted, BYTE *pbFingerNumber)
{
	BOOL bRet = TRUE;
	FPINFO TEMPLATE;
	if (pFP)
		memcpy(&TEMPLATE, pFP, sizeof(FPINFO));
	else
		bRet = (SB_FP_PROCESSIMAGE256(&TEMPLATE) == FP_ERR_SUCCESS);
	bRet = bRet && Com_AntipassSend(UI_VERIFY_FP, &TEMPLATE, pUserInfo, pbDisabled, pbAdapted, pbFingerNumber);
	return bRet;
}

BOOL uiFpVerifyO2O(FPINFO *pFP, UINT64 nID, BOOL *pbAdapted, BYTE *pbFingerNumber)
{
	BOOL bRet = FALSE;
	int nPosFP, nPosUI;
	FPINFO FP;
//	DWORD dwSTime = uiTimeGetTickCount();

	nPosUI = DbUserInfoGetPosition(nID);
	if (nPosUI == dbLicense.nMaxEnrollCount)
		return FALSE;

	if (!pFP)
	{
		pFP = &FP;
		SB_FP_PROCESSIMAGE256(pFP);
	}

	for (int i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
	{
		nPosFP = DbFpGetPosition(nPosUI, i);
		if (nPosFP < 0 || nPosFP >= dbLicense.nMaxEnrollCount)
			continue;
		if (SB_FP_VERIFYFPDATA(pFP, nPosFP, pbAdapted) == FP_ERR_SUCCESS)
		{
			if (*pbAdapted && DbFpSaveOne(nPosFP))
			{
				*pbFingerNumber = i;
				bRet = TRUE;
			}
			break;
		}
	}

	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
DWORD uiCardCapture(void)
{
	DWORD dwID = 0;

	if (!dbLicense.bUseCard)
		goto _lExit;

	if(Wiegand_Read(&dwID) == 0)
	{
// 		if (dbSetupTotal.setSystem.bAntipassUse)
// 		{
// 			uiLogGlogAdd(Wiegand_GetUserID(dwID), VM_RF, 0, TRUE);
// 			return 0;
// 		}
		uiBuzzerKey();
		uiTimeSetLastActionTime();
	}
	else if (g_uiProcStatus.bExistRFMod && (dwID = RFMOD_READ()))
	{
		uiBuzzerKey();
		uiTimeSetLastActionTime();
	}
	else
	{
		dwID = 0;
	}

_lExit:
	return dwID;
}

BOOL uiCardEnroll(USER_INFO *pUserInfo, DWORD dwCardNumber)
{
	return DbUserInfoEnroll(pUserInfo, BACKUP_CARD, &dwCardNumber);
}

void uiCardEnrollDelete(UINT64 nID)
{
	DbUserInfoDelete(nID, 0x01 << BACKUP_CARD);
}

BOOL uiCardVerify(DWORD dwCardNumber, USER_INFO *pUserInfo, BYTE *pbDisabled)
{
	int nPosUI;
	BOOL bRet = TRUE;

	*pbDisabled = FALSE;

	nPosUI = DbUserInfoCardVerify(dwCardNumber);
	if (nPosUI < 0 || nPosUI >= dbLicense.nMaxEnrollCount)
	{
		bRet = FALSE;
		goto _lExit;
	}

	if (!DbUserInfoIsAble(nPosUI))
	{
		*pbDisabled = UI_DISABLED;
		bRet = FALSE;
		goto _lExit;
	}

	memcpy(pUserInfo, &gpUserInfoEnrollData[nPosUI], sizeof(USER_INFO));

_lExit:
	return bRet;
}

BOOL uiCardVerifyByMaster(DWORD dwCardNumber, USER_INFO *pUserInfo, BYTE *pbDisabled)
{
	return Com_AntipassSend(UI_VERIFY_RF, &dwCardNumber, pUserInfo, pbDisabled, NULL, NULL);
}

void uiCardCaptureInit(void)
{
	DWORD dwID = 0;
	Wiegand_Read(&dwID);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL uiPwdEnroll(USER_INFO *pUserInfo, char* pcPwd)
{
	DWORD dwPassword = STRING2PWD(pcPwd);
	return DbUserInfoEnroll(pUserInfo, BACKUP_PASSWORD, &dwPassword);  
}

void uiPwdEnrollDelete(UINT64 nID)
{
	DbUserInfoDelete(nID, 0x01 << BACKUP_PASSWORD);
}

BOOL uiPwdVerify(UINT64 nID, char* pcPwd, USER_INFO *pUserInfo, BYTE *pbDisabled)
{
	int nPosUI;
	BOOL bRet = TRUE;

	*pbDisabled = FALSE;
	
	nPosUI = DbUserInfoPwdVerify(nID, STRING2PWD(pcPwd));
	if (nPosUI < 0 || nPosUI >= dbLicense.nMaxEnrollCount)
	{
		bRet = FALSE;
		goto _lExit;
	}

	if (!DbUserInfoIsAble(nPosUI))
	{
		*pbDisabled = UI_DISABLED;
		bRet = FALSE;
		goto _lExit;
	}
	
	memcpy(pUserInfo, &gpUserInfoEnrollData[nPosUI], sizeof(USER_INFO));

_lExit:
	return bRet;
}

BOOL uiIDVerify(UINT64 nID, USER_INFO *pUserInfo, BYTE *pbDisabled)
{
	int nPosUI;
	BOOL bRet = TRUE;

	*pbDisabled = FALSE;

	nPosUI = DbUserInfoGetPosition(nID);
	if (nPosUI == dbLicense.nMaxEnrollCount)
	{
		bRet = FALSE;
		goto _lExit;
	}

	if (!DbUserInfoIsAble(nPosUI))
	{
		*pbDisabled = UI_DISABLED;
		bRet = FALSE;
		goto _lExit;
	}

	memcpy(pUserInfo, &gpUserInfoEnrollData[nPosUI], sizeof(USER_INFO));

_lExit:
	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiLogSlogAdd(UINT64 nManagerID, BYTE byAction, UINT64 nUserID, BYTE byResult)
{
	MLOG_INFO mLog;

	memset(&mLog, 0, sizeof(MLOG_INFO));
	mLog.dwSeconds = uiRtcGetSeconds();
	mLog.nManagerID = nManagerID;
	mLog.byAction = byAction;
	mLog.nUserID = nUserID;
	mLog.byResult = byResult;
	DbSLogAdd(&mLog);

	if (dbSetupTotal.setSystem.nMLogWarning)
	{
		if (dbLicense.nSlogMaxCount - 1 - DbSLogCount() < dbSetupTotal.setSystem.nMLogWarning)
		{
			uiAlarmStart(UI_ALARM_LOGOVERFLOW);
			uiEventSend_ALARM_ON(UI_ALARM_LOGOVERFLOW, 0);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SLOG_OVERFLOW, LOGOUT_ALARM_TIMEOUT);
			uiAlarmStop(UI_ALARM_LOGOVERFLOW);
		//	SETUP_TIMER(TIMER_LOGOUT_ALARM, LOGOUT_ALARM_TIMEOUT, 1, NULL);
		}
	}
	DbSLogGet(&mLog, DbSLogGetReadPos(), 1);  
	//uiEventSend_SLOG(&mLog);//这里也有发送
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
void uiLogSlogAdd2(UINT64 nManagerID, BYTE byAction, UINT64 nUserID, BYTE byResult)
{
	MLOG_INFO mLog;

	memset(&mLog, 0, sizeof(MLOG_INFO));
	mLog.dwSeconds = uiRtcGetSeconds();
	mLog.nManagerID = nManagerID;
	mLog.byAction = byAction;
	mLog.nUserID = nUserID;
	mLog.byResult = byResult;
	DbSLogAdd(&mLog);

	if (dbSetupTotal.setSystem.nMLogWarning)
	{
		if (dbLicense.nSlogMaxCount - 1 - DbSLogCount() < dbSetupTotal.setSystem.nMLogWarning)
		{
			uiAlarmStart(UI_ALARM_LOGOVERFLOW);
			uiEventSend_ALARM_ON(UI_ALARM_LOGOVERFLOW, 0);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SLOG_OVERFLOW, LOGOUT_ALARM_TIMEOUT);
			uiAlarmStop(UI_ALARM_LOGOVERFLOW);
		//	SETUP_TIMER(TIMER_LOGOUT_ALARM, LOGOUT_ALARM_TIMEOUT, 1, NULL);
		}
	}
	//uiEventSend_SLOG(&mLog);
}

int uiLogSlogGetCountPerMgr(UINT64/* nIDMgr*/)
{
// 	int nRet = 0, i, nMax = dbSetupTotal.setLog.nSLogPos;
// 
// 	if (nIDMgr == 0)
// 		return (nMax - dbSetupTotal.setNoMenu.nReadMLogPos);
// 
// 	for (i=dbSetupTotal.setNoMenu.nReadMLogPos;i<nMax;i++)
// 	{
// 		if(gpMLogs[i].nManagerID == nIDMgr)
// 			nRet++;
// 	}
// 
// 	return nRet;
	return 0;
}

extern BOOL http_WEB_CONNECT;
//////////////////////////////////////////////////////////////////////////
void uiLogGlogAdd(UINT64 nID, BYTE byAction, BYTE byTrStatus, BOOL bAntipassOut)
{
	ALOG_INFO gLog;

	gLog.dwSeconds = uiRtcGetSeconds();
	gLog.nID = nID;
	gLog.byAction = byAction;
	gLog.byTrStatus = byTrStatus;
	gLog.bAntipassOut = bAntipassOut;
	
	DbGLogAdd(&gLog);

	if (dbSetupTotal.setSystem.nGLogWarning)
	{
		if (dbLicense.nGlogMaxCount - 1 - DbGLogCount() < dbSetupTotal.setSystem.nGLogWarning)
		{
			uiAlarmStart(UI_ALARM_LOGOVERFLOW);
			uiEventSend_ALARM_ON(UI_ALARM_LOGOVERFLOW, 0);
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_GLOG_OVERFLOW, LOGOUT_ALARM_TIMEOUT);
			uiAlarmStop(UI_ALARM_LOGOVERFLOW);
			//SETUP_TIMER(TIMER_LOGOUT_ALARM, LOGOUT_ALARM_TIMEOUT, 0, NULL);
		}
	}
	
	//原先是存在的
	//DbGLogGet(&gLog, DbGLogGetReadPos(), 1); 
	DM9000_Check();
	//确认tcp/ip连上并且服务端有回应才发送
	if(http_WEB_CONNECT == TRUE && tcpclient_connect_isok()==1)
	{
		//首先判断机器中是否有断网时保存的没有上传的
		//然后再决定是否上传
	   xprintf("DbGLogCount()==%d\r\n",DbGLogCount());	
	   if((DbGLogCount() - 1) == 0)
	   {
		if(web2_send_glog(&gLog))//发送成功后在把数据加入
		{
			
			//web2_recv_data(1000);//add by loveywm 2013.02.21
			xprintf("@@@@@@@@@@@@@@@@\r\n");
			
		}
		else
		{
			xprintf("$$$$$$$$$$$$$$$$$$$$$$\r\n");
		}
	   }
	}	

	//uiEventSend_GLOG(&gLog);//注意这里
	
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
BOOL uiSL811_IsExist(void)
{
	return TRUE;
}

BOOL uiSL811_IsDetected(void)
{
	int  i;
	char szUsbDevices[6][5] = {"sda0", "sda1", "sdb0", "sdb1", "sdc0", "sdc1"};
	char szCommandLine[64];
	BOOL bRet = FALSE;

	i = 0;
	while (!bRet && i < 6)
	{
		sprintf(szCommandLine, "/dev/%s", szUsbDevices[i]);
		bRet = (mount(szCommandLine, USB_MOUNTPOINT, "vfat", 0, NULL) == 0);
		i++;
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
void uiSL811_Remove(void)
{
	umount(USB_MOUNTPOINT);
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_ReadFileBinary(HFILE *pFile, void* pBuffer, int nSize)
{
	if (!*pFile || *pFile == INVALID_HANDLE_VALUE)
		return FALSE;
	return (read(*pFile, pBuffer, nSize) == nSize);
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_WriteFileBinary(HFILE *pFile, void* pBuffer, int nSize)
{
	if (!*pFile || *pFile == INVALID_HANDLE_VALUE)
		return FALSE;
	return (write(*pFile, pBuffer, nSize) == nSize);
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_WriteFilePrintf(HFILE *pFile, char *fmt, ...)
{
	va_list vl;
	char szBuf[128];

	if (!pFile || *pFile == INVALID_HANDLE_VALUE)
		return FALSE;

	va_start(vl, fmt);
	vsprintf(szBuf, fmt, vl);
	va_end(vl);

	return (write(*pFile, szBuf, strlen(szBuf)) == (int)strlen(szBuf));
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadGlogInternal(const char* szFilePrefix, int nStartPos, BOOL* pbEmpty)  
{
	BOOL bRet = TRUE;
	int i, nCount;
	char strFileName[64];
	QFile f;
	ALOG_INFO *pLogBuffer = NULL;
	DWORD dwMagic = MAGIC_GLOG;

	char buf[100]; 

/*
	if (FREE_SPACE(USB_MOUNTPOINT) < (int)DWORD_ALIGN(4 + dbLicense.nGlogMaxCount * sizeof(ALOG_INFO)))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_USB_ISFULL, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
	*/

	sprintf(strFileName, "%s/%s_%03d.txt", USB_MOUNTPOINT, szFilePrefix, dbSetupTotal.setSystem.nMachineID);  //xf 090818

	f.setFileName(strFileName);

	*pbEmpty = FALSE;

// 	if (nStartPos == DbGLogPos())
// 	{
// 		*pbEmpty = TRUE;
// 		bRet = FALSE;
// 		goto _lExit;
// 	}

	if (!f.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		bRet = FALSE;
		goto _lExit;
	}

	pLogBuffer = (ALOG_INFO*)malloc(dbLicense.nGlogMaxCount * sizeof(ALOG_INFO));
	if (!pLogBuffer)
	{
		bRet = FALSE;
		goto _lExit;
	}

   	nCount = DbGLogGet(pLogBuffer, nStartPos, DbGLogCountAll() - nStartPos); 

	if (nCount)
	{
		memset(buf, 0, sizeof(buf));
		strcpy(buf, "CPNo\t" "TMNo\t" "EnNo\t" "Name\t\t" "GMNo\t" "Mode\t" "DateTime\r\n");

        if (f.write(buf, strlen(buf)) != strlen(buf))
		{
			bRet = FALSE;
			goto _lExit;
		}

        for (i=0; i<nCount; i++)
		{
	        memset(buf, 0, sizeof(buf));
            sprintf(buf, "%d\t%d\t%d\t \t\t%d\t%d\t%s\r\n", 
				   i+1,
				   dbSetupTotal.setSystem.nMachineID,
 					(DWORD)pLogBuffer[i].nID,
				//	" ",
					dbSetupTotal.setSystem.nMachineID,
 					pLogBuffer[i].byAction,
					uiRtcSeconds2LogStringForDownload(pLogBuffer[i].dwSeconds));
		
			if (f.write(buf, strlen(buf)) != strlen(buf))
			{
				bRet = FALSE;
				goto _lExit;
			}
		}   
	}
	else
	{
		*pbEmpty = TRUE;
		bRet = FALSE;
	}

_lExit:
	FREE(pLogBuffer);
	f.close();

	uiSL811_Remove();

	if (!bRet)
		return FALSE;

	uiLcdProgress(100);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadGlog(BOOL* pbEmpty)
{
	BOOL bRet = TRUE;
	if(!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	if (!DbGLogCountAll())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_NOLOG, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	uiLcdProgressDlgShow(UISTR_MENU_GLOGDOWNLOAD); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);
	
    if (!uiSL811_DownloadGlogInternal("GLG", DbGLogGetReadPos(), pbEmpty))  
	{
		uiLcdMessageBox(UI_MSG_ERROR, *pbEmpty ? UISTR_STATUS_NOLOG : UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
		bRet = FALSE;
	}
	else
	{
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	}
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

//	DbGLogSetReadPos(DbGLogPos());  
	DbGLogSetReadPos(DbGLogCountAll() % dbLicense.nGlogMaxCount); 
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadAllGlog(BOOL* pbEmpty)
{
	BOOL bRet = TRUE;
	if(!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	if (!DbGLogCountAll())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_NOLOG, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	uiLcdProgressDlgShow(UISTR_MENU_ALLGLOGDOWNLOAD); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);
	
	if (!uiSL811_DownloadGlogInternal("AGL", 0, pbEmpty))
	{
		uiLcdMessageBox(UI_MSG_ERROR, *pbEmpty ? UISTR_STATUS_NOLOG : UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
		bRet = FALSE;
	}
	else
	{
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	}
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

//	DbGLogSetReadPos(DbGLogPos());  
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadSlogInternal(const char* szFilePrefix, int nStartPos, BOOL* pbEmpty)  
{
	BOOL bRet = TRUE;
	int i, nCount = 0;
	char strFileName[64];
	QFile f;
	MLOG_INFO *pLogBuffer = NULL;
	DWORD dwMagic = MAGIC_SLOG;
	char buf[100]; 

/*
	if (FREE_SPACE(USB_MOUNTPOINT) < (int)DWORD_ALIGN(4 + dbLicense.nSlogMaxCount * sizeof(MLOG_INFO)))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_USB_ISFULL, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
	*/

	sprintf(strFileName, "%s/%s_%03d.txt", USB_MOUNTPOINT, szFilePrefix, dbSetupTotal.setSystem.nMachineID);  //xf 090818
	f.setFileName(strFileName);

	*pbEmpty = FALSE;

// 	if (nStartPos == DbSLogPos())
// 	{
// 		*pbEmpty = TRUE;
// 		bRet = FALSE;
// 		goto _lExit;
// 	}

	if (!f.open(QIODevice::ReadWrite | QIODevice::Truncate))
	{
		bRet = FALSE;
		goto _lExit;
	}

	pLogBuffer = (MLOG_INFO*)malloc(dbLicense.nSlogMaxCount * sizeof(MLOG_INFO));
	if (!pLogBuffer)
	{
		bRet = FALSE;
		goto _lExit;
	}

    nCount = DbSLogGet(pLogBuffer, nStartPos, DbSLogCountAll() - nStartPos);  

	if (nCount)  
	{
		memset(buf, 0, sizeof(buf));
		strcpy(buf, "CPNo\t" "TMNo\t" "SEnNo\t" "SMNo\t" "GEnNo\t" "GMNo\t" "Mani\t" "FpNo\t" "DateTime\r\n");

        if (f.write(buf, strlen(buf)) != strlen(buf))
		{
			bRet = FALSE;
			goto _lExit;
		}

        for (i=0; i<nCount; i++)
		{
            memset(buf, 0, sizeof(buf));
		    sprintf(buf, "%d\t%d\t%d\t%d\t%d\t%d\t%d\t%d\t%s\r\n",
				     i+1,
					 dbSetupTotal.setSystem.nMachineID,
 					 (DWORD)pLogBuffer[i].nManagerID,
					 dbSetupTotal.setSystem.nMachineID,
 					 (DWORD)pLogBuffer[i].nUserID,
					 dbSetupTotal.setSystem.nMachineID,
 				//	 UISTR(UISTR_SLOG_START + pLogBuffer[i].byAction),
				     pLogBuffer[i].byAction,
 					 pLogBuffer[i].byResult,
 					 uiRtcSeconds2LogStringForDownload(pLogBuffer[i].dwSeconds));  
		
			if (f.write(buf, strlen(buf)) != strlen(buf))
			{
				bRet = FALSE;
				goto _lExit;
			}
		} 
	}
	else
	{
		*pbEmpty = TRUE;
		bRet = FALSE;
	}   

_lExit:
	FREE(pLogBuffer);
	f.close();

	uiSL811_Remove();

	if (!bRet)
		return FALSE;

	uiLcdProgress(100);

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadSlog(BOOL* pbEmpty)
{
	BOOL bRet = TRUE;

	if(!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	if (!DbSLogCountAll())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_NOLOG, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}
	
	uiLcdProgressDlgShow(UISTR_MENU_MLOGDOWNLOAD); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

    if (!uiSL811_DownloadSlogInternal("SLG", DbSLogGetReadPos(), pbEmpty))  
	{
		uiLcdMessageBox(UI_MSG_ERROR, *pbEmpty ? UISTR_STATUS_NOLOG : UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
		bRet = FALSE;
	}
	else
	{
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	}
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

//	DbSLogSetReadPos(DbSLogPos());  
	DbSLogSetReadPos(DbSLogCountAll() % dbLicense.nSlogMaxCount); 
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
BOOL uiSL811_DownloadAllSlog(BOOL* pbEmpty)
{
	BOOL bRet = TRUE;

	if(!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}

	if (!DbSLogCountAll())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_NOLOG, UI_MSGTIMEOUT);
		uiSL811_Remove();
		return FALSE;
	}
	
	uiLcdProgressDlgShow(UISTR_MENU_ALLMLOGDOWNLOAD); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_WAIT_FOR_COMMUNICATING);

	if (!uiSL811_DownloadSlogInternal("ASL", 0, pbEmpty))
	{
		uiLcdMessageBox(UI_MSG_ERROR, *pbEmpty ? UISTR_STATUS_NOLOG : UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
		bRet = FALSE;
	}
	else
	{
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	}   

	uiLcdProgressDlgExit(); g_bProgress = FALSE;

//	DbSLogSetReadPos(DbSLogPos());  
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
int uiSL811_VoiceAndPhotoSize(void)
{
	int i;
	int nSize = 0;
	char *szVoiceFile;
	char *szPhotoFile;

	if (!SDCARD_MOUNT())
		return nSize;

	for (i=0; i<dbLicense.nMaxEnrollCount; i++)
	{
		if (!gpUserInfoEnrollData[i].ID)
			continue;
		szVoiceFile = DbUserInfoGetVoiceFilename(gpUserInfoEnrollData[i].ID);
		nSize += FILE_SIZE(szVoiceFile);
		szPhotoFile = DbUserInfoGetPhotoFilename(gpUserInfoEnrollData[i].ID);
		nSize += FILE_SIZE(szPhotoFile);
	}
	return nSize;
}

BOOL uiSL811_DownloadAllEnroll(void)
{
	xprintf("1\r\n");
	char strFileName[64];
	HFILE fi = INVALID_HANDLE_VALUE;
	BOOL bRet = TRUE;
	DWORD dwMagic = MAGIC_ENROLLDB;
	T_ENROLLDB_HDR hdr;
	int nOffset = 0;
	int i;
	char *strTemp = NULL;

	hdr.dwUIIndexSize  = FLASH_UI_INDEX_SIZE;
	hdr.dwFPIndexSize  = dbLicense.nMaxEnrollCount;
	hdr.dwUserInfoSize = dbLicense.nMaxEnrollCount * sizeof(USER_INFO);
	hdr.dwFPSize       = dbLicense.nMaxEnrollCount * sizeof(FPINFO);
	xprintf("4\r\n");
	if (!uiSL811_IsDetected())
	{
		xprintf("3\r\n");
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
	xprintf("5\r\n");
	if (!Db_GetUserCount())
	{
		xprintf("6\r\n");
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

/*
	if (FREE_SPACE(USB_MOUNTPOINT) < 
		(int)DWORD_ALIGN(4 + hdr.dwUIIndexSize + hdr.dwFPIndexSize + hdr.dwUserInfoSize + hdr.dwFPSize + uiSL811_VoiceAndPhotoSize()))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_USB_ISFULL, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
*/
	xprintf("7\r\n");
	uiLcdProgressDlgShow(UISTR_MENU_USERINFODOWNLOAD); 
	g_bProgress = TRUE;
	xprintf("20\r\n");
	strcpy(strFileName, USB_MOUNTPOINT "/" DB_ENROLLDATA_FILENAME ".dat");
	xprintf("21\r\n");
	xprintf("strFileName===%s\r\n",strFileName);
	fi = open(strFileName, O_CREAT |O_RDWR| O_TRUNC,777);
	if (fi == INVALID_HANDLE_VALUE)
	{
		xprintf("22\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	xprintf("23\r\n");
	xprintf("dwMagic/d===%d\r\n",dwMagic);
	xprintf("dwMagic/x===%x\r\n",dwMagic);

	struct stat ywm;
        int loveywm;
        loveywm = stat(strFileName,&ywm);
	if(loveywm != 0)
	{
		xprintf("the stat is wrong\r\n");
	}
        xprintf("%s file size =%d\r\n",strFileName,ywm.st_size);
        xprintf("%s file mode =%d\r\n",strFileName,ywm.st_mode);
	
	
	if (write(fi, &dwMagic, 4) != 4)
	{

		xprintf("24\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	xprintf("40\r\n");
	nOffset += 4;
	xprintf("25\r\n");
	if (write(fi, &hdr, sizeof(hdr)) != sizeof(hdr))
	{
		xprintf("26\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	nOffset += sizeof(hdr);

	if (write(fi, gpUIIndexData, FLASH_UI_INDEX_SIZE) != FLASH_UI_INDEX_SIZE)
	{
		xprintf("27\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	nOffset += hdr.dwUIIndexSize;

	if (write(fi, gpIndexData, dbLicense.nMaxEnrollCount) != dbLicense.nMaxEnrollCount)
	{
		xprintf("28\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	nOffset += hdr.dwFPIndexSize;
	xprintf("8\r\n");
	if (!_Db_FlashWrite(fi, gpUserInfoEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_INFO), NULL, nOffset))
	{
		xprintf("9\r\n");
		bRet = FALSE;
		goto labelLast001;
	}
	nOffset += hdr.dwUserInfoSize;

	if (!_Db_FlashWrite(fi, gpFingerEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(FPINFO), NULL, nOffset))
	{
		bRet = FALSE;
		goto labelLast001;
	}
	nOffset += hdr.dwFPSize;

	FD_CLOSE(fi);
	xprintf("10\r\n");
	if (Db_GetUserVoiceCount() > 0)
	{
		xprintf("11\r\n");
		uiLcdProgressStart(UISTR_STATUS_VOICE_DOWNLOAD);
		RMDIR(USB_MOUNTPOINT PATH_USER_VOICE);
		if (MKDIR(USB_MOUNTPOINT PATH_USER_VOICE))
		{
			for (i=0; i<dbLicense.nMaxEnrollCount; i++)
			{
				if (!gpUserInfoEnrollData[i].ID)
					continue;
				strTemp = DbUserInfoGetVoiceFilename(gpUserInfoEnrollData[i].ID);
				if (FILE_EXIST(strTemp))
					QFile::copy(strTemp, QString(strTemp).replace(SDCARD_MOUNTPOINT, USB_MOUNTPOINT));
				uiLcdProgress(LCDPROG_PERCENT(i, dbLicense.nMaxEnrollCount));
			}
		}
		uiLcdProgressEnd();
	}

	if (Db_GetUserPhotoCount() > 0)
	{
		uiLcdProgressStart(UISTR_STATUS_PHOTO_DOWNLOAD);
		RMDIR(USB_MOUNTPOINT PATH_USER_PHOTO);
		if (MKDIR(USB_MOUNTPOINT PATH_USER_PHOTO))
		{
			for (i=0; i<dbLicense.nMaxEnrollCount; i++)
			{
				if (!gpUserInfoEnrollData[i].ID)
					continue;
				strTemp = DbUserInfoGetPhotoFilename(gpUserInfoEnrollData[i].ID);
				if (FILE_EXIST(strTemp))
					QFile::copy(strTemp, QString(strTemp).replace(SDCARD_MOUNTPOINT, USB_MOUNTPOINT));
				uiLcdProgress(LCDPROG_PERCENT(i, dbLicense.nMaxEnrollCount));
			}
		}
		uiLcdProgressEnd();
	}

labelLast001:
xprintf("12\r\n");
	FD_CLOSE(fi);
	uiSL811_Remove();

	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	if (bRet)
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	else
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);

_lExit:
	xprintf("13\r\n");
	uiSL811_Remove();
	return bRet;
}

BOOL uiSL811_UploadAllEnroll(void)
{
	char strFileName[64];
	HFILE fi = INVALID_HANDLE_VALUE;
	BOOL bRet = TRUE;
	DWORD dwMagic;
	T_ENROLLDB_HDR hdr;
	int nIndexDBChanged;
	int nOffset = 0;

	if (!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
	strcpy(strFileName, USB_MOUNTPOINT "/" DB_ENROLLDATA_FILENAME ".dat");
	fi = open(strFileName, O_RDONLY);
	if (fi == INVALID_HANDLE_VALUE)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_NO_FILES, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
	{
		bRet = FALSE;
		goto _lExit;
	}

	uiLcdProgressDlgShow(UISTR_MENU_USERINFOUPLOAD); g_bProgress = TRUE;

	if (read(fi, &dwMagic, 4) != 4 || dwMagic != MAGIC_ENROLLDB)
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += 4;

	if (read(fi, &hdr, sizeof(hdr)) != sizeof(hdr) ||
		hdr.dwUIIndexSize != FLASH_UI_INDEX_SIZE ||
		hdr.dwFPIndexSize != (DWORD)dbLicense.nMaxEnrollCount ||
		hdr.dwUserInfoSize != dbLicense.nMaxEnrollCount * sizeof(USER_INFO) ||
		hdr.dwFPSize != dbLicense.nMaxEnrollCount * sizeof(FPINFO))
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += sizeof(hdr);

	Db_DeleteAllEnrollData();

	if (read(fi, gpUIIndexData, FLASH_UI_INDEX_SIZE) != FLASH_UI_INDEX_SIZE)
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += hdr.dwUIIndexSize;

	if (read(fi, gpIndexData, dbLicense.nMaxEnrollCount) != dbLicense.nMaxEnrollCount)
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += hdr.dwFPIndexSize;

	if (!_Db_FlashRead(fi, gpUserInfoEnrollData, 0, dbLicense.nMaxEnrollCount, sizeof(USER_INFO), 0, NULL, NULL, nOffset))
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += hdr.dwUserInfoSize;

	if (!_Db_ReadFpDataFromFlash(fi, gpFingerEnrollData, 0, dbLicense.nMaxEnrollCount, 0, &nIndexDBChanged, nOffset))
	{
		bRet = FALSE;
		goto labelLast101;
	}
	nOffset += hdr.dwFPSize;

	DbFpSave();
	DbFPIndexSave();
	DbUserInfoSave();
	DbUIIndexSave();

labelLast101:;
	if (bRet)
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	else
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);

	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	if (!bRet)
		Db_LoadAllData(TRUE);

_lExit:
	FD_CLOSE(fi);
	uiSL811_Remove();
	return bRet;
}

BOOL uiSL811_MsgUpload(void)
{
	BOOL bRet = TRUE;
	DWORD dwMagic;
	char strFileName[64];
	HFILE fi = INVALID_HANDLE_VALUE;
	MSG_INFO msg[MSG_INFO_COUNT];
	int nFileSize;

	if (!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit1;
	}
	sprintf(strFileName, "%s/SMSG.dat", USB_MOUNTPOINT);
	fi = open(strFileName, O_RDONLY);
	if (fi == INVALID_HANDLE_VALUE)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_NO_FILES, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit1;
	}

	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
	{
		bRet = FALSE;
		goto _lExit1;
	}

	ioctl(fi, FIONREAD, &nFileSize);

	if (!uiSL811_ReadFileBinary(&fi, &dwMagic, 4) || dwMagic != MAGIC_SMSG)
	{
		bRet = FALSE;
		goto _lExit;
	}

	nFileSize -= 4;
	nFileSize = nFileSize / sizeof(MSG_INFO) * sizeof(MSG_INFO);
	memset(msg, 0, sizeof(msg));
	if (!uiSL811_ReadFileBinary(&fi, &msg[0], nFileSize))
	{
		bRet = FALSE;
		goto _lExit;
	}

	memcpy(&dbSetupTotal.setTimezone.tzMsg[0], &msg[0], nFileSize);
	memcpy(&dbSetupTimezoneNew.tzMsg[0], &dbSetupTotal.setTimezone.tzMsg[0], sizeof(MSG_INFO) * MSG_INFO_COUNT);
	DbSetupTotalWrite();

_lExit:
	if (bRet)
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	else
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);

_lExit1:
	FD_CLOSE(fi);
	uiSL811_Remove();
	return bRet;
}

BOOL uiSL811_MP3Upload(void)
{
	BOOL bRet = TRUE;

	if (!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	DIALOGBOX(CMp3Upload);

_lExit:
	uiSL811_Remove();
	return bRet;
}

BOOL uiSL811_FirmwareUpgrade(void)
{
	BOOL bRet = TRUE;
	
	if (!uiSL811_IsDetected())
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_UDISK_NOTFOUND, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}
// 	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
// 		goto _lExit;

	DIALOGBOX(CSystemUpgrade);

_lExit:
	uiSL811_Remove();
	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int uiGetCurrentTR()
{
	DB_TIMESECTION_A *tz;
	DWORD dwCurrentTime = g_uiProcStatus.dwCurrentSecond % (24 * 3600);
	DWORD dwFrom, dwTo;

	for (int i=0; i<(int)ITEM_CNT(dbSetupTotal.setTimezone.tzTr); i++)
	{
		tz = &dbSetupTotal.setTimezone.tzTr[i].RANGE;
		dwFrom = tz->bStartHour * 3600 + tz->bStartMinute * 60;
		dwTo = tz->bEndHour * 3600 + tz->bEndMinute * 60 + 59;
		if (dwFrom <= dwCurrentTime && dwCurrentTime <= dwTo)
			return (int)(dbSetupTotal.setTimezone.tzTr[i].STATUS);
	}
	return -1;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int uiBellGetStatus()
{
	static BOOL __BELL_TRIGER[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	DB_TIMESECTION_A tz;

	uiRtcSeconds2YMDHMS(uiRtcGetSeconds(), &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);

	for (int i=0; i<(int)ITEM_CNT(dbSetupTotal.setTimezone.tzBell); i++)
	{
		tz = dbSetupTotal.setTimezone.tzBell[i].RANGE;
		if (tz.bStartHour == nHour && tz.bStartMinute == nMinute)
		{
			if (!__BELL_TRIGER[i])
			{
				__BELL_TRIGER[i] = TRUE;
				return i;
			}
		}
		else
			__BELL_TRIGER[i] = FALSE;
	}
	return -1;
}

void uiBellOn(BOOL bOn)
{
	if (dbSetupTotal.setSystem.dwBindingID)
	{
		bOn ? LOCK_BELL_START() : LOCK_BELL_STOP();
	}
	else
	{
		bOn ? BELL_ON() : BELL_OFF();
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static QPixmap *__MSG_PMAP = NULL;
static int __MSG_POSITION = 0;
static QLabel *__MSG_WIDGET = NULL;
static QString __MSG_STRING;
static BOOL __MSG_PERSONAL = FALSE;

QString uiMsgGetCurrentString(UINT64 nID, int nGroup)
{
	int i;
	DWORD dwSecondCur;
	MSG_INFO *pMsg;
	QString szMessage;

	dwSecondCur = g_uiProcStatus.dwCurrentSecond;

	for (i=0; i<MSG_INFO_COUNT; i++)
	{
		pMsg = &dbSetupTotal.setTimezone.tzMsg[i];
		if ((pMsg->Valid == 0) || (!nID && pMsg->Tag != SMSG_ALL) || (nID && pMsg->Tag == SMSG_ALL))
			continue;
		if (pMsg->ValidMinutes && (dwSecondCur - pMsg->StartTime) >= (DWORD)pMsg->ValidMinutes * 60/* + 59*/)
			continue;
		if (!pMsg->ValidMinutes && dwSecondCur < pMsg->StartTime)
			continue;
		if (pMsg->Tag == SMSG_USER && pMsg->Belong && (WORD)nID != pMsg->Belong)
			continue;
		if (pMsg->Tag == SMSG_GROUP && (WORD)nGroup != pMsg->Belong)
			continue;
		szMessage = szMessage + UNICODE2STRING((WORD*)pMsg->Contents, MSG_LEN >> 1) + QString(" ");
	}
	return szMessage;
}

void uiMsgStart(QString szMessage, BOOL bPersonalMessage)
{
	if (!szMessage.length())
	{
		uiMsgStop();
		return;
	}
	if (__MSG_STRING == szMessage)
		return;

	if (__MSG_WIDGET)
		uiMsgStop();

	if (bPersonalMessage)
		__MSG_WIDGET = g_VerifyWindow->ui.lblStatusText;
	else
		__MSG_WIDGET = g_MainWindow->ui.lblMessageArea;

// 	QLabel* pBackup = __MSG_WIDGET;
// 	uiMsgStop();
// 	__MSG_WIDGET = pBackup;

	__MSG_STRING = szMessage;
	__MSG_PERSONAL = bPersonalMessage;
	SETUP_TIMER(TIMER_SMSG, 200, 0, NULL);
}

void uiMsgDrawCurrentStatus()
{
	if (__MSG_PMAP == NULL)
	{
		QFontMetrics fontMetrics = __MSG_WIDGET->fontMetrics();
		int w = __MSG_WIDGET->width() + fontMetrics.width(__MSG_STRING);
		int h = fontMetrics.height();

		__MSG_PMAP = new QPixmap(w, h);
		if (__MSG_PMAP == NULL)
		{
//			printf("Memory allocation error\n");
			return;
		}

		__MSG_PMAP->fill(QColor(0, 0, 0, 0));

		QPainter painter(__MSG_PMAP);
		painter.setFont(SB_FONT_4());
		painter.setPen(QPen(QColor(0, 0, 0)));
		uiLcdDrawText(&painter, 1, 1, w, h, Qt::AlignRight, __MSG_STRING, QColor(255, 255, 255), QColor(255, 255, 255));
		__MSG_POSITION = 0;
	}

	QPixmap pmap(*__MSG_PMAP);
	pmap.fill(QColor(0, 0, 0, 0));

	QPainter painter(&pmap);
	painter.drawPixmap(0, 0, *__MSG_PMAP, __MSG_POSITION, 0, __MSG_WIDGET->width(), __MSG_WIDGET->height());
	__MSG_WIDGET->setPixmap(pmap);
	__MSG_POSITION += 10;
	if (__MSG_POSITION > pmap.width())
	{
		__MSG_POSITION = 0;
		if (__MSG_PERSONAL)
			uiMsgStop();
	}
}

BOOL uiMsgPersonalIsFlowing()
{
	return (__MSG_PERSONAL && __MSG_PMAP);
}

void uiMsgStop()
{
//	__MSG_WIDGET->hide();
	if (!__MSG_WIDGET)
		return;

	__MSG_STRING = "";
	__MSG_WIDGET->setText(" ");
	__MSG_PERSONAL = FALSE;
	STOP_TIMER(TIMER_SMSG);
	DELETE(__MSG_PMAP);
	__MSG_WIDGET = NULL;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
////////////////////////////////NoClose  Tamper   Duress       IlgVerify    IlgOpen     LogOverflow		PCAlarm  NoComm
static int __ALARM_TIMER[] =   {200,     400,     600,         800,         1000,       1200,			1500,    2000};
static BOOL __ALARM_TRIGER[] = {FALSE,   FALSE,   FALSE,       FALSE,       FALSE,      FALSE,			FALSE,   FALSE};
static int __ALARM_LOG[] = 
{
	SLOG_NOCLOSE_ALARM,
	SLOG_TAMPER_ALARM,
	-1,
	SLOG_ILLEGALVERIFY_ALARM,
	SLOG_ILGOPEN_ALARM,
	-1,
	-1,
	-1
};

BOOL uiAlarmStart(int nType, BOOL bBuzzerOnly)
{
	DWORD dwBuzzer = 0;

	if (!dbLicense.bUseAlarmFunction)
		return FALSE;

	if (nType > UI_ALARM_END)
		return FALSE;

	if (__ALARM_TRIGER[nType])
		return FALSE;

	uiTimeSetLastActionTime();

	if (__ALARM_LOG[nType] >= 0)
		uiLogSlogAdd(0, (BYTE)__ALARM_LOG[nType]);

	__ALARM_TRIGER[nType] = TRUE;
	if (nType != UI_ALARM_DURESS)
		dwBuzzer = 1;
//	dwBuzzer = 1; //please note the uiAlarmStop()'s 'TIMER_ALARM'

	if (!bBuzzerOnly && dbSetupTotal.setSystem.dwBindingID && g_uiProcStatus.nAlarmStatusFromController == -1)
		LOCK_ALARM_START();

	g_uiBuildMenu = TRUE;
	g_uiProcStatus.bAlarming = TRUE;
	g_uiProcStatus.bAlarmStatus = TRUE;
	g_uiProcStatus.bAlarmPrevStatus = FALSE;
	SETUP_TIMER(TIMER_ALARM, __ALARM_TIMER[nType], dwBuzzer, NULL);
	return TRUE;
}

BOOL uiAlarmStop(int nType /*= -1*/)
{
	int i;

	if (nType >= UI_ALARM_START && nType <= UI_ALARM_END && __ALARM_TRIGER[nType])
		__ALARM_TRIGER[nType] = 0;
	else if (nType == -1)
		memset(__ALARM_TRIGER, 0, sizeof(__ALARM_TRIGER));
	else
		return FALSE;

	for (i=UI_ALARM_START; i<=UI_ALARM_END; i++)
	{
		if (__ALARM_TRIGER[i])
			break;
	}

	if (i >= UI_ALARM_START && i <= UI_ALARM_END)
	{
		SETUP_TIMER(TIMER_ALARM, __ALARM_TIMER[i], 1/*dwBuzzer*/, NULL);
		return TRUE;
	}

	STOP_TIMER(TIMER_ALARM);
	
	uiBuzzerOff();
	if (dbSetupTotal.setSystem.dwBindingID)
	{
		LOCK_ALARM_STOP();
		g_uiProcStatus.nAlarmStatusFromController = -1;
	}
	else
		ALARM_OFF();
	g_uiProcStatus.bAlarming = FALSE;
	g_uiProcStatus.bAlarmPrevStatus = FALSE;
	g_uiProcStatus.bAlarmStatus = FALSE;
	g_uiBuildMenu = TRUE;
	return TRUE;
}

void uiAlarmDuress(UINT64 nID)
{
	uiLogSlogAdd(0, SLOG_DURESS_ALARM, nID);

	if (dbSetupTotal.setSystem.nAlarmDelay)
	{
		SETUP_TIMER(TIMER_DURESS_ALARM, dbSetupTotal.setSystem.nAlarmDelay*1000, 1, NULL);
	}
	else
	{
		uiAlarmStart(UI_ALARM_DURESS);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
int uiPowerGetStatus()
{
	int nSecCur = (int)g_uiProcStatus.dwCurrentSecond;
	int nIdleTime = uiTimeGetIdleTime() / 60000;

	if (g_uiProcStatus.bAlarming /*|| QApplication::focusWidget() != g_MainWindow*/)
		return -1;

	if ((dbSetupTotal.setSystem.nIdletimeForPoweroff && nIdleTime >= dbSetupTotal.setSystem.nIdletimeForPoweroff) ||
		(dbSetupTotal.setSystem.dwAutoPoweroffTime && uiRtcDiffSecond(nSecCur, dbSetupTotal.setSystem.dwAutoPoweroffTime) <= 3))
		return UI_POWER_OFF;
	if ((dbSetupTotal.setSystem.nIdletimeForSleep && nIdleTime >= dbSetupTotal.setSystem.nIdletimeForSleep) ||
		(dbSetupTotal.setSystem.dwAutoSleepTime && uiRtcDiffSecond(nSecCur, dbSetupTotal.setSystem.dwAutoSleepTime) <= 3))
		return UI_POWER_SLEEP;
	if (dbSetupTotal.setSystem.nIdletimeForLcdswitch && nIdleTime >= dbSetupTotal.setSystem.nIdletimeForLcdswitch)
		return UI_POWER_LCDSWITCH;
	return -1;
}

void uiPowerSetStatus(int nStatus, DWORD dwParam)
{

/*	switch (nStatus)
	{
	case UI_POWER_OFF:
		uiSoundOut(SOUND_TURNOFF, UI_BUZZER_NONE, UITIME_VOICE);
		if (dwParam)
		{
			if (dbSetupTotal.setSystem.dwBindingID)
				LOCK_DEINIT();

			uiDoorClose();

			uiLogSlogAdd(0, SLOG_TURNOFF, 0, 0);
			SB30000DEV_DEINIT(g_bPoweroffFlag);
			if (g_bPoweroffFlag)
			{
				sync();
				umount(SDCARD_MOUNTPOINT);
				umount(USB_MOUNTPOINT);
				umount(ENROLLDATA_MOUNTPOINT);
				POWER_OFF();
				reboot(RB_POWER_OFF);
				while (1) {};
			}
			else
				exit(g_params.nConsoleUse - 1);
		}
		else
		{
			uiLogSlogAdd(0, SLOG_TURNOFF, 0, 1);
			uiPowerEnterSleep(TRUE);
			uiLogSlogAdd(0, SLOG_TURNON, 0, 1);
		}
		break;
	case UI_POWER_SLEEP:
		uiPowerEnterSleep(FALSE);
		break;
	}*/
	
}

void uiPowerEnterSleep(BOOL bPoweroff)
{
	uiDoorClose();
	uiRtcSynchronize();

	////////////////////////////////////////////////////////////////////////
        //MP3_PLAY(NULL);

	if (dbSetupTotal.setSystem.dwBindingID)
		LOCK_DEINIT();

	///////////////////////////////////////////////////////////////////////
	CloseCameraDevice(); /*g_uiProcStatus.bCameraStatus = FALSE;*/
	if (SDCARD_ISMOUNT())
		umount(SDCARD_MOUNTPOINT); /*g_uiProcStatus.bSDCardStatus = FALSE;*/
	umount(USB_MOUNTPOINT);
	
	RFMOD_SUSPEND();
	SBUM_SUSPEND();
	uiCMOSPower(FALSE);
	uiLedOff();
	uiLedKeyBackground(FALSE);
	LCD_BG_OFF();
	uiBuzzerOff();
	KEYBOARD_SLEEP(TRUE, bPoweroff);
	fp_setlivecheck(FALSE);

	///////////////////////////////////////////////////////////////////////
	SB_EXEC("echo mem > /sys/power/state");

	///////////////////////////////////////////////////////////////////////
	fp_setlivecheck(TRUE);
	KEYBOARD_SLEEP(FALSE, bPoweroff);
	uiTimeSetLastActionTime();
	RFMOD_RESUME();
	SBUM_RESUME();
	SDCARD_RESET();
	SDCARD_DETECT();
	POST_EVENTS(); LCD_BG_ON();
	uiCMOSPower(TRUE);

	if (dbSetupTotal.setSystem.dwBindingID)
		LOCK_INIT(dbSetupTotal.setSystem.dwBindingID);
	xrtcalarmconfig(dbSetupTotal.setSystem.dwAutoPoweronTime);

	uiRtcSynchronize();
}

void uiPowerReboot()
{
	if (dbSetupTotal.setSystem.dwBindingID)
		LOCK_DEINIT();

	sync();
	umount(SDCARD_MOUNTPOINT);
	umount(USB_MOUNTPOINT);
	umount(ENROLLDATA_MOUNTPOINT);
	//reboot(RB_AUTOBOOT);
	SystemReset();
	while (1) {};
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_HEART
// Input    :
//     pLogData - heart for send
// Output   :
// Return   :
//

BOOL uiEventSend_HEART(void)
{
	BOOL bRet = TRUE;
	DWORD data[1];

    comm_sendtime();
	xprintf("%s","uiEventSend_HEART\n");
	data[0] = (DWORD)EVENT_HEART;
	//if( comm_send_event(EVENT_HEART, &dbLicense.szSerialNumber[0], sizeof(dbLicense.szSerialNumber)) == 0 )
     bRet=comm_send_event(EVENT_HEART, &dbLicense.szSerialNumber[0], 32 );
  	if(bRet==0)
	{
		tcpclient_connect_start();
	}
       //http_WEB_CONNECT=bRet;

    return bRet;
}

BOOL uiEventSend_TIMESYN(void)
{
	BOOL bRet = TRUE;
	DWORD data[1];

    DWORD seconds=uiRtcGetSeconds();
	xprintf("%s","uiEventSend_TIMESYN\n");
	data[0] = (DWORD)EVENT_TIMESYN;
	//if( comm_send_event(EVENT_HEART, &dbLicense.szSerialNumber[0], sizeof(dbLicense.szSerialNumber)) == 0 )
    if( comm_send_event(EVENT_TIMESYN, &seconds, sizeof(seconds) ) == 0 )	
	{
		tcpclient_connect_start();
	}

    return bRet;
}

//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_GLOG
// Input    :
//     pLogData - general log data for send
// Output   :
// Return   :
//
DWORD	dwGlogIndex=0;

BOOL uiEventSend_GLOG(ALOG_INFO *pLogData)
{
	BOOL bRet = TRUE;
      ALOG_INFO_INDEX  gLog;
    comm_sendtime();
	xprintf("%s","uiEventSend_GLOG\n");
	gLog.bAntipassOut=pLogData->bAntipassOut;
	
	gLog.byAction=pLogData->byAction;
	gLog.byTrStatus=pLogData->byTrStatus;
	gLog.dwIndex=dwGlogIndex;
	gLog.dwSeconds=pLogData->dwSeconds;
	gLog.nID=pLogData->nID;
	bRet= comm_send_event(EVENT_GLOG, &gLog, sizeof(ALOG_INFO_INDEX));

	xprintf("uiEventSend_GLOG before dwGlogIndex=%d\n\r",dwGlogIndex);
	xprintf("bret=%d\n\r",bRet);
	
	xprintf("gLog.dwSeconds==%d\r\n",gLog.dwSeconds);
	xprintf("gLog.nID==%d\r\n",gLog.nID);
	xprintf("gLog.byAction==%d\r\n",gLog.byAction);
	xprintf("gLog.dwIndex==%d\r\n",gLog.dwIndex);

      if(bRet==0)
	{
		xprintf("the bret is 0!!\r\n");
		tcpclient_connect_start();
	}

    //http_WEB_CONNECT=bRet;
	return bRet;
}

BOOL uiEventSend_SLOG(MLOG_INFO *pLogData)
{
	BOOL bRet = TRUE;

    comm_sendtime();
	xprintf("%s","uiEventSend_SLOG\n");
	bRet=comm_send_event(EVENT_SLOG, pLogData, sizeof(MLOG_INFO));
	 if(bRet==0)		
	{
	
		tcpclient_connect_start();
	}
    //http_WEB_CONNECT=bRet;

	return bRet;
}


//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_PRESS_FP
// Input    :
// Output   :
// Return   :
//
void uiEventSend_PRESS_FP(void)
{
	//发送的是02 00 00 00
	//comm_send_event(EVENT_PRESS_FP, NULL, 0);//注意这个发送
}

//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_VERIFY_SUCCESS
// Input    :
//     nVerifyMode - Verification mode(FP, RF, PWD, ID, etc)
//     ID - Verified user's ID number
// Output   :
// Return   :
//
void uiEventSend_VERIFY_SUCCESS(int/* nVerifyMode*/, UINT64 ID)
{
	DWORD data[1];
	data[0] = (DWORD)ID;
	xprintf("the send is in uieventsend_verify_sucess!!!\r\n");
	xprintf("data[0]==%d\r\n",data[0]);
	//comm_send_event(EVENT_VERIFY_SUCCESS, data, sizeof(data));
}

//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_VERIFY_FAIL
// Input    :
//     nVerifyMode - Verification mode(FP, RF, PWD, ID, etc)
// Output   :
// Return   :
//
void uiEventSend_VERIFY_FAIL(int nVerifyMode)
{
	DWORD data[1];
	data[0] = (DWORD)nVerifyMode;
	//comm_send_event(EVENT_VERIFY_FAIL, data, sizeof(data));
}

//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_ALARM_ON
// Input    :
//     nAlarmType - The alarm type
//     ID - ID number who generates this alarm. In the case of PC, SOS-key long press,
//          tamper, log overflow, OCX, illegal door open ,func-key, ilg-verify and controller, this may be 0.
// Output   :
// Return   :
//
void uiEventSend_ALARM_ON(int nAlarmType, UINT64 ID)
{
	DWORD data[2];
	data[0] = (DWORD)nAlarmType;
	data[1] = (DWORD)ID;
	xprintf("the send is in uieventsend_alarm_on!! send data is id!!1\r\n");
	xprintf("IDxxx===%d\r\n",ID);
	//comm_send_event(EVENT_ALARM_ON, data, sizeof(data));
}

//////////////////////////////////////////////////////////////////////////
// Function : uiEventSend_ALARM_OFF
// Input    :
//     nAlarmType - Alarm type. If this is -1, it means all alarm.
//     nAlarmReleaseType - Alarm release mode(one of Auto, User, Manager and OCX)
//     ID - ID number who removes this alarm. This may be 0 in the case of auto-release, s-manager, OCX, etc.
// Output   :
// Return   :
//
void uiEventSend_ALARM_OFF(int nAlarmType, int nAlarmReleaseType, UINT64 ID)
{
	DWORD data[3];
	data[0] = (DWORD)nAlarmType;
	data[1] = (DWORD)nAlarmReleaseType;
	data[2] = (DWORD)ID;
	//comm_send_event(EVENT_ALARM_OFF, data, sizeof(data));
}

