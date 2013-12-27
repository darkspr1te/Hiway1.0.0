#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>

#include <stdio.h>
#include "SBLabel.h"

#define QCOLOR(_color_)	(QColor(qRed((_color_)), qGreen((_color_)), qBlue((_color_)), qAlpha((_color_))))

//////////////////////////////////////////////////////////////////////////
SBLabel::SBLabel(QWidget *parent /* = NULL */, QRgb bgColor /* = qRgb */)
	: QWidget(parent)
{
	int i;

	for (i=0; i<MAX_TEXTITEM_CNT; i++)
	{
		m_StringList[i].x = 0;
		m_StringList[i].y = 0;
		m_StringList[i].foreColor = 0;
		m_StringList[i].bgColor = 0;
		m_StringList[i].char_width = 0;
		m_StringList[i].char_height = 0;
		m_StringList[i].bDrawByChar = 0;
		m_StringList[i].str = "";
	}

	m_bgColor = bgColor;
}

//////////////////////////////////////////////////////////////////////////
SBLabel::~SBLabel()
{

}

//////////////////////////////////////////////////////////////////////////
QString SBLabel::GetText(int nIndex)
{
	if (nIndex >= MAX_TEXTITEM_CNT)
		return QString("");
	return m_StringList[nIndex].str;
}

//////////////////////////////////////////////////////////////////////////
BOOL SBLabel::SetText(int nIndex, QString str, QRgb foreColor, QRgb bgColor, int x, int y, int char_width, int char_height, BOOL bDrawByChar)
{
	BOOL bRet = TRUE;
	TEXTITEM *item;

	if (nIndex >= MAX_TEXTITEM_CNT)
	{
		bRet = FALSE;
		goto _lExit;
	}

	if (x == -1 && nIndex > 0)
	{
		QFontMetrics fm = fontMetrics();
		item = &m_StringList[nIndex - 1];
		x = 5 + item->x + fm.width(item->str);
//		x = 5 + item->x + item->char_width * item->str.length();
	}

	item = &m_StringList[nIndex];
	item->x = x;
	item->y = y;
	item->foreColor = foreColor;
	item->bgColor = bgColor;
	item->char_width = (unsigned char)char_width;
	item->char_height = (unsigned char)char_height;
	item->bDrawByChar = bDrawByChar;
	item->str = str;

	update();
_lExit:
	return bRet;
}

BOOL SBLabel::ClearText(int from, int to)
{
	int i;
	for (i=from; i<=to; i++)
	{
		if (i >= MAX_TEXTITEM_CNT)
			break;
		SetText(i, "");
	}
	return TRUE;
}

//////////////////////////////////////////////////////////////////////////
void SBLabel::paintEvent(QPaintEvent *e)
{
	QPainter p(this);
	QRect r = e->rect();
	TEXTITEM *item;
	int len;
	int k;

	p.fillRect(r, QBrush(QCOLOR(m_bgColor)));

	for (int i=0; i<MAX_TEXTITEM_CNT; i++)
	{
		item = &m_StringList[i];
		len = item->str.length();

		if (!len)
			continue;

		QPen forePen(QCOLOR(item->foreColor));
		QBrush bgBrush(QCOLOR(item->bgColor), Qt::SolidPattern);
		QFontMetrics fm = fontMetrics();

		p.save();

		p.setPen(forePen);
		p.fillRect(item->x, item->y, fm.width(item->str), item->char_height, bgBrush);
//		p.fillRect(item->x, item->y, item->char_width * len, item->char_height, bgBrush);

		if (item->bDrawByChar)
		{
			for (k=0; k<len; k++)
			{
				p.drawText(
//				item->x + k * item->char_width + (item->char_width / 2) - fm.width(item->str[k]),
					item->x + k * item->char_width,
					item->y + item->char_height,
					QString(item->str[k]));
			}
		}
		else
			p.drawText(item->x, item->y, fm.width(item->str), item->char_height, Qt::AlignVCenter, item->str);
		
		p.restore();
	}
}

/*
QFontMetrics fontMetrics(displayFont);
painter.setPen(QPen(Qt::black));
for (int row = beginRow; row <= endRow; ++row) {

	for (int column = beginColumn; column <= endColumn; ++column) {

		int key = row*columns + column;
		painter.setClipRect(column*squareSize, row*squareSize, squareSize, squareSize);

		if (key == lastKey)
			painter.fillRect(column*squareSize + 1, row*squareSize + 1, squareSize, squareSize, QBrush(Qt::red));

		painter.drawText(column*squareSize + (squareSize / 2) - fontMetrics.width(QChar(key))/2,
			row*squareSize + 4 + fontMetrics.ascent(),
			QString(QChar(key)));
	}
}
}
*/