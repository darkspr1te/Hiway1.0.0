#include "../precomp.h"
#include "SystemManage.h"
#include <QtCore/QDir>
#include <QtGui/QPainter>

void uiProcDrawStatusBar(QWidget *pWindow, int nstrLeft, int nstrMiddle, int nstrRight);
void MenuSettingStart(BOOL bFirst = FALSE);
void MenuSettingEnd(int nStrTitle);
int uiProcBoxNumber(QWidget* parent, int x, int y, int cx, int cy,
					BOOL* pbRet, int nInitial, int nMin, int nMax, BOOL b0isNo,
					int nUnitStr, int nKeyFrom = 0, int nKeyTo = 9, BOOL bAutoMinMaxSel = TRUE,
					Qt::Alignment align = Qt::AlignVCenter | Qt::AlignRight);
int uiProcBoxSelect(QWidget *pWnd, int x, int y, int w, int h, BOOL *pbRet, int nValue, int from, int to, QStringList *pStrList = NULL, BOOL bResize = TRUE);
int uiProcBoxTime(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE, BOOL bSecondShow = TRUE);
int uiProcBoxTimerange(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial);
const char* uiProcMenuGetItemImageFilename(int nItemStr);

static int DO_CLOSE(int fd)
{
	FD_CLOSE(fd);
	return fd;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX_BELLCOUNT	10
static T_ITEM_A __rowdata_bell[4];
static int __bell_index = 0;
static T_ITEM_A* GetRowData_bell(DWORD dwID)
{
	if (dwID >= MAX_BELLCOUNT)
		return NULL;

	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzBell[dwID];
	__rowdata_bell[0].szValue = QString("%1").arg(dwID + 1);
	__rowdata_bell[1].szValue = QString("%1:%2").arg(tz->RANGE.bStartHour).arg(tz->RANGE.bStartMinute);
	__rowdata_bell[2].szValue = QString("%1%2").arg(tz->RANGE.bEndMinute).arg(UISTR(UISTR_UNIT_SECOND));

	return __rowdata_bell;
}

CBellSetup::CBellSetup(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	setTitle(NULL, UISTR(UISTR_MENU_POWERMANAGE_BELL));
}

void CBellSetup::DoProcess()
{
	SBTable tblBellSet(ui.lblBackgroundFrame);

	tblBellSet.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblBellSet.InsertColumn(-1, UISTR(UISTR_BELL_NO), Qt::AlignVCenter|Qt::AlignLeft, 60);
	tblBellSet.InsertColumn(-1, UISTR(UISTR_BELL_STIME), Qt::AlignVCenter|Qt::AlignLeft, 110);
	tblBellSet.InsertColumn(-1, UISTR(UISTR_BELL_LENGTH), Qt::AlignVCenter|Qt::AlignLeft, 110);
	tblBellSet.SetRowDataCallback(GetRowData_bell);
	tblBellSet.SetRowHeight(20);
	tblBellSet.SetGridUse(3);
	tblBellSet.SetRowCount(MAX_BELLCOUNT);
	tblBellSet.show();

	int nKey;

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_ESC:
			MenuSettingEnd(UISTR_MENU_POWERMANAGE_BELL);
			goto _lExit;
		case UIKEY_OK:
			__bell_index = tblBellSet.GetCurrentIndex();
			DIALOGBOX(CBellSetOne);
			tblBellSet.OnRedraw();
			break;
		default:
			tblBellSet.OnKeyPress(nKey);
			break;
		}
	}

_lExit:
	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CBellSetOne::CBellSetOne(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));

	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzBell[__bell_index];
	
	m_dwBellTime = tz->RANGE.bStartHour * 3600 + tz->RANGE.bStartMinute * 60;
	ui.txtBellTime->setText(uiRtcGetTime(m_dwBellTime, FALSE));
	
	m_nBellLength = tz->RANGE.bEndMinute;
	ui.txtBellLength->setText(QString("%1").arg(m_nBellLength));

	ui.comboBellType->setCurrentIndex(tz->RANGE.bEndHour);

	ui.lblBellType->hide();
	ui.comboBellType->hide();
}

void CBellSetOne::DoProcess()
{
	int nKey;

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}
}

