#ifndef __PROGRESSDLG_H__
#define __PROGRESSDLG_H__

#include "define.h"
#include "ui_progress-dlg.h"

class CProgressDlg : public QDialog
{
	Q_OBJECT

public:
	CProgressDlg(QWidget *parent = NULL);
	~CProgressDlg();
	void SetTitle(QString szTitle);
	void SetText(QString szText);
	void SetWindowSize(int w, int h);
	void SetProgressPercent(int nPercent);

private:
	GUI_DLG_DEFINE(Ui::ProgressDlg);
};

#endif /*__MESSAGEBOX_H__*/
