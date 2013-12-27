#include "../precomp.h"
#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "../gui/SBLabel.h"
#include "t9_main.h"
#include "t9_symbol.h"

//////////////////////////////////////////////////////////////////////////
extern SBLabel*		g_T9Window;
static QString		g_szSymCharacters;
static int			g_PageIndex;

//////////////////////////////////////////////////////////////////////////
void sym_Init(void)
{
	g_PageIndex = 0;
}

//////////////////////////////////////////////////////////////////////////
QString GetSymbolStr()
{
	int i;
	QString szSymbol;

	for (i = 0; i < (int)ITEM_CNT(KS_SYmb_2); i++)
		szSymbol += KS_SYmb_2[i];

	return szSymbol;
}

//////////////////////////////////////////////////////////////////////////
QChar sym_keyPress(int nKey)
{
	QChar chRet;

	if (nKey == UIKEY_MENU)
		chRet = UIKEY_MENU;
	if (nKey == UIKEY_UP)
		g_PageIndex--;
	if (nKey == UIKEY_DOWN)
		g_PageIndex++;
	if (nKey >= UIKEY_1 && nKey <= UIKEY_9)
	{
		if (uiKeyGetKeyLong(1000) == nKey)
		{
			QString str = GetSymbolStr();
			chRet = str[g_PageIndex * 9 + nKey - UIKEY_1];
		}
	}

	T9_DRAW_CHARS(9, g_PageIndex, TRUE, GetSymbolStr());
	return chRet;
}
