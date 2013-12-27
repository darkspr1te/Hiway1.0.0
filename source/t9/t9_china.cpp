#include "../precomp.h"
#include <QtGui/QApplication>
#include <QtCore/QTranslator>

#include "../gui/SBLabel.h"
#include "t9_main.h"
#include "t9_china.h"

//////////////////////////////////////////////////////////////////////////
extern SBLabel*		g_T9Window;
//////////////////////////////////////////////////////////////////////////
static int			g_KeyBuffer[8];
static int			g_KeyBufIdx;
static int			g_SubIndex;
static int			g_PageIndex;
//////////////////////////////////////////////////////////////////////////

//
//
//////////////////////////////////////////////////////////////////////////
struct Key_index* GetAlphaStr()
{
	int i;
	int nKey;
	struct Key_index *KCHZ;

	if (g_KeyBufIdx == 0)
		return NULL;

	nKey = g_KeyBuffer[0];
	KCHZ=Key_index_headkey[nKey];
	while (strcmp(KCHZ->KC, "end"))
	{
		for (i=0; i<g_KeyBufIdx; i++)
		{
			nKey = g_KeyBuffer[i] + '2';
			if (nKey != KCHZ->KC[i])
				break;
		}

		if ( i == g_KeyBufIdx)
			return KCHZ;
		else
			KCHZ++;
	}

	return NULL;
}

//////////////////////////////////////////////////////////////////////////
const char* GetChineseStr()
{
	int i, k;
//	const char** pinyin;
	const char* szPinyin;
	struct Key_index* KCHZ;
	struct PY_index *cpHZ;
	int nCount;
	
	KCHZ = GetAlphaStr();
	if (KCHZ)
	{
		g_SubIndex += KCHZ->Sy_num;
		g_SubIndex %= KCHZ->Sy_num;

		szPinyin = KCHZ->KC_Symb[g_SubIndex];
		k = szPinyin[0] - 'a';
		cpHZ = PY_index_headletter[k];
		nCount = ((DWORD)(PY_index_headletter[k + 1]) - (DWORD)(PY_index_headletter[k])) / sizeof(struct PY_index);
		for (k=0; k<nCount; k++)
		{
			for (i=1; i<g_KeyBufIdx; i++)
			{
				if (szPinyin[i] != cpHZ[k].PY[i-1])
					break;
			}
			if (i == g_KeyBufIdx)
				return cpHZ[k].PY_mb;
		}
	}

	return NULL;
}

//
//
//////////////////////////////////////////////////////////////////////////
void chn_Init(void)
{
	memset(g_KeyBuffer, UIKEY_NONE, sizeof(g_KeyBuffer));
	g_KeyBufIdx = 0;
	g_SubIndex = 0;
	g_PageIndex = 0;
	g_nEditStatus = T9_Start;
}

//////////////////////////////////////////////////////////////////////////
void chn_DrawPinYin()
{
	int i;
	struct Key_index* KCHZ;
//	const char** pinyin;
	QString szPinyin;
//	int nStartPos;
	
	g_T9Window->ClearText(T9_PINYIN_INDEX, T9_PINYIN_INDEX + T9_PINYIN_INDEX_COUNT - 1);

	KCHZ = GetAlphaStr();
	if (KCHZ)
	{
		QRgb rgbForeColor, rgbBgColor;

		g_SubIndex += KCHZ->Sy_num;
		g_SubIndex %= KCHZ->Sy_num;

		for (i=0; i<KCHZ->Sy_num; i++)
		{
			if(i == g_SubIndex)
			{
				rgbForeColor = T9_PINYIN_FORECOLOR_SEL;
				rgbBgColor = T9_PINYIN_BGCOLOR_SEL;
			}
			else
			{
				rgbForeColor = T9_PINYIN_FORECOLOR;
				rgbBgColor = T9_PINYIN_BGCOLOR;
			}

			szPinyin = KCHZ->KC_Symb[i];
			g_T9Window->SetText(T9_PINYIN_INDEX + i, szPinyin, rgbForeColor, rgbBgColor,
				i ? -1 : T9_PINYIN_POS_X, T9_PINYIN_POS_Y, T9_PINYIN_CHAR_WIDTH, T9_PINYIN_CHAR_HEIGHT);   
		}
	}
}

//////////////////////////////////////////////////////////////////////////
QChar chn_keyPress(int nKey)
{
	QChar chRet;

	switch (nKey)
	{
	case UIKEY_MENU:
		if (g_KeyBufIdx > 0)
			g_KeyBufIdx--;
		else
			chRet = UIKEY_MENU;
		break;
// 	case UIKEY_OK:
// 	case UIKEY_DOWN:
// 		chRet = chn_CharSelectProc();
// 		break;
	//case UIKEY_LEFT:
	//	g_SubIndex--;
	//	g_PageIndex = 0;
	//	break;
	//case UIKEY_RIGHT:
	//	g_SubIndex++;
	//	g_PageIndex = 0;
	//	break;
	case UIKEY_UP:
		if(g_nEditStatus == T9_Edit)
		{
			g_SubIndex--;
			g_PageIndex = 0;
		}
		else
			g_PageIndex--;
		break;
	case UIKEY_DOWN:
		if(g_nEditStatus == T9_Edit)
		{
			g_SubIndex++;
			g_PageIndex = 0;
		}
		else
			g_PageIndex++;
		break;
	default:
		if (nKey >= UIKEY_1 && nKey <= UIKEY_9)
		{
			if(g_nEditStatus == T9_Start)
			{
				g_nEditStatus = T9_Edit;
			}
			if (g_KeyBufIdx &&/* uiKeyGetKeyLong(1000) == nKey &&*/ g_nEditStatus == T9_Select)
			{
				QString str = QWidget::tr(GetChineseStr());

				chRet = str[g_PageIndex * 9 + nKey - UIKEY_1];
				if (chRet != 0)
					chn_Init();
			}
			else if (nKey != UIKEY_1 && g_KeyBufIdx < 8 && g_nEditStatus == T9_Edit)
			{
				g_KeyBuffer[g_KeyBufIdx++] = nKey - UIKEY_2;
				if (!GetAlphaStr())
					g_KeyBufIdx--;
				else
					g_SubIndex = 0;
			}
		}
		break;
	}
	if(g_nEditStatus == T9_Edit)
		chn_DrawPinYin();
	if(g_KeyBufIdx == 0)
	{
		g_T9Window->ClearText(0, MAX_TEXTITEM_CNT);
		g_nEditStatus = T9_Start;
	}
	else
		T9_DRAW_CHARS(9, g_PageIndex, TRUE, QWidget::tr(GetChineseStr()));

// _lExit:
	return chRet;
}
