#ifndef __MAIN_WINDOW_H__
#define __MAIN_WINDOW_H__

#include "define.h"
#include "ui_main.h"
#include "ui_verify.h"
#include "ui_bell-dlg.h"
#include <QtCore/QSet>

//////////////////////////////////////////////////////////////////////////
class QDialog;
template <class Key, class T>
class QMap;

typedef void (*TIMERPROC)(QWidget*, DWORD, DWORD);
typedef struct _timer_data
{
	DWORD dwTimerID;
	DWORD dwProcessedTime;
	int   nElapse;
	DWORD dwParam;
}T_TIMER_DATA;
#define MAX_TIMER_COUNT		50
//////////////////////////////////////////////////////////////////////////
class CMainWindow : public QWidget
{
	Q_OBJECT

public:
	CMainWindow(QWidget *parent = NULL);
	~CMainWindow() {};
	int SetTimer(DWORD dwTimerID, int nElapse, DWORD dwParam, TIMERPROC lpTimerFunc);
	void StopTimer(DWORD dwTimerID);
	void DrawClock(BOOL bFirst = FALSE);

public Q_SLOTS:;
	void OnTimer();

public:
	GUI_DLG_DEFINE(Ui::MainWidget);
	QPixmap m_ClockPixmap;
	int m_ClockW, m_ClockH;

};

#define VERIFY_DURESS_INIT()		{g_uiProcStatus.bDuressFlag = FALSE;}
#define VERIFY_DURESS_START(_id_)	{g_uiProcStatus.bDuressFlag = TRUE; uiAlarmDuress((_id_)); uiEventSend_ALARM_ON(UI_ALARM_DURESS, (_id_));}
#define VERIFY_DURESS_AUTOSTOP()	({BOOL _res_ = FALSE; if (!g_uiProcStatus.bDuressFlag) _res_ = uiAlarmStop(UI_ALARM_DURESS); _res_;})
//////////////////////////////////////////////////////////////////////////
class CVerify : public QDialog
{
	Q_OBJECT

public:
	CVerify(QWidget *parent = NULL);
	~CVerify() {};
	void InitResults(int nVerifyMode = 0);
	void VerifyLoop(int nFirstDigit = -1);
	void VerifySManager0();
	void DoAccessControl(struct _user_info *pUserInfo);
	void ACCacheFlush();
	void DrawPhoto(struct _user_info *pUserInfo, int nVerifyMode, BOOL bIsReverify);
	BOOL CurrentVerifyIsValid(int nUserVerifyMode, DWORD dwVerifiedStatus, int *pnNextVerify = NULL);
	BOOL NextVerifyIsValid(int nUserVerifyMode, DWORD dwVerifiedStatus, int nNextVerifyMode);

	GUI_DLG_DEFINE(Ui::Verify);

private:
	QPixmap m_pmapPhoto;
	QPixmap m_pmapCamera;
	QPixmap m_pmapFinger;
	QPixmap m_pmapCard;
	QPixmap m_pmapPassword;
	QSet<UINT64> m_ACCacheUsers;
	BYTE	m_AcCacheGroups;
};

//////////////////////////////////////////////////////////////////////////
class CBellDlg : public QDialog
{
	Q_OBJECT

public:
	CBellDlg(QWidget *parent = NULL);
	~CBellDlg() {};
	int DoProcess(int nBellNumber);

private:
	GUI_DLG_DEFINE(Ui::BellDlg);
};

void DispDeviceState(void);

#endif /*__MAIN_WINDOW_H__*/
