#include "../precomp.h"
#include "MessageBox.h"
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QPen>
#include <QtGui/QColor>

QPushButton *pMessageBoxbtnOK;

//////////////////////////////////////////////////////////////////////////
CMessageBox::CMessageBox(QWidget *parent)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;
	ui.Moretextlabel->hide();    //add

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	pMessageBoxbtnOK=ui.btnOK;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetIcon(QString szIconFile)
{
	QPixmap pmap(szIconFile);
	ui.lblIcon->setPixmap(pmap);
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetText(QString szText)
{
	int i;
	int w = ui.lblStatus->width();
	QFontMetrics fm = ui.lblStatus->fontMetrics();

	for (i=0; i<szText.length(); i++)
	{
		if (fm.width(szText, i + 1) > w)
			break;
	}

	QString szMessage = szText;
	if (i < szText.length())
		szMessage.insert(i, "\r\n");

	ui.lblStatus->setText(szMessage);
}

void CMessageBox::SetText2(QString szText)
{
        int i;
        int w = ui.Moretextlabel->width();
        QFontMetrics fm = ui.Moretextlabel->fontMetrics();

        ui.Moretextlabel->setText(szText);
}

BOOL CMessageBox::MsgBoxProc_Message3(QString szMessage)
{
	BOOL bRet = TRUE;
	int nPosFP, nPosUI;
//	DWORD dwSTime = uiTimeGetTickCount();
	int nKey;
	//int w = width();
	int h = height();

	uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
	SetIcon(QString(GUI_RESOURCE_PATH) + QString("icon-question.png"));
	SetText(szMessage);
	show();
	SetType(UI_MSG_QUESTION);

	QPoint pos_lblStatus = ui.lblStatus->pos();
	QPoint pos_lblIcon = ui.lblIcon->pos();
	//int w_lblStatus = ui.lblStatus->width();

    //ui.btnOK->hide();
        //ui.btnESC->hide();

        ui.btnOK->hide();
        ui.btnESC->hide();
	ui.lblStatus->move(pos_lblStatus.x(), h / 2 - pos_lblStatus.y() / 2);
	//msgBox.ui.lblIcon->move(pos_lblIcon.x(), h / 2 - pos_lblIcon.y() / 2);
	

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	POST_EVENTS();


	return bRet;

}
BOOL CMessageBox::MsgBoxProc_Message(char *szMessage)
{
	BOOL bRet = TRUE;
	int nPosFP, nPosUI;
//	DWORD dwSTime = uiTimeGetTickCount();
	int nKey;
	//int w = width();
	int h = height();

	uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
	SetIcon(QString(GUI_RESOURCE_PATH) + QString("icon-question.png"));
	SetText(QString(szMessage));
	show();
	SetType(UI_MSG_QUESTION);

	QPoint pos_lblStatus = ui.lblStatus->pos();
	QPoint pos_lblIcon = ui.lblIcon->pos();
	//int w_lblStatus = ui.lblStatus->width();

    //ui.btnOK->hide();
        //ui.btnESC->hide();

        ui.btnOK->hide();
        ui.btnESC->hide();
	ui.lblStatus->move(pos_lblStatus.x(), h / 2 - pos_lblStatus.y() / 2);
	//msgBox.ui.lblIcon->move(pos_lblIcon.x(), h / 2 - pos_lblIcon.y() / 2);
	

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	POST_EVENTS();


	return bRet;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::SetType(int nType)
{
	int w = width();
	QPoint pos = ui.btnOK->pos();
	int w_btnOK = ui.btnOK->width();

	switch (nType)
	{
	case UI_MSG_OK:
	case UI_MSG_ERROR:
		ui.btnESC->hide();
//		ui.btnOK->hide();
//		ui.lblBackground->setGeometry(0, 0, ui.lblBackground->width(), 75);
		ui.btnOK->move(w / 2 - w_btnOK / 2, pos.y());
		break;
	}
}

//////////////////////////////////////////////////////////////////////////
int CMessageBox::MsgBoxProc(unsigned int nTimeout /* = 0xFFFFFFFF */)
{
	int nKey;
	m_nRet = UI_MSGRET_ESC;

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	while (!m_bTerminateFlag && uiTimeIsTimeout(nTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}
	
//_lExit:
	return m_nRet;
}

int CMessageBox::MsgBoxProc2(unsigned int nTimeout /* = 0xFFFFFFFF */)
{
	int nKey;
	//int w = width();
	int h = height();	
	QPoint pos_lblStatus = ui.lblStatus->pos();
	QPoint pos_lblIcon = ui.lblIcon->pos();
	//int w_lblStatus = ui.lblStatus->width();

    ui.btnOK->hide();
	ui.btnESC->hide();
	//msgBox.ui.lblIcon->hide();
		ui.lblStatus->show();
	ui.lblStatus->move(pos_lblStatus.x(), h / 2 - pos_lblStatus.y() / 2);
	//ui.lblIcon->move(pos_lblIcon.x(), h / 2 - pos_lblIcon.y() / 2);
	
	m_nRet = UI_MSGRET_ESC;

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	while (!m_bTerminateFlag && uiTimeIsTimeout(nTimeout) == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(TRUE);
		if ((nKey >= UIKEY_0 && nKey <= UIKEY_9)||nKey == UIKEY_DOWN)
		{
			m_nRet = nKey;
			m_bTerminateFlag = TRUE;		
		}
		else if (nKey == UIKEY_ESC)
			OnBtnESC();		
		//if ((nKey=g_VerifyWindow->FpVerifyLoop()))
	    if(uiCMOSCaptureFP())
		{
		   m_nRet = -1;
		   m_bTerminateFlag = TRUE;
		}	

	}
	
//_lExit:
	return m_nRet;
}

BOOL CMessageBox::MsgBoxProc_Message4(char *szMessage)
{
	BOOL bRet = TRUE;
	int nPosFP, nPosUI;
//	DWORD dwSTime = uiTimeGetTickCount();
	int nKey;
	//int w = width();
	int h = height();
	

	uiSoundOut(SOUND_QUESTION, UI_BUZZER_NONE);
	SetIcon(QString(GUI_RESOURCE_PATH) + QString("icon-question.png"));
        SetText2(QString(szMessage));
        //SetText(QString(szMessage));
	show();
	SetType(UI_MSG_QUESTION);

	QPoint pos_lblStatus = ui.lblStatus->pos();
	QPoint pos_lblIcon = ui.lblIcon->pos();
	//int w_lblStatus = ui.lblStatus->width();

    	ui.btnOK->hide();
	ui.btnESC->hide();
        ui.Moretextlabel->show();
	ui.lblStatus->hide();
	//ui.lblStatus->move(pos_lblStatus.x(), h / 2 - pos_lblStatus.y() / 2);
	//msgBox.ui.lblIcon->move(pos_lblIcon.x(), h / 2 - pos_lblIcon.y() / 2);
	

	if (LCD_BLANK_STATUS() == FBINFO_BLANK_PAUSE)
		LCD_BLANK(FBINFO_BLANK_RESUME);

	POST_EVENTS();


	return bRet;
}


//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnOK()
{
	m_nRet = UI_MSGRET_OK;
	m_bTerminateFlag = TRUE;
}

//////////////////////////////////////////////////////////////////////////
void CMessageBox::OnBtnESC()
{
	m_nRet = UI_MSGRET_ESC;
	m_bTerminateFlag = TRUE;
}
