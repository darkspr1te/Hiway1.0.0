#ifndef __USER_MANAGE_H__
#define __USER_MANAGE_H__

#include "define.h"
#include "Mainframe.h"
#include "ui_enroll-1.h"
#include "ui_enroll-2.h"
#include "ui_enroll-fp.h"
#include "ui_enroll-card.h"
#include "ui_enroll-voice.h"
#include "ui_enroll-photo.h"
#include "ui_enroll-delete.h"
#include "ui_input-userid.h"
#include "ui_input-userid2.h"
#include "ui_input-userid-name.h"
#include "ui_input-pwd.h"
#include "ui_duress-set.h"
#include "ui_search-user.h"
#include "ui_search-log.h"
#include "ui_user-edit.h"
#include "ui_msg-edit.h"
#include "ui_user-del.h"    

//////////////////////////////////////////////////////////////////////////
class CEnrollStep1 : public QDialog
{
	Q_OBJECT

public:
	enum {ID_ALL, ID_NEW, ID_BACKUP};
	CEnrollStep1(QWidget *parent = NULL, UINT64 nID = 0, BOOL bNew = TRUE,BOOL bEdit = FALSE);
	~CEnrollStep1() {}
	BOOL EnrollParamSet(int nCandidateDiff = 1);
	BOOL EnrollCheck(BOOL bIDChange = FALSE);
	BOOL EnrollUserInfo();
	int DoProcess(int nEdit = 0);

public Q_SLOTS:
	;
	void OnFocusChanged(QWidget *from, QWidget *to);
	void OnIDChange(const QString & szID);
	void OnPasswordChange(const QString & szPassword);
	BOOL OnBtnOK();
	BOOL OnBtnESC();

protected:
	bool event(QEvent *e);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::EnrollStep1);
	BOOL m_bNew;
	BOOL m_nEdit;
	UINT64 m_nCandidateID;
	UINT64 m_nID;
	int m_nManager;
};

//////////////////////////////////////////////////////////////////////////
class CEnrollStep2 : public QDialog
{
	Q_OBJECT
	
public:
		enum {NEW,EDIT};
	CEnrollStep2(QWidget *parent = NULL);
	~CEnrollStep2() {}
	int DoProcess(int nEdit);

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();

private:
	BOOL bTerminateFlag;
	GUI_DLG_DEFINE(Ui::EnrollStep2);
	QList<QPushButton*> m_BtnList;
};

//////////////////////////////////////////////////////////////////////////
class CEnrollFP : public QDialog
{
	Q_OBJECT

public:
	CEnrollFP(QWidget *parent = NULL);
	~CEnrollFP() {}
	int EnrollFPExit();
	int DoProcess();
	void FP_DrawEnrollStatus(int Nth);

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();
	BOOL OnKeyPressESC();

private:
	GUI_DLG_DEFINE(Ui::EnrollFP);
	QPixmap m_pmapFinger;
};

//////////////////////////////////////////////////////////////////////////
class CEnrollCard : public QDialog
{
	Q_OBJECT

public:
	CEnrollCard(QWidget *parent = NULL);
	~CEnrollCard() {}
	void DoProcess();

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();
	BOOL OnKeyPressESC();

private:
	GUI_DLG_DEFINE(Ui::EnrollCard);
};

//////////////////////////////////////////////////////////////////////////
class CEnrollVoice : public QDialog
{
	Q_OBJECT

public:
	CEnrollVoice(QWidget *parent = NULL);
	~CEnrollVoice() {}
	void DoProcess();

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();
	BOOL OnKeyPressESC();
	int OnVoiceRecord(char *szFilename);

private:
	GUI_DLG_DEFINE(Ui::EnrollVoice);
	unsigned int m_unRecState;
	QPixmap m_pmapVoicePlay;
	QPixmap m_pmapVoiceRec;
	QPixmap m_pmapVoiceFlow1;
	QPixmap m_pmapVoiceFlow2;
};

//////////////////////////////////////////////////////////////////////////
class CEnrollPhoto : public QDialog
{
	Q_OBJECT

public:
	CEnrollPhoto(QWidget *parent = NULL);
	~CEnrollPhoto() {}
	void DoProcess();

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();
	BOOL OnKeyPressESC();

private:
	Ui::EnrollPhoto ui;
};

//////////////////////////////////////////////////////////////////////////
class CEnrollDelete : public QDialog
{
	Q_OBJECT

public:
	CEnrollDelete(QWidget *parent = NULL);
	~CEnrollDelete() {}
	void DoProcess();

public Q_SLOTS:
	;
	BOOL OnKeyPressOK();
	BOOL OnKeyPressESC();

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::EnrollDelete);
	UINT64 m_nID;
	QList<QPushButton*> m_BtnList;
};

