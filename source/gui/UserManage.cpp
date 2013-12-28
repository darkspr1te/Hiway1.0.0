#include "../precomp.h"
#include "UserManage.h"
#include "../t9/t9_main.h"
#include "SBTable.h"
#include "Menu.h"
#include <QtGui/QPainter>

extern void xprintf (
	const char*	str,	/* Pointer to the format string */
	...					/* Optional arguments */
);
//作用:编辑用户的时候不从服务器下载信息
//也就是注册的时候下载，编辑的时候屏蔽
static BOOL USER_EDIT_FLAG=0;

extern int     gWgInLength;  
extern  BOOL ComClientSendCardPasswordData(UINT64 ID ,int card ,BOOL iscard);

extern T_UI_PROCSTATUS g_uiProcStatus;
extern UINT64 g_uiMenuIDForUerTZ;
extern int g_uiPopupTitle;
int uiProcBoxDate(QWidget* parent, int x, int y, int cx, int cy, BOOL* pbRet, int nInitial, int nFormat = 0, BOOL bKeyCheck = FALSE, BOOL bAutoSize = TRUE);
int uiProcBoxSelect(QWidget *pWnd, int x, int y, int w, int h, BOOL *pbRet, int nValue, int from, int to, QStringList *pStrList = NULL, BOOL bResize = TRUE);
void uiProcDrawStatusbar(QLabel *pLbl, int nOK, int nESC);
BOOL uiEnrollUserInfo(USER_INFO *pUserInfo);
BOOL uiPwdEnroll(USER_INFO *pUserInfo, char* pcPwd);
//////////////////////////////////////////////////////////////////////////
void uiEnrollSetTitle(QLabel *pTitlebar)
{
	QString szTitle = QString("%1: %2  %3")
		.arg(UISTR(UISTR_ENROLL_CURRENT_USER))
		.arg(UserId_BCDtoSTR(gUserInfoTemp.ID))
		.arg(UISTR(UISTR_ENROLL_NAME));
//		.arg(UNICODE2STRING(gUserInfoTemp.NAME, USERNAME_LENGTH));

	xprintf("szTitle=%s\r\n",UserId_BCDtoSTR(gUserInfoTemp.ID));
	uiLcdSetLabelText2(pTitlebar, szTitle, TITLECOLOR,QColor(),UNICODE2STRING(gUserInfoTemp.NAME, USERNAME_LENGTH));
}

//////////////////////////////////////////////////////////////////////////
void uiEnrollSetStatus(QWidget *pWindow, UINT64 nID)
{
	int i;
	int nFingerCount = 0;
	WORD wEnrollStatus = Db_GetEnrolledIDMask(nID);
	for (i = BACKUP_FINGER0; i <= BACKUP_FINGER9; i++)
	{
		QString szID = QString("lblFinger") + QString("%1").arg(i+1);
		QLabel *lbl = pWindow->findChild<QLabel*>(szID);
		
		if (wEnrollStatus & (1 << i))
		{
			if (lbl)
				lbl->setEnabled(TRUE);
			nFingerCount++;
		}
		else
		{
			if (lbl)
				lbl->setEnabled(FALSE);
		}
	}

	QLabel *lblFingerIcon = pWindow->findChild<QLabel*>("lblFingerIcon");
	QLabel *lblCardIcon = pWindow->findChild<QLabel*>("lblCardIcon");
	QLabel *lblPwdIcon = pWindow->findChild<QLabel*>("lblPwdIcon");
	QLabel *lblVoiceIcon = pWindow->findChild<QLabel*>("lblVoiceIcon");
	QLabel *lblPhotoIcon = pWindow->findChild<QLabel*>("lblPhotoIcon");
	QLabel *lblPhotoArea = pWindow->findChild<QLabel*>("lblPhotoArea");

	if (lblFingerIcon)
		lblFingerIcon->setEnabled(nFingerCount != 0);
	if (lblCardIcon && dbLicense.bUseCard)
		lblCardIcon->setEnabled(wEnrollStatus & (1 << BACKUP_CARD));
	if (lblPwdIcon)
		lblPwdIcon->setEnabled(wEnrollStatus & (1 << BACKUP_PASSWORD));
	if (lblVoiceIcon && dbLicense.bUseMP3)
		lblVoiceIcon->setEnabled(DbUserInfoHasVoice(nID));
	if (lblPhotoIcon && dbLicense.bUseCamera)
	{
		BOOL bHasPhoto = DbUserInfoHasPhoto(nID);
		lblPhotoIcon->setEnabled(bHasPhoto);

		if (lblPhotoArea)
		{
			if (bHasPhoto)
			{
				QPixmap pmap_org = *lblPhotoArea->pixmap();
				QPixmap pmap(DbUserInfoGetPhotoFilename(nID));
				DrawCamera(lblPhotoArea, &pmap_org, &pmap);
			}
			else
			{
				QPixmap pmap(GUI_RESOURCE_PATH "default-character.png");
				lblPhotoArea->setPixmap(pmap);
			}
		}
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollStep1::CEnrollStep1(QWidget *parent /* = NULL */, UINT64 nID /* = 0 */, BOOL bNew /* = TRUE */, BOOL/* bEdit*/ /*= FALSE*/)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();
	show();
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
	connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnIDChange(const QString &)));
	/*connect(ui.txtPassword, SIGNAL(textEdited(const QString &)), this, SLOT(OnPasswordChange(const QString &)));*/
	//connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));

	ui.comboPart->setFont(SB_FONT_4());  
	EDITBOX_2_T9InputBox(ui.txtName);
	EDITBOX_2_T9InputBox(ui.txtID);

	m_bNew = bNew;
	m_nCandidateID = -1;
	m_nID = nID;

	QString szTitle = QString("[%1]-%2")
		.arg(UISTR(UISTR_MENU_USERMANAGE))
		.arg(UISTR(bNew ? UISTR_MENU_ENROLLNEW : UISTR_MENU_ENROLLBACKUP));
	uiLcdSetLabelText(ui.lblTitleText,szTitle,TITLECOLOR,QColor());
	int nParts = DbPartCount();
	for (int i=0; i<nParts; i++)
		ui.comboPart->addItem(DbPartGet(i));  

	ui.lblPart->hide();
	ui.comboPart->hide();
	ui.txtName->setMaxLength(12);
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

	m_bTerminateFlag = !EnrollParamSet();
}

BOOL CEnrollStep1::EnrollParamSet(int nCandidateDiff /* = 1 */)
{
	if (nCandidateDiff >= 0)
	{
		if (m_nCandidateID == (UINT64)(-1))
			//m_nCandidateID = 1;
#if PRODUCT_AB == 1
			m_nCandidateID = 1000001;
#else
                     m_nCandidateID = 1;
#endif
		else
			m_nCandidateID += nCandidateDiff;

		m_nCandidateID = Db_GetCandidateID(m_bNew, m_nCandidateID);
		if (!m_nCandidateID)
		{
			if (m_bNew)
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_NOUSER, UI_MSGTIMEOUT);
			return FALSE;
		}
		//ui.txtID->setText(ID2STRING(m_nCandidateID));
		ui.txtID->setText(UserId_BCDtoSTR(m_nCandidateID));		
		m_nID = m_nCandidateID;
	}

	USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);  

	if (m_bNew || !pUserInfo)  
	{
		ui.txtName->clear();
		//ui.txtPassword->setText(PWD2STRING(DEFAULT_PASSWORD));
		//ui.txtPasswordConfirm->setText(PWD2STRING(DEFAULT_PASSWORD));
		ui.comboLevel->setCurrentIndex(0);
		if(DbPartCount()>1)
		ui.comboPart->setCurrentIndex(1);
		else
		ui.comboPart->setCurrentIndex(0);   
	}
	else
	{
		ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
		//ui.txtPassword->setText(PWD2STRING(pUserInfo->PWD));
		//ui.txtPasswordConfirm->setText(PWD2STRING(pUserInfo->PWD));
		ui.comboLevel->setCurrentIndex(PRIV_INDEX(DbUserInfoFlagManagerGet(pUserInfo)));
		if (pUserInfo->PART < DbPartCount())
			ui.comboPart->setCurrentIndex(pUserInfo->PART);
		else
			ui.comboPart->setCurrentIndex(0);  
	}

	if (nCandidateDiff >= 0)
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}
	return TRUE;
}

BOOL CEnrollStep1::EnrollCheck(BOOL bIDChange /* = FALSE */)
{
	BOOL bRet = TRUE;
	int MGR_LIST[] = {PRIV_USER, PRIV_MGR, PRIV_SMGR};

	m_nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
	m_nManager = MGR_LIST[ui.comboLevel->currentIndex()];

	if (m_nEdit == ID_ALL)
		m_bNew = !DbUserInfoIsUsedID(m_nID);
	if (bIDChange)
	{
		m_nCandidateID = m_nID;
		goto _lExit;
	}
// 	if (uiProcEnrollIsManagerFull(m_nManager))
// 	{
// 		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
// 		bRet = FALSE;
// 		goto _lExit;
// 	}

	if (m_bNew && Db_GetUserCount() >= dbLicense.nMaxEnrollCount)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	if (/*m_bNew &&*/
		m_nManager != PRIV_USER && 
		m_nManager != DbUserInfoGetPrivilege(m_nID) &&
		Db_GetManagerCount((BYTE)m_nManager) + 1 > dbSetupTotal.setSystem.nManagersNumber)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_MANAGER_OVERFLOW, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
	{
		if(DbUserInfoGetPrivilege(m_nID) == PRIV_SMGR)
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
			ui.comboLevel->setFocus(Qt::MouseFocusReason);
			bRet = FALSE;
			goto _lExit;
		}
		if (m_nManager == PRIV_SMGR ||
			(m_nManager == PRIV_MGR && m_nID != g_uiProcStatus.nIDCurrentMgr))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
			ui.comboLevel->setFocus(Qt::MouseFocusReason);
			bRet = FALSE;
			goto _lExit;
		}
	}
	if (!m_nID/*ui.txtID->text().isEmpty()*/ ||
		(m_bNew && DbUserInfoIsUsedID(m_nID)) ||
		(!m_bNew && !DbUserInfoIsUsedID(m_nID)))
	{
		int nStr = UISTR_ENROLL_INVALID_ID;
		if (!m_nID)
			nStr = UISTR_ENROLL_INVALID_ID;
		else if (m_bNew)
			nStr = UISTR_ENROLL_USED_ID;
		else if (!m_bNew)
			nStr = UISTR_ENROLLDELETE_NODATA;
		uiLcdMessageBox(UI_MSG_ERROR,nStr,UI_MSGTIMEOUT);
		EnrollParamSet(0);
		bRet = FALSE;
		goto _lExit;
	}


	//if (ui.txtPassword->text() != ui.txtPasswordConfirm->text())
	//{
	//	uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INCORRECT_PWD, UI_MSGTIMEOUT);
	//	ui.txtPassword->setText("");
	//	ui.txtPasswordConfirm->setText("");
	//	ui.txtPassword->setFocus(Qt::MouseFocusReason);
	//	bRet = FALSE;
	//	goto _lExit;
	//}

	if (TRUE)
	{
		USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

		memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));

		gUserInfoTemp.ID = m_nID;
		STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);   
		//gUserInfoTemp.PWD = STRING2PWD(STR2ASCII(ui.txtPassword->text()));
		DbUserInfoFlagManagerSet(&gUserInfoTemp, m_nManager);
		gUserInfoTemp.PART = ui.comboPart->currentIndex();    
	}

	m_nCandidateID = m_nID;

_lExit:
	return bRet;
}

BOOL CEnrollStep1::EnrollUserInfo()
{
	BOOL bRet;
	USER_INFO *TEMP, BACKUP;

	TEMP = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	if (TEMP)
		memcpy(&BACKUP, TEMP, sizeof(USER_INFO));

	bRet = DbUserInfoEnroll(&gUserInfoTemp, BACKUP_ALL, NULL);

	if (bRet)
	{
		if (m_bNew)
		{
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, m_nID, bRet);
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, m_nID, bRet);
		}
		else
		{
			if (memcmp(BACKUP.NAME, gUserInfoTemp.NAME, sizeof(WORD) * USERNAME_LENGTH) ||
				BACKUP.PWD != gUserInfoTemp.PWD ||
				DbUserInfoFlagManagerGet(&BACKUP) != DbUserInfoFlagManagerGet(&gUserInfoTemp) ||
				BACKUP.PART != gUserInfoTemp.PART)
			{
				if (BACKUP.PWD != gUserInfoTemp.PWD)
					uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, m_nID, bRet);
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, m_nID, bRet);
			}
		}
	}
	return bRet;
}

int CEnrollStep1::DoProcess(int nEdit /*=0*/)//注册处理第一步
{
	int nKey;
	BOOL bRet;
	QPushButton *pCurrentBtn;
	xprintf("nedit==%d\r\n",nEdit);
	xprintf("ID_NEW==%d\r\n",ID_NEW);
	m_nEdit = nEdit;
	if (m_nEdit == ID_NEW)
		m_bNew = TRUE;
	else if (m_nEdit == ID_BACKUP)
		m_bNew = FALSE;

	if(!m_bNew) 
	{
		uiLcdSetLabelText(ui.lblTitleText,UISTR(UISTR_USER_EDIT),TITLECOLOR,QColor());
		ui.txtID->setText(UserId_BCDtoSTR(gUserInfoTemp.ID));
		EnrollCheck(TRUE);
		EnrollParamSet(-1);
	}
	if(m_nEdit == ID_NEW)
	{
		uiLcdSetLabelText(ui.lblTitleText,UISTR(UISTR_USER_NEW),TITLECOLOR,QColor());
	}
	
	/*m_bTerminateFlag = !EnrollParamSet();*/
	
	ui.txtID->selectAll();
	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
//xprintf("i wait for press ok or esc ???\r\n");
		nKey = uiKeyGetKey(TRUE);

		switch (nKey)
		{
		//case UIKEY_F2://Save
		//	if (EnrollCheck())
		//	{
		//		if (EnrollUserInfo())
		//			uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLL_SAVEOK, UI_MSGTIMEOUT);
		//		else
		//			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_SAVEFAIL, UI_MSGTIMEOUT);
		//	}
		//	break;
		//case UIKEY_F3://NextEnroll
		//	m_bNew = TRUE;
		//	EnrollParamSet(1);
		//	break;
		case UIKEY_ESC:
			if (OnBtnESC())
				goto _lExit;
			break;
		case UIKEY_OK:
			pCurrentBtn = (QPushButton*)QApplication::focusWidget();
			if(pCurrentBtn == ui.btnOK)  
			bRet = OnBtnOK();  //转入下步骤
			break;  
		default:
			break;
		}
	}

_lExit:
	return 0;
}



void CEnrollStep1::OnFocusChanged(QWidget *from, QWidget *to)
{
	BOOL  bResult;
	xprintf("xxxx1\r\n");
	if (from == (QWidget*)ui.txtID)
	{
		xprintf("xxxx2\r\n");
		UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
		ui.txtID->setText(UserId_BCDtoSTR(nID)); //for empty string
		if(UserId_isOk()==0)
		{
		  	uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
		  	ui.txtID->setFocus(Qt::MouseFocusReason);
		  	ui.txtID->selectAll();	
		  	return ;
		}

		xprintf("xxxx3\r\n");
		if (!nID && (to == (QWidget*)ui.txtName || to == (QWidget*)ui.btnESC))
		{
			if (!EnrollCheck())
			{
				ui.txtID->setFocus(Qt::MouseFocusReason);
				ui.txtID->selectAll();
			}
			EnrollParamSet(-1);
		}	
		xprintf("xxxx4\r\n");
		if(USER_EDIT_FLAG==0 && dbLicense.bOnLineEnroll==TRUE) //在编辑用户时不要从服务器获取姓名。
		{
			if(to == (QWidget*)ui.txtName)
			{
				//获取服务器姓名
				xprintf("xxxx\r\n");
				xprintf("nID===%d\r\n",nID);
				int nRet;
				//当npin是1时，只获取name，0就下载注册
				nRet =HttpClient_main(DEVID,nID,0,0,HTTP_DEPTPUNCH,TRUE);
				xprintf("nRet===%d\r\n",nRet);
				if(nRet == 0)
				{
					xprintf("nRet===0\r\n");
					uiLcdMessageBox(UI_MSG_ERROR, UISTR_GET_NAME_FAIL, 1000);
					QString str = QWidget::tr("");	
					ui.txtName->setText(str);
					//ui.txtID->setFocus(Qt::MouseFocusReason);
					ui.txtID->selectAll();
				}
				else 
				{
					xprintf("gUserInfoTemp.NAME=%s \r\n", gUserInfoTemp.NAME);
					QString str =UNICODE2STRING((WORD *)gUserInfoTemp.NAME,USERNAME_LENGTH);
					//QString str = QWidget::tr((char *)gUserInfoTemp.NAME);	
					ui.txtName->setText(str);
				}
				/*	bResult=ComClientGetName(nID,gUserInfoTemp.NAME,USERNAME_LENGTH);
				if(bResult==0)
				{
				    	uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_GET_NAME_FAIL, 3000);
					QString str = QWidget::tr("");	
					ui.txtName->setText(str);
					ui.txtID->setFocus(Qt::MouseFocusReason);
					ui.txtID->selectAll();
				//	return ;
				}
				else if(bResult==3)
				{
				    uiLcdMessageBox(UI_MSG_ERROR, UISTR_SERVER_NO_ENROLL_ID, 3000);
					QString str = QWidget::tr("");	
					ui.txtName->setText(str);
					ui.txtID->setFocus(Qt::MouseFocusReason);
					ui.txtID->selectAll();
				//	return ;
				}			
				else
				{
					xprintf("gUserInfoTemp.NAME=%s \r\n", gUserInfoTemp.NAME);
					QString str =UNICODE2STRING((WORD *)gUserInfoTemp.NAME,USERNAME_LENGTH);
					//QString str = QWidget::tr((char *)gUserInfoTemp.NAME);	
					ui.txtName->setText(str);
				}
			*/	
			}
			else
			{
					ui.txtID->setFocus(Qt::MouseFocusReason);
					ui.txtID->selectAll();		
			}
			xprintf("xxxx5\r\n");
		}
		xprintf("xxxx6\r\n");
	}

	if (to == (QWidget*)ui.txtID)
		ui.txtID->selectAll();
	uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);

}

void CEnrollStep1::OnIDChange(const QString & szID)
{
	UINT64 nID = STRING2ID(STR2ASCII(szID));
	if (nID > 999999999)
	{
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
		ui.txtID->setText(ID2STRING(999999999));
		ui.txtID->selectAll();
	}
	EnrollCheck(TRUE);  
	EnrollParamSet(-1);  
}

void CEnrollStep1::OnPasswordChange(const QString & /*szPassword*/)
{
	//ui.txtPasswordConfirm->clear();
}

BOOL CEnrollStep1::OnBtnOK()
{
	int nRet;
	if (!EnrollCheck())//检测要注册的相关信息
		return FALSE;

	/*EnrollUserInfo();*/

	USER_INFO BACKUP;
	USER_INFO *pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	bzero(&BACKUP, sizeof(USER_INFO));
	if (pUI)
		memcpy(&BACKUP, pUI, sizeof(USER_INFO));

	memset(&gUserInfoTemp.NAME, 0, sizeof(gUserInfoTemp.NAME));  
	STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);  
	//xprintf("ui.txtName=%s \r\n", (const char*)U2G(ui.txtName->text()));

	if (pUI && memcmp(pUI, &gUserInfoTemp, sizeof(USER_INFO)))
		uiEnrollUserInfo(&gUserInfoTemp);//用户注册
xprintf("i must enter the second steps!!!\r\n");
	nRet = DIALOGBOXEX(CEnrollStep2,CEnrollStep2::NEW);//进入第二阶段注册
	pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	if (pUI && memcmp(&BACKUP, pUI, sizeof(USER_INFO)))
	{
		if (m_nEdit == ID_ALL)
		{
			m_bNew = TRUE;
			if (Db_GetUserCount() == dbLicense.nMaxEnrollCount)
			{
				m_bNew = FALSE;
				m_nCandidateID = 0;
			}
			EnrollParamSet(0);
		}
		else
		{
			if (Db_GetUserCount() == dbLicense.nMaxEnrollCount)
			{
				m_bTerminateFlag = TRUE;
				return TRUE;
			}
			EnrollParamSet(1);
		}
	}
	else
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}

	return TRUE;
}

BOOL CEnrollStep1::OnBtnESC()
{
// 	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
// 		return FALSE;

	m_bTerminateFlag = TRUE;
	return TRUE;
}

bool CEnrollStep1::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollStep2::CEnrollStep2(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	bTerminateFlag = FALSE;
	ui.setupUi(this);
	GUI_DLG_SET_THEME();

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR);
	
	ui.lblStatusText->setPalette(pal);

	if (!dbLicense.bUseCard)
		ui.btnEnrollCard->setEnabled(FALSE);

#if 	USE_CARD
	ui.btnEnrollFP->setEnabled(FALSE);
	ui.btnEnrollCard->setFocus(Qt::MouseFocusReason);
#endif

#if   1
	//m_BtnList.append(ui.btnEnrollFP);
#endif
	m_BtnList.append(ui.btnEnrollCard);
	m_BtnList.append(ui.btnEnrollPWD);
	ui.btnUserEdit->hide();	
	
	uiEnrollSetTitle(ui.lblTitleText);
	if(gUserInfoTemp.ID!=0)
		uiEnrollSetStatus(this, gUserInfoTemp.ID);
}

int CEnrollStep2::DoProcess(int nEdit)
{
	int nKey;
	if(nEdit == EDIT)
	{
		ui.btnUserEdit->show();
		m_BtnList.append(ui.btnUserEdit);
	}
	if(gUserInfoTemp.ID ==0) return 1;

	while (!bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(TRUE);

		if (nKey > 0 && nKey < m_BtnList.count() + 1)
		{
			if (m_BtnList[nKey] == ui.btnEnrollCard && !dbLicense.bUseCard)
				break;
			//if (m_BtnList[nKey-1] == ui.btnEnrollVoice && !dbLicense.bUseMP3)
			//	break;

			m_BtnList[nKey-1]->setFocus(Qt::MouseFocusReason);
			nKey = UIKEY_OK;
		}

		switch (nKey)
		{
		case UIKEY_OK:
xprintf("i am in step2'dorress OnKeyPressOK()\r\n");			
			OnKeyPressOK();
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}

_lExit:
	return 0;
}

BOOL CEnrollStep2::OnKeyPressOK()
{
	QPushButton *pCurrentBtn = (QPushButton*)QApplication::focusWidget();

	if (pCurrentBtn == ui.btnEnrollFP)
	{
// 		if (DbFpGetUnusedFingernumber(gUserInfoTemp.ID) >= dbLicense.nBackupNumber)
// 		{
// 			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLFP_FPFULL, UI_MSGTIMEOUT);
// 			goto _lExit;
// 		}

		xprintf("i should go to cenrollfp!!!\r\n");

		DIALOGBOX(CEnrollFP);//d调用指纹注册了

	}
	else if (pCurrentBtn == ui.btnEnrollCard)
	{
		if (DbUserInfoFlagEnrollStatusGet(&gUserInfoTemp, BACKUP_CARD) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLCARD_RFEXIST, UITIME_OUT))
			goto _lExit;
		DIALOGBOX(CEnrollCard);
	}
	//else if (pCurrentBtn == ui.btnEnrollVoice)
	//{
	//	if (!SDCARD_MOUNT())
	//	{
	//		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_NOTFOUND, UI_MSGTIMEOUT);
	//		goto _lExit;
	//	}
	//	//voice file check
	//	if (DbUserInfoHasVoice(gUserInfoTemp.ID) &&
	//		!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLVOICE_VOICEEXIST, UITIME_OUT))
	//		goto _lExit;
	//	DIALOGBOX(CEnrollVoice);
	//}
/*	else if (pCurrentBtn == ui.btnEnrollPhoto)
	{
	//	if (!SDCARD_MOUNT())
	//	{
	//		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_NOTFOUND, UI_MSGTIMEOUT);
	//		goto _lExit;
	//	}   
		if (!CAMERA_ON())
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_CAMERA_NOTFOUND, UI_MSGTIMEOUT);
			goto _lExit;
		}
		//photo file check
		if (DbUserInfoHasPhoto(gUserInfoTemp.ID) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLPHOTO_PHOTOEXIST, UITIME_OUT))
			goto _lExit;
		DIALOGBOX(CEnrollPhoto);
	}
	*/
	else if(pCurrentBtn == ui.btnEnrollPWD)
	{
	xprintf("i should go to cenrollpwd!!!\r\n");	
		if (DbUserInfoFlagEnrollStatusGet(&gUserInfoTemp, BACKUP_PASSWORD) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLPWD_PWDEXIST, UITIME_OUT))
			goto _lExit;

		DWORD dwPassword = DIALOGBOX_RET(CInputPWD);
		xprintf("111dwPassword==%d\r\n",dwPassword);
		xprintf("111dwPassword==%x\r\n",dwPassword);
		xprintf("111dwPassword==%p\r\n",dwPassword);
		if (dwPassword)
		{
			BOOL bResult;
			xprintf("comet1\r\n");
			xprintf("dwPassword==%d\r\n",dwPassword);
			bResult = uiEnrollUserInfo(&gUserInfoTemp);
			if (bResult)
			{
				bResult = uiPwdEnroll(&gUserInfoTemp, PWD2STRING(dwPassword));
				uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, gUserInfoTemp.ID, bResult);
				xprintf("comet4\r\n");
			}
			if (bResult)
			{
				xprintf("comet2\r\n");
				xprintf("dwPassword==%d\r\n",dwPassword);
				xprintf("gUserInfoTemp.PWD==%d\r\n",gUserInfoTemp.PWD);
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);

				//这里出现问题了
				//if(ComClientSendFingerData(gUserInfoTemp.ID,BACKUP_PASSWORD,(BYTE*)&dwPassword)==0)
					 //DbFpUploadDataSave(gUserInfoTemp.ID,BACKUP_PASSWORD,0);
				u32 ywmbymgr;
				if(gUserInfoTemp.FLAG.members.byMgr == 1)
				{
					ywmbymgr = 0;
				}
				else if(gUserInfoTemp.FLAG.members.byMgr == 6)
				{
					ywmbymgr = 2;
				}
				else if(gUserInfoTemp.FLAG.members.byMgr == 7)
				{
					ywmbymgr = 1;
				}
				else 
				{
					ywmbymgr = 0;
				}
					
				if(web2_send_finger(gUserInfoTemp.ID,BACKUP_PASSWORD,ywmbymgr,(u8*)&dwPassword) == 0)
				//if(sendfinger_web(gUserInfoTemp.ID,BACKUP_PASSWORD,ywmbymgr,(u8*)&(gUserInfoTemp.PWD)) == 0)	
				{
					DbFpUploadDataSave(gUserInfoTemp.ID,BACKUP_PASSWORD,0);//这个是在离线时记录的
					xprintf("loveywm3344\r\n");
				}
				
				xprintf("comet3\r\n");
			}
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLPWD_FAIL, UI_MSGTIMEOUT);
		}
	}
	else if(pCurrentBtn == ui.btnUserEdit)
	{
		DIALOGBOX(CUserEdit);
		uiEnrollSetTitle(ui.lblTitleText);
	}

_lExit:
	uiEnrollSetStatus(this, gUserInfoTemp.ID);
	return TRUE;
}

BOOL uiEnrollUserInfo(USER_INFO *pUserInfo)
{
	BOOL bRet = FALSE;
	BOOL bNew = FALSE;
	USER_INFO *TEMP, BACKUP;

	if (!pUserInfo)
		return FALSE;
	TEMP = (USER_INFO*)DbUserInfoGetPointer(pUserInfo->ID);
	if (TEMP)
	{
		bNew = TRUE;
		memcpy(&BACKUP, TEMP, sizeof(USER_INFO));
	}

	bRet = DbUserInfoEnroll(pUserInfo, BACKUP_ALL, NULL);  

	if (bRet)
	{
		if (bNew)
			uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, pUserInfo->ID, bRet);
		else
		{
			if (memcmp(BACKUP.NAME, pUserInfo->NAME, sizeof(WORD) * USERNAME_LENGTH) ||
				DbUserInfoFlagManagerGet(&BACKUP) != DbUserInfoFlagManagerGet(pUserInfo) ||
				BACKUP.PART != pUserInfo->PART)
			{
				uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, pUserInfo->ID, bRet);
			}
		}
	}
	return TRUE;
}

BOOL uiEnrollUserInfo2(USER_INFO *pUserInfo)
{
	BOOL bRet = FALSE;
	BOOL bNew = FALSE;
	USER_INFO *TEMP, BACKUP;

	if (!pUserInfo)
		return FALSE;
	TEMP = (USER_INFO*)DbUserInfoGetPointer(pUserInfo->ID);
	if (TEMP)
	{
		bNew = TRUE;
		memcpy(&BACKUP, TEMP, sizeof(USER_INFO));
	}

	bRet = DbUserInfoEnroll(pUserInfo, BACKUP_ALL, NULL);  

	if (bRet)
	{
		if (bNew)
			;//uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, pUserInfo->ID, bRet);
		else
		{
			if (memcmp(BACKUP.NAME, pUserInfo->NAME, sizeof(WORD) * USERNAME_LENGTH) ||
				DbUserInfoFlagManagerGet(&BACKUP) != DbUserInfoFlagManagerGet(pUserInfo) ||
				BACKUP.PART != pUserInfo->PART)
			{
				;//uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, pUserInfo->ID, bRet);
			}
		}
	}
	return TRUE;
}



void uiProcEnroll(USER_INFO */*pUserInfo*/, int nStr)
{
	if (nStr == UISTR_MENU_ENROLL_FP)
	{
		DIALOGBOX(CEnrollFP);
	}
	else if (nStr == UISTR_MENU_ENROLL_PWD)
	{
		if (DbUserInfoFlagEnrollStatusGet(&gUserInfoTemp, BACKUP_PASSWORD) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLPWD_PWDEXIST, UITIME_OUT))
			goto _lExit;

		DWORD dwPassword = DIALOGBOX_RET(CInputPWD);
		if (dwPassword)
		{
			BOOL bResult;
			bResult = uiEnrollUserInfo(&gUserInfoTemp);
			if (bResult)
			{
				bResult = uiPwdEnroll(&gUserInfoTemp, PWD2STRING(dwPassword));
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, gUserInfoTemp.ID, bResult);
			}
			if (bResult)
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLPWD_FAIL, UI_MSGTIMEOUT);
		}
	}
	else if (nStr == UISTR_MENU_ENROLL_RFCARD)
	{
		if (DbUserInfoFlagEnrollStatusGet(&gUserInfoTemp, BACKUP_CARD) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLCARD_RFEXIST, UITIME_OUT))
			goto _lExit;
		DIALOGBOX(CEnrollCard);
	}
	else if (nStr == UISTR_MENU_ENROLL_VOICE)
	{
		if (!DbUserInfoGetPointer(gUserInfoTemp.ID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
			goto _lExit;
		}
		if (!SDCARD_MOUNT())
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_NOTFOUND, UI_MSGTIMEOUT);
			goto _lExit;
		}
		//voice file check
		if (DbUserInfoHasVoice(gUserInfoTemp.ID) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLVOICE_VOICEEXIST, UITIME_OUT))
			goto _lExit;
		DIALOGBOX(CEnrollVoice);
	}
	else if (nStr == UISTR_MENU_ENROLL_PHOTO)
	{
		if (!DbUserInfoGetPointer(gUserInfoTemp.ID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
			goto _lExit;
		}
		if (!SDCARD_MOUNT())
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SDCARD_NOTFOUND, UI_MSGTIMEOUT);
			goto _lExit;
		}
		if (!CAMERA_ON())
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_CAMERA_NOTFOUND, UI_MSGTIMEOUT);
			goto _lExit;
		}
		//photo file check
		if (DbUserInfoHasPhoto(gUserInfoTemp.ID) &&
			!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLPHOTO_PHOTOEXIST, UITIME_OUT))
			goto _lExit;
		DIALOGBOX(CEnrollPhoto);
	}

_lExit:
	return;
}

BOOL uiProcEnrollDelete(UINT64 nID, int nStr)
{
	int nBackup = 0;
	int nSLogType = -1;
	USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);

	if (!pUserInfo)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
		return FALSE;
	}

	if (nStr == UISTR_MENU_DELETE_FP)
	{
		if (!DbFpGetFingerCountPerUser(pUserInfo))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOFP, UI_MSGTIMEOUT);
			return TRUE;
		}

		for (int i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
			nBackup |= (0x01 << i);
		nSLogType = SLOG_DELETE_FP;
	}
	else if (nStr == UISTR_MENU_DELETE_RFCARD)
	{
		if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_CARD))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOCARD, UI_MSGTIMEOUT);
			return TRUE;
		}

		nBackup |= (0x01 << BACKUP_CARD);
		nSLogType = SLOG_DELETE_CARD;
	}
	else if (nStr == UISTR_MENU_REMOVE_PWD)
	{
		if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_PASSWORD))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOPWD, UI_MSGTIMEOUT);
			return TRUE;
		}

		nBackup |= (0x01 << BACKUP_PASSWORD);
		nSLogType = SLOG_DELETE_PASSWORD;
	}
	else if (nStr == UISTR_MENU_DELETE_VOICE)
	{
		if (!DbUserInfoHasVoice(nID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOVOICE, UI_MSGTIMEOUT);
			return TRUE;
		}

		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
		{
			unlink(DbUserInfoGetVoiceFilename(nID));
			DbUserInfoSetVoice(nID, FALSE);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLLDELETE_DELETESUCCESS, UI_MSGTIMEOUT);
		}
	}
	else if (nStr == UISTR_MENU_DELETE_PHOTO)
	{
		if (!DbUserInfoHasPhoto(nID))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOPHOTO, UI_MSGTIMEOUT);
			return TRUE;
		}

		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
		{
			unlink(DbUserInfoGetPhotoFilename(nID));
			DbUserInfoSetPhoto(nID, FALSE);
			uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLLDELETE_DELETESUCCESS, UI_MSGTIMEOUT);
		}
	}
	else if (nStr == UISTR_MENU_DELETE_ALL)
	{
		nBackup = 0xFFFF;
		nSLogType = SLOG_DELETE_USER;
	}

	if (nBackup && uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
	{
		BOOL bResult;
		bResult = DbUserInfoDelete(nID, nBackup);
		uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLLDELETE_DELETESUCCESS, UI_MSGTIMEOUT);
		if (nSLogType)
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, (BYTE)nSLogType, nID, bResult);
	}

	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
enum {T_ENROLL_TIMEOUT, T_ENROLL_ESC, T_ENROLL_OK, T_ENROLL_RETRY, T_ENROLL_NEXT};

CEnrollFP::CEnrollFP(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR);

 	pal.setColor(QPalette::All, QPalette::Text, QColor(0,250,0));
	ui.txtFpNumber->setPalette(pal);

	m_pmapFinger = *ui.lblFpArea->pixmap();
	uiEnrollSetTitle(ui.lblTitleText);

	ui.lblFpNumber->hide();
	ui.txtFpNumber->hide();
}

int CEnrollFP::EnrollFPExit()
{
	int nRet = T_ENROLL_TIMEOUT;
	int nKey;
	BOOL bExit = FALSE;

	//ui.btnOK->setEnabled(TRUE);
	//ui.btnOK->setFocus(Qt::MouseFocusReason);

	while (!bExit && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();	

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_UP://Retry
			nRet = T_ENROLL_RETRY;
			bExit = TRUE;
			break;
		case UIKEY_DOWN://Next Enroll
			nRet = T_ENROLL_NEXT;
			bExit = TRUE;
			break;
		case UIKEY_OK:
			nRet = T_ENROLL_OK;
			bExit = TRUE;
			break;
		case UIKEY_ESC:
			nRet = T_ENROLL_ESC;
			bExit = TRUE;
			break;
		}
	}

	return nRet;
}

int CEnrollFP::DoProcess()
{
	int nFpEnrollStep;
	int nRet;
	UINT64 nID = gUserInfoTemp.ID;
	int nFP = DbFpGetUnusedFingernumber(nID);
//	WORD wEnrollMask = Db_GetEnrolledIDMask(nID);
	QString szFingerNumber;
	int nEnrollStatus = 0;
	int nKey;
	int nPosFP, nPosUI = DbUserInfoGetPosition(nID);
	int  INDEX_BACKUP_POS = -1;
	BYTE INDEX_BACKUP_VAL = 0;
//	FPINFO FP_BACKUP;
	BOOL bFpFull = FALSE;
	BOOL bResult;
	//UINT64 j;
	//BOOL bRet;
xprintf("loveywm 111\r\n");
	memset(SB_FP__256IMAGE, 192, 256*256);
	DrawFingerprint(ui.lblFpArea, &m_pmapFinger);
	POST_EVENTS();
labeFpEnrollStart:
	INDEX_BACKUP_POS = -1;
	if (nFP == dbLicense.nBackupNumber || DbUserInfoGetCount(BACKUP_FINGER) == dbLicense.nMaxEnrollCount)
	{
		if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLFP_FPFULL, UITIME_OUT))
		{
			bFpFull = TRUE;
			nFP = DbFpGetUsedFingernumber(nID);
		}
		else
			return nEnrollStatus;
	}
	if (bFpFull && nFP == -1)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOFP, UI_MSGTIMEOUT);
		return nEnrollStatus;
	}

	uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESSFP1), FOREGROUND_COLOR);
	uiSoundOut(SOUND_PRESSFINGER_1, UI_BUZZER_NONE, UITIME_VOICE, TRUE);

labelAgainFpEnroll:
	if (INDEX_BACKUP_POS >= 0)
	{
		gpIndexData[INDEX_BACKUP_POS] = INDEX_BACKUP_VAL;
//		memcpy(&gpFingerEnrollData[INDEX_BACKUP_POS], &FP_BACKUP, sizeof(FPINFO));
		INDEX_BACKUP_POS = -1;
	}
	if (nPosUI < dbLicense.nMaxEnrollCount)
	{
		nPosFP = DbFpGetPosition(nPosUI, nFP);
		if (nPosFP >= 0)
		{
			INDEX_BACKUP_POS = nPosFP;
			INDEX_BACKUP_VAL = gpIndexData[nPosFP];
//			memcpy(&FP_BACKUP, &gpFingerEnrollData[nPosFP], sizeof(FPINFO));
			gpIndexData[nPosFP] = 0;
		}
	}

	szFingerNumber = QString("%1-%2")
		.arg(UserId_BCDtoSTR(gUserInfoTemp.ID))
		.arg(nFP);
	ui.txtFpNumber->setText(szFingerNumber);
	ui.txtFpNumber->setFocus(Qt::MouseFocusReason);
	ui.txtFpNumber->setSelection(szFingerNumber.length() - 1, 1);

	memset(SB_FP__256IMAGE, 192, 256*256);
	DrawFingerprint(ui.lblFpArea, &m_pmapFinger);

	if (bFpFull && !DbUserInfoGetPointer(nID, nFP))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLFP_NOT_ENROLLED, UI_MSGTIMEOUT);
		nFP =  DbFpGetUsedFingernumber(nID, nFP);
		goto labelAgainFpEnroll;
	}

	//ui.btnOK->setEnabled(FALSE);
	//ui.btnESC->setFocus(Qt::MouseFocusReason);
	FP_DrawEnrollStatus(0);
	nFpEnrollStep = 1;
	uiFpEnrollStart();//注册函数