void CBellSetOne::OnBtnOK()
{
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzBell[__bell_index];
	uiRtcSeconds2YMDHMS(m_dwBellTime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	if (ui.txtBellLength->text().toInt() > 255)
	{
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
		ui.txtBellLength->setText(QString("%1").arg(255));
		ui.txtBellLength->setFocus(Qt::MouseFocusReason);
		ui.txtBellLength->selectAll();
		return;
	}
	tz->RANGE.bStartHour = (BYTE)nHour;
	tz->RANGE.bStartMinute = (BYTE)nMinute;
	tz->RANGE.bEndMinute = (BYTE)ui.txtBellLength->text().toInt();
	tz->RANGE.bEndHour = (BYTE)ui.comboBellType->currentIndex();
	m_bTerminateFlag = TRUE;
}

void CBellSetOne::OnBtnESC()
{
	m_bTerminateFlag = TRUE;
}

void CBellSetOne::OnFocusChanged(QWidget */*from*/, QWidget *to)
{
	BYTE nKey;
	QRect rc;
//	int nRet;

	if (to == (QWidget*)ui.txtBellTime)
	{
		rc = ui.txtBellTime->geometry();
		m_dwBellTime = uiProcBoxTime(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwBellTime, TRUE, FALSE, FALSE);
		ui.txtBellTime->setText(uiRtcGetTime(m_dwBellTime, FALSE));
		switch (nKey)
		{
		case UIKEY_OK:
			ui.btnOK->setFocus(Qt::MouseFocusReason);
			OnBtnOK();
			break;
		case UIKEY_ESC:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			OnBtnESC();
			break;
		case UIKEY_UP:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
			ui.txtBellLength->setFocus(Qt::MouseFocusReason);
			break;
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
#define MAX_TRCOUNT	10

static T_ITEM_A __rowdata_tr[4];
static int __tr_index = 0;
static T_ITEM_A* GetRowData_tr(DWORD dwID)
{
	if (dwID >= MAX_TRCOUNT)
		return NULL;

	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzTr[dwID];
	__rowdata_tr[0].szValue = QString("%1").arg(dwID + 1);
	// 	__rowdata_tr[1].szValue = UNICODE2STRING(tz->NAME, TZNAME_LENGTH);
	__rowdata_tr[1].szValue = QString("%1:%2").arg(tz->RANGE.bStartHour).arg(tz->RANGE.bStartMinute);
	__rowdata_tr[2].szValue = QString("%1:%2").arg(tz->RANGE.bEndHour).arg(tz->RANGE.bEndMinute);
	__rowdata_tr[3].szValue = UISTR(UISTR_FUNC_START + tz->STATUS);

	return __rowdata_tr;
}

CTrSetup::CTrSetup(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	setTitle(NULL, UISTR(UISTR_MENU_POWERMANAGE_TRSWITCH));
}

void CTrSetup::DoProcess()
{
	SBTable tblTRSet(ui.lblBackgroundFrame);

	tblTRSet.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblTRSet.InsertColumn(-1, UISTR(UISTR_TR_NO), Qt::AlignVCenter|Qt::AlignLeft, 40);
	tblTRSet.InsertColumn(-1, UISTR(UISTR_TR_STIME), Qt::AlignVCenter|Qt::AlignLeft, 70);
	tblTRSet.InsertColumn(-1, UISTR(UISTR_TR_ETIME), Qt::AlignVCenter|Qt::AlignLeft, 70);
	tblTRSet.InsertColumn(-1, UISTR(UISTR_TR_STATUS), Qt::AlignVCenter|Qt::AlignLeft, 100);
	tblTRSet.SetRowDataCallback(GetRowData_tr);
	tblTRSet.SetRowHeight(20);
	tblTRSet.SetGridUse(3);
	tblTRSet.SetRowCount(MAX_TRCOUNT);
	tblTRSet.show();

	int nKey;

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_ESC:
			MenuSettingEnd(UISTR_MENU_POWERMANAGE_TRSWITCH);
			goto _lExit;
		case UIKEY_OK:
			__tr_index = tblTRSet.GetCurrentIndex();
			DIALOGBOX(CTrSetOne);
			tblTRSet.OnRedraw();
			break;
		default:
			tblTRSet.OnKeyPress(nKey);
			break;
		}
	}

_lExit:
	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CTrSetOne::CTrSetOne(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));

	int i;
	for (i=UISTR_FUNC_START; i<=UISTR_FUNC_END; i++)
		ui.comboStatus->addItem(UISTR(i));

	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzTr[__tr_index];
	m_dwSTime = tz->RANGE.bStartHour * 3600 + tz->RANGE.bStartMinute * 60;
	ui.txtSTime->setText(uiRtcGetTime(m_dwSTime, FALSE));
	m_dwETime = tz->RANGE.bEndHour * 3600 + tz->RANGE.bEndMinute * 60;
	ui.txtETime->setText(uiRtcGetTime(m_dwETime, FALSE));
	ui.comboStatus->setCurrentIndex(tz->STATUS);
}

void CTrSetOne::DoProcess()
{
	int nKey;

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}
}