//////////////////////////////////////////////////////////////////////////
class CDuressFP : public QDialog
{
	Q_OBJECT

public:
	CDuressFP(QWidget *parent = NULL);
	~CDuressFP() {};
	int DoProcess(BOOL bDuressSet);
	void DuressSet(struct _user_info *pUserInfo, BYTE byFingerNumber);
	void DuressRemove(struct _user_info *pUserInfo, BYTE byFingerNumber);

private:
	GUI_DLG_DEFINE(Ui::DuressFP);
	QPixmap m_pmapFinger;
};

//////////////////////////////////////////////////////////////////////////
class CInputUserID : public QDialog
{
	Q_OBJECT

public:
	CInputUserID(QWidget *parent = NULL);
	~CInputUserID() {}
	UINT64 DoProcess(BOOL bAutoSearch = TRUE, int nFirstKey = -1);
	DWORD  DoPwdInputProcess(int key);
	DWORD  DoPwdInputProcess();
	void   SetPasswordLength(int nlength);
	//Ôö¼ÓµÄ
	DWORD DoUserIdInputProcess(int key);
	DWORD DoDeptIdInputProcess();
	DWORD DoPIdInputProcess();

public Q_SLOTS:
	void OnBtnOK_ID();
	void OnBtnOK_PWD();	
	void OnBtnESC();
	void OnTextChange(const QString & strText);
	
protected:
		bool event(QEvent *e);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::UserIDInput);
	UINT64 m_nID;
	BOOL m_bAutoSearchID;
	DWORD m_dwPassword;
};


//////////////////////////////////////////////////////////////////////////
class CInputUserID2 : public QDialog
{
	Q_OBJECT

public:
	CInputUserID2(QWidget *parent = NULL);
	~CInputUserID2() {}
	UINT64 DoProcess(BOOL bAutoSearch = TRUE, int nFirstKey = -1);

public Q_SLOTS:
	;
	void OnBtnOK();
	void OnBtnESC();
	void OnTextChange(const QString & strText);
	
protected:
		bool event(QEvent *e);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::UserIDInput2);
	UINT64 m_nID;
	BOOL m_bAutoSearchID;
	DWORD m_dwPassword;
};


//////////////////////////////////////////////////////////////////////////
class CInputUserIDName : public QDialog
{
	Q_OBJECT

public:
	enum {ID_ALL, ID_NEW, ID_BACKUP};
	CInputUserIDName(QWidget *parent = NULL);
	~CInputUserIDName() {}
	BOOL EnrollParamSet(int nCandidateDiff = 1);
	BOOL EnrollCheck(BOOL bIDChange = FALSE);
	BOOL DoProcess(int nOperateMode);

protected:
	bool event(QEvent *e);

public Q_SLOTS:
	;
	void OnFocusChanged(QWidget *from, QWidget *to);
	void OnIDChange(const QString & szID);
	BOOL OnBtnOK();
	BOOL OnBtnESC();

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::InputUserIDName);
	BOOL m_bNew;
	int m_nOperateMode;
	UINT64 m_nCandidateID;
	UINT64 m_nID;
	int m_nManager;
	BOOL m_bRet;
};

//////////////////////////////////////////////////////////////////////////
class CInputPWD : public QDialog
{
	Q_OBJECT

public:
	CInputPWD(QWidget *parent = NULL);
	~CInputPWD() {}
	DWORD DoProcess();

	public Q_SLOTS:
		;
		void OnBtnOK();
		void OnBtnESC();
		void OnPasswordChange(const QString & szPassword);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::InputPWD);
	DWORD m_dwPassword;
};

//////////////////////////////////////////////////////////////////////////
class CSearchUser : public QDialog
{
	Q_OBJECT

public:
	CSearchUser(QWidget *parent = NULL);
	~CSearchUser() {}
	int DoProcess();

protected:
	bool event(QEvent *e);

public Q_SLOTS:
	;
	void OnFocusChanged(QWidget *from, QWidget *to);
	void OnBtnOK();
	void OnBtnESC();

private:
	BYTE m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::UserSearch);
	int m_nRet;
};

//////////////////////////////////////////////////////////////////////////
class CUserList : public CMainFrame
{
	Q_OBJECT

public:
	CUserList(QWidget *parent = NULL);
	~CUserList() {}
	void DoProcess();
};

