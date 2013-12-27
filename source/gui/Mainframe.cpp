#include "../precomp.h"
#include "Mainframe.h"
#include <QtGui/QPixmap>

CMainFrame::CMainFrame(QWidget *parent /* = NULL */)
	: QDialog(parent)
{
	GUI_DLG_IMPL(TRUE);
	GUI_DLG_SET_THEME();  

	m_pmapFrame = *ui.lblBackgroundFrame->pixmap();

	m_nFrameX = 0;
	m_nFrameY = ui.lblTitleIcon->height();
	m_nFrameWidth = ui.lblBackgroundFrame->width();
	m_nFrameHeight = ui.lblBackgroundFrame->height() - m_nFrameY - ui.lblStatusText->height();
}

CMainFrame::~CMainFrame()
{

}

void CMainFrame::setTitle(QString szIconFile, QString szTitle)
{
	QPixmap pmap_icon(szIconFile);
	ui.lblTitleIcon->setPixmap(pmap_icon);
	uiLcdSetLabelText(ui.lblTitleText, szTitle, TITLECOLOR,QColor());
}