xprintf("loveywm 222\r\n");
//以nFpEnrollStep为标志在这里循环三次获取指纹，最后一次完成，然后上传
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_ESC)
			goto _lExit;
		if (nKey == UIKEY_UP)
			goto labeFpEnrollStart;
// 		if (nFpEnrollStep == 1 && nKey >= UIKEY_0 && nKey <= UIKEY_9)
// 		{
// 			nFP = nKey;
// 			goto labelAgainFpEnroll;
// 		}

		if (uiCMOSCaptureFP())//注意这个函数里面的信息
		{
			uiBuzzerAlarm();
//			if (dbSetupTotal.setSystem.bFPShow)
//			{
				DrawFingerprint(ui.lblFpArea, &m_pmapFinger);
				POST_EVENTS();
//			}
			uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_TAKEOFF), FOREGROUND_COLOR);
			nRet = uiFpEnrollNth(nFpEnrollStep);//取第一个指纹
			if (nRet != UIENROLL_RET_TRUE)
				nFpEnrollStep = 3;
			else
				FP_DrawEnrollStatus(nFpEnrollStep);
xprintf("loveywm 333\r\n");
xprintf("nFpEnrollStep==%d\r\n",nFpEnrollStep);
			if (nFpEnrollStep < 3)
			{
				WAIT_EVENT((uiCMOSIsPressFP()));//循环指纹是否按下
			}

			if (nRet != UIENROLL_RET_TRUE || nFpEnrollStep != 3)
			{
				memset(SB_FP__256IMAGE, 192, 256*256);
				DrawFingerprint(ui.lblFpArea, &m_pmapFinger);
			/*	ui.btnESC->setFocus(Qt::MouseFocusReason);*/
			}

			nFpEnrollStep++;
xprintf("loveywm 444\r\n");
xprintf("nFpEnrollStep==%d\r\n",nFpEnrollStep);
xprintf("loveywm 555\r\n");
xprintf("nRet==%d\r\n",nRet);
			if (nFpEnrollStep == 2)
			{
				uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESSFP2), FOREGROUND_COLOR);
				uiSoundOut(SOUND_PRESSFINGER_2, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
			}
			else
				if (nFpEnrollStep == 3)
				{
					uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESSFP3), FOREGROUND_COLOR);
					uiSoundOut(SOUND_PRESSFINGER_3, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
				}
				else
					if (nFpEnrollStep == 4)
					{   
						if (nRet == UIENROLL_RET_TRUE)
							nRet = uiFpEnrollEnd((FPINFO*)&gFpData[0]);//指纹

						if (nRet == UIENROLL_RET_FALSE)
						{
							uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESAGAIN), FOREGROUND_COLOR);
							uiSoundOut(SOUND_PRESSFP_RETRY, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
							uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_BACKUPENROLL_FP, nID, FALSE);
							goto labelAgainFpEnroll;
						}

						if (nRet == UIENROLL_RET_DUPLICATE)
						{
							uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_FPDOUBLED), FOREGROUND_COLOR);
							uiSoundOut(SOUND_FPDOUBLED, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
							uiTimeDelay(1000);
//							uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_TAKEOFF), FOREGROUND_COLOR);
							WAIT_EVENT((uiCMOSIsPressFP()));
							uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESAGAIN), FOREGROUND_COLOR);
							uiSoundOut(SOUND_PRESSFP_RETRY, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
							uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_BACKUPENROLL_FP, nID, FALSE);
							goto labelAgainFpEnroll;
						}
						
//						WAIT_EVENT((uiCMOSIsPressFP()));
						nEnrollStatus |= (1 << nFP);
						bResult = uiEnrollUserInfo(&gUserInfoTemp);
				xprintf("bResult==%d\r\n",bResult);
						if (bResult)
						{
						 /*      if(ComClientSendFingerImage(gUserInfoTemp.ID, nFP, SB_FP__256IMAGE)==0)
						       {
								uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLL_FAIL), FOREGROUND_COLOR);
								uiSoundOut(SOUND_PRESSFP_RETRY, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
								uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_BACKUPENROLL_FP, nID, FALSE);
								goto labelAgainFpEnroll;
						       }   */
							   
							bResult = DbUserInfoEnroll(&gUserInfoTemp, nFP, &gFpData[0]);//在这里注册了
							uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_BACKUPENROLL_FP, nID, bResult);
							uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_ENROLLSUCCESS), FOREGROUND_COLOR);
							uiSoundOut(SOUND_FPENROLL_SUCCESS, UI_BUZZER_OK, UITIME_VOICE, TRUE);
							
							//ComClientSendFingerImage(gUserInfoTemp.ID, nFP, SB_FP__256IMAGE);
							//最好在这里先判断下网络有没有连上，然后再上传(这个暂时没完成)
							//if(ComClientSendFingerData(gUserInfoTemp.ID,nFP,(BYTE*)&gFpData[0])==0)//在这里发送了，则就是我要找的,改动这个函数了
							//整理权限
							u32 ywmbymgr;
							if(gUserInfoTemp.FLAG.members.byMgr == 1)
							{
								ywmbymgr = 0;
							}
							else if(gUserInfoTemp.FLAG.members.byMgr == 6)
							{
								ywmbymgr = 2;
							}
							else if(gUserInfoTemp.FLAG.members.byMgr == 7)
							{
								ywmbymgr = 1;
							}
							else 
							{
								ywmbymgr = 0;
							}
							if(web2_send_finger(gUserInfoTemp.ID,nFP,ywmbymgr,(u8*)&gFpData[0]) == 0)
							{
								DbFpUploadDataSave(gUserInfoTemp.ID,nFP,0);//这个是在离线时记录的
								xprintf("loveywm3344\r\n");
							}
						}
						break;
					}
		}
	}

	if (uiTimeIsTimeout())
		goto _lExit;

_lEnrollFPExit:
	nRet = EnrollFPExit();
	if (nRet == T_ENROLL_RETRY)
	{
// 		if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
// 			goto _lEnrollFPExit;
		DbUserInfoDelete(gUserInfoTemp.ID, 1<<nFP);
		uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLFP_PRESAGAIN), FOREGROUND_COLOR);
		uiSoundOut(SOUND_PRESSFP_RETRY, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
		goto labelAgainFpEnroll;
	}
	else if (nRet == T_ENROLL_NEXT)
	{
		nFP = DbFpGetUnusedFingernumber(nID, nFP);
		goto labeFpEnrollStart;
	}
	else if (nRet == T_ENROLL_OK)
	{
		goto _lExit;  
	}
	else
	{
	}

	return nEnrollStatus;

_lExit:

	if (INDEX_BACKUP_POS >= 0)
	{
		gpIndexData[INDEX_BACKUP_POS] = INDEX_BACKUP_VAL;
//		memcpy(&gpFingerEnrollData[INDEX_BACKUP_POS], &FP_BACKUP, sizeof(FPINFO));
		INDEX_BACKUP_POS = -1;
	}

	return nEnrollStatus;
}

void CEnrollFP::FP_DrawEnrollStatus(int Nth)
{
	switch (Nth)
	{
	case 1:
		ui.lblEnrollStatus1->setEnabled(TRUE);
		break;
	case 2:
		ui.lblEnrollStatus2->setEnabled(TRUE);
		break;
	case 3:
		ui.lblEnrollStatus3->setEnabled(TRUE);
		break;
	default:
		ui.lblEnrollStatus1->setEnabled(FALSE);
		ui.lblEnrollStatus2->setEnabled(FALSE);
		ui.lblEnrollStatus3->setEnabled(FALSE);
		break;
	}
}

BOOL CEnrollFP::OnKeyPressOK()
{
	return TRUE;
}

BOOL CEnrollFP::OnKeyPressESC()
{
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollCard::CEnrollCard(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	uiEnrollSetTitle(ui.lblTitleText);
}

void CEnrollCard::DoProcess()
{
	int nKey;
	BOOL bResult;
	DWORD dwID, dwIDValid = 0;
	BOOL bDisabled;
	USER_INFO TEMP;
	char szBuf[32]; 

	ui.txtCardNumber->setFocus(Qt::MouseFocusReason);
	uiSoundOut(SOUND_INPUT_CARD, UI_BUZZER_NONE, UITIME_VOICE, TRUE);

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		dwID = uiCardCapture();

		if (dwID != 0)
		{
			if ((uiCardVerify(dwID, &TEMP, &bDisabled) || bDisabled) && (TEMP.ID != gUserInfoTemp.ID))
			{
				ui.lblEnrollStatus->setText(UISTR(UISTR_ENROLLCARD_RFDOUBLED_REINPUT));
				ui.txtCardNumber->setText("");
				uiSoundOut(SOUND_CARDDOUBLED_RETRY, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
				dwIDValid = 0;
				uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_CARD, gUserInfoTemp.ID, FALSE);
				continue;
			}
			else
			{
				ui.lblEnrollStatus->setText(UISTR(UISTR_ENROLLCARD_ENROLLSUCCESS));
				//ui.txtCardNumber->setText(QString("%1").arg(dwID));
                			if (gWgInLength == 26)
					 sprintf(szBuf, "%u", dwID);
				//else sprintf(szBuf, "%x", dwID);
				else if (WiegandCardType==1) 
					sprintf(szBuf, "%u", dwID);
				else 
					sprintf(szBuf, "%x", dwID);
				ui.txtCardNumber->setText(szBuf);				
				ui.btnOK->setFocus(Qt::MouseFocusReason);
				uiSoundOut(SOUND_CARDENROLL_SUCCESS, UI_BUZZER_OK, UITIME_VOICE, TRUE);
				dwIDValid = dwID;	
			}
		}

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_UP:
			dwIDValid = 0;
			ui.txtCardNumber->setText("");
			ui.txtCardNumber->setFocus(Qt::MouseFocusReason);
			ui.lblEnrollStatus->setText(UISTR(UISTR_ENROLLCARD_INPUTRF));
			uiSoundOut(SOUND_INPUT_CARD, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
			break;
		case UIKEY_OK:
			if (dwIDValid)
			{
				bResult = uiCardEnroll(&gUserInfoTemp, dwIDValid);
				uiLogSlogAdd2(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_CARD, gUserInfoTemp.ID, bResult);
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, 0, TRUE);
				//if(ComClientSendFingerData(gUserInfoTemp.ID,BACKUP_CARD,(BYTE*)&dwIDValid)==0)
				     //DbFpUploadDataSave(gUserInfoTemp.ID,BACKUP_CARD,0);
				u32 ywmbymgr;
				if(gUserInfoTemp.FLAG.members.byMgr == 1)
				{
					ywmbymgr = 0;
				}
				else if(gUserInfoTemp.FLAG.members.byMgr == 6)
				{
					ywmbymgr = 2;
				}
				else if(gUserInfoTemp.FLAG.members.byMgr == 7)
				{
					ywmbymgr = 1;
				}
				else 
				{
					ywmbymgr = 0;
				}
					
				if(web2_send_finger(gUserInfoTemp.ID,BACKUP_CARD,ywmbymgr,(u8*)&dwIDValid) == 0)	
				{
					DbFpUploadDataSave(gUserInfoTemp.ID,BACKUP_CARD,0);//这个是在离线时记录的
					xprintf("loveywm card\r\n");
				}     
				goto _lExit;
			}
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}
_lExit:
	return;
}

BOOL CEnrollCard::OnKeyPressOK()
{
	return TRUE;
}

BOOL CEnrollCard::OnKeyPressESC()
{
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollVoice::CEnrollVoice(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	ui.lblRecoredStat2->hide();
	ui.lblLeftSecond->hide();

	m_pmapVoicePlay = QPixmap(GUI_RESOURCE_PATH "voice-play.png");
	m_pmapVoiceRec  = QPixmap(GUI_RESOURCE_PATH "voice-rec.png");
	m_pmapVoiceFlow1= QPixmap(GUI_RESOURCE_PATH "voice-flow1.png");
	m_pmapVoiceFlow2= QPixmap(GUI_RESOURCE_PATH "voice-flow2.png");

	ui.lblRecoredStat2->setPixmap(m_pmapVoiceFlow2);
	ui.lblFilename->setText(QString(DbUserInfoGetVoiceFilename(gUserInfoTemp.ID)).section('/', -1));
	m_unRecState = 0;
	uiEnrollSetTitle(ui.lblTitleText);
}

void CEnrollVoice::DoProcess()
{
	int nKey;
	DWORD nStartRecTime = 0;
//	DWORD nLoopStatus = 1;
	DWORD nPrevDisplayTime = 0;
//	char szVoiceTemp[] = SDCARD_MOUNTPOINT PATH_USER_VOICE "/VOICE-TEMP.wav";
	char szVoiceTemp[] = "/tmp/voice-temp.wav";

	ui.lblRecoredStat1->setPixmap(m_pmapVoicePlay);
	ui.lblStatusText->setText(UISTR(UISTR_ENROLLVOICE_START));
	ui.lblEnrollStatus->setFocus(Qt::MouseFocusReason);
	uiSoundOut(SOUND_TALK_YOURNAME, UI_BUZZER_NONE, UITIME_VOICE, TRUE);

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_OK:
			if (m_unRecState%2 == 0)
			{
				if (!COPY_FILE(szVoiceTemp, DbUserInfoGetVoiceFilename(gUserInfoTemp.ID)) ||
					!DbUserInfoSetVoice(gUserInfoTemp.ID, TRUE))
				{
					uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
					break;
				}
				goto _lExit;
			}
			break;
		/*case UIKEY_RIGHT:
			if(OnVoiceRecord(szVoiceTemp) == 0)
			{
				nStartRecTime = 0;
				ui.btnOK->setFocus(Qt::MouseFocusReason);
			}
			else
			{
				nStartRecTime = uiTimeGetTickCount();
				ui.lblEnrollStatus->setFocus(Qt::MouseFocusReason);
			}
			break;*/
		case UIKEY_ESC:
			if (m_unRecState%2 == 0)
			{
				DELETE_FILE(szVoiceTemp);
				goto _lExit;
			}
			break;
		}

		if (nStartRecTime && (m_unRecState != 0))
		{
			int nDiffTime = uiTimeGetTickCount() - nStartRecTime;

			if (nDiffTime > 10000)
			{
				OnVoiceRecord(szVoiceTemp);//stop
				nStartRecTime = 0;
			}
			else
			{
				if (uiTimeGetTickCount() - nPrevDisplayTime > 500)
				{
					int nStatePix = (nDiffTime / 500) % 2;
					if ((nStatePix)== 0)
						ui.lblRecoredStat2->setPixmap(m_pmapVoiceFlow1);
					else if((nStatePix) == 1)
						ui.lblRecoredStat2->setPixmap(m_pmapVoiceFlow2);
					nPrevDisplayTime = uiTimeGetTickCount();
					ui.lblLeftSecond->setText(QString("%1%2").arg(10 - nDiffTime / 1000).arg(UISTR(UISTR_UNIT_SECOND)));
				}
			}
		}
	}
_lExit:
	return;
}

BOOL CEnrollVoice::OnKeyPressOK()
{
	return TRUE;
}

int CEnrollVoice::OnVoiceRecord(char *szFilename)
{
	++m_unRecState;
//	printf("OnVoiceRecord rec -> m_unRecState = %d\n", m_unRecState);
	if((m_unRecState % 2) == 1){
		DWORD dwDummy = 0;
		if(!SAVE_FILE(szFilename, (BYTE*)&dwDummy, sizeof(dwDummy)))
			return 0;
		ui.lblLeftSecond->setText("");
		ui.lblRecoredStat2->show();
		ui.lblLeftSecond->show();
		
		ui.lblRecoredStat1->setPixmap(m_pmapVoiceRec);

		ui.lblStatusText->setText(UISTR(UISTR_ENROLLVOICE_STOP));
//		printf("OnVoiceRecord->wave_rec_start - 0\n");
//		if (Wave_Rec_Start(szFilename) < 0)
		{
//			printf("record starting fail.\r\n");
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UITIME_OUT);

			ui.lblRecoredStat1->setPixmap(m_pmapVoicePlay);
			ui.lblRecoredStat2->hide();
			ui.lblLeftSecond->hide();
			ui.lblStatusText->setText(UISTR(UISTR_ENROLLVOICE_START));
			uiSoundOut(SOUND_VOICERECORD_RETRY, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
			m_unRecState = 0;
			return -1;
		}
//		printf("OnVoiceRecord->wave_rec_start - 1\n");
		uiTimeDelay(1000);
//		Wave_Rec_End();
	}
	else{
//		printf("wave_rec_end - 0\n");
		m_unRecState = 0;
//		Wave_Rec_End();
		ui.lblRecoredStat2->hide();
		ui.lblLeftSecond->hide();
		ui.lblStatusText->setText(UISTR(UISTR_ENROLLVOICE_START));
		ui.lblRecoredStat1->setPixmap(m_pmapVoicePlay);
		uiTimeDelay(1);
		uiSoundOut(SOUND_VOICERECORD_SUCCESS, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
		uiTimeDelay(10);
		if (uiLcdMessageBox(UI_MSG_QUESTION, USITR_ENROLLVOICE_PLAYBACK, UITIME_OUT)){
			uiTimeDelay(1);
//			MP3_PLAY(szFilename);
			uiTimeDelay(1);
		}
//		printf("wave_rec_end - 1\n");
		return 0;
	}

	return 1;
}

BOOL CEnrollVoice::OnKeyPressESC()
{
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollPhoto::CEnrollPhoto(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR);
	ui.lblTitleText->setPalette(pal);
	ui.lblEnrollStatus->setPalette(pal);

	uiEnrollSetTitle(ui.lblTitleText);
}

void CEnrollPhoto::DoProcess()
{
	int nKey;
	int nStatus = 0;
	QPixmap pmap = *ui.lblCameraArea->pixmap();
	QPixmap pmap_raw;
	int nSize = 0;

	ui.lblEnrollStatus->setFocus(Qt::MouseFocusReason);
	uiSoundOut(SOUND_PREPARE_FOR_PHOTO, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
//	sb_ResumeVideo(&g_VideoIn);

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		if (nStatus == 0)
		{
			if (CAMERA_CAPTURE())
			{
				nSize = sb_get_jpg_size(&g_VideoIn);
				pmap_raw.loadFromData(g_VideoIn.pFramebuffer, nSize);
				DrawCamera(ui.lblCameraArea, &pmap, &pmap_raw);
			}
			else
				ui.lblCameraArea->setPixmap(pmap);
		}

		nKey = uiKeyGetKey();
		switch (nKey)
		{
		case UIKEY_ESC:
			goto _lExit;
		case UIKEY_OK:
			if (nStatus == 1)
			{
				if (SAVE_FILE(DbUserInfoGetPhotoFilename(gUserInfoTemp.ID), g_VideoIn.pFramebuffer, nSize) &&
					DbUserInfoSetPhoto(gUserInfoTemp.ID, TRUE))
				{
					uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				}
				else
				{
					uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
					uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLPHOTO_RETRY), FOREGROUND_COLOR);
					uiTimeDelay(1000);
					nStatus = 0;
					uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLPHOTO_PREPARE), FOREGROUND_COLOR);
					uiSoundOut(SOUND_PREPARE_FOR_PHOTO, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
					break;
				}
				goto _lExit;
			}
			break;
		/*case UIKEY_RIGHT:
			if (nStatus == 0)
			{
				uiSoundOut(SOUND_CAMERA_TONE, UI_BUZZER_NONE, UITIME_VOICE);
				nStatus = 1;
				uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLPHOTO_SUCCESS), FOREGROUND_COLOR);
				ui.btnOK->setFocus(Qt::MouseFocusReason);
				uiSoundOut(SOUND_PHOTO_SUCCESS, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
			}
			break;*/
		case UIKEY_UP:
			if (nStatus == 1)
			{
				nStatus = 0;
				uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(UISTR_ENROLLPHOTO_PREPARE), FOREGROUND_COLOR);
				ui.lblEnrollStatus->setFocus(Qt::MouseFocusReason);
				uiSoundOut(SOUND_PREPARE_FOR_PHOTO, UI_BUZZER_NONE, UITIME_VOICE, TRUE);
			}
			break;
		}
	}
