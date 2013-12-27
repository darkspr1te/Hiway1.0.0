#ifndef __T9_MAIN_H__
#define __T9_MAIN_H__

#include "../gui/define.h"
#include "ui_t9-input.h"

class QLineEdit;
class SBLabel;

//////////////////////////////////////////////////////////////////////////
#define T9_IME_INDEX			0
#define T9_IME_FORECOLOR		g_rgbForeColor
#define T9_IME_BGCOLOR			(qRgba(255, 255, 255, 0))
#define T9_IME_POS_X			0
#define T9_IME_POS_Y			0
#define T9_IME_CHAR_WIDTH		10
#define T9_IME_CHAR_HEIGHT		16

#define T9_PINYIN_INDEX			1
#define T9_PINYIN_INDEX_COUNT	6
#define T9_PINYIN_FORECOLOR		g_rgbForeColor
#define T9_PINYIN_BGCOLOR		(qRgba(255, 255, 255, 0))
#define T9_PINYIN_FORECOLOR_SEL	(qRgba(255, 255, 255, 255))
#define T9_PINYIN_BGCOLOR_SEL	(qRgba(179, 182, 185, 255))
#define T9_PINYIN_POS_X			0
#define T9_PINYIN_POS_Y			0
#define T9_PINYIN_CHAR_WIDTH	12
#define T9_PINYIN_CHAR_HEIGHT	16   

#define T9_VIEW_INDEX			17
#define T9_VIEW_FORECOLOR		g_rgbForeColor
#define T9_VIEW_BGCOLOR			(qRgba(255, 255, 255, 0))
#define T9_VIEW_POS_X			0
#define T9_VIEW_POS_Y			0
#define T9_VIEW_CHAR_WIDTH		20
#define T9_VIEW_CHAR_HEIGHT		16

#define T9_STR_INDEX			18
#define T9_STR_FORECOLOR		g_rgbForeColor
#define T9_STR_BGCOLOR			(qRgba(255, 255, 255, 0))
#define T9_STR_POS_X			0
#define T9_STR_POS_Y			2    
#define T9_STR_CHAR_WIDTH		25
#define T9_STR_CHAR_HEIGHT		16

#define T9_NUM_INDEX			19
#define T9_NUM_FORECOLOR		g_rgbForeColor
#define T9_NUM_BGCOLOR			(qRgba(255, 255, 255, 0))
#define T9_NUM_POS_X			0
#define T9_NUM_POS_Y			20   
#define T9_NUM_CHAR_WIDTH		25
#define T9_NUM_CHAR_HEIGHT		16

extern int g_nEditStatus;

enum {T9_Start = 1,T9_Edit=2,T9_Select=3,T9_End=4};

//////////////////////////////////////////////////////////////////////////
class CT9Window : public QDialog
{
	Q_OBJECT

public:
	CT9Window(QWidget *parent = NULL);
	~CT9Window();
	SBLabel* GetInputWindow();

public:
	GUI_DLG_DEFINE(Ui::T9InputDlg);
	SBLabel* m_InputWindow;
};

//////////////////////////////////////////////////////////////////////////
void T9_INPUT_PROC(QWidget* mainWidget, QLineEdit* ctrlTextEdit);
BOOL T9_DRAW_CHARS(int nPageSize, int & nPageIndex, BOOL bNumber, QString str);

#endif /*__T9_MAIN_H__*/