//////////////////////////////////////////////////////////////////////////
class CSearchLog : public QDialog
{
	Q_OBJECT

public:
	enum {LOG_SLOG, LOG_GLOG, LOG_GLOG_BY_USER};  
	CSearchLog(QWidget *parent = NULL);
	~CSearchLog() {}
	int DoProcess(int nLogType);
	void SetUserInfo(struct _user_info *pUserInfo);

protected:
	bool event(QEvent *e);

public Q_SLOTS:;
	void OnBtnOK();
	void OnBtnESC();
	void OnDateChanged(int nIndex);
	void OnFocusChanged(QWidget *from, QWidget *to);

private:
	BYTE m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::LogSearch);
	int m_nRet;
	DWORD m_dwFromTime, m_dwToTime;
	BOOL m_nLogType;
	struct _user_info *m_pUserInfo;
};

//////////////////////////////////////////////////////////////////////////
class CSLogList : public CMainFrame
{
	Q_OBJECT

public:
	CSLogList(QWidget *parent = NULL);
	~CSLogList() {}
	void DoProcess();

private:
	BOOL m_bTerminateFlag;
};

//////////////////////////////////////////////////////////////////////////
class CGLogList : public CMainFrame
{
	Q_OBJECT

public:
	CGLogList(QWidget *parent = NULL, struct _user_info *pUserInfo = NULL);
	~CGLogList() {}
	void DoProcess();

private:
	BOOL m_bTerminateFlag;
};

/************************************************************************/
/*  Modify by HCH      Date : 2009/07/06                                */
/************************************************************************/
class CUserManage : public CMainFrame
{
	Q_OBJECT

public:
	CUserManage(QWidget *parent = NULL);
	~CUserManage() {}
	void DoProcess();

private:
	BOOL m_bTerminateFlag;
};

///////////////////////////////////////////////////////////////////////////////

class CMsgManage:public CMainFrame
{
	Q_OBJECT
public:
	CMsgManage(QWidget *parent = NULL);
	~CMsgManage(){}
	void DoProcess(); 
	//BOOL bNew();
	//BOOL bEdit();
	//BOOL bDel();
private:
	BOOL m_bTerminateFlag;
};
class CMsgEdit:public QDialog
{
	Q_OBJECT
public :
	enum{MSG_NEW=-1,MSG_EDIT};
	CMsgEdit(QWidget * parent=NULL);
	~CMsgEdit(){}
	int DoProcess(int nType);
protected:
	bool event(QEvent *e);

public Q_SLOTS:
		;
		void OnBtnOK();
		void OnBtnESC();
	//	void OnTextChange(const QString & strText);
		void OnFocusChanged(QWidget *from, QWidget *to);
		void OnCurrentIndexChanged(int index);
private:
	BOOL m_bTerminateFlag;
	DWORD m_dwStartTime;
	BOOL m_bOK ;
	GUI_DLG_DEFINE(Ui::MsgEdit);
};
class CUserEdit : public QDialog
{
	Q_OBJECT

public:
	CUserEdit(QWidget *parent = NULL, UINT64 nID = 0, BOOL bNew = TRUE);
	~CUserEdit() {}
	BOOL EnrollParamSet(int nCandidateDiff = 1);
	BOOL EnrollCheck(BOOL bIDChange = FALSE);
	BOOL EnrollUserInfo();
	void DoProcess();

	public Q_SLOTS:
		;
		void OnFocusChanged(QWidget *from, QWidget *to);
		void OnIDChange(const QString & szID);
		void OnPasswordChange(const QString & szPassword);
		BOOL OnBtnOK();
		BOOL OnBtnESC();

protected:
	bool event(QEvent *e);

private:
	BOOL m_bTerminateFlag;
	GUI_DLG_DEFINE(Ui::UserEdit);
	BOOL m_bNew;
	UINT64 m_nCandidateID;
	UINT64 m_nID;
	int m_nManager;
};

class CUserDel : public QDialog
{
	Q_OBJECT

public:
	CUserDel(QWidget *parent = NULL);
	~CUserDel() {}
	void DoProcess();
	int SetUserInfo(UINT64 nID, QString szName);

public Q_SLOTS:;
	void OnBtnOK();
	void OnBtnESC();
	void OnFocusChanged(QWidget *from, QWidget *to);

protected:
	bool event(QEvent *e);

private:
	BOOL m_bTerminateFlag;
	DWORD m_dwStartTime;
	BOOL m_bOK ;
	GUI_DLG_DEFINE(Ui::UserDel);  
	struct _user_info *m_pUserInfo;
};

/************************************************************************/
/*  add by loveywm      Date : 2012/10/22                                */
/************************************************************************/
class CDepartmentManage : public CMainFrame
{
	Q_OBJECT

public:
	CDepartmentManage(QWidget *parent = NULL);
	~CDepartmentManage() {}
	UINT64 DoProcess();

private:
	BOOL m_bTerminateFlag;
};




#endif /*__USER_MANAGE_H__*/
