#include "../precomp.h"
#include "ProgressDlg.h"
#include <QtGui/QPixmap>
#include <QtGui/QPainter>
#include <QtGui/QFont>
#include <QtGui/QPen>
#include <QtGui/QColor>

//////////////////////////////////////////////////////////////////////////
CProgressDlg::CProgressDlg(QWidget *parent)
	: QDialog(parent)
{
	GUI_DLG_IMPL(FALSE);
	GUI_DLG_CENTER(this);
	GUI_DLG_SET_THEME_1();
	ui.progressBar->setValue(0);
//	move(25, 50);
}

//////////////////////////////////////////////////////////////////////////
CProgressDlg::~CProgressDlg()
{
}

//////////////////////////////////////////////////////////////////////////
void CProgressDlg::SetTitle(QString /*szTitle*/)
{
}

//////////////////////////////////////////////////////////////////////////
void CProgressDlg::SetText(QString szText)
{
	ui.lblMessage->setText(szText);
}

//////////////////////////////////////////////////////////////////////////
void CProgressDlg::SetProgressPercent(int nPercent)
{
	ui.progressBar->setValue(nPercent);
}
