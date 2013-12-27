#ifndef __MAINFRAME_H__
#define __MAINFRAME_H__

#include "define.h"
#include "ui_mainframe.h"

class QPixmap;

class CMainFrame : public QDialog
{
	Q_OBJECT

public:
	CMainFrame(QWidget *parent = NULL);
	~CMainFrame();
	void setTitle(QString szIcon, QString szTitle);
	int getFrameX() {return m_nFrameX;}
	int getFrameY() {return m_nFrameY;}
	int getFrameWidth() {return m_nFrameWidth;}
	int getFrameHeight() {return m_nFrameHeight;}

	GUI_DLG_DEFINE(Ui::MainFrame);

	QPixmap m_pmapFrame;

protected:
	int m_nFrameX;
	int m_nFrameY;
	int m_nFrameWidth;
	int m_nFrameHeight;
};

#endif /*__MAINFRAME_H__*/