_lExit:
//	sb_PauseVideo(&g_VideoIn);
	
	return;
}

BOOL CEnrollPhoto::OnKeyPressOK()
{
	return TRUE;
}

BOOL CEnrollPhoto::OnKeyPressESC()
{
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CEnrollDelete::CEnrollDelete(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	m_bTerminateFlag = FALSE;
//	m_nID = DIALOGBOX_RET(CInputUserID);
	m_nID = gUserInfoTemp.ID;
	if (m_nID && m_nID != (UINT64)(-1))
	{
		USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
		else
			memset(&gUserInfoTemp, 0, sizeof(USER_INFO));

		if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
		{
			int nPrivManager = DbUserInfoGetPrivilege(m_nID);
			if (nPrivManager == PRIV_SMGR ||
				(nPrivManager == PRIV_MGR && m_nID != g_uiProcStatus.nIDCurrentMgr))
			{
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
				m_bTerminateFlag = TRUE;
			}
		}
	}
	else
		m_bTerminateFlag = TRUE;

	GUI_DLG_IMPL(FALSE);
	GUI_DLG_SET_THEME();

	if (!dbLicense.bUseCard)
		ui.btnDeleteCard->setEnabled(FALSE);
	if (!dbLicense.bUseMP3)
		//ui.btnDeleteVoice->setEnabled(FALSE);

	m_BtnList.append(ui.btnDeleteFP);
	m_BtnList.append(ui.btnDeleteCard);
	m_BtnList.append(ui.btnDeletePwd);
	//m_BtnList.append(ui.btnDeleteVoice);
	//m_BtnList.append(ui.btnDeletePhoto);
	m_BtnList.append(ui.btnDeleteAll);

	uiEnrollSetTitle(ui.lblTitleText);
	uiEnrollSetStatus(this, m_nID);
}

void CEnrollDelete::DoProcess()
{
	int nKey;

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(TRUE);

		if (nKey > 0 && nKey < m_BtnList.count() + 1)
		{
			if (m_BtnList[nKey-1] == ui.btnDeleteCard && !dbLicense.bUseCard)
				break;
			//if (m_BtnList[nKey-1] == ui.btnDeleteVoice && !dbLicense.bUseMP3)
			//	break;

			m_BtnList[nKey-1]->setFocus(Qt::MouseFocusReason);
			nKey = UIKEY_OK;
		}

		switch (nKey)
		{
		case UIKEY_OK:
			OnKeyPressOK();
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}
_lExit:
	return;
}

BOOL CEnrollDelete::OnKeyPressOK()
{
	QPushButton *pCurrentBtn = (QPushButton*)QApplication::focusWidget();
	USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);
	int nBackup = 0;
	int nSLogType = -1;
	BOOL bResult;

	if (!pUserInfo)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NODATA, UI_MSGTIMEOUT);
		return FALSE;
	}

	if (pCurrentBtn == ui.btnDeleteFP)
	{
		if (!DbFpGetFingerCountPerUser(pUserInfo))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOFP, UI_MSGTIMEOUT);
			return TRUE;
		}

		for (int i=BACKUP_FINGER0; i<=BACKUP_FINGER9; i++)
			nBackup |= (0x01 << i);
		nSLogType = SLOG_DELETE_FP;
	}
	else if (pCurrentBtn == ui.btnDeleteCard)
	{
		if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_CARD))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOCARD, UI_MSGTIMEOUT);
			return TRUE;
		}

		nBackup |= (0x01 << BACKUP_CARD);
		nSLogType = SLOG_DELETE_CARD;
	}
	else if (pCurrentBtn == ui.btnDeletePwd)
	{
		if (!DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_PASSWORD))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLLDELETE_NOPWD, UI_MSGTIMEOUT);
			return TRUE;
		}

		nBackup |= (0x01 << BACKUP_PASSWORD);
		nSLogType = SLOG_DELETE_PASSWORD;
	}
	/*else if (pCurrentBtn == ui.btnDeleteVoice)
	{
		if (DbUserInfoHasVoice(m_nID))
		{
			if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
			{
				unlink(DbUserInfoGetVoiceFilename(m_nID));
				DbUserInfoSetVoice(m_nID, FALSE);
				uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
			}
		}
	}
	else if (pCurrentBtn == ui.btnDeletePhoto)
	{
		if (DbUserInfoHasPhoto(m_nID))
		{
			if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
			{
				unlink(DbUserInfoGetPhotoFilename(m_nID));
				DbUserInfoSetPhoto(m_nID, FALSE);
				uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
			}
		}
	}*/
	else if (pCurrentBtn == ui.btnDeleteAll)
	{
		nBackup = 0xFFFF;
		nSLogType = SLOG_DELETE_USER;
	}

	if (nBackup && nSLogType != SLOG_DELETE_USER &&uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ENROLLDELETE_DELETECONFIRM, UITIME_OUT))
	{
		bResult = DbUserInfoDelete(m_nID, nBackup);   
		uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLLDELETE_DELETESUCCESS, UI_MSGTIMEOUT);
		if (nSLogType)
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, (BYTE)nSLogType, m_nID, bResult);
	}
	else if (nBackup && nSLogType == SLOG_DELETE_USER &&uiLcdMessageBox(UI_MSG_QUESTION, UISTR_STATUS_MSG_ALLDEL_ALARM, UITIME_OUT))
	{
		bResult = DbUserInfoDelete(m_nID, nBackup);   
		uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLLDELETE_DELETESUCCESS, UI_MSGTIMEOUT);
		if (nSLogType)
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, (BYTE)nSLogType, m_nID, bResult);
		DbFpUploadDataClear(m_nID);
	}   
	uiEnrollSetStatus(this, m_nID);

	return TRUE;
}

BOOL CEnrollDelete::OnKeyPressESC()
{
	return TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CDuressFP::CDuressFP(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	m_pmapFinger = *ui.lblFpArea->pixmap();

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR);
	ui.lblTitleText->setPalette(pal);
	ui.lblFpNumber->setPalette(pal);
	ui.lblEnrollStatus->setPalette(pal);

	uiEnrollSetTitle(ui.lblTitleText);
}

int CDuressFP::DoProcess(BOOL bDuressSet)
{
	BYTE byDisabled;
	BYTE byAdapted;
	BYTE byFingerNumber;
	BOOL bRet;
	int nKey;
	USER_INFO TEMP;
	BOOL bContinue = FALSE;
	int nStatusStr = UISTR_DURESS_PRESS_ENROLLEDFP;

	memset(SB_FP__256IMAGE, 192, 256*256);
	DrawFingerprint(ui.lblFpArea, &m_pmapFinger);

	do
	{
		bContinue = FALSE;
		uiLcdSetLabelText(ui.lblEnrollStatus, UISTR(nStatusStr), FOREGROUND_COLOR);
		nStatusStr = UISTR_DURESS_PRESS_ENROLLEDFP;

		while (uiTimeIsTimeout() == FALSE)
		{
			POST_EVENTS();
			DM9000_Check();

			if (uiCMOSCaptureFP())
			{
				bContinue = TRUE;
				uiBuzzerAlarm();
				if (dbSetupTotal.setSystem.bFPShow)
				{
					DrawFingerprint(ui.lblFpArea, &m_pmapFinger);
					POST_EVENTS();
				}
				bRet = uiFpVerifyO2N(NULL, &TEMP, &byDisabled, &byAdapted, &byFingerNumber);
				bRet = bRet && (TEMP.ID == gUserInfoTemp.ID);
				
				if (bRet)
				{
					ui.txtFpNumber->setText(QString("%1-%2").arg(UserId_BCDtoSTR(TEMP.ID)).arg(byFingerNumber));
					if (bDuressSet)
						DuressSet(&TEMP, byFingerNumber);
					else
						DuressRemove(&TEMP, byFingerNumber);
				}
				else
				{
					ui.txtFpNumber->clear();
					nStatusStr = UISTR_ENROLLFP_PRESAGAIN;
					uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
					break;
				}
			}

			nKey = uiKeyGetKey();
			if (nKey == UIKEY_ESC)
			{
				bContinue = FALSE;
				break;
			}
		}
	} while (bContinue);

	return 0;
}

void CDuressFP::DuressSet(USER_INFO *pUserInfo, BYTE byFingerNumber)
{
	if (DbUserInfoGetDuress(pUserInfo->ID, byFingerNumber))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_DURESS_ALREADYSET, UI_MSGTIMEOUT);
		return;
	}
	if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_DURESS_SET_CONFIRM, UITIME_OUT))
	{
		if (DbUserInfoSetDuress(pUserInfo->ID, byFingerNumber, 1))
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		else
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
	}
}

void CDuressFP::DuressRemove(USER_INFO *pUserInfo, BYTE byFingerNumber)
{
	if (!DbUserInfoGetDuress(pUserInfo->ID, byFingerNumber))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_DURESS_NOT, UI_MSGTIMEOUT);
		return;
	}
	if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_DURESS_REMOVE_CONFIRM, UITIME_OUT))
	{
		if (DbUserInfoSetDuress(pUserInfo->ID, byFingerNumber, 0))
			uiLcdMessageBox(UI_MSG_OK, UISTR_ACTION_SUCCESS, UI_MSGTIMEOUT);
		else
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ACTION_FAIL, UI_MSGTIMEOUT);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CInputUserID::CInputUserID(QWidget */*parent = NULL */)
{
	m_bTerminateFlag = FALSE;
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	SetPasswordLength(PWD_LENTH);
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnTextChange(const QString &)));
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

}

UINT64 CInputUserID::DoProcess(BOOL bAutoSearch /* = TRUE */, int nFirstKey /* = -1 */)
{
	int nKey;
	
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_ID()));

	m_nID = 0;
	m_bAutoSearchID = bAutoSearch;
	ui.lblStatus->hide();
	ui.lblIconPWD->hide();
	ui.lblPWD->hide();
	ui.txtPWD->hide();

	setObjectName("UserIDInput");


	if (nFirstKey >= UIKEY_0 && nFirstKey <= UIKEY_9)
		ui.txtID->setText(QString("%1").arg(nFirstKey));
	ui.txtID->setFocus(Qt::MouseFocusReason);

	if (m_bAutoSearchID)
	{
		m_nID = Db_GetCandidateID(FALSE, m_nID);
		ui.txtID->setText(UserId_BCDtoSTR(m_nID));
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(KEY_BK);  		
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_nID;
}

DWORD CInputUserID::DoUserIdInputProcess(int key)
	{
		int nKey;

		connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
		setObjectName("UserPWDInput");

		m_dwPassword = 0;
		//ui.lblStatus->hide();
		ui.lblIconPWD->hide();
		ui.lblIcon->show();
		ui.lblID->hide();
		ui.txtID->hide();
		ui.lblPWD->setText(QString("PIN"));
		ui.lblStatus->setText(QString("Enter PIN"));
		ui.lblStatus->show();
		ui.txtPWD->setMaxLength(6);
		ui.txtPWD->setEchoMode(QLineEdit::Normal);
		PostKeyEvent(key, ui.txtPWD, KEY_BK);  

		while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
		{
			POST_EVENTS();
			nKey = uiKeyGetKey(KEY_BK);  
			if (nKey == UIKEY_ESC)
				OnBtnESC();
		}

		return m_dwPassword;

	}



DWORD CInputUserID::DoDeptIdInputProcess()
	{
		int nKey;

		connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
		setObjectName("UserPWDInput");

		m_dwPassword = 0;
		//ui.lblStatus->hide();
		ui.lblIconPWD->hide();
		ui.lblIcon->show();
		ui.lblID->hide();
		ui.txtID->hide();
		ui.lblPWD->setText(QString("Dept ID"));
		ui.lblStatus->setText(QString("Enter Department ID"));
		ui.lblStatus->show();
		ui.txtPWD->setMaxLength(10);
		ui.txtPWD->setEchoMode(QLineEdit::Normal);

		while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
		{
			POST_EVENTS();
	
			nKey = uiKeyGetKey(KEY_BK);  
			if (nKey == UIKEY_ESC)
				OnBtnESC();
		}

		return m_dwPassword;

	}


DWORD CInputUserID::DoPIdInputProcess()
{
	int nKey;
    int temp;
	
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
	setObjectName("UserPWDInput");

	m_dwPassword = 0;
	//ui.lblStatus->hide();
	ui.lblIconPWD->hide();
	ui.lblIcon->show();
	ui.lblID->hide();
	ui.txtID->hide();
	ui.lblPWD->setText(QString("PIN"));

	ui.lblStatus->setText(QString("Enter PIN or Swipe Badge"));
	ui.lblStatus->show();
	ui.txtPWD->setMaxLength(10);
	ui.txtPWD->setEchoMode(QLineEdit::Normal);

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		if((temp=uiCardCapture()))
		{
			m_dwPassword=temp;
			m_bTerminateFlag = TRUE;
		}

		nKey = uiKeyGetKey(KEY_BK);  
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_dwPassword;

}



DWORD CInputUserID::DoPwdInputProcess(int key)
{
		int nKey;

		connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
		setObjectName("UserPWDInput");

		m_dwPassword = 0;
		//ui.lblStatus->hide();
		ui.lblIconPWD->hide();
		ui.lblIcon->show();
		ui.lblID->hide();
		ui.txtID->hide();
		ui.lblPWD->setText(QString("PIN"));
		ui.lblStatus->setText(QString("Enter PIN"));
		ui.lblStatus->show();
		ui.txtPWD->setMaxLength(6);
		ui.txtPWD->setEchoMode(QLineEdit::Normal);
		if(key!=UIKEY_NONE)
		   PostKeyEvent(key, ui.txtPWD, KEY_BK);  

		while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
		{
			POST_EVENTS();

			nKey = uiKeyGetKey(KEY_BK);  
			if (nKey == UIKEY_ESC)
				OnBtnESC();
		}

		return m_dwPassword;

/*
	int nKey;

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
	setObjectName("UserPWDInput");

	m_dwPassword = 0;
	ui.lblStatus->hide();
	ui.lblIcon->hide();
	ui.lblID->hide();
	ui.txtID->hide();

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(KEY_BK); 
		if (uiCMOSCaptureFP())
		{
		   OnBtnESC();
		   m_dwPassword=0xffffffff;
		}
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_dwPassword;
*/	
}
DWORD CInputUserID::DoPwdInputProcess()
{
	
	int nKey;

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK_PWD()));
	setObjectName("UserPWDInput");

	m_dwPassword = 0;
	ui.lblStatus->hide();
	ui.lblIcon->hide();
	ui.lblID->hide();
	ui.txtID->hide();

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(KEY_BK); 
		if (uiCMOSCaptureFP())
		{
		   OnBtnESC();
		   m_dwPassword=0xffffffff;
		}
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_dwPassword;
	
}

void CInputUserID::SetPasswordLength(int nlength)
{
	ui.txtPWD->setMaxLength(nlength);
}

void CInputUserID::OnBtnOK_ID()
{
	UINT64 nID;
	USER_INFO BACKUP;
	USER_INFO *pUserInfo = NULL;

	nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
	if(UserId_isOk()==0)
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	    uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
	    return ;
	}
	if (m_bAutoSearchID && (!nID || Db_IsUnusedID(nID)))
	{
		int nStr;
		if (!nID)
			nStr = UISTR_ENROLL_INVALID_ID;
		else
			nStr = UISTR_ENROLLDELETE_NODATA;
		nID = 0;
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		ui.lblStatus->setText(UISTR(nStr));
		ui.lblStatus->show();
		if (TRUE)
		{
			nID = Db_GetCandidateID(FALSE, nID);
			ui.txtID->setText(UserId_BCDtoSTR(nID));
			ui.txtID->setFocus(Qt::MouseFocusReason);
			ui.txtID->selectAll();
		}
		return;
	}
	if (g_uiPopupTitle < 0)
	{
		m_nID = nID ? nID : -1;
		m_bTerminateFlag = TRUE;
		return;
	}

	if (g_uiPopupTitle == UISTR_MENU_ENROLLDELETE)
	{
		gUserInfoTemp.ID = nID;
		pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
		else
			memset(&gUserInfoTemp, 0, sizeof(USER_INFO));
		if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
		{
			int nPrivManager = DbUserInfoFlagManagerGet(&gUserInfoTemp);
			if (nPrivManager == PRIV_SMGR ||
				(nPrivManager == PRIV_MGR && gUserInfoTemp.ID != g_uiProcStatus.nIDCurrentMgr))
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
				ui.lblStatus->setText(UISTR(UISTR_VERIFY_ILLEGAL));
				ui.lblStatus->show();
				ui.txtID->setFocus(Qt::MouseFocusReason);
				ui.txtID->selectAll();
				return;
			}
		}
	}
	if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE ||
		g_uiPopupTitle == UISTR_MENU_ACSETTING_DURESS_MANAGE)
	{
		g_uiMenuIDForUerTZ = nID;
		pUserInfo = (USER_INFO*)DbUserInfoGetPointer(g_uiMenuIDForUerTZ);
		if (!pUserInfo)
			return;
		if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE)
		{
			if (DbUserInfoFlagGTZStatusGet(pUserInfo) && pUserInfo->TIMEGROUP > 0)
			{
				pUserInfo->UserTZ[0] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupA;
				pUserInfo->UserTZ[1] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupB;
				pUserInfo->UserTZ[2] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupC;
				DbUserInfoEnroll(pUserInfo, BACKUP_ALL, NULL);
			}
		}
		memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
	}

	memcpy(&BACKUP, &gUserInfoTemp, sizeof(USER_INFO));

	CMenu *pMenu = new CMenu;
	pMenu->show();
	uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);
	pMenu->MenuProc(g_uiPopupTitle);
	DELETE(pMenu);

	pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);

	if (g_uiPopupTitle == UISTR_MENU_ENROLLDELETE)
	{
		if (!Db_GetUserCount())
		{
			m_bTerminateFlag = TRUE;
			return;
		}
		if (!pUserInfo || memcmp(&BACKUP, pUserInfo, sizeof(USER_INFO)))
			nID = Db_GetCandidateID(FALSE, nID + 1);
	}
	if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE ||
		g_uiPopupTitle == UISTR_MENU_ACSETTING_DURESS_MANAGE)
	{
		if (pUserInfo && memcmp(&BACKUP, pUserInfo, sizeof(USER_INFO)))
			nID = Db_GetCandidateID(FALSE, nID + 1);
	}

	ui.txtID->setText(UserId_BCDtoSTR(nID));
	ui.txtID->setFocus(Qt::MouseFocusReason);
	ui.txtID->selectAll();
}

void CInputUserID::OnBtnOK_PWD()
{
	if (!ui.txtPWD->text().length())
	{
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		return;
	}
	m_dwPassword = STRING2PWD(STR2ASCII(ui.txtPWD->text()));
	m_bTerminateFlag = TRUE;
}

void CInputUserID::OnBtnESC()
{
	m_nID = 0;
	m_dwPassword = 0;
	m_bTerminateFlag = TRUE;
}

