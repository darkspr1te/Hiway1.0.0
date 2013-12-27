#include "../precomp.h"

#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QKeyEvent>

#include "t9_main.h"
#include "../gui/SBLabel.h"

//////////////////////////////////////////////////////////////////////////
SBLabel* g_T9Window = NULL;
SBLabel* g_T9Staute =NULL;
int g_nEditStatus;

void chn_Init(void);
void eng_Init(void);
void sym_Init(void);
QChar chn_keyPress(int nKey);
QChar eng_keyPress(int nKey);
QChar sym_keyPress(int nKey);

void uiProcDrawStatusbar(QLabel *pLbl, int nOK, int nESC);
/************************************************************************/
/*                                                                      */
/************************************************************************/
CT9Window::CT9Window(QWidget */*parent = NULL */)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
//	GUI_DLG_SET_THEME_1();

	m_InputWindow = new SBLabel(this, qRgba(59, 129, 212, 0));
	if (!m_InputWindow)
		return;
	//	ui.lblBackground->hide();
	m_InputWindow->setGeometry(ui.lblStatusText->x(), ui.lblStatusText->y(),ui.lblStatusText->width(),ui.lblStatusText->height());  
	m_InputWindow->show();  
	m_InputWindow->setFont(SB_FONT_4());

	GUI_DLG_STATUSBAR();
}

CT9Window::~CT9Window()
{
	if (m_InputWindow)
		delete m_InputWindow;
}

SBLabel* CT9Window::GetInputWindow()
{
	return m_InputWindow;
}

//////////////////////////////////////////////////////////////////////////
enum {IME_CHINA, IME_ENGLISH, IME_COUNT}; 

//////////////////////////////////////////////////////////////////////////
void T9_INPUT_PROC(QWidget* mainWidget, QLineEdit* ctrlTextEdit)
{
	int nKey;
	QLabel* pIcon,*pStatusBar;

	
	pIcon = mainWidget->findChild<QLabel*>("lblStatusIcon");
	pIcon->setGeometry(20,201,24,24);
	pStatusBar = mainWidget->findChild<QLabel*>("lblStatusText");
	pStatusBar->hide();

	QPixmap pixmap(QString(GUI_RESOURCE_PATH) + QString("t9-input.png")) ;
	QPixmap oldpixmap;
	oldpixmap =*pIcon->pixmap();
	pIcon->setPixmap(pixmap);
	
	QChar ch;
	int nIME = IME_CHINA;
    const int __IME_STR[] = {UISTR_T9_CHN, UISTR_T9_ENG}; 
	QString strResult = ctrlTextEdit->text();

	chn_Init();
	eng_Init();
	
	g_nEditStatus = T9_Start;	

	g_T9Staute = new SBLabel(mainWidget,qRgba(59, 129, 212, 0));
	g_T9Staute->setGeometry(258,17,T9_IME_CHAR_WIDTH*5,T9_IME_CHAR_HEIGHT+3);
	g_T9Staute->show();
	g_T9Staute->setFont(SB_FONT_4());
	g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR, T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);
	g_T9Window = new SBLabel(mainWidget, qRgba(59, 129, 212, 0));
    g_T9Window->setGeometry(45,195 ,275,40);  
	g_T9Window ->show();  
	g_T9Window->setFont(SB_FONT_4());
	
	while (uiTimeIsTimeout() == FALSE)
	{
		POST_EVENTS();

		nKey = uiKeyGetKey();
		if (nKey == UIKEY_NONE)
			continue;
		if (uiKeyIsDigit((T_UI_KEY)nKey) && strResult.length() >= ctrlTextEdit->maxLength())
			continue;

		switch(nKey)
		{
        case UIKEY_POWER:       
			if(g_nEditStatus == T9_Start || g_nEditStatus == T9_Select)
			{
				nIME = (nIME + 1) % IME_COUNT;

				chn_Init();
				eng_Init();

				g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
				g_T9Staute->SetText(T9_IME_INDEX, UISTR(__IME_STR[nIME]), T9_IME_FORECOLOR, T9_IME_BGCOLOR,
					T9_IME_POS_X, T9_IME_POS_Y, T9_IME_CHAR_WIDTH, T9_IME_CHAR_HEIGHT);
				 ctrlTextEdit->setText(strResult);
				break;
			}
			break;
        case UIKEY_OK:
            if(g_nEditStatus == T9_Edit)
			{
				g_nEditStatus = T9_Select;
				goto _lDefaultProcess;
				break;
			} 
			else goto _lExit;
			break;
		case UIKEY_ESC:
			goto _lExit;
		default:
_lDefaultProcess:
			if (nIME == IME_CHINA)
				ch = chn_keyPress(nKey);
			else if (nIME == IME_ENGLISH)
				ch = eng_keyPress(nKey);
			if (ch == UIKEY_MENU)
			{
				if (strResult.length() > 0)
				{
					strResult.remove(strResult.length() - 1, 1);
						ctrlTextEdit->setText(strResult);
				}
			}
			else if (ch != 0)
			{
				strResult += ch;
					ctrlTextEdit->setText(strResult);
					g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
				WAIT_EVENT(GETKEY(TRUE) == nKey);
			}
			break;
		}
	}

_lExit:
	pIcon->setPixmap(oldpixmap);
	pStatusBar->show();
	
	DELETE(g_T9Staute);
	DELETE(g_T9Window);

	return;
}

//////////////////////////////////////////////////////////////////////////
BOOL T9_DRAW_CHARS(int nPageSize, int & nPageIndex, BOOL /*bNumber*/, QString str)
{
	int i;
	int from, to;
	int nPageCount;
	QString strNumber = "";
	QString strOutput = "";

	if (str.length() == 0)
	{
		g_T9Window->ClearText(T9_NUM_INDEX, T9_STR_INDEX);
		return FALSE;
	}

	nPageSize = MIN(nPageSize, 9);
	nPageCount = (str.length() + nPageSize - 1) / nPageSize;
	nPageIndex += nPageCount;
	nPageIndex %= nPageCount;

	if (nPageIndex * nPageSize >= str.length())
		return FALSE;
	
	from = nPageIndex * nPageSize;
	to   = from + nPageSize;

	for (i = from; i < to; i++)
	{
		if (i >= str.length())
			break;

		strNumber += QString("%1").arg(i - from + 1);
		strOutput += str[i];
	}

	if (from > 0)
		strOutput += UISTR(UISTR_SYMBOL_UP);
	if (to < str.length())
		strNumber += UISTR(UISTR_SYMBOL_DOWN);

//_lExit:
	if(g_nEditStatus == T9_Edit)
	{	
		g_T9Window->ClearText(T9_NUM_INDEX, MAX_TEXTITEM_CNT);
		g_T9Window->SetText(T9_STR_INDEX, strOutput, T9_STR_FORECOLOR, T9_STR_BGCOLOR, 
			T9_NUM_POS_X, T9_NUM_POS_Y, T9_STR_CHAR_WIDTH, T9_STR_CHAR_HEIGHT, TRUE);
	}
	else
	{
		g_T9Window->ClearText(T9_PINYIN_INDEX, T9_PINYIN_INDEX + T9_PINYIN_INDEX_COUNT - 1);
		g_T9Window->SetText(T9_NUM_INDEX, strNumber, T9_NUM_FORECOLOR, T9_NUM_BGCOLOR,
			T9_NUM_POS_X, T9_NUM_POS_Y, T9_NUM_CHAR_WIDTH, T9_NUM_CHAR_HEIGHT, TRUE);
		g_T9Window->SetText(T9_STR_INDEX, strOutput, T9_STR_FORECOLOR, T9_STR_BGCOLOR, 
			T9_STR_POS_X, T9_STR_POS_Y, T9_STR_CHAR_WIDTH, T9_STR_CHAR_HEIGHT, TRUE);    

	}
		return TRUE;
}
