#ifndef __DEFINE_H__
#define __DEFINE_H__

//////////////////////////////////////////////////////////////////////////
typedef int						HFILE;

typedef char					CHAR;
typedef short					SHORT;
typedef int						INT;

typedef unsigned char			BYTE;
typedef unsigned char			BOOL;
typedef unsigned short			WORD;
typedef unsigned int			DWORD;
typedef long					LONG;
typedef unsigned long long		UINT64;

//////////////////////////////////////////////////////////////////////////
#ifndef NULL
#define NULL					(0)
#endif /*NULL*/
#ifndef TRUE
#define TRUE					(1)
#endif /*TRUE*/
#ifndef FALSE
#define FALSE					(0)
#endif /*FALSE*/
#ifndef INVALID_HANDLE_VALUE
#define INVALID_HANDLE_VALUE	(-1)
#endif /*INVALID_HANDLE_VALUE*/

//////////////////////////////////////////////////////////////////////////
#define MAKEWORD(a, b)			((WORD)(((BYTE)(a)) | ((WORD)((BYTE)(b))) << 8))
#define MAKELONG(a, b)			((LONG)(((WORD)(a)) | ((DWORD)((WORD)(b))) << 16))
#define LOWORD(l)				((WORD)(l))
#define HIWORD(l)				((WORD)(((DWORD)(l) >> 16) & 0xFFFF))
#define LOBYTE(w)				((BYTE)(w))
#define HIBYTE(w)				((BYTE)(((WORD)(w) >> 8) & 0xFF))
#define PACKED					__attribute__((packed))
#define TR(_s_)					(QObject::tr((_s_)))

#define PERF_CHECK(_X_)			//_X_

#define SB_FONT(_name_, _size_)	(QFont((_name_), (_size_)))
#define SB_FONT_0()				(SB_FONT("sbfont", 50))
#define SB_FONT_1()				(SB_FONT("sbfont", 40))
#define SB_FONT_2()				(SB_FONT("sbfont", 14))
#define SB_FONT_3()				(SB_FONT("sbfont", 13))
#define SB_FONT_4()				(SB_FONT("sbfont", 12))
#define TiltleFont				SB_FONT_2()

#define GUI_CURRENT_THEME		g_nCurrentTheme
#define FOREGROUND_COLOR		QColor(g_rgbForeColor)
#define FOREGROUND_COLOR1		QColor(g_rgbForeColor1)
#define BACKGROUND_COLOR		QColor(g_rgbBackgroundColor)
#define TITLECOLOR				QColor(255,255,10)   
#define BACKGROUND_IMAGE		g_bgImageFilename
#define INPUTBOX_IMAGE			g_inputboxImageFilename
#define TITLE_IMAGE				g_titleImageFilename
#define BOTTOM_IMAGE			g_bottomImageFilename
#define CLOCK_IMAGE				g_clockImageFilename

#define GUI_DLG_DEFINE(_DLG_)	_DLG_ ui
#define GUI_DLG_IMPL(_MAX_)		{ui.setupUi(this); if (_MAX_) setGeometry(0, 0, LCD_SIZE_X, LCD_SIZE_Y);}
#define GUI_DLG_CENTER(_DLG_)	{(_DLG_)->move((LCD_SIZE_X - (_DLG_)->width()) / 2, (LCD_SIZE_Y - (_DLG_)->height()) / 2);}
#define GUI_DLG_SET_FORE_COLOR(_pal_, _col_) {(_pal_)->setColor(QPalette::All, QPalette::WindowText, (_col_)); \
											  (_pal_)->setColor(QPalette::All, QPalette::Text, (_col_)); \
											 }


#define ROM_FLASH_SIZE			17			//16M


#define GUI_DLG_SET_THEME()		\
{ \
	ui.lblBackground->setPixmap(QPixmap(BACKGROUND_IMAGE)); \
	ui.lblTitleBackground->setPixmap(QPixmap(TITLE_IMAGE)); \
	SET_DLG_ITEM_COLOR(this,1); \
}

#define GUI_DLG_SET_THEME_1() {ui.lblBackground->setPixmap(QPixmap(INPUTBOX_IMAGE)); SET_DLG_ITEM_COLOR(this);}

#define GUI_DLG_STATUSBAR()		\
{ \
	int w = ui.lblStatusbar->width(); \
	int h = ui.lblStatusbar->height(); \
	QPixmap pmap(BACKGROUND_IMAGE); \
	pmap = pmap.copy((LCD_SIZE_X - w) / 2, LCD_SIZE_Y - h, w, h); \
	ui.lblStatusbar->setPixmap(pmap); \
	uiLcdSetLabelText(ui.lblStatusText, ui.lblStatusText->text(), FOREGROUND_COLOR); \
}

#define DIALOGBOX(_class_)		({_class_ *__OBJ = new _class_; if (__OBJ) { __OBJ->show(); __OBJ->DoProcess(); delete __OBJ;}})
#define DIALOGBOX_RET(_class_)	({int _ret_=0; _class_ *__OBJ = new _class_; if (__OBJ) { __OBJ->show(); _ret_=__OBJ->DoProcess(); delete __OBJ;} _ret_;})
#define DIALOGBOX_RET_HAS_NAME(_c_, _n_) ({int _ret_=0; _c_ *__OBJ = new _c_; if (__OBJ) { __OBJ->setObjectName((_n_)); __OBJ->show(); _ret_=__OBJ->DoProcess(); delete __OBJ;} _ret_;})
#define DIALOGBOXEX(_c_, _p_)	({int _ret_=0; _c_ *__OBJ = new _c_; if (__OBJ) { __OBJ->show(); _ret_=__OBJ->DoProcess(_p_); delete __OBJ;} _ret_;})
#define DIALOGBOXEX_HAS_NAME(_c_, _p_, _n_) ({int _ret_=0; _c_ *__OBJ = new _c_; if (__OBJ) { __OBJ->setObjectName((_n_)); __OBJ->show(); _ret_=__OBJ->DoProcess(_p_); delete __OBJ;} _ret_;})

#define WM_USER					(QEvent::User)
#define WM_T9INPUT				((QEvent::Type)(WM_USER + 1))

#define TIMER_RTCCLOCK			0x1001
#define TIMER_LED_ON			0x1002
#define TIMER_MANAGERREQUEST	0x1003
#define TIMER_DATETIME_SETUP	0x1004
#define TIMER_ALARM				0x1005
#define TIMER_SYSMONITOR		0x1006
#define TIMER_SMSG				0x1007
#define TIMER_ACCACHE_FLUSH		0x1008
#define TIMER_DURESS_ALARM		0x1009
#define TIMER_SOSKEY_RELEASE	0x100A
#define TIMER_KEYPAD_BACKGROUND	0x100B
#define TIMER_LOCK_RESTORE		0x100C
#define TIMER_LOGOUT_ALARM		0x100D

#define SETUP_TIMER(_timerid_, _timeout_, _param_, _callback_)	{if (g_MainWindow) g_MainWindow->SetTimer((_timerid_), (_timeout_), (_param_), (_callback_));}
#define STOP_TIMER(_timerid_)	{if (g_MainWindow) g_MainWindow->StopTimer((_timerid_));}

#endif /*__DEFINE_H__*/