void CInputUserID::OnTextChange(const QString & /*strText*/)
{
	ui.lblStatus->hide();
}

bool CInputUserID::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);		
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());		
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CInputUserID2::CInputUserID2(QWidget */*parent = NULL */)
{

	m_bTerminateFlag = FALSE;
	//GUI_DLG_IMPL(FALSE);
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_CENTER(this);
	//GUI_DLG_SET_THEME_1();
	GUI_DLG_SET_THEME();
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnTextChange(const QString &)));
	QPixmap pmap_icon(GUI_RESOURCE_PATH + QString("GROUP.png"));   
	ui.lblTitleIcon->setPixmap(pmap_icon);

	QString szTitle = QString("%1")
		.arg(UISTR(UISTR_HELP_INPUTID));
	uiLcdSetLabelText(ui.lblTitleText,szTitle,TITLECOLOR,QColor());
         uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);	
	//ui.txtID->setechoMode(8);
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);
	EDITBOX_2_T9InputBox(ui.txtID);

}

UINT64 CInputUserID2::DoProcess(BOOL bAutoSearch /* = TRUE */, int nFirstKey /* = -1 */)
{
	int nKey;
	
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));

	m_nID = 0;
	m_bAutoSearchID = bAutoSearch;
	//ui.lblStatusText->hide();

	setObjectName("UserIDInput");


	//if (nFirstKey >= UIKEY_0 && nFirstKey <= UIKEY_9)
	//	ui.txtID->setText(QString("%1").arg(nFirstKey));
	ui.txtID->setFocus(Qt::MouseFocusReason);

	if (m_bAutoSearchID)
	{
		m_nID = Db_GetCandidateID(FALSE, m_nID);
		ui.txtID->setText(UserId_BCDtoSTR(m_nID));
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}
	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey(KEY_BK);  	
		//nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_nID;
}

void CInputUserID2::OnBtnOK()
{
	UINT64 nID;
	USER_INFO BACKUP;
	USER_INFO *pUserInfo = NULL;

	nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
	if(UserId_isOk()==0)
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	    uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
	    return ;
	}
	if (m_bAutoSearchID && (!nID || Db_IsUnusedID(nID)))
	{
		int nStr;
		if (!nID)
			nStr = UISTR_ENROLL_INVALID_ID;
		else
			nStr = UISTR_ENROLLDELETE_NODATA;
		nID = 0;
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		//ui.lblStatus->setText(UISTR(nStr));
		//ui.lblStatus->show();
		if (TRUE)
		{
			nID = Db_GetCandidateID(FALSE, nID);
			ui.txtID->setText(UserId_BCDtoSTR(nID));
			ui.txtID->setFocus(Qt::MouseFocusReason);
			ui.txtID->selectAll();
		}
		return;
	}
	if (g_uiPopupTitle < 0)
	{
		m_nID = nID ? nID : -1;
		m_bTerminateFlag = TRUE;
		return;
	}

	if (g_uiPopupTitle == UISTR_MENU_ENROLLDELETE)
	{
		gUserInfoTemp.ID = nID;
		pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
		else
			memset(&gUserInfoTemp, 0, sizeof(USER_INFO));
		if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
		{
			int nPrivManager = DbUserInfoFlagManagerGet(&gUserInfoTemp);
			if (nPrivManager == PRIV_SMGR ||
				(nPrivManager == PRIV_MGR && gUserInfoTemp.ID != g_uiProcStatus.nIDCurrentMgr))
			{
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
				ui.lblStatusText->setText(UISTR(UISTR_VERIFY_ILLEGAL));
				ui.lblStatusText->show();
				ui.txtID->setFocus(Qt::MouseFocusReason);
				ui.txtID->selectAll();
				return;
			}
		}
	}
	if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE ||
		g_uiPopupTitle == UISTR_MENU_ACSETTING_DURESS_MANAGE)
	{
		g_uiMenuIDForUerTZ = nID;
		pUserInfo = (USER_INFO*)DbUserInfoGetPointer(g_uiMenuIDForUerTZ);
		if (!pUserInfo)
			return;
		if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE)
		{
			if (DbUserInfoFlagGTZStatusGet(pUserInfo) && pUserInfo->TIMEGROUP > 0)
			{
				pUserInfo->UserTZ[0] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupA;
				pUserInfo->UserTZ[1] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupB;
				pUserInfo->UserTZ[2] = dbSetupTimezoneNew.tzGroup[gUserInfoTemp.TIMEGROUP - 1].bGroupC;
				DbUserInfoEnroll(pUserInfo, BACKUP_ALL, NULL);
			}
		}
		memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
	}

	memcpy(&BACKUP, &gUserInfoTemp, sizeof(USER_INFO));

	CMenu *pMenu = new CMenu;
	pMenu->show();
	uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);
	pMenu->MenuProc(g_uiPopupTitle);
	DELETE(pMenu);

	pUserInfo = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);

	if (g_uiPopupTitle == UISTR_MENU_ENROLLDELETE)
	{
		if (!Db_GetUserCount())
		{
			m_bTerminateFlag = TRUE;
			return;
		}
		if (!pUserInfo || memcmp(&BACKUP, pUserInfo, sizeof(USER_INFO)))
			nID = Db_GetCandidateID(FALSE, nID + 1);
	}
	if (g_uiPopupTitle == UISTR_MENU_ACSETTING_USERTIMEZONE ||
		g_uiPopupTitle == UISTR_MENU_ACSETTING_DURESS_MANAGE)
	{
		if (pUserInfo && memcmp(&BACKUP, pUserInfo, sizeof(USER_INFO)))
			nID = Db_GetCandidateID(FALSE, nID + 1);
	}

	ui.txtID->setText(UserId_BCDtoSTR(nID));
	ui.txtID->setFocus(Qt::MouseFocusReason);
	ui.txtID->selectAll();
}

void CInputUserID2::OnBtnESC()
{
	m_nID = 0;
	m_dwPassword = 0;
	m_bTerminateFlag = TRUE;
}

void CInputUserID2::OnTextChange(const QString & /*strText*/)
{

}

bool CInputUserID2::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);		
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());		
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CInputUserIDName::CInputUserIDName(QWidget */*parent *//* = NULL */)
{
	m_bTerminateFlag = FALSE;
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME_1();
//	GUI_DLG_CENTER(this);

	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
	connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnIDChange(const QString &)));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));

	GUI_DLG_STATUSBAR();
	uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

	EDITBOX_2_T9InputBox(ui.txtID);
	EDITBOX_2_T9InputBox(ui.txtName);
}

BOOL CInputUserIDName::EnrollParamSet(int nCandidateDiff /* = 1 */)
{
	if (nCandidateDiff >= 0)
	{
		if ((int)m_nCandidateID == -1)
			m_nCandidateID = 1;
		else
			m_nCandidateID += nCandidateDiff;

		m_nCandidateID = Db_GetCandidateID(m_bNew, m_nCandidateID);
		if (!m_nCandidateID)
		{
			if (m_bNew)
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
			else
				uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_NOUSER, UI_MSGTIMEOUT);
			return FALSE;
		}
		//ui.txtID->setText(ID2STRING(m_nCandidateID));
		ui.txtID->setText(UserId_BCDtoSTR(m_nCandidateID));		
		m_nID = m_nCandidateID;
	}

	USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

	if (m_bNew || !pUserInfo)
	{
		ui.txtName->clear();
		ui.comboLevel->setCurrentIndex(0);
	}
	else
	{
		ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
		ui.comboLevel->setCurrentIndex(PRIV_INDEX(DbUserInfoFlagManagerGet(pUserInfo)));
	}

	if (nCandidateDiff >= 0)
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}
	return TRUE;
}

BOOL CInputUserIDName::EnrollCheck(BOOL bIDChange /* = FALSE */)
{
	BOOL bRet = TRUE;
	int MGR_LIST[] = {PRIV_USER, PRIV_MGR, PRIV_SMGR};

	m_nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));

	if (m_nOperateMode == ID_ALL)
	{
		m_nManager = MGR_LIST[ui.comboLevel->currentIndex()];
		m_bNew = !DbUserInfoIsUsedID(m_nID);
	}

	if (bIDChange)
	{
		m_nCandidateID = m_nID;
		goto _lExit;
	}

	if (m_bNew && Db_GetUserCount() >= dbLicense.nMaxEnrollCount)
	{
		uiLcdMessageOut(UI_MSG_ERROR, ui.lblStatus, UISTR_ENROLL_OVERFLOW);
		ui.lblStatus->setText(UISTR(UISTR_ENROLL_OVERFLOW));
		bRet = FALSE;
		goto _lExit;
	}

	if (/*m_bNew &&*/
		m_nManager != PRIV_USER && 
		m_nManager != DbUserInfoGetPrivilege(m_nID) &&
		Db_GetManagerCount((BYTE)m_nManager) + 1 > dbSetupTotal.setSystem.nManagersNumber)
	{
		uiLcdMessageOut(UI_MSG_ERROR, ui.lblStatus, UISTR_ENROLL_MANAGER_OVERFLOW);
		bRet = FALSE;
		goto _lExit;
	}

	if (!m_nID/*ui.txtID->text().isEmpty()*/ ||
		(m_bNew && DbUserInfoIsUsedID(m_nID)) ||
		(!m_bNew && !DbUserInfoIsUsedID(m_nID)))
	{
		int nStr = UISTR_ENROLL_INVALID_ID;
		if (!m_nID)
			nStr = UISTR_ENROLL_INVALID_ID;
		else if (m_bNew)
			nStr = UISTR_ENROLL_USED_ID;
		else if (!m_bNew)
			nStr = UISTR_ENROLLDELETE_NODATA;
		uiLcdMessageOut(UI_MSG_ERROR, ui.lblStatus, nStr);
		EnrollParamSet(0);
		bRet = FALSE;
		goto _lExit;
	}

	if (TRUE)
	{
		USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

		memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));

		gUserInfoTemp.ID = m_nID;
		STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);
		DbUserInfoFlagManagerSet(&gUserInfoTemp, m_nManager);
	}

	m_nCandidateID = m_nID;

_lExit:
	return bRet;
}


BOOL CInputUserIDName::DoProcess(int nOperateMode)
{
	int nKey;

	m_bNew = TRUE;
	m_nOperateMode = nOperateMode;
	m_nCandidateID = -1;
	m_nID = gUserInfoTemp.ID;
	m_nManager = PRIV_USER;
	m_bRet = FALSE;

	if (m_nOperateMode == ID_NEW)
		m_bNew = TRUE;
	else if (m_nOperateMode == ID_BACKUP)
		m_bNew = FALSE;

	m_bTerminateFlag = !EnrollParamSet();

	ui.txtID->selectAll();
	ui.lblStatus->setText("");

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

//_lExit:
	return m_bRet;
}

void CInputUserIDName::OnFocusChanged(QWidget *from, QWidget *to)
{
	if (from == (QWidget*)ui.txtID)
	{
		//UINT64 nID = STRING2ID(STR2ASCII(ui.txtID->text()));
		UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));	
		if(UserId_isOk()==0)
		{
	      uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
		  return ;
		}
		ui.txtID->setText(UserId_BCDtoSTR(nID)); //for empty string

		if (!nID && (to == (QWidget*)ui.txtName || to == (QWidget*)ui.btnESC))
		{
			if (!EnrollCheck())
			{
				ui.txtID->setFocus(Qt::MouseFocusReason);
				ui.txtID->selectAll();
			}
			EnrollParamSet(-1);
		}
	}
	
	if(to == (QWidget*)ui.txtName)
	{
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);
	}
	else
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);
}

void CInputUserIDName::OnIDChange(const QString & szID)
{
	UINT64 nID = STRING2ID(STR2ASCII(szID));
	if (nID > 999999999)
	{
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
		ui.txtID->setText(ID2STRING(999999999));
		ui.txtID->selectAll();
	}
	if (EnrollCheck(TRUE))
		ui.lblStatus->setText("");
	EnrollParamSet(-1);
}

BOOL CInputUserIDName::OnBtnOK()
{
	if (!EnrollCheck())
		return FALSE;

	if (g_uiPopupTitle < 0)
	{
		m_bRet = TRUE;
		m_bTerminateFlag = TRUE;
		return TRUE;
	}

	USER_INFO BACKUP;
	USER_INFO *pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	bzero(&BACKUP, sizeof(USER_INFO));
	if (pUI)
		memcpy(&BACKUP, pUI, sizeof(USER_INFO));
	if (pUI && memcmp(pUI, &gUserInfoTemp, sizeof(USER_INFO)))
		uiEnrollUserInfo(&gUserInfoTemp);

	CMenu *pMenu = new CMenu;
	pMenu->show();
	uiSoundOut(SOUND_MENUSELECT, UI_BUZZER_NONE);
	pMenu->MenuProc(g_uiPopupTitle);
	DELETE(pMenu);
	pUI = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	if (pUI && memcmp(&BACKUP, pUI, sizeof(USER_INFO)))
	{
		m_bNew = TRUE;
		if (Db_GetUserCount() == dbLicense.nMaxEnrollCount)
		{
			m_bNew = FALSE;
			m_nCandidateID = 0;
		}
		EnrollParamSet(0);
	}
	else
	{
		ui.txtID->setFocus(Qt::MouseFocusReason);
		ui.txtID->selectAll();
	}
	return TRUE;
}

BOOL CInputUserIDName::OnBtnESC()
{
// 	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
// 		return FALSE;

	m_bRet = FALSE;
	m_bTerminateFlag = TRUE;
	return TRUE;
}

bool CInputUserIDName::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);		
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());		
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CInputPWD::CInputPWD(QWidget */*parent *//* = NULL */)
{
	m_bTerminateFlag = FALSE;
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(ui.txtPassword, SIGNAL(textEdited(const QString &)), this, SLOT(OnPasswordChange(const QString &)));

	uiEnrollSetTitle(ui.lblTitleText);

	m_dwPassword = 0;
}

DWORD CInputPWD::DoProcess()
{
	int nKey;

	ui.lblStatus->hide();
	uiSoundOut(SOUND_INPUT_PWD, UI_BUZZER_NONE, UI_MSGTIMEOUT, TRUE);

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	}

	return m_dwPassword;
}

void CInputPWD::OnBtnOK()
{
	if (QApplication::focusWidget() == (QWidget*)ui.txtPassword)
	{
		ui.txtPasswordConfirm->setFocus(Qt::MouseFocusReason);
		return;
	}
	if (ui.txtPassword->text() != ui.txtPasswordConfirm->text())
	{
		ui.lblStatus->setText(UISTR(UISTR_ENROLL_INCORRECT_PWD));
		ui.lblStatus->show();
		uiSoundOut(SOUND_PWD_ERROR, UI_BUZZER_ERROR, UITIME_VOICE, TRUE);
		ui.txtPassword->setText("");
		ui.txtPasswordConfirm->setText("");
		ui.txtPassword->setFocus(Qt::MouseFocusReason);
		return;
	}
	m_dwPassword = STRING2PWD(STR2ASCII(ui.txtPassword->text()));
	m_bTerminateFlag = TRUE;
}

void CInputPWD::OnBtnESC()
{
	m_dwPassword = 0;
	m_bTerminateFlag = TRUE;
}

void CInputPWD::OnPasswordChange(const QString & /*szPassword*/)
{
	ui.lblStatus->hide();
	ui.txtPasswordConfirm->clear();
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static WORD* __USER_SEARCH_RESULT_LIST = NULL;
static int __USER_SEARCH_RESULT_CNT = 0;

static int DoUserSearch(UINT64 nID, QString szName)
{
	if (!__USER_SEARCH_RESULT_LIST)
		__USER_SEARCH_RESULT_LIST = new WORD[dbLicense.nMaxEnrollCount];
	if (!__USER_SEARCH_RESULT_LIST)
		return 0;

	BOOL bOK;
	int nCount = 0;
	QString szID = (nID ? QString(UserId_BCDtoSTR(nID)) : QString(""));

	for (int i=0; i<dbLicense.nMaxEnrollCount; i++)
	{
		if (!gpUserInfoEnrollData[i].ID)
			continue;

		bOK = (QString(UserId_BCDtoSTR(gpUserInfoEnrollData[i].ID)).contains(szID) == TRUE);
		bOK = bOK && (UNICODE2STRING(gpUserInfoEnrollData[i].NAME, USERNAME_LENGTH).contains(szName) == TRUE);
		if (bOK)
			__USER_SEARCH_RESULT_LIST[nCount++] = i;  
	}

//	printf("nCount = %d\n", nCount);   
	return nCount;
}


CSearchUser::CSearchUser(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	m_bTerminateFlag = FALSE;

	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

	GUI_DLG_STATUSBAR();

	EDITBOX_2_T9InputBox(ui.txtName);
	EDITBOX_2_T9InputBox(ui.txtID);
	uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);

//	ui.lblStatus->hide();

	m_nRet = 0;
}

int CSearchUser::DoProcess()
{
	int nKey;
	USER_INFO UserInfo;
	DWORD dwCardNumber;
	BOOL bDisabled;
	BOOL bAdapted;
	BYTE byFingerNumber;
	BOOL bVerifySuccess = FALSE;

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
		if (uiCMOSCaptureFP())
		{
			uiBuzzerAlarm();
			if (uiFpVerifyO2N(NULL, &UserInfo, &bDisabled, &bAdapted, &byFingerNumber))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if ((dwCardNumber = uiCardCapture()))
		{
			uiBuzzerAlarm();
			if (uiCardVerify(dwCardNumber, &UserInfo, &bDisabled))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if (bVerifySuccess)
		{
			bVerifySuccess = FALSE;
			ui.txtID->setText(UserId_BCDtoSTR(UserInfo.ID));
			ui.txtName->setText(UNICODE2STRING(UserInfo.NAME, USERNAME_LENGTH));
		}
	}

	return m_nRet;
}

bool CSearchUser::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

void CSearchUser::OnFocusChanged(QWidget *from, QWidget */*to*/)
{

	    uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK); 
	   
}

void CSearchUser::OnBtnOK()
{
	m_nRet = 1;

// 	if (ui.txtID->text().isEmpty() && ui.txtName->text().isEmpty())
// 	{
// 		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_INVALIDPARAM, UI_MSGTIMEOUT);
// 		return;
// 	}
	__USER_SEARCH_RESULT_CNT = DoUserSearch(UserId_STRtoBCD(STR2ASCII(ui.txtID->text())), ui.txtName->text());
	if (!__USER_SEARCH_RESULT_CNT)
	{
		m_nRet = 0;
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_NODATA, UI_MSGTIMEOUT);
		m_bTerminateFlag = TRUE;
	}
	else
	{
		DIALOGBOX(CUserList);
	}
}

void CSearchUser::OnBtnESC()
{
	m_nRet = 0;
	m_bTerminateFlag = TRUE;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_user[5];
UINT64 n_nID;        
static T_ITEM_A* GetRowData_user(DWORD dwID)
{
	if (dwID >= (DWORD)__USER_SEARCH_RESULT_CNT)
		return NULL;
	dwID = __USER_SEARCH_RESULT_LIST[dwID];
	USER_INFO* pUserInfo = &gpUserInfoEnrollData[dwID];

	n_nID = pUserInfo->ID;   

	/*ID*/	__rowdata_user[0].szValue = TR(UserId_BCDtoSTR(pUserInfo->ID));
	/*Name*/__rowdata_user[1].szValue = UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH);
//	/*TZ*/  __rowdata_user[2].szValue = QString("%1").arg(pUserInfo->TIMEGROUP);
	/*FP*/	__rowdata_user[2].szValue = QString("%1").arg(DbFpGetFingerCountPerUser(pUserInfo));
	/*CD*/	__rowdata_user[3].szValue = UISTR(UISTR_YESNO_START + DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_CARD));
	/*PWD*/	__rowdata_user[4].szValue = UISTR(UISTR_YESNO_START + DbUserInfoFlagEnrollStatusGet(pUserInfo, BACKUP_PASSWORD));

	return __rowdata_user;
}

