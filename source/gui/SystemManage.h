#ifndef __SYSTEM_MANAGE_H__
#define __SYSTEM_MANAGE_H__

#include "Mainframe.h"
#include "SBTable.h"
#include "SBLabel.h"
#include "ui_set-bellone.h"
#include "ui_set-trone.h"
#include "ui_selftest-keyboard.h"
#include "ui_selftest-memory.h"
#include "ui_selftest-rtc.h"
#include "ui_selftest-sensor.h"
#include "ui_selftest-sound.h"

//////////////////////////////////////////////////////////////////////////
class CBellSetup : public CMainFrame
{
	Q_OBJECT

public:
	CBellSetup(QWidget *parent = NULL);
	~CBellSetup() {}
	void DoProcess();
};

class CBellSetOne : public QDialog
{
	Q_OBJECT

public:
	CBellSetOne(QWidget *parent = NULL);
	~CBellSetOne() {}
	void DoProcess();

public Q_SLOTS:
	;
	void OnBtnOK();
	void OnBtnESC();
	void OnFocusChanged(QWidget *from, QWidget *to);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::BellSetOne);
	DWORD m_dwBellTime;
	int m_nBellLength;
};

//////////////////////////////////////////////////////////////////////////
class CTrSetup : public CMainFrame
{
	Q_OBJECT

public:
	CTrSetup(QWidget *parent = NULL);
	~CTrSetup() {}
	void DoProcess();
};

class CTrSetOne : public QDialog
{
	Q_OBJECT

public:
	CTrSetOne(QWidget *parent = NULL);
	~CTrSetOne() {}
	void DoProcess();

public Q_SLOTS:
	;
	void OnBtnOK();
	void OnBtnESC();
	void OnFocusChanged(QWidget *from, QWidget *to);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::TRSetOne);
	DWORD m_dwSTime, m_dwETime;
};

//////////////////////////////////////////////////////////////////////////
class CTimezoneSetup : public CMainFrame
{
	Q_OBJECT

public:
	CTimezoneSetup(QWidget *parent = NULL);
	~CTimezoneSetup() {}
	void DoProcess();
};

//////////////////////////////////////////////////////////////////////////
class CMp3Upload : public CMainFrame
{
	Q_OBJECT
public:
	CMp3Upload(QWidget *parent = NULL);
	~CMp3Upload() {}
	void DoProcess();
};

//////////////////////////////////////////////////////////////////////////
class CSystemUpgrade : public CMainFrame
{
	Q_OBJECT
public:
	CSystemUpgrade(QWidget *parent = NULL);
	~CSystemUpgrade() {}
	void DoProcess();
	BOOL DoUpgrade(QString szFilename);
};

//////////////////////////////////////////////////////////////////////////
class CSelftestKeyboard : public QDialog
{
	Q_OBJECT
public:
	CSelftestKeyboard(QWidget *parent = NULL);
	~CSelftestKeyboard() {}
	int DoProcess(DWORD dwTimeout = -1UL);

private:
	GUI_DLG_DEFINE(Ui::SelftestKeyboard);
};

class CSelftestMemory : public QDialog
{
	Q_OBJECT
public:
	CSelftestMemory(QWidget *parent = NULL);
	~CSelftestMemory() {}
	int DoProcess();

private:
	GUI_DLG_DEFINE(Ui::SelftestMemory);
};

class CSelftestRtc : public QDialog
{
	Q_OBJECT
public:
	CSelftestRtc(QWidget *parent = NULL);
	~CSelftestRtc() {}
	int DoProcess(DWORD dwTimeout = -1UL);

public Q_SLOTS:;
	void OnBtnEsc();

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::SelftestRtc);
};

class CSelftestSensor : public QDialog
{
	Q_OBJECT
public:
	CSelftestSensor(QWidget *parent = NULL);
	~CSelftestSensor() {}
	int DoProcess(DWORD dwTimeout = -1UL);

private:
	GUI_DLG_DEFINE(Ui::SelftestSensor);
};

class CSelftestSound : public QDialog
{
	Q_OBJECT
public:
	CSelftestSound(QWidget *parent = NULL);
	~CSelftestSound() {}
	int DoProcess(DWORD dwTimeout = -1UL);

public Q_SLOTS:;
	void OnBtnPlay();
	void OnBtnEsc();

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::SelftestSound);
};

class CSelftestAll : public CMainFrame
{
	Q_OBJECT
public:
	CSelftestAll(QWidget *parent = NULL);
	~CSelftestAll() {}
	int DoProcess();
	void OnDraw(int from, int to, BYTE *pValidList);
};

//////////////////////////////////////////////////////////////////////////
class CHelpWindow : public CMainFrame
{
	Q_OBJECT

public:
	CHelpWindow(QWidget *parent = NULL);
	~CHelpWindow() {}
	int DoProcess(int nStrHelp);

protected:
	void paintEvent(QPaintEvent *e);

private:
	QString m_szHelp;
};

#endif /*__SYSTEM_MANAGE_H__*/