void CTrSetOne::OnBtnOK()
{
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	DB_TZ_NORMAL *tz = &dbSetupTimezoneNew.tzTr[__tr_index];

	uiRtcSeconds2YMDHMS(m_dwSTime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	tz->RANGE.bStartHour = nHour;
	tz->RANGE.bStartMinute = nMinute;
	
	uiRtcSeconds2YMDHMS(m_dwETime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
	tz->RANGE.bEndHour = nHour;
	tz->RANGE.bEndMinute = nMinute;

	tz->STATUS = ui.comboStatus->currentIndex();
	m_bTerminateFlag = TRUE;
}

void CTrSetOne::OnBtnESC()
{
	m_bTerminateFlag = TRUE;
}

void CTrSetOne::OnFocusChanged(QWidget */*from*/, QWidget *to)
{
	BYTE nKey;
	QRect rc;
//	int nRet;

	if (to == (QWidget*)ui.txtSTime)
	{
		rc = ui.txtSTime->geometry();
		m_dwSTime = uiProcBoxTime(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwSTime, TRUE, FALSE, FALSE);
		ui.txtSTime->setText(uiRtcGetTime(m_dwSTime, FALSE));
		switch (nKey)
		{
		case UIKEY_OK:
			ui.btnOK->setFocus(Qt::MouseFocusReason);
			OnBtnOK();
			break;
		case UIKEY_ESC:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			OnBtnESC();
			break;
		case UIKEY_UP:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
			ui.txtETime->setFocus(Qt::MouseFocusReason);
			break;
		}		
	}
	if (to == (QWidget*)ui.txtETime)
	{
		rc = ui.txtETime->geometry();
		m_dwETime = uiProcBoxTime(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwETime, TRUE, FALSE, FALSE);
		ui.txtETime->setText(uiRtcGetTime(m_dwETime, FALSE));
		switch (nKey)
		{
		case UIKEY_OK:
			ui.btnOK->setFocus(Qt::MouseFocusReason);
			OnBtnOK();
			break;
		case UIKEY_ESC:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			OnBtnESC();
			break;
		case UIKEY_UP:
			ui.txtSTime->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
			ui.comboStatus->setFocus(Qt::MouseFocusReason);
			break;
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_tz[2];
static T_ITEM_A __rowdata_tz_week[2];
static DB_TZACCESS* __current_tzaccess = NULL;

static T_ITEM_A* GetRowData_tz(DWORD dwID)
{
	if (dwID >= ACCESS_TIME_SET_COUNT)
		return NULL;

//	DB_TZACCESS* tz = &dbSetupTimezoneNew.tzAccess[dwID];
	__rowdata_tz[0].szValue = QString("%1").arg(dwID + 1);

	return __rowdata_tz;
}
static T_ITEM_A* GetRowData_tzweek(DWORD dwID)
{
	if (!__current_tzaccess || dwID >= 7)
		return NULL;
	DB_TIMESECTION_A *tz = &__current_tzaccess->RANGE[dwID];
	QString szRange;
	szRange.sprintf("%02d:%02d - %02d:%02d", tz->bStartHour, tz->bStartMinute, tz->bEndHour, tz->bEndMinute);
	__rowdata_tz_week[0].szValue = UISTR(UISTR_WEEKDAY_START + dwID);
	__rowdata_tz_week[1].szValue = szRange;
	return __rowdata_tz_week;
}

CTimezoneSetup::CTimezoneSetup(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	const char* szIconFile = uiProcMenuGetItemImageFilename(UISTR_MENU_ACSETTING_TIMEZONE);
	setTitle(szIconFile ? QString(GUI_RESOURCE_PATH "%1").arg(szIconFile) : QString(""), UISTR(UISTR_MENU_ACSETTING_TIMEZONE));
}

void CTimezoneSetup::DoProcess()
{
	int nKey;
	BOOL bRet;
	QString strResult;
	int nResult;
	SBTable tblTz(ui.lblBackgroundFrame);
	SBTable tz_week(&tblTz);
	DWORD dwPrevTime = uiTimeGetTickCount() - 501;
	SBTable *activeWidget = &tblTz;
	SBTable *inactiveWidget = &tz_week;


	tblTz.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblTz.InsertColumn(-1, UISTR(UISTR_TZHDR_NO), Qt::AlignVCenter|Qt::AlignLeft, 50);
	tblTz.InsertColumn(-1, UISTR(UISTR_TZHDR_CONTENT), 0, 220);
	tblTz.SetRowDataCallback(GetRowData_tz);

	tblTz.SetRowHeight(20);
	tblTz.SetGridUse(3);
	tblTz.SetLastColumnMergeUse(TRUE);
	tblTz.SetRowCount(ACCESS_TIME_SET_COUNT);
	tblTz.show();

	POST_EVENTS(); // Don't clear !!!!
	int x, y, cx, cy;
	tblTz.GetTableItemArea(0, 1, x, y, cx, cy);
	tz_week.SetTableRect(x + 10, y + 10, cx - 20, 128);

	tz_week.InsertColumn(-1, UISTR(UISTR_TZHDR_NO), Qt::AlignVCenter|Qt::AlignHCenter, 60);
	tz_week.InsertColumn(-1, UISTR(UISTR_TZHDR_CONTENT), Qt::AlignVCenter|Qt::AlignLeft, cx - 20 - 60);

	tz_week.SetRowHeight(18);
	tz_week.SetGridUse(3);
	tz_week.SetHeaderUse(FALSE);
	tz_week.SetScrollUse(FALSE);
	tz_week.SetSelectedBkColor(tz_week.GetBkColor());
	tz_week.SetSelectedForeColor(tz_week.GetForeColor());
	tz_week.SetRowCount(7);
	tz_week.SetRowDataCallback(GetRowData_tzweek);

	tz_week.show();

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		if (uiTimeGetTickCount() - dwPrevTime > 500)
		{
			__current_tzaccess = &dbSetupTimezoneNew.tzAccess[tblTz.GetCurrentIndex()];
			tblTz.OnRedraw();
			tz_week.OnRedraw();
			dwPrevTime = uiTimeGetTickCount();
		}

		nKey = uiKeyGetKey();

		if (nKey == UIKEY_NONE)
			continue;

		switch (nKey)
		{
		case UIKEY_ESC:
			MenuSettingEnd(UISTR_MENU_ACSETTING_TIMEZONE);
			goto _lExit;
		case UIKEY_OK:
			activeWidget->GetTableItemArea(activeWidget->GetCurrentIndex(), 1, x, y, cx, cy);

			if (activeWidget == &tblTz)
			{
			}
			else
			{
				QRgb rgbForeColor = g_rgbForeColor;
				g_rgbForeColor = qRgb(0, 0, 0);
				nResult = uiProcBoxTimerange(activeWidget, x+1, y, cx-2, cy, &bRet, *(int*)&__current_tzaccess->RANGE[activeWidget->GetCurrentIndex()]);
				g_rgbForeColor = rgbForeColor;
				if (bRet)
					__current_tzaccess->RANGE[activeWidget->GetCurrentIndex()] = *(DB_TIMESECTION_A*)&nResult;
			}
			break;
	/*	case UIKEY_LEFT:*/
		case UIKEY_UP:
			{
				if (activeWidget == &tblTz)
				{
					activeWidget = &tz_week;
					inactiveWidget = &tblTz;
				}
				else
				{
					activeWidget = &tblTz;
					inactiveWidget = &tz_week;
				}
				activeWidget->SetSelectedBkColor();
				activeWidget->SetSelectedForeColor();
				if (inactiveWidget == &tz_week)
				{
					inactiveWidget->SetSelectedBkColor(inactiveWidget->GetBkColor());
					inactiveWidget->SetSelectedForeColor(inactiveWidget->GetForeColor());
				}
			}
			break;
		//case UIKEY_UP:
		case UIKEY_DOWN:
			if (activeWidget == &tblTz)
				tz_week.SetCurrentIndex(0);
			activeWidget->OnKeyPress(nKey);
			break;
		default:
			activeWidget->OnKeyPress(nKey);
			break;
		}

		dwPrevTime = uiTimeGetTickCount() - 501;
	}

_lExit:
	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_mp3[2];
static QStringList __mp3_files;
static int __mp3_fileindex[MAX_SOUND_COUNT];
static SBTable *__mp3_table = NULL;
static T_ITEM_A* GetRowData_mp3(DWORD dwID)
{
	if (dwID > SOUND_END)
		return NULL;
	int nIndex = __mp3_fileindex[dwID];
	__rowdata_mp3[0].szValue = UISTR(UISTR_SOUND_START + dwID);
	if (nIndex >= 0)
	{
		__mp3_table->SetForeColor(qRgb(255, 0, 0));
		__rowdata_mp3[1].szValue = __mp3_files[nIndex];
	}
	else
	{
		__mp3_table->SetForeColor(qRgb(0, 0, 0));
		__rowdata_mp3[1].szValue = QString("%1.mp3").arg(dwID);
	}
	return __rowdata_mp3;
}

CMp3Upload::CMp3Upload(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	setTitle("", UISTR(UISTR_MENU_MP3UPLOAD));
	uiLcdSetLabelText(ui.lblStatusText, UISTR(UISTR_MP3UPLOAD_DESC), FOREGROUND_COLOR);
}


void CMp3Upload::DoProcess()
{
    //hiway
/*	int i, nRet;
	int nKey;
	BOOL bRet;
	SBTable tblMp3(ui.lblBackgroundFrame);
	int x, y, cx, cy;
	QDir dir(QString(USB_MOUNTPOINT), "*.mp3 *.wav");

	if (!dir.count())
	{
		hide();
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_NO_FILES, UI_MSGTIMEOUT);
		return;
	}

	__mp3_files.clear();
	for (i=0; i<(int)ITEM_CNT(__mp3_fileindex); i++)
		__mp3_fileindex[i] = -1;
	__mp3_table = &tblMp3;

	__mp3_files = dir.entryList();

	for (i=0; i<__mp3_files.count(); i++)
	{
		if (__mp3_files[i].contains(".wav", Qt::CaseInsensitive))
		{
			int nIndex = atoi(STR2ASCII(__mp3_files[i]));
			if (nIndex < 0 || nIndex >= (int)ITEM_CNT(__mp3_fileindex))
				continue;
			if (__mp3_files[i].toLower() != QString("%1.wav").arg(nIndex))
				continue;
			QString src = dir.path() + QString("/") + __mp3_files[i];
			HFILE fd = open(STR2ASCII(src), O_RDONLY | O_LARGEFILE);
			int speed, bits, stereo, nTotalCount;
			BOOL bOK = TRUE;

			if (fd != INVALID_HANDLE_VALUE)
			{
				if (check_wave(fd, &speed, &bits, &stereo, &nTotalCount) != 1 || bits != 16)
					bOK = FALSE;
				fd = DO_CLOSE(fd);
				if (bOK)
					__mp3_fileindex[nIndex] = i;
			}
		}
	}

	tblMp3.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblMp3.InsertColumn(-1, "A", Qt::AlignVCenter|Qt::AlignLeft, 125);
	tblMp3.InsertColumn(-1, "B", 0, 150);
	tblMp3.SetRowDataCallback(GetRowData_mp3);

	tblMp3.SetHeaderUse(FALSE);
	tblMp3.SetRowHeight(20);
	tblMp3.SetGridUse(3);
	tblMp3.SetRowCount(SOUND_END + 1);
	tblMp3.show();

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_ESC:
			bRet = FALSE;
			for (i=0; i<MAX_SOUND_COUNT; i++)
			{
				if (__mp3_fileindex[i] >= 0)
					bRet = TRUE;
			}
			if (!bRet)
				goto _lExit;
			if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_MP3UPLOAD_CONFIRM, UITIME_OUT))
				goto _lUpload;
			else
				goto _lExit;
			break;
		case UIKEY_OK:
			i = tblMp3.GetCurrentIndex();
			tblMp3.GetTableItemArea(i, 1, x, y, cx, cy);
			nRet = uiProcBoxSelect(&tblMp3, x, y, cx, cy, &bRet, __mp3_fileindex[i], 0, __mp3_files.count()-1, &__mp3_files, FALSE);
			if (bRet)
			{
				QString src = dir.path() + QString("/") + __mp3_files[nRet];
				HFILE fd = open(STR2ASCII(src), O_RDONLY | O_LARGEFILE);
				int speed, bits, stereo, nTotalCount;
				BOOL bOK = TRUE;

				if (fd != INVALID_HANDLE_VALUE)
				{
					if (check_wave(fd, &speed, &bits, &stereo, &nTotalCount) != 1 || bits != 16)
					{
						bOK = FALSE;
						uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_INVALID_WAVFORMAT, UI_MSGTIMEOUT);
					}
					fd = DO_CLOSE(fd);
				}
				else
				{
					bOK = FALSE;
					uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
				}

				if (bOK)
					__mp3_fileindex[i] = nRet;
			}
			tblMp3.OnRedraw();
			break;
// 		case UIKEY_RIGHT:
// 			i = tblMp3.GetCurrentIndex();
// 			if (__mp3_fileindex[i] < 0)
// 				uiSoundOut(i, UI_BUZZER_NONE);
// 			else
// 			{
// 				i = __mp3_fileindex[i];
// 				QString src = dir.path() + QString("/") + __mp3_files[i];
// 				if (MP3_PLAY(STR2ASCII(src)) == FALSE)
// 					uiLcdMessageBox(UI_MSG_ERROR, UISTR_STATUS_INVALID_WAVFORMAT, UI_MSGTIMEOUT);
// 			}
// 			break;
		default:
			tblMp3.OnKeyPress(nKey);
			break;
		}
	}

	if (uiTimeIsTimeout())
		goto _lExit;

_lUpload:
	for (i=0; i<MAX_SOUND_COUNT; i++)
	{
		int nIndex = __mp3_fileindex[i];
		if (nIndex < 0)
			continue;
		QString src = dir.path() + QString("/") + __mp3_files[nIndex];
		QString dst = QString(MP3_GetFileName(dbSetupTotal.setSystem.nLanguage, i));
		QFile::remove(dst);
		QFile::copy(src, dst);
	}
_lExit:
        return;*/
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
QStringList __fw_files;
static SBTable *__fw_table;
static T_ITEM_A __rowdata_fw[2];
static T_ITEM_A* GetRowData_fw(DWORD dwID)
{
	if (dwID > (DWORD)__fw_files.count())
		return NULL;
	__rowdata_fw[0].szValue = __fw_files[dwID];
	return __rowdata_fw;
}

CSystemUpgrade::CSystemUpgrade(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	setTitle("", UISTR(UISTR_MENU_ADVANCEDSETTING_FWUPGRADE));
//	ui.lblStatusText->setText(UISTR(UISTR_MP3UPLOAD_DESC));
}

void CSystemUpgrade::DoProcess()
{
	int i;
	int nKey;
	BOOL bRet;
	SBTable tblFiles(ui.lblBackgroundFrame);
//	int x, y, cx, cy;
	QDir dir(QString(USB_MOUNTPOINT));

	dir.setFilter(QDir::Files);

	//Filtering according to magic number...
	i = 0;
	__fw_files = dir.entryList();
	while (i < __fw_files.count())
	{
		QFile f(QString(USB_MOUNTPOINT) + QString("/") + __fw_files[i]);
		DWORD dwMagic = 0;
		if (!f.open(QIODevice::ReadOnly))
		{
			__fw_files.removeAt(i);
			continue;
		}
		f.read((char*)&dwMagic, 4);
		if ((dwMagic != MAGIC_DOWNLOADER) && (dwMagic != MAGIC_ROOTFS) && (dwMagic != MAGIC_ZIMAGE))
		{
			__fw_files.removeAt(i);
			f.close();
			continue;
		}
		f.close();
		i++;
	}

	if (!__fw_files.count())
	{
		hide();
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_NO_FILES, UI_MSGTIMEOUT);
		return;
	}

	__fw_table = &tblFiles;

	tblFiles.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblFiles.InsertColumn(-1, "A", Qt::AlignVCenter|Qt::AlignLeft, m_nFrameWidth);
	tblFiles.SetRowDataCallback(GetRowData_fw);

	tblFiles.SetHeaderUse(FALSE);
	tblFiles.SetRowHeight(20);
	tblFiles.SetGridUse(3);
	tblFiles.SetRowCount(__fw_files.count());
	tblFiles.show();

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_ESC:
			bRet = FALSE;
			goto _lExit;
		case UIKEY_OK:
			i = tblFiles.GetCurrentIndex();
			if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
			{
				if (DoUpgrade(QString(USB_MOUNTPOINT) + QString("/") + __fw_files[i]))
					uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
				else
					uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
			}
			break;
		default:
			tblFiles.OnKeyPress(nKey);
			break;
		}
	}

_lExit:
	return;
}

BOOL CSystemUpgrade::DoUpgrade(QString szFilename)
{
	BOOL bRet = TRUE;
	HFILE hFile;
	BYTE* pRomImage = NULL;
	int nFileSize;
	int nReadPtr = 0, nReadTotalCnt, nReadCnt;
	int nPercent;

        hFile = ::open(STR2ASCII(szFilename), O_RDONLY);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	ioctl(hFile, FIONREAD, &nFileSize);

	if (nFileSize > ROM_IMAGE_SIZE)
	{
//		printf("Filesize is too long\n");
		return FALSE;
	}

	Db_FreeAllData();

	pRomImage = (BYTE*)malloc(ROM_IMAGE_SIZE);
	if (!pRomImage)
	{
		bRet = FALSE;
		goto _lExit;
	}

	nReadTotalCnt = nFileSize;

	uiLcdProgressDlgShow(UISTR_COMMUNICATING); g_bProgress = TRUE;
	uiLcdProgressStart(UISTR_COMMUNICATING);
	while (nReadTotalCnt > 0)
	{
		nPercent = LCDPROG_PERCENT(nReadPtr, nFileSize);
		uiLcdProgress(nPercent);

		nReadCnt = (nReadTotalCnt > FLASH_SECTOR_SIZE) ? FLASH_SECTOR_SIZE : nReadTotalCnt;
		if (read(hFile, &pRomImage[nReadPtr], nReadCnt) != nReadCnt)
		{
			bRet = FALSE;
			goto _lExit;
		}
		nReadTotalCnt -= nReadCnt;
		nReadPtr += nReadCnt;
	}
	uiLcdProgressDlgExit(); g_bProgress = FALSE;

	bRet = _Db_FWWriteToFlash(pRomImage, MAKE_SECTOR_SIZE(nFileSize));

_lExit:
	uiLcdProgressDlgExit(); g_bProgress = FALSE;
	FREE(pRomImage);
	Db_LoadAllData(TRUE);

	return bRet;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
//////////////////////////////////////////////////////////////////////////
CSelftestKeyboard::CSelftestKeyboard(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	GUI_DLG_STATUSBAR();
}

int CSelftestKeyboard::DoProcess(DWORD dwTimeout /* = -1UL */)
{
	const char* __btn_names[] = 
	{
		"btn0", // UIKEY_0,
		"btn1", // UIKEY_1,
		"btn2", // UIKEY_2,
		"btn3", // UIKEY_3,
		"btn4", // UIKEY_4,
		"btn5", // UIKEY_5,
		"btn6", // UIKEY_6,
		"btn7", // UIKEY_7,
		"btn8", // UIKEY_8,
		"btn9", // UIKEY_9,
		"btnMENU", // UIKEY_MENU,
		"btnUP", // UIKEY_UP,
		"btnDOWN", // UIKEY_DOWN,
		"btnOK", // UIKEY_OK,
		"btnESC", // UIKEY_ESC,
		"btnPOWER", // UIKEY_POWER, 
	};
	int nKey;
	QWidget *pCurrentWidget;

	ui.btnOK->setFocus(Qt::MouseFocusReason);

	while (uiTimeIsTimeout(dwTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_NONE)
			continue;
		if (nKey == UIKEY_ESC)
			break;
		pCurrentWidget = findChild<QWidget*>(__btn_names[nKey]);
		if (pCurrentWidget)
		{
			pCurrentWidget->setFocus(Qt::MouseFocusReason);
            PostKeyEvent(UIKEY_OK, pCurrentWidget, TRUE);  
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
CSelftestMemory::CSelftestMemory(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
}

int CSelftestMemory::DoProcess()
{
	int nKey;
	DWORD dwSize;
	DWORD dwAddr;
	int nPercent, nPercentPrev;
	BYTE bySave;
	BOOL bRet = TRUE;

	nPercentPrev = 0;
	ui.progressBar->setValue(0);

	dwSize = sizeof(FPINFO) * dbLicense.nMaxEnrollCount;
	for (dwAddr = 0; dwAddr < dwSize; dwAddr++)
	{
		if ((dwAddr & 1023) == 0)
		{
			nKey = uiKeyGetKey();
			if (nKey == UIKEY_ESC)
				return 0;

			nPercent = LCDPROG_PERCENT(dwAddr >> 10, dwSize >> 10);
			if (nPercent != nPercentPrev)
			{
				nPercentPrev = nPercent;
				ui.progressBar->setValue(nPercent);
				POST_EVENTS();
			}
		}

		dwAddr += (DWORD)gpFingerEnrollData;
		bySave = *(BYTE*)dwAddr;
		*(BYTE*)dwAddr = 0;
		if (*(BYTE*)dwAddr != 0)
		{
			bRet = FALSE;
			break;
		}
		*(BYTE*)dwAddr = 0xFF;
		if (*(BYTE*)dwAddr != 0xFF)
		{
			bRet = FALSE;
			break;
		}
		*(BYTE*)dwAddr = bySave;
		dwAddr -= (DWORD)gpFingerEnrollData;
	}

	if (bRet)
		uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
	else
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
	return bRet;
}

//////////////////////////////////////////////////////////////////////////
CSelftestRtc::CSelftestRtc(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnEsc()));
}

int CSelftestRtc::DoProcess(DWORD dwTimeout /* = -1UL */)
{
	int nKey;
	int nYear, nMonth, nDay, nWeekday, nHour, nMinute, nSecond;
	char szTime[64];

	while (!m_bTerminateFlag && uiTimeIsTimeout(dwTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnEsc();

		RtcGet(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
		sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", nYear+2000, nMonth, nDay, nHour, nMinute, nSecond);
		ui.txtInternalRTC->setText(szTime);

		Rtc1Get(&nYear, &nMonth, &nDay, &nWeekday, &nHour, &nMinute, &nSecond);
		sprintf(szTime, "%04d-%02d-%02d %02d:%02d:%02d", nYear+2000, nMonth, nDay, nHour, nMinute, nSecond);
		ui.txtExternalRTC->setText(szTime);
	}
	return TRUE;
}

void CSelftestRtc::OnBtnEsc()
{
	m_bTerminateFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
CSelftestSensor::CSelftestSensor(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
}

int CSelftestSensor::DoProcess(DWORD dwTimeout /* = -1UL */)
{
	int nKey;
	DWORD dwTime = uiTimeGetTickCount() - 1001;
	QPixmap pmap = *ui.lblFpArea->pixmap();

	while (uiTimeIsTimeout(dwTimeout) == FALSE)
	{
		POST_EVENTS();

		if (uiTimeGetTickCount() - dwTime > 1000)
		{
			ui.lblStatus->setText(UISTR(UISTR_VERIFY_PRESS_FINGER));
			memset(SB_FP__256IMAGE, 192, 256*256);
			DrawFingerprint(ui.lblFpArea, &pmap);
		}

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_ESC || nKey == UIKEY_OK)
			break;
		if (uiCMOSCaptureFP())
		{
			uiBuzzerAlarm();
			DrawFingerprint(ui.lblFpArea, &pmap);
			ui.lblStatus->setText(UISTR(UISTR_ACTION_SUCCESS));
			dwTime = uiTimeGetTickCount();
		}
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
CSelftestSound::CSelftestSound(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;
	connect(ui.btnPlay, SIGNAL(clicked()), this, SLOT(OnBtnPlay()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnEsc()));
	GUI_DLG_STATUSBAR();
}

int CSelftestSound::DoProcess(DWORD dwTimeout /* = -1UL */)
{
	int nKey;
	BOOL bKeyboardTone = dbSetupTotal.setSystem.bKeyTones;
	BOOL bVoiceOut = dbSetupTotal.setSystem.bVoiceOut;
	int sound_list[] = {SOUND_BELL1, SOUND_VERIFY_FAIL, APLUS_OK, APLUS_REVERIFY};

	dbSetupTotal.setSystem.bKeyTones = FALSE;
	dbSetupTotal.setSystem.bVoiceOut = TRUE;

// 	for (i=UISTR_SOUND_START; i<=UISTR_SOUND_END; i++)
// 		ui.comboBox->addItem(UISTR(i));

	while (!m_bTerminateFlag && uiTimeIsTimeout(dwTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_OK)
			uiSoundOut(sound_list[ui.comboBox->currentIndex()], UI_BUZZER_NONE);
		else if (nKey != UIKEY_NONE)
			uiBuzzerKey();

		if (nKey == UIKEY_ESC)
			OnBtnEsc();
		if(nKey == UIKEY_UP)
		{
			if(ui.comboBox->currentIndex() == 0)
				ui.comboBox->setCurrentIndex(ui.comboBox->count()-1);
			else
				ui.comboBox->setCurrentIndex(ui.comboBox->currentIndex()-1);
		}
		if(nKey == UIKEY_DOWN)
		{
			if(ui.comboBox->currentIndex()== ui.comboBox->count()-1)
				ui.comboBox->setCurrentIndex(0);
			else
				ui.comboBox->setCurrentIndex(ui.comboBox->currentIndex()+1);
		}
	}

	dbSetupTotal.setSystem.bKeyTones = bKeyboardTone;
	dbSetupTotal.setSystem.bVoiceOut = bVoiceOut;
	return 0;
}

void CSelftestSound::OnBtnPlay()
{
	//do play
}

void CSelftestSound::OnBtnEsc()
{
	m_bTerminateFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
int uiSelftestLcd(DWORD dwTimeout = -1UL)
{
	int nKey;
	DWORD dwPrevTime = uiTimeGetTickCount() - 1001;
	QLabel w;
	Qt::GlobalColor __color_table[] = {Qt::red, Qt::green, Qt::blue};
	int __color_index = 0;

	w.setGeometry(0, 0, LCD_SIZE_X, LCD_SIZE_Y);
	w.show();

	while (uiTimeIsTimeout(dwTimeout) == FALSE)
	{
		POST_EVENTS();

		if (uiTimeGetTickCount() - dwPrevTime > 1000)
		{
			int i;
			QPixmap pmap(LCD_SIZE_X, LCD_SIZE_Y);
			QPainter p(&pmap);

// 			for (i=0; i<6; i++)
// 				p.fillRect(0, i*40, LCD_SIZE_X, 60, QBrush(__color_table[(__color_index + i) % 3]));
			for (i=0; i<4; i++)
				p.fillRect(i*(LCD_SIZE_X / 4), 0, LCD_SIZE_X / 4, LCD_SIZE_Y, QBrush(__color_table[(__color_index + i) % 3]));

			p.drawText(0, 0, LCD_SIZE_X, LCD_SIZE_Y, Qt::AlignVCenter | Qt::AlignHCenter, UISTR(UISTR_STATUS_LCDTEST));

			w.setPixmap(pmap);
			__color_index++;
			dwPrevTime = uiTimeGetTickCount();
		}

		nKey = uiKeyGetKey();
		if (nKey != UIKEY_NONE)
			break;
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
CSelftestAll::CSelftestAll(QWidget *parent /* = NULL */)
	:CMainFrame(parent)
{
	setTitle("", UISTR(UISTR_MENU_SELFTEST_ALL));
	ui.lblStatusText->hide();
}

int CSelftestAll::DoProcess()
{
	BYTE VALID_LIST[12];
	int from = UISTR_MENU_SELFTEST_MEMORY;
	int to = UISTR_MENU_SELFTEST_RTC;
	int nResult;

	memset(VALID_LIST, 0, sizeof(VALID_LIST));
	OnDraw(from, to, VALID_LIST);

	for (int i=from; i<=to; i++)
	{
		POST_EVENTS();

		if (/*(i == UISTR_MENU_SELFTEST_SOUND) ||*/ (i == UISTR_MENU_SELFTEST_MP3))
			continue;

		nResult = 0;
		switch (i)
		{
		case UISTR_MENU_SELFTEST_MEMORY:
			uiTimeSetLastActionTime();
			nResult = DIALOGBOX_RET(CSelftestMemory);
			break;
		case UISTR_MENU_SELFTEST_LCD:
			uiTimeSetLastActionTime();
			nResult = uiSelftestLcd(3000);
			break;
		case UISTR_MENU_SELFTEST_SOUND:
			uiTimeSetLastActionTime();
			nResult = DIALOGBOXEX(CSelftestSound, 3000);
			break;
		case UISTR_MENU_SELFTEST_SENSOR:
			uiTimeSetLastActionTime();
			nResult = DIALOGBOXEX(CSelftestSensor, 3000);
			break;
		case UISTR_MENU_SELFTEST_KEYBOARD:
			uiTimeSetLastActionTime();
			nResult = DIALOGBOXEX(CSelftestKeyboard, 3000);
			break;
		case UISTR_MENU_SELFTEST_RTC:
			uiTimeSetLastActionTime();
			nResult = DIALOGBOXEX(CSelftestRtc, 3000);
			break;
		}
		VALID_LIST[i - from] = 1;
		OnDraw(UISTR_MENU_SELFTEST_MEMORY, UISTR_MENU_SELFTEST_RTC, VALID_LIST);
		uiTimeDelay(500);
	}

	uiTimeSetLastActionTime();
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		if (uiKeyGetKey() == UIKEY_ESC)
			break;
	}
	return 0;
}

void CSelftestAll::OnDraw(int from, int to, BYTE *pValidList)
{
	QPixmap pmap = m_pmapFrame;
	QPainter painter(&pmap);
	int x, y, w, h, w_spacer;

	w_spacer = 5;
	x = w_spacer; y = m_nFrameY + 10;
	w = m_nFrameWidth - 15; h = 26;

	painter.save();
	painter.setPen(FOREGROUND_COLOR);
	for (int i=from; i<=to; i++)
	{
		x = w_spacer;

		painter.drawText(x, y, w-x, h, Qt::AlignVCenter | Qt::AlignLeft, QString("%1. %2").arg(i-from+1).arg(UISTR(i)));
		if (pValidList[i - from])
		{
			QPixmap pmap_checked(GUI_RESOURCE_PATH "icon-checked.png");
			painter.drawPixmap(x + w - 30, y + 2, pmap_checked);
		}
		y += h;
	}
	painter.restore();
	ui.lblBackgroundFrame->setPixmap(pmap);
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CHelpWindow::CHelpWindow(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	ui.lblTitleIcon->hide();
	ui.lblTitleBackground->hide();
	ui.lblTitleText->hide();
	uiLcdSetLabelText(ui.lblStatusText, UISTR(USITR_STATUS_HELP), FOREGROUND_COLOR);
	m_nFrameY -= 20;
}

int CHelpWindow::DoProcess(int nStrHelp)
{
/*	QString szHelpOrg = UISTR(nStrHelp);
	QFontMetrics fm = ui.lblBackgroundFrame->fontMetrics();
	int w = m_nFrameWidth - 10;
	int i, k;
	int pos;
	BOOL bRemakeString = FALSE;

	for (i=0; i<szHelpOrg.length(); i++)
	{
		if (fm.width(szHelpOrg, i+1) > w)
		{
			bRemakeString = TRUE;
			break;
		}
	}

	m_szHelp = szHelpOrg;
	if (bRemakeString)
	{
		k = 1;
		pos = 0;
		while (1)
		{
			if (k * i >= szHelpOrg.length())
				break;
			m_szHelp.insert(pos + k * i, "\r\n");
			k += 1;
			pos += 2;
		}
	}
*/
	m_szHelp = UISTR(nStrHelp);

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		if (uiKeyGetKey() != UIKEY_NONE)
			break;
	}
	return 0;
}

void CHelpWindow::paintEvent(QPaintEvent *e)
{
	CMainFrame::paintEvent(e);

	QPixmap pmap = m_pmapFrame;
	QPainter painter(&pmap);

	painter.drawText(m_nFrameX + 5, m_nFrameY + 5, m_nFrameWidth - 10, m_nFrameHeight + 10, Qt::AlignLeft | Qt::TextWordWrap, m_szHelp);

	ui.lblBackgroundFrame->setPixmap(pmap);
}