CUserList::CUserList(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	ui.lblTitleText->setText(QString("%1     %2%3")
		.arg(UISTR(UISTR_MENU_ENROLLVIEW))
		.arg(__USER_SEARCH_RESULT_CNT)
		.arg(UISTR(UISTR_UNIT_PEOPLE)));	
	ui.lblStatusText->setText(UISTR(UISTR_STATUS_USER));   
}

void CUserList::DoProcess()
{
	int nKey;
	SBTable tblUserList(ui.lblBackgroundFrame);

	tblUserList.setFont(SB_FONT_4());
	tblUserList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);

	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_ID), Qt::AlignVCenter|Qt::AlignLeft, 90);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_NAME), Qt::AlignVCenter|Qt::AlignLeft, 90);
//	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_TZ), Qt::AlignVCenter|Qt::AlignLeft, 60);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_FP), Qt::AlignVCenter|Qt::AlignHCenter, 40);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_CARD), Qt::AlignVCenter|Qt::AlignHCenter, 20);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_PWD), Qt::AlignVCenter|Qt::AlignHCenter, 40);

	tblUserList.SetRowHeight(20);
	tblUserList.SetGridUse(3);
	tblUserList.SetContiniousScrollUse(FALSE);

	tblUserList.SetRowCount(__USER_SEARCH_RESULT_CNT);
	tblUserList.SetRowDataCallback(GetRowData_user);
	tblUserList.show();

	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
        case UIKEY_OK:
			UINT64 nID;
            nID = n_nID;
			xfprintf("0:nID=%d\r\n", nID);
			if (nID && nID != (UINT64)(-1))
			{
				USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(nID);
				if (pUserInfo)
					memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
				else
					memset(&gUserInfoTemp, 0, sizeof(USER_INFO));

				if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
				{
					int nPrivManager = DbUserInfoGetPrivilege(nID);
					if (nPrivManager == PRIV_SMGR ||
						(nPrivManager == PRIV_MGR && nID != g_uiProcStatus.nIDCurrentMgr))
					{
						uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
						break;
					}
				}
			}
			DIALOGBOXEX(CEnrollStep1,CEnrollStep1::ID_BACKUP);
			break;
		case UIKEY_ESC:
			goto _lExit;
		default:
			tblUserList.OnKeyPress(nKey);
			break;
		}
	}

_lExit:
	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static DWORD* __MLOG_SEARCH_RESULT_LIST = NULL;
static DWORD* __GLOG_SEARCH_RESULT_LIST = NULL;
static int __MLOG_SEARCH_RESULT_CNT = 0;
static int __GLOG_SEARCH_RESULT_CNT = 0;
static MLOG_INFO *__MLOG_BUF = NULL;
static ALOG_INFO *__GLOG_BUF = NULL;

int DoSuperLogSearch(UINT64 nID, QString szName, int fromDate, int toDate)
{
	if (!__MLOG_SEARCH_RESULT_LIST)
		__MLOG_SEARCH_RESULT_LIST = new DWORD[dbLicense.nSlogMaxCount];
	if (!__MLOG_SEARCH_RESULT_LIST)
		return 0;

	BOOL bOK;
	int nCount = 0;
	QString szID = (nID ? QString(UserId_BCDtoSTR(nID)) : QString(""));
	int nLogCnt;
	BOOL bLogReload = FALSE;

	if (!__MLOG_BUF)
	{
		__MLOG_BUF = (MLOG_INFO*)malloc(sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount);
		bLogReload = TRUE;
	}
	if (!__MLOG_BUF)
		return 0;

	nLogCnt = DbSLogCount();
	if (bLogReload)
	{
		bzero(__MLOG_BUF, sizeof(MLOG_INFO) * dbLicense.nSlogMaxCount);
		nLogCnt = DbSLogGet(__MLOG_BUF, DbSLogGetReadPos(), nLogCnt);
	}

    for (int i=nLogCnt; i>=0; i--)  
	{
		if (!__MLOG_BUF[i].dwSeconds)
			continue;
 		USER_INFO* pUserinfo = (USER_INFO*)DbUserInfoGetPointer(__MLOG_BUF[i].nManagerID);
 		bOK = (QString(UserId_BCDtoSTR(__MLOG_BUF[i].nManagerID)).contains(szID) == TRUE);
		if (pUserinfo)
 			bOK = bOK && (UNICODE2STRING(pUserinfo->NAME, USERNAME_LENGTH).contains(szName) == TRUE);
		else
			bOK = bOK && (szName.length() == 0);
 		bOK = bOK && (__MLOG_BUF[i].dwSeconds >=(DWORD)fromDate && __MLOG_BUF[i].dwSeconds <= (DWORD)toDate);

		if (bOK)
		{
			__MLOG_SEARCH_RESULT_LIST[nCount++] = i;
		}
	}

	return nCount;
}

int DoUserLogSearch(UINT64 nID, QString szName, DWORD fromDate, DWORD toDate)
{
	if (!__GLOG_SEARCH_RESULT_LIST)
		__GLOG_SEARCH_RESULT_LIST = new DWORD[dbLicense.nGlogMaxCount];
	if (!__GLOG_SEARCH_RESULT_LIST)
		return 0;

	int i;
	BOOL bOK = TRUE;
	int nCount = 0;
	QString szID = (nID ? QString(UserId_BCDtoSTR(nID)) : QString(""));
	int nLogCount;
	BOOL bLogReload = FALSE;
	QMap<UINT64, USER_INFO*> mapUI;

	if (!__GLOG_BUF)
	{
		__GLOG_BUF = (ALOG_INFO*)malloc(sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount);
		bLogReload = TRUE;
	}
	if (!__GLOG_BUF)
		return 0;

	//nLogCount = DbGLogCount();
	nLogCount = DbGLogCountAll();
	if (bLogReload)
	{
		bzero(__GLOG_BUF, sizeof(ALOG_INFO) * dbLicense.nGlogMaxCount);
		//DbGLogGet(__GLOG_BUF, DbGLogGetReadPos(), nLogCount);
		DbGLogGet(__GLOG_BUF, 0, nLogCount);
	}

	if (nLogCount > 0)
	{
		for (i=0; i<dbLicense.nMaxEnrollCount; i++)
		{
			if (gpUserInfoEnrollData[i].ID)
				mapUI.insert(gpUserInfoEnrollData[i].ID, &gpUserInfoEnrollData[i]);
		}
	}

    for (i=nLogCount; i>=0; i--)  
	{
		if (!__GLOG_BUF[i].dwSeconds)
			continue;
 		bOK = (QString(UserId_BCDtoSTR(__GLOG_BUF[i].nID)).contains(szID) == TRUE);
		if (mapUI.contains(__GLOG_BUF[i].nID))
		{
			USER_INFO *pUserinfo = mapUI[__GLOG_BUF[i].nID];
 			bOK = bOK && (UNICODE2STRING(pUserinfo->NAME, USERNAME_LENGTH).contains(szName) == TRUE);
		}
		else
			bOK = bOK && (szName.length() == 0);
 		bOK = bOK && (__GLOG_BUF[i].dwSeconds >=fromDate && __GLOG_BUF[i].dwSeconds <= toDate);

		if (bOK)
		{
			__GLOG_SEARCH_RESULT_LIST[nCount++] = i;
		}
	}

	mapUI.clear();

	return nCount;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CSearchLog::CSearchLog(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	m_bTerminateFlag = FALSE;
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();

	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(ui.comboDate, SIGNAL(currentIndexChanged(int)), SLOT(OnDateChanged(int)));
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));

	EDITBOX_2_T9InputBox(ui.txtName);

	m_dwFromTime = uiRtcGetSeconds();
	ui.txtFrom->setText(uiRtcGetDate(m_dwFromTime));

	m_dwToTime = uiRtcGetSeconds();
	ui.txtTo->setText(uiRtcGetDate(m_dwToTime));
	m_nRet = 0;
	m_pUserInfo = NULL;

	ui.lblDate->hide();
	ui.comboDate->hide();
	ui.lblFrom->hide();
	ui.txtFrom->hide();
	ui.lblTo->hide();
	ui.txtTo->hide();
	EDITBOX_2_T9InputBox(ui.txtID);
	uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);
	
}

int CSearchLog::DoProcess(int nLogType)
{
	int nKey;
	USER_INFO UserInfo;
	DWORD dwCardNumber;
	BOOL bDisabled;
	BOOL bAdapted;
	BYTE byFingerNumber;
	BOOL bVerifySuccess = FALSE;

	m_nLogType = nLogType;
	if (m_nLogType == LOG_GLOG_BY_USER)
	{
		ui.lblTitleText->setText(UISTR(UISTR_MENU_GLOGVIEW));
		ui.comboDate->setFocus(Qt::MouseFocusReason);
		ui.txtID->setEnabled(FALSE);
		ui.txtName->setEnabled(FALSE);
	}
	
	ui.txtID->setFocus(Qt::MouseFocusReason);
	
	if(m_nLogType ==LOG_SLOG)
	{
		QPixmap pmap_icon(GUI_RESOURCE_PATH + QString("SEARCH_MLOG.png"));
		ui.lblTitleIcon->setPixmap(pmap_icon);
		ui.lblTitleText->setText(UISTR(UISTR_MENU_MLOGVIEW));
	}
	if(m_nLogType == LOG_GLOG)
	{
		ui.lblTitleText->setText(UISTR(UISTR_MENU_GLOGVIEW));
	}

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
		nKey =  uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
		if (!m_pUserInfo && uiCMOSCaptureFP())
		{
			uiBuzzerAlarm();
			if (uiFpVerifyO2N(NULL, &UserInfo, &bDisabled, &bAdapted, &byFingerNumber))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if (!m_pUserInfo && (dwCardNumber = uiCardCapture()))
		{
			uiBuzzerAlarm();
			if (uiCardVerify(dwCardNumber, &UserInfo, &bDisabled))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if (bVerifySuccess)
		{
			bVerifySuccess = FALSE;
			ui.txtID->setText(UserId_BCDtoSTR(UserInfo.ID));
			ui.txtName->setText(UNICODE2STRING(UserInfo.NAME, USERNAME_LENGTH));
		}
	}

	return m_nRet;
}

void CSearchLog::SetUserInfo(USER_INFO *pUserInfo)
{
	m_pUserInfo = pUserInfo;
	ui.txtID->setText(UserId_BCDtoSTR(pUserInfo->ID));
	ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
	ui.txtID->setFocusPolicy(Qt::NoFocus);
	ui.txtName->setFocusPolicy(Qt::NoFocus);
	ui.lblStatus->hide();
}

bool CSearchLog::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

enum {UI_LOGSEARCH_ALL, UI_LOGSEARCH_LASTWEEK, UI_LOGSEARCH_PASTMONTH, UI_LOGSEARCH_DATERANGE};
void CSearchLog::OnBtnOK()
{
	int nYear, nMonth, nDay, nHour, nMinute, nSecond;
	DWORD now = uiRtcGetSeconds();
	DWORD from = 0, to = 0;
	QWidget *pInvalidWidget = NULL;
//	char strTemp[16];

	switch (ui.comboDate->currentIndex())
	{
	case UI_LOGSEARCH_ALL:
		from = 0;
		to = now;
		break;
	case UI_LOGSEARCH_LASTWEEK:
		from = now - 7*24*3600;
		to = now;
		break;
	case UI_LOGSEARCH_PASTMONTH:
		from = now - 31*24*3600;
		to = now;
		break;
	case UI_LOGSEARCH_DATERANGE:
		uiRtcSeconds2YMDHMS(m_dwFromTime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		from = uiRtcGetSeconds(nYear, nMonth, nDay, 0, 0, 0);

		uiRtcSeconds2YMDHMS(m_dwToTime, &nYear, &nMonth, &nDay, &nHour, &nMinute, &nSecond);
		to = uiRtcGetSeconds(nYear, nMonth, nDay, 23, 59, 59);
		break;
	}
	if (m_nLogType == LOG_GLOG_BY_USER && ui.txtID->text().isEmpty())
		pInvalidWidget = (QWidget*)ui.txtID;
// 	if (!pInvalidWidget && ui.txtName->text().isEmpty())
// 		pInvalidWidget = (QWidget*)ui.txtName;
	if (pInvalidWidget)
	{
		if (m_nLogType == LOG_GLOG_BY_USER)
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_MUST_VERIFY, UI_MSGTIMEOUT);
		else
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_INVALIDPARAM, UI_MSGTIMEOUT);
		pInvalidWidget->setFocus(Qt::MouseFocusReason);
		return;
	}

	int nSearchResult;
	m_nRet = 1;

	if (m_nLogType != LOG_SLOG)
	{
		nSearchResult = __GLOG_SEARCH_RESULT_CNT = 
			DoUserLogSearch(UserId_STRtoBCD(STR2ASCII(ui.txtID->text())), ui.txtName->text(), from, to);
	}
	else
	{
		nSearchResult = __MLOG_SEARCH_RESULT_CNT = 
			DoSuperLogSearch(UserId_STRtoBCD(STR2ASCII(ui.txtID->text())), ui.txtName->text(), from, to);
	}
	if (!nSearchResult)
	{
		m_nRet = 0;
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_NODATA, UI_MSGTIMEOUT);
		FREE(__GLOG_BUF);
		DELETE(__GLOG_SEARCH_RESULT_LIST);
		FREE(__MLOG_BUF);
		DELETE(__MLOG_SEARCH_RESULT_LIST);
		return;
	}
	if (m_nLogType != LOG_SLOG)
	{
		DIALOGBOX(CGLogList);
	}
	else
	{
		DIALOGBOX(CSLogList);
	}
}

void CSearchLog::OnBtnESC()
{
	m_nRet = 0;
	m_bTerminateFlag = TRUE;
}

void CSearchLog::OnDateChanged(int nIndex)
{
	if (nIndex == UI_LOGSEARCH_DATERANGE)
	{
		ui.txtFrom->setEnabled(TRUE);
		ui.txtTo->setEnabled(TRUE);
	}
	else
	{
		ui.txtFrom->setDisabled(TRUE);
		ui.txtTo->setDisabled(TRUE);
	}
}

void CSearchLog::OnFocusChanged(QWidget *from, QWidget *to)
{
	BYTE nKey;
	QRect rc;
//	int nRet;
	if (from == (QWidget*)ui.txtID)
	{
		UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
		if(UserId_isOk()==0)
		{
		  uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
		  ui.txtID->setFocus(Qt::MouseFocusReason);
		  ui.txtID->selectAll();	
		  return ;
		}
	}

	if (to == (QWidget*)(ui.txtFrom))
	{
		rc = ui.txtFrom->geometry();
		m_dwFromTime = uiProcBoxDate(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwFromTime, 0, TRUE, FALSE);
		ui.txtFrom->setText(uiRtcGetDate(m_dwFromTime));
		switch (nKey)
		{
		case UIKEY_OK:
			OnBtnOK();
			break;
		case UIKEY_ESC:
			OnBtnESC();
			break;
		case UIKEY_UP:
			ui.comboDate->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
				ui.txtTo->setFocus(Qt::MouseFocusReason);
			break;
		}
	}
	if (to == (QWidget*)(ui.txtTo))
	{
		rc = ui.txtTo->geometry();
		m_dwToTime = uiProcBoxDate(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwToTime, 0, TRUE, FALSE);
		ui.txtTo->setText(uiRtcGetDate(m_dwToTime));
		switch (nKey)
		{
		case UIKEY_OK:
			OnBtnOK();
			break;
		case UIKEY_ESC:
			OnBtnESC();
			break;
		case UIKEY_UP:
			ui.txtFrom->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
			if(ui.txtID->isEnabled())
				ui.txtID->setFocus(Qt::MouseFocusReason);
			else
				ui.btnOK->setFocus(Qt::MouseFocusReason);
			break;
		}
	}
	if(to ==(QWidget*)(ui.txtName))
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);
	else
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);     
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_slog[5];
static T_ITEM_A* GetRowData_slog(DWORD dwID)
{
	if (dwID >= (DWORD)__MLOG_SEARCH_RESULT_CNT)
		return NULL;

	dwID = __MLOG_SEARCH_RESULT_LIST[dwID];
	MLOG_INFO *pLogData = &__MLOG_BUF[dwID];

	__rowdata_slog[0].szValue = uiRtcSeconds2LogString(pLogData->dwSeconds);
	__rowdata_slog[1].szValue = UserId_BCDtoSTR(pLogData->nManagerID);
	__rowdata_slog[2].szValue = UISTR(UISTR_SLOG_START + pLogData->byAction);

	return __rowdata_slog;
}

CSLogList::CSLogList(QWidget *parent /* = NULL */)
	: CMainFrame(parent)
{
	m_bTerminateFlag = FALSE;

// 	int nRet = DIALOGBOXEX(CSearchLog, CSearchLog::LOG_SLOG);
// 	if (!nRet)
// 		m_bTerminateFlag = TRUE;
	uiLcdSetLabelText(
		ui.lblTitleText,
		QString("%1     %2%3").arg(UISTR(UISTR_MENU_MLOGVIEW)).arg(__MLOG_SEARCH_RESULT_CNT).arg(UISTR(UISTR_UNIT_LOG)),
		TITLECOLOR);
	uiLcdSetLabelText(ui.lblStatusText,UISTR(UISTR_STATUS_LOG),FOREGROUND_COLOR);  
}

void CSLogList::DoProcess()
{
	int nKey;
	SBTable tblLogList(ui.lblBackgroundFrame);

	tblLogList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_TIMESTAMP), Qt::AlignVCenter|Qt::AlignHCenter, 90);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_ID), Qt::AlignVCenter|Qt::AlignHCenter, 85);
//	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_NAME), Qt::AlignVCenter|Qt::AlignHCenter, 45);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_CONTENT), Qt::AlignVCenter|Qt::AlignHCenter, 100);

	tblLogList.SetRowHeight(20);
	tblLogList.SetGridUse(3);
	tblLogList.SetContiniousScrollUse(FALSE);

	tblLogList.SetRowCount(__MLOG_SEARCH_RESULT_CNT);
	tblLogList.SetRowDataCallback(GetRowData_slog);
	tblLogList.show();

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
// 		case UIKEY_MENU:
// 			UserManageShortcutMenuProc();
// 			break;
		case UIKEY_UP:
			tblLogList.OnKeyUp();
			break;
		case UIKEY_DOWN:
			tblLogList.OnKeyDown();
			break;
		case UIKEY_0:
			tblLogList.OnPageUp();
			break;
		case UIKEY_OK:
			tblLogList.OnPageDown();
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}

_lExit:
	if (__MLOG_BUF)
		FREE(__MLOG_BUF);
	if (__MLOG_SEARCH_RESULT_LIST)
		DELETE(__MLOG_SEARCH_RESULT_LIST);

	return;
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_glog[5];
static T_ITEM_A* GetRowData_glog(DWORD dwID)
{
	if (dwID >= (DWORD)__GLOG_SEARCH_RESULT_CNT)
		return NULL;

	dwID = __GLOG_SEARCH_RESULT_LIST[dwID];
	ALOG_INFO *pLogData = &__GLOG_BUF[dwID];
	int nStrAction = UISTR_VERIFYMODE_START + VERIFYMODE2INDEX(pLogData->byAction);
	int nStrTr = UISTR_FUNC_START + pLogData->byTrStatus;

	__rowdata_glog[0].szValue = uiRtcSeconds2LogString(pLogData->dwSeconds);
	__rowdata_glog[1].szValue = UserId_BCDtoSTR(pLogData->nID);
	if( pLogData->byTrStatus != TR_DUTYNO )
		 __rowdata_glog[2].szValue = QString("%1:%2").arg(UISTR(nStrAction)).arg(UISTR(nStrTr));
	else __rowdata_glog[2].szValue = QString("%1").arg(UISTR(nStrAction));

	return __rowdata_glog;  
}

