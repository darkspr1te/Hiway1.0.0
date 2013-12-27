#ifndef __SB_LABEL_H__
#define __SB_LABEL_H__
#include "define.h"
#include <QtGui/QWidget>
#include <QtGui/QPainter>

#define MAX_TEXTITEM_CNT	20

class QWidget;

typedef struct _text_item
{
	int x;
	int y;
	QRgb foreColor;
	QRgb bgColor;
	unsigned char char_width;
	unsigned char char_height;
	unsigned char bDrawByChar;
	QString str;
}TEXTITEM;

class SBLabel : public QWidget
{
	Q_OBJECT

public:
	SBLabel(QWidget *parent = NULL, QRgb bgColor = qRgb(255, 255, 255));
	~SBLabel();
	QString GetText(int nIndex = 0);
	BOOL SetText(int nIndex, QString str, QRgb foreColor = qRgb(0, 0, 0), QRgb bgColor = qRgb(255, 255, 255), int x = 5, int y = 5, int char_width = 7, int char_height = 14, BOOL bDrawByChar = FALSE);
	BOOL ClearText(int from, int to);

protected:
	void paintEvent(QPaintEvent *e);

private:
	TEXTITEM m_StringList[MAX_TEXTITEM_CNT];
	QRgb m_bgColor;
};

#endif /*__SB_LABEL_H__*/
