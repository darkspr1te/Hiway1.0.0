#include "../precomp.h"
#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "../gui/SBLabel.h"
#include "t9_main.h"
#include "t9_english.h"

//////////////////////////////////////////////////////////////////////////
extern SBLabel*		g_T9Window;

//////////////////////////////////////////////////////////////////////////
static int			g_KeyBuffer;
static int			g_SubIndex;
//////////////////////////////////////////////////////////////////////////

//
//
//////////////////////////////////////////////////////////////////////////
void eng_Init(void)
{
	g_KeyBuffer = UIKEY_NONE;
	g_SubIndex = 0;
	g_nEditStatus =T9_Start;
}

//////////////////////////////////////////////////////////////////////////
QString GetEnglishStr()
{
	int i;
	int nKey;
	QString szEnglish;
	struct Key_index *KCHZ;

	if (g_KeyBuffer == UIKEY_NONE)
		return NULL;

	nKey = g_KeyBuffer - UIKEY_2;
	KCHZ = &Key_index_en[nKey];
	for (i=0; i<KCHZ->Sy_num; i++)
		szEnglish += KCHZ->KC_Symb[i];
	return szEnglish;
}

//////////////////////////////////////////////////////////////////////////
QChar eng_keyPress(int nKey)
{
	int nPageIndex = 0;
	QChar chRet;
	
	if (nKey == UIKEY_MENU)
	{
		if (g_KeyBuffer != UIKEY_NONE)
			
		{
			g_KeyBuffer = UIKEY_NONE;
			g_nEditStatus = T9_Start;
		}
		else
			chRet = UIKEY_MENU;
	}

	if (nKey >= UIKEY_1 && nKey <= UIKEY_9)
	{
		if (g_KeyBuffer != UIKEY_NONE && g_nEditStatus == T9_Select)
		{
			QString str = GetEnglishStr();

			chRet = str[0 * 9 + nKey - UIKEY_1];
			if (chRet != 0)
			{
				eng_Init();
				goto _lExit;
			}
		}
		else if (nKey != UIKEY_1 && g_nEditStatus == T9_Start)
		{
			g_KeyBuffer = nKey;
			g_nEditStatus = T9_Select;
		}		
	}

	if(g_KeyBuffer == UIKEY_NONE)
		g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
	else
	T9_DRAW_CHARS(9, nPageIndex, TRUE, GetEnglishStr());

_lExit:
	return chRet;
}