CGLogList::CGLogList(QWidget *parent /* = NULL */, struct _user_info *pUserInfo /* = NULL */)
	: CMainFrame(parent)
{
	int nRet = 0;

	m_bTerminateFlag = FALSE;

	if (pUserInfo)
	{
		CSearchLog *pLogSearch = new CSearchLog;
		if (pLogSearch)
		{
			pLogSearch->SetUserInfo(pUserInfo);
			pLogSearch->show();
			nRet = pLogSearch->DoProcess(TRUE);
			delete pLogSearch;
		}
	}
// 	else
// 	{
// 		nRet = DIALOGBOXEX(CSearchLog, CSearchLog::LOG_GLOG);
// 	}
// 
// 	if (!nRet)
// 		m_bTerminateFlag = TRUE;

	uiLcdSetLabelText(
		ui.lblTitleText,
		QString("%1     %2%3").arg(UISTR(UISTR_MENU_GLOGVIEW)).arg(__GLOG_SEARCH_RESULT_CNT).arg(UISTR(UISTR_UNIT_LOG)),
		TITLECOLOR);
	uiLcdSetLabelText(ui.lblStatusText,UISTR(UISTR_STATUS_LOG),FOREGROUND_COLOR);  
}

void CGLogList::DoProcess()
{
	int nKey;
	SBTable tblLogList(ui.lblBackgroundFrame);

	tblLogList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_TIMESTAMP), Qt::AlignVCenter|Qt::AlignHCenter, 90);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_ID), Qt::AlignVCenter|Qt::AlignHCenter, 85);
	tblLogList.InsertColumn(-1, UISTR(UISTR_LOGHDR_CONTENT), Qt::AlignVCenter|Qt::AlignHCenter, 100);

	tblLogList.SetRowHeight(20);
	tblLogList.SetGridUse(3);
	tblLogList.SetContiniousScrollUse(FALSE);

	tblLogList.SetRowCount(__GLOG_SEARCH_RESULT_CNT);
	tblLogList.SetRowDataCallback(GetRowData_glog);
	tblLogList.show();

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey();
		switch (nKey)
		{
// 		case UIKEY_MENU:
// 			UserManageShortcutMenuProc();
// 			break;
		case UIKEY_UP:
			tblLogList.OnKeyUp();
			break;
		case UIKEY_DOWN:
			tblLogList.OnKeyDown();
			break;
		case UIKEY_0:
			tblLogList.OnPageUp();
			break;
		case UIKEY_OK:
			tblLogList.OnPageDown();
			break;
		case UIKEY_ESC:
			goto _lExit;
		}
	}

_lExit:
	if (__GLOG_BUF)
		FREE(__GLOG_BUF);
	if (__GLOG_SEARCH_RESULT_LIST)
		DELETE(__GLOG_SEARCH_RESULT_LIST);

	return;
}

/************************************************************************/
/*   Modify by HCH  Date : 2009:07:06                 */
/************************************************************************/
CUserManage::CUserManage(QWidget *parent /* = NULL */)
: CMainFrame(parent)
{
	m_bTerminateFlag = FALSE;
    QPixmap pmap_sel(QString(GUI_RESOURCE_PATH) + QString("ENROLLEDIT.png"));   
	ui.lblTitleIcon->setPixmap(pmap_sel);
	ui.lblTitleText->setText(UISTR(UISTR_MENU_ENROLLEDIT));         
	ui.lblStatusText->setText(UISTR(UISTR_USER_STATUS));	
	__USER_SEARCH_RESULT_CNT = DoUserSearch(0, "");
	if (!__USER_SEARCH_RESULT_CNT)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_NODATA, UI_MSGTIMEOUT);
		m_bTerminateFlag = TRUE;
	}
}

void CUserManage::DoProcess()
{
	int nKey;
	UINT64 m_nID;
	SBTable tblUserList(ui.lblBackgroundFrame);


	tblUserList.setFont(SB_FONT_4());
	tblUserList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);

	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_ID), Qt::AlignVCenter|Qt::AlignLeft, 90);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_NAME), Qt::AlignVCenter|Qt::AlignLeft, 90);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_FP), Qt::AlignVCenter|Qt::AlignHCenter, 40);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_CARD), Qt::AlignVCenter|Qt::AlignHCenter, 40);
	tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_PWD), Qt::AlignVCenter|Qt::AlignHCenter, 40);

	tblUserList.SetRowHeight(20);
	tblUserList.SetGridUse(3);
	tblUserList.SetContiniousScrollUse(FALSE);

    __USER_SEARCH_RESULT_CNT = DoUserSearch(0, "");  
 	if(__USER_SEARCH_RESULT_CNT ==0)
 		tblUserList.SetRowCount(1);
 	else
		tblUserList.SetRowCount(__USER_SEARCH_RESULT_CNT);
	tblUserList.SetRowDataCallback(GetRowData_user); 
	tblUserList.show();


	int nRet; 
	while (!uiTimeIsTimeout() && !m_bTerminateFlag)
	{ 
		if(__USER_SEARCH_RESULT_CNT != 0)
			gUserInfoTemp = gpUserInfoEnrollData[__USER_SEARCH_RESULT_LIST[tblUserList.GetCurrentIndex()]];

		nKey = uiKeyGetKey();
		DM9000_Check();
		switch (nKey)
		{
		case UIKEY_1:           //SEARCH
			DIALOGBOX(CSearchUser);
			__USER_SEARCH_RESULT_CNT = DoUserSearch(0, "");
			break;
        case UIKEY_OK:	
			if(__USER_SEARCH_RESULT_CNT ==0)
				break;
			else
				m_nID = gUserInfoTemp.ID;
				if (m_nID && m_nID != (UINT64)(-1))
				{
					USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);
					if (pUserInfo)
						memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));
					else
						memset(&gUserInfoTemp, 0, sizeof(USER_INFO));

					if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
					{
						int nPrivManager = DbUserInfoGetPrivilege(m_nID);
						if (nPrivManager == PRIV_SMGR ||
							(nPrivManager == PRIV_MGR && m_nID != g_uiProcStatus.nIDCurrentMgr))
						{
							uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
							break;
						}
					}
				}
				USER_EDIT_FLAG=1;
				nRet = DIALOGBOXEX(CEnrollStep1,CEnrollStep1::ID_BACKUP);
				USER_EDIT_FLAG=0;
			break;

        case UIKEY_2:     
			tblUserList.OnPageUp();
			break;
        case UIKEY_3:    
			tblUserList.OnPageDown();
			break;
		case UIKEY_ESC:
			goto _lExit;
		default:
			break;
		}

		POST_EVENTS();
		tblUserList.OnRedraw();
		tblUserList.OnKeyPress(nKey);
	}
_lExit:
		
	return;
}


CUserDel::CUserDel(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	m_bTerminateFlag = FALSE;
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();
	  
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));
	connect(ui.comboDate, SIGNAL(currentIndexChanged(int)), SLOT(OnDateChanged(int)));
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));

	EDITBOX_2_T9InputBox(ui.txtName);
	EDITBOX_2_T9InputBox(ui.txtID);

	m_pUserInfo = NULL;  
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

	ui.lblDate->hide();
	ui.comboDate->hide();
	ui.lblFrom->hide();
	ui.txtFrom->hide();
	ui.lblTo->hide();
	ui.txtTo->hide();
}

void CUserDel::DoProcess()
{
    int nKey;
	USER_INFO UserInfo;
	DWORD dwCardNumber;
	BOOL bDisabled;
	BOOL bAdapted;
	BYTE byFingerNumber;
	BOOL bVerifySuccess = FALSE;

	QPixmap pmap_icon(GUI_RESOURCE_PATH + QString("ENROLLDELS.png"));   
	ui.lblTitleIcon->setPixmap(pmap_icon);
	ui.lblTitleText->setText(UISTR(UISTR_MENU_ENROLLDEL));
	
	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();
		nKey =  uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
		if (!m_pUserInfo && uiCMOSCaptureFP())
		{
			uiBuzzerAlarm();
			if (uiFpVerifyO2N(NULL, &UserInfo, &bDisabled, &bAdapted, &byFingerNumber))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if (!m_pUserInfo && (dwCardNumber = uiCardCapture()))
		{
			uiBuzzerAlarm();
			if (uiCardVerify(dwCardNumber, &UserInfo, &bDisabled))
			{
				uiSoundOut(SOUND_OK, UI_BUZZER_OK, UITIME_VOICE);
				bVerifySuccess = TRUE;
			}
			else
				uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR, UITIME_VOICE);
		}
		if (bVerifySuccess)
		{
			bVerifySuccess = FALSE;
			ui.txtID->setText(UserId_BCDtoSTR(UserInfo.ID));
			ui.txtName->setText(UNICODE2STRING(UserInfo.NAME, USERNAME_LENGTH));
		}
	}

	return;
}

int CUserDel::SetUserInfo(UINT64 nID, QString szName)
{
	int i;
	BOOL bOK;
	QString szID = (nID ? QString(UserId_BCDtoSTR(nID)) : QString(""));

	for (i=0; i<dbLicense.nMaxEnrollCount; i++)
	{
	//	if (!gpUserInfoEnrollData[i].ID)
	//		continue;

		bOK = (QString(UserId_BCDtoSTR(gpUserInfoEnrollData[i].ID)).contains(szID) == TRUE);
		bOK = bOK && (UNICODE2STRING(gpUserInfoEnrollData[i].NAME, USERNAME_LENGTH).contains(szName) == TRUE);
		if (bOK)
			break;  
	}

	return i;
}

bool CUserDel::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());	
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

void CUserDel::OnBtnOK()
{
	if (!DoUserSearch(UserId_STRtoBCD(STR2ASCII(ui.txtID->text())), ui.txtName->text()))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_NODATA, UI_MSGTIMEOUT);
		m_bTerminateFlag = TRUE;
	}
	else
	{

		gUserInfoTemp = gpUserInfoEnrollData[SetUserInfo(UserId_STRtoBCD(STR2ASCII(ui.txtID->text())), ui.txtName->text())];
		DIALOGBOX(CEnrollDelete);
	}
}

void CUserDel::OnBtnESC()
{
	m_bTerminateFlag = TRUE;
}

void CUserDel::OnFocusChanged(QWidget *from, QWidget *to)
{
	if (from == (QWidget*)ui.txtID)
	{
		UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
		if(UserId_isOk()==0)
		{
		  uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, 3000);
		  ui.txtID->setFocus(Qt::MouseFocusReason);
		  ui.txtID->selectAll();	
		  return ;
		}
	}

	if(to ==(QWidget*)(ui.txtName))
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_T9, UISTR_STATUS_ESC_BACK);
	else
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);          
}

/************************************************************************/
/*                                                                      */
/************************************************************************/
static T_ITEM_A __rowdata_msg[5];
#define MSG_CONTEXT_CNT = 6;
static T_ITEM_A* GetRowData_Msg(DWORD dwID)
{
	MSG_INFO msg_info;
	BOOL bRet;

	msg_info.Belong =0;
	msg_info.SMSID = 0;
	msg_info.StartTime = (DWORD)0;
	msg_info.Tag = (BYTE)0;
	msg_info.Valid = (BYTE)0;
	msg_info.ValidMinutes = (WORD)0;
	memset(msg_info.Contents, 0, sizeof(msg_info.Contents));
	QString strContents ;

	if (dwID >= (DWORD)MSG_INFO_COUNT)
		return NULL;
	bRet = memcmp(&msg_info,&dbSetupTotal.setTimezone.tzMsg[dwID],sizeof(MSG_INFO));
	if(!bRet)
	{
		__rowdata_msg[0].szValue = QString("--");
		__rowdata_msg[1].szValue = QString("--/-- --:--");	
		__rowdata_msg[2].szValue = QString("--");	
		__rowdata_msg[3].szValue = QString("--");	
		__rowdata_msg[4].szValue = QString("--");	
	}
	else
	{
		__rowdata_msg[0].szValue = QString("%1").arg(dbSetupTotal.setTimezone.tzMsg[dwID].SMSID); 		/* ID     */
		__rowdata_msg[1].szValue = uiRtcGetDate(dbSetupTotal.setTimezone.tzMsg[dwID].StartTime).right(5) + " " + uiRtcGetTime(dbSetupTotal.setTimezone.tzMsg[dwID].StartTime).left(5);	/* Start  Time*/
		DWORD dwValidMinute = dbSetupTotal.setTimezone.tzMsg[dwID].ValidMinutes;
		if(dwValidMinute == 0)
		{
		__rowdata_msg[2].szValue = QString("--");
		}
		else if(dwValidMinute < 1440)
		{
			__rowdata_msg[2].szValue = QString(uiRtcGetTime(dwValidMinute*60).left(5));
		}
		else
		{
			__rowdata_msg[2].szValue = QString("%1").arg((dwValidMinute + 1439)/1440) + QString(UISTR(UISTR_MSG_UNIT));
		}	
		__rowdata_msg[3].szValue =(dbSetupTotal.setTimezone.tzMsg[dwID].Tag ? UISTR(UISTR_MSG_TYPE_USER):UISTR(UISTR_MSG_TYPE_GENERAL));/* Type */
		strContents =  UNICODE2STRING((WORD*)dbSetupTotal.setTimezone.tzMsg[dwID].Contents,MSG_LEN >> 1);	/* Contents    */
		__rowdata_msg[4].szValue = strContents.length()>6 ? (strContents.left(6) + "...") : strContents ;
	}
	
	
	return __rowdata_msg;
}

CMsgManage::CMsgManage(QWidget */*parent=NULL*/)
{
	m_bTerminateFlag = NULL;
	QPixmap pmap_sel(QString(GUI_RESOURCE_PATH) + QString("MESSINFO.png"));
	ui.lblTitleIcon->setPixmap(pmap_sel);
	ui.lblTitleText->setText(UISTR(UISTR_MSG_MANAGE));
	ui.lblStatusText->setText(UISTR(UISTR_MSG_STATUS));	
}

void CMsgManage::DoProcess()
{
	
	int nKey;
	int nReturn;
	BOOL bChangedMsg;
	//-------------------------Bulid Table --------------------------
	SBTable tblUserList(ui.lblBackgroundFrame);

	tblUserList.setFont(SB_FONT_4());
	tblUserList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);

	tblUserList.InsertColumn(-1, UISTR(UISTR_MSG_ID), Qt::AlignVCenter|Qt::AlignLeft, 35);
	tblUserList.InsertColumn(-1, UISTR(UISTR_MSG_STARTTIME), Qt::AlignVCenter|Qt::AlignLeft, 87);
	tblUserList.InsertColumn(-1, UISTR(UISTR_MSG_INTERVAL), Qt::AlignVCenter|Qt::AlignHCenter, 50);
	tblUserList.InsertColumn(-1, UISTR(UISTR_MSG_TYPE), Qt::AlignVCenter|Qt::AlignHCenter, 40);
	tblUserList.InsertColumn(-1, UISTR(UISTR_MSG_TEXT), Qt::AlignVCenter|Qt::AlignHCenter, 40);

	tblUserList.SetRowHeight(20);
	tblUserList.SetGridUse(3);
	tblUserList.SetContiniousScrollUse(FALSE);

	tblUserList.SetRowCount(MSG_INFO_COUNT);
	tblUserList.SetRowDataCallback(GetRowData_Msg);
	tblUserList.show();
	//------------------------------------------------------------

	//--------------Main Loop-------------------------------------

	MSG_INFO msg_info;
	
	msg_info.Belong =0;
	msg_info.SMSID = 0;
	msg_info.StartTime = (DWORD)0;
	msg_info.Tag = (BYTE)0;
	msg_info.Valid = (BYTE)0;
	msg_info.ValidMinutes = (WORD)0;
	memset(msg_info.Contents, 0, sizeof(msg_info.Contents));

	while (!uiTimeIsTimeout() && !m_bTerminateFlag)
	{
		POST_EVENTS();
		DM9000_Check();
		nKey = uiKeyGetKey();

		switch(nKey)
		{
		case UIKEY_1:
			nReturn = DIALOGBOXEX(CMsgEdit,CMsgEdit::MSG_NEW);
			break;
		case UIKEY_2:
			nReturn = DIALOGBOXEX(CMsgEdit,tblUserList.GetCurrentIndex());
			break;
		case UIKEY_3:
			bChangedMsg = memcmp(&dbSetupTotal.setTimezone.tzMsg[tblUserList.GetCurrentIndex()], &msg_info, sizeof(MSG_INFO));
			if(bChangedMsg && uiLcdMessageBox(UI_MSG_QUESTION,UISTR_STATUS_MSG_DEL_ALARM,UITIME_OUT))
			{
				dbSetupTotal.setTimezone.tzMsg[tblUserList.GetCurrentIndex()] = msg_info;
				DbSetupTotalWrite();
			}
			break;
		case UIKEY_4:
			tblUserList.OnPageUp();
			break;
		case UIKEY_5:
			tblUserList.OnPageDown();
			break;
		case UIKEY_ESC:
			return;

		default:
			break;
		}
		tblUserList.OnRedraw();
		tblUserList.OnKeyPress(nKey);
	}
	//-------------------------------------------------------------

}

/************************************************************************/
/*                                                                      */
/************************************************************************/
CMsgEdit::CMsgEdit(QWidget * parent/* =NULL */)
: QDialog(parent)
{
	m_bTerminateFlag = FALSE;
	m_bOK = FALSE;

	GUI_DLG_IMPL(FALSE);
	GUI_DLG_SET_THEME();
	GUI_DLG_CENTER(this);
	
//	connect(ui.txtContent,SIGNAL(textEdited(const QString &),this,SLOT(OnTextChange(const QString &))));
	connect(ui.comboTag,SIGNAL(currentIndexChanged(int)),this,SLOT(OnCurrentIndexChanged(int)));
	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
	connect(ui.btnESC,SIGNAL(clicked()),this,SLOT(OnBtnESC()));

	EDITBOX_2_T9InputBox(ui.txtContent);
}

int CMsgEdit::DoProcess(int nType)
{
	int nKey;

	connect(ui.btnOK,SIGNAL(clicked()),this,SLOT(OnBtnOK()));
	
	if(nType == MSG_NEW)
	{	
		uiLcdSetLabelText(ui.lblTitleText,UISTR(UISTR_MSG_NEW),TITLECOLOR,QColor());
		ui.txtID->setText(QString(""));
		ui.txtStartTime->setText(uiRtcGetDate()+ " " + uiRtcGetTime());
		m_dwStartTime = uiRtcGetSeconds();
		ui.txtValidMinutes->setText(QString("0"));
		ui.comboTag->setCurrentIndex(0);
		ui.txtContent->setText(QString(""));
		ui.txtBelong->setText(QString(""));
	}
	if(nType >= MSG_EDIT)
	{
		uiLcdSetLabelText(ui.lblTitleText,UISTR(UISTR_MSG_EDIT),TITLECOLOR,QColor());
		ui.txtID->setText(QString("%1").arg(nType));
		ui.txtID->setDisabled(TRUE);
		ui.txtStartTime->setText(uiRtcGetDate(dbSetupTotal.setTimezone.tzMsg[nType].StartTime) +" " + uiRtcGetTime(dbSetupTotal.setTimezone.tzMsg[nType].StartTime));
		ui.txtValidMinutes->setText(QString("%1").arg(dbSetupTotal.setTimezone.tzMsg[nType].ValidMinutes));
		ui.comboTag->setCurrentIndex(dbSetupTotal.setTimezone.tzMsg[nType].Tag);
		ui.txtContent->setText(UNICODE2STRING((WORD*)dbSetupTotal.setTimezone.tzMsg[nType].Contents,MSG_LEN >> 1));
		ui.txtBelong->setText(QString("%1").arg(dbSetupTotal.setTimezone.tzMsg[nType].Belong));
		m_dwStartTime = dbSetupTotal.setTimezone.tzMsg[nType].StartTime;
	}
		ui.txtID->setFocus(Qt::MouseFocusReason);

	//--------------Main Loop-------------------------------------
	while (!uiTimeIsTimeout() && !m_bTerminateFlag)
	{
		POST_EVENTS();
		DM9000_Check();	
		nKey = uiKeyGetKey(TRUE);
		if (nKey == UIKEY_ESC)
			OnBtnESC();
	/*	if(nKey == UIKEY_OK)
			OnBtnOK();*/
	}
	//-------------------------------------------------------------
	return 0;
}

void CMsgEdit::OnBtnESC()
{
	m_bTerminateFlag = TRUE;
}

void CMsgEdit::OnBtnOK()
{
	MSG_INFO msg_info_t;
	BOOL bChangedMsg;
	memset(msg_info_t.Contents, 0, sizeof(msg_info_t.Contents));
	msg_info_t.SMSID =  UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
	STRING2UNICODE(ui.txtContent->text(),(WORD*)msg_info_t.Contents,MSG_LEN >> 1);
	msg_info_t.StartTime =m_dwStartTime;
	msg_info_t.Belong= UserId_STRtoBCD(STR2ASCII(ui.txtBelong->text()));
	msg_info_t.Tag = ui.comboTag->currentIndex();
	msg_info_t.Valid = 1;
	msg_info_t.ValidMinutes =UserId_STRtoBCD(STR2ASCII(ui.txtValidMinutes->text()));

	if(msg_info_t.SMSID <10 && ui.txtContent->text().length()!=0 )
	{
		dbSetupTotalTemp.setTimezone.tzMsg[msg_info_t.SMSID] = msg_info_t;
		bChangedMsg = memcmp(&dbSetupTotal.setTimezone.tzMsg[msg_info_t.SMSID], &dbSetupTotalTemp.setTimezone.tzMsg[msg_info_t.SMSID], sizeof(MSG_INFO));
		if (bChangedMsg)
		{
			if (uiLcdMessageBox(UI_MSG_QUESTION, UISTR_STATUS_SAVE_QUESTION, UITIME_OUT))
			{
				memcpy(&dbSetupTotal.setTimezone.tzMsg[msg_info_t.SMSID], &dbSetupTotalTemp.setTimezone.tzMsg[msg_info_t.SMSID], sizeof(MSG_INFO));
				DbSetupTotalWrite();
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETTINGCHANGED,  0, UISTR_MENU_MESSINFO);
				m_bTerminateFlag = TRUE;
			}
		}
	}
	else
	{
		
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
		uiLcdMessageBox(UI_MSG_OK,UISTR_STATUS_MSG_INPUT_ERROR,UI_MSGTIMEOUT);
	}
	POST_EVENTS();
}
void CMsgEdit::OnFocusChanged(QWidget *from, QWidget *to)
{
	BYTE nKey;
	QRect rc;

	if(to == (QWidget*)(ui.txtStartTime))
	{	
		rc = ui.txtStartTime->geometry();
	//	m_dwStartTime = STRING2ID(STR2ASCII(ui.txtStartTime->text()));
		m_dwStartTime =uiProcBoxDate(this, rc.left(), rc.top(), rc.width(), rc.height(), &nKey, m_dwStartTime,2, TRUE, FALSE);
		ui.txtStartTime->setText(uiRtcGetDate(m_dwStartTime) + " " + uiRtcGetTime(m_dwStartTime) );
		switch(nKey)
		{
		case UIKEY_ESC:
			ui.btnESC->setFocus(Qt::MouseFocusReason);
			OnBtnESC();
			break;
		case UIKEY_UP:
			if(ui.txtID->isEnabled())
				ui.txtID->setFocus(Qt::MouseFocusReason);
			else
				ui.txtContent->setFocus(Qt::MouseFocusReason);
			break;
		case UIKEY_DOWN:
			ui.txtValidMinutes->setFocus(Qt::MouseFocusReason);
			break;

		}
		/*nKey = uiKeyGetKey(TRUE);*/
	}
	
	if(to == (QWidget*)(ui.btnOK))
	{	
		if(ui.txtID->isEnabled())
			ui.txtID->setFocus(Qt::MouseFocusReason);
		else
			ui.txtStartTime->setFocus(Qt::MouseFocusReason);
	}
	if(from == (QWidget*)(ui.txtID) && to == (QWidget*)(ui.btnESC))
	{
		ui.txtContent->setFocus(Qt::MouseFocusReason);
	}
		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);
}


bool CMsgEdit::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		T9_INPUT_PROC(this, ui.txtContent);
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}
void CMsgEdit::OnCurrentIndexChanged(int index)
{
	if(index == 1)
	{
		ui.txtBelong->setEnabled(TRUE);
	}
	else
	{
		ui.txtBelong->setEnabled(FALSE);
	}
}
//////////////////////////////////////////////////////////////////////////

CUserEdit::CUserEdit(QWidget *parent /* = NULL */, UINT64 /*nID*/ /* = 0 */, BOOL /*bNew*/ /* = TRUE */)
: QDialog(parent)
{
	ui.setupUi(this);
	show();

	connect(qApp, SIGNAL(focusChanged(QWidget*, QWidget*)), this, SLOT(OnFocusChanged(QWidget*, QWidget*)));
	connect(ui.txtID, SIGNAL(textEdited(const QString &)), this, SLOT(OnIDChange(const QString &)));
	/*connect(ui.txtPassword, SIGNAL(textEdited(const QString &)), this, SLOT(OnPasswordChange(const QString &)));*/
	connect(ui.btnOK, SIGNAL(clicked()), this, SLOT(OnBtnOK()));
	connect(ui.btnESC, SIGNAL(clicked()), this, SLOT(OnBtnESC()));

	QPalette pal = palette();
	GUI_DLG_SET_FORE_COLOR(&pal, FOREGROUND_COLOR1);
	ui.txtID->setMaxLength(IDNUMBER_LENGTH);

	ui.lblID->setPalette(pal);
	ui.lblName->setPalette(pal);
	ui.lblLevel->setPalette(pal);
	ui.lblPart->setPalette(pal);
	ui.txtID->setPalette(pal);
	ui.txtName->setPalette(pal);
	ui.comboLevel->setPalette(pal);
	ui.comboPart->setPalette(pal);    

	ui.comboPart->setFont(SB_FONT_4());   
	EDITBOX_2_T9InputBox(ui.txtName);

	m_bNew = FALSE;
	m_nCandidateID = gUserInfoTemp.ID;
	m_nID = gUserInfoTemp.ID;

	ui.txtID->setText(UserId_BCDtoSTR(m_nCandidateID));
	ui.txtID->setReadOnly(TRUE);
	int nParts = DbPartCount();
	for (int i=0; i<nParts; i++)
		ui.comboPart->addItem(DbPartGet(i));   

	m_bTerminateFlag = !EnrollParamSet();
}

BOOL CUserEdit::EnrollParamSet(int nCandidateDiff /* = 1 */)
{
	if (nCandidateDiff >= 0)
	{
	}

	USER_INFO* pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

	if (m_bNew || !pUserInfo)
	{
		ui.txtName->clear();
		ui.comboLevel->setCurrentIndex(0);
		ui.comboPart->setCurrentIndex(0);   
	}
	else
	{
		ui.txtName->setText(UNICODE2STRING(pUserInfo->NAME, USERNAME_LENGTH));
		ui.comboLevel->setCurrentIndex(PRIV_INDEX(DbUserInfoFlagManagerGet(pUserInfo)));
		if (pUserInfo->PART < DbPartCount())
			ui.comboPart->setCurrentIndex(pUserInfo->PART);
		else
			ui.comboPart->setCurrentIndex(0);   
	}

	return TRUE;
}

BOOL CUserEdit::EnrollCheck(BOOL bIDChange /* = FALSE */)
{
	BOOL bRet = TRUE;
	int MGR_LIST[] = {PRIV_USER, PRIV_MGR, PRIV_SMGR};

//	m_nID = STRING2ID(STR2ASCII(ui.txtID->text()));
	m_nManager = MGR_LIST[ui.comboLevel->currentIndex()];

	m_bNew = !DbUserInfoIsUsedID(m_nID);

	if (bIDChange)
	{
		m_nCandidateID = m_nID;
		goto _lExit;
	}
	// 	if (uiProcEnrollIsManagerFull(m_nManager))
	// 	{
	// 		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
	// 		bRet = FALSE;
	// 		goto _lExit;
	// 	}

	if (m_bNew && Db_GetUserCount() >= dbLicense.nMaxEnrollCount)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_OVERFLOW, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	if (/*m_bNew &&*/
		m_nManager != PRIV_USER && 
		m_nManager != DbUserInfoGetPrivilege(m_nID) &&
		Db_GetManagerCount((BYTE)m_nManager) + 1 > dbSetupTotal.setSystem.nManagersNumber)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_MANAGER_OVERFLOW, UI_MSGTIMEOUT);
		bRet = FALSE;
		goto _lExit;
	}

	if (g_uiProcStatus.byMgr != PRIV_SMGR && Db_GetManagerCount(PRIV_SMGR))
	{
		if (m_nManager == PRIV_SMGR ||
			(m_nManager == PRIV_MGR && m_nID != g_uiProcStatus.nIDCurrentMgr))
		{
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_VERIFY_ILLEGAL, UI_MSGTIMEOUT);
			ui.comboLevel->setFocus(Qt::MouseFocusReason);
			bRet = FALSE;
			goto _lExit;
		}
	}

	if (!m_nID/*ui.txtID->text().isEmpty()*/ ||
		(m_bNew && DbUserInfoIsUsedID(m_nID)) ||
		(!m_bNew && !DbUserInfoIsUsedID(m_nID)))
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_INVALID_ID, UI_MSGTIMEOUT);
		EnrollParamSet(0);
		bRet = FALSE;
		goto _lExit;
	}

	if (TRUE)
	{
		USER_INFO *pUserInfo = (USER_INFO*)DbUserInfoGetPointer(m_nID);

		memset(&gUserInfoTemp, 0, sizeof(gUserInfoTemp));
		if (pUserInfo)
			memcpy(&gUserInfoTemp, pUserInfo, sizeof(USER_INFO));

		gUserInfoTemp.ID = m_nID;
		STRING2UNICODE(ui.txtName->text(), gUserInfoTemp.NAME, USERNAME_LENGTH);
		//gUserInfoTemp.PWD = STRING2PWD(STR2ASCII(ui.txtPassword->text()));
		DbUserInfoFlagManagerSet(&gUserInfoTemp, m_nManager);
		gUserInfoTemp.PART = ui.comboPart->currentIndex();    
	}

	m_nCandidateID = m_nID;

_lExit:
	return bRet;
}

BOOL CUserEdit::EnrollUserInfo()
{
	BOOL bRet;
	USER_INFO *TEMP, BACKUP;

	TEMP = (USER_INFO*)DbUserInfoGetPointer(gUserInfoTemp.ID);
	if (TEMP)
		memcpy(&BACKUP, TEMP, sizeof(USER_INFO));

	bRet = DbUserInfoEnroll(&gUserInfoTemp, BACKUP_ALL, NULL);

	if (bRet)
	{
		if (m_bNew)
		{
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, m_nID, bRet);
			uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, m_nID, bRet);
		}
		else
		{
			if (memcmp(BACKUP.NAME, gUserInfoTemp.NAME, sizeof(WORD) * USERNAME_LENGTH) ||
				BACKUP.PWD != gUserInfoTemp.PWD ||
				DbUserInfoFlagManagerGet(&BACKUP) != DbUserInfoFlagManagerGet(&gUserInfoTemp) ||
				BACKUP.PART != gUserInfoTemp.PART)
			{
				if (BACKUP.PWD != gUserInfoTemp.PWD)
					uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_SETPASSWORD, m_nID, bRet);
				uiLogSlogAdd(g_uiProcStatus.nIDCurrentMgr, SLOG_ENROLL_USER, m_nID, bRet);
			}
		}
	}
	return bRet;
}

void CUserEdit::DoProcess()
{
	int nKey;

	//ui.txtID->selectAll();

	while (!m_bTerminateFlag && uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();
		DM9000_Check();

		nKey = uiKeyGetKey(TRUE);

		switch (nKey)
		{
		//case UIKEY_F2://Save
		//	if (EnrollCheck())
		//	{
		//		if (EnrollUserInfo())
		//			uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLL_SAVEOK, UI_MSGTIMEOUT);
		//		else
		//			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_SAVEFAIL, UI_MSGTIMEOUT);
		//	}
		//	break;
		//case UIKEY_F3://NextEnroll
		//	m_bNew = TRUE;
		//	EnrollParamSet(1);
		//	break;
		case UIKEY_ESC:
			if (OnBtnESC())
				goto _lExit;
			break;
		default:
			break;
		}
	}

_lExit:
	return;
}

void CUserEdit::OnFocusChanged(QWidget *from, QWidget *to)
{
	if (from == (QWidget*)ui.txtID)
	{
		UINT64 nID = UserId_STRtoBCD(STR2ASCII(ui.txtID->text()));
		ui.txtID->setText(UserId_BCDtoSTR(nID)); //for empty string

		if (!nID && (to == (QWidget*)ui.txtName || to == (QWidget*)ui.btnESC))
		{
			if (!EnrollCheck())
			{
				ui.txtID->setFocus(Qt::MouseFocusReason);
				ui.txtID->selectAll();
			}
			EnrollParamSet(-1);
		}
	}

	if (to == (QWidget*)ui.txtID)
		ui.txtID->selectAll();

		uiProcDrawStatusbar(ui.lblStatusText, UISTR_STATUS_OK_SELECT, UISTR_STATUS_ESC_BACK);

}

void CUserEdit::OnIDChange(const QString & szID)
{
	UINT64 nID = STRING2ID(STR2ASCII(szID));
	if (nID > 999999999)
	{
		uiSoundOut(SOUND_ERROR, UI_BUZZER_ERROR);
		ui.txtID->setText(ID2STRING(999999999));
		ui.txtID->selectAll();
	}
	EnrollCheck(TRUE);
	EnrollParamSet(-1);
}

void CUserEdit::OnPasswordChange(const QString & /*szPassword*/)
{
	//ui.txtPasswordConfirm->clear();
}

BOOL CUserEdit::OnBtnOK()
{
	if (EnrollCheck())
	{
		if (EnrollUserInfo())
			uiLcdMessageBox(UI_MSG_OK, UISTR_ENROLL_SAVEOK, UI_MSGTIMEOUT);
		else
			uiLcdMessageBox(UI_MSG_ERROR, UISTR_ENROLL_SAVEFAIL, UI_MSGTIMEOUT);
	}
	m_bTerminateFlag = TRUE;
	return TRUE;
}

BOOL CUserEdit::OnBtnESC()
{
	// 	if (!uiLcdMessageBox(UI_MSG_QUESTION, UISTR_ACTION_CONFIRM, UITIME_OUT))
	// 		return FALSE;

	m_bTerminateFlag = TRUE;
	return TRUE;
}

bool CUserEdit::event(QEvent *e)
{
	if (e->type() == WM_T9INPUT)
	{
		//T9_INPUT_PROC(this, ui.txtName);
		T9_INPUT_PROC(this, (QLineEdit*)QApplication::focusWidget());	
		return TRUE;
	}
	else
	{
		return QDialog::event(e);
	}
}

/************************************************************************/
/*   add by loveywm  Date : 2012.10.22                 */
/************************************************************************/
static T_ITEM_A __rowdata_department[2];
static T_ITEM_A* GetRowData_department(DWORD n)
{
		__rowdata_department[0].szValue = QString(Http_DeptStrGet(n,1));
		__rowdata_department[1].szValue = QString(Http_DeptStrGet(n,2));

	return __rowdata_department;
}

static WORD* __DEPT_SEARCH_RESULT_LIST = NULL;
static int __DEPT_SEARCH_RESULT_CNT = 0;

static int DoDepartmentSearch(UINT64 nID, QString szName)
{
	int nCount = 0;

	return nCount;
}

CDepartmentManage::CDepartmentManage(QWidget *parent /* = NULL */)
: CMainFrame(parent)
{
	m_bTerminateFlag = FALSE;
    QPixmap pmap_sel(QString(GUI_RESOURCE_PATH) + QString("ENROLLEDIT1.png"));   
	ui.lblTitleIcon->setPixmap(pmap_sel);
	ui.lblTitleText->setText("Department List");         
	//ui.lblStatusText->setText(UISTR(UISTR_USER_STATUS));
	ui.lblStatusText->setText("OK:confirm < >:select Esc:back");
	__DEPT_SEARCH_RESULT_CNT = Http_DeptStrCNTGet();
	if (!__DEPT_SEARCH_RESULT_CNT)
	{
		uiLcdMessageBox(UI_MSG_ERROR, UISTR_SEARCH_NODATA, UI_MSGTIMEOUT);
		m_bTerminateFlag = TRUE;
	}
}

UINT64 CDepartmentManage::DoProcess()
{
	xprintf("UINT64 CDepartmentManage::DoProcess\r\n");
	int nKey;
	UINT64 nDept;
	SBTable tblUserList(ui.lblBackgroundFrame);


	tblUserList.setFont(SB_FONT_4());
	tblUserList.SetTableRect(m_nFrameX, m_nFrameY, m_nFrameWidth, m_nFrameHeight);

	//tblUserList.InsertColumn(-1, UISTR(UISTR_ULHDR_ID), Qt::AlignVCenter|Qt::AlignLeft, 60);
	tblUserList.InsertColumn(-1, "Department ID", Qt::AlignVCenter|Qt::AlignLeft, 100);
	tblUserList.InsertColumn(-1, "Department Name", Qt::AlignVCenter|Qt::AlignHCenter, 150);

	tblUserList.SetRowHeight(20);
	tblUserList.SetGridUse(3);
	tblUserList.SetContiniousScrollUse(FALSE);

    __DEPT_SEARCH_RESULT_CNT =Http_DeptStrCNTGet();  
 	if(__DEPT_SEARCH_RESULT_CNT ==0)
 		tblUserList.SetRowCount(1);
 	else
		tblUserList.SetRowCount(__DEPT_SEARCH_RESULT_CNT);
	tblUserList.SetRowDataCallback(GetRowData_department); 
	tblUserList.show();

xprintf("44444\r\n");
	nDept=0; 
	while (!uiTimeIsTimeout() && !m_bTerminateFlag)
	{ 

		nKey = uiKeyGetKey();
		switch (nKey)
		{
        case UIKEY_OK:	
			if(__DEPT_SEARCH_RESULT_CNT ==0)
				break;
			else
                nDept=STRING2ID(Http_DeptStrGet(tblUserList.GetCurrentIndex(),1));
			m_bTerminateFlag=1;
			break;

        case UIKEY_2:     
			tblUserList.OnPageUp();
			break;
        case UIKEY_3:    
			tblUserList.OnPageDown();
			break;
		case UIKEY_ESC:
			goto _lExit;
		default:
			break;
		}
xprintf("5555ywm\r\n");
		POST_EVENTS();
		tblUserList.OnRedraw();
		tblUserList.OnKeyPress(nKey);
	}
_lExit:
		
	return nDept;
}


