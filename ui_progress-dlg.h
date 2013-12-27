/********************************************************************************
** Form generated from reading ui file 'progress-dlg.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_PROGRESS_2D_DLG_H
#define UI_PROGRESS_2D_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>

QT_BEGIN_NAMESPACE

class Ui_ProgressDlg
{
public:
    QLabel *lblBackground;
    QLabel *lblMessage;
    QProgressBar *progressBar;

    void setupUi(QDialog *ProgressDlg)
    {
        if (ProgressDlg->objectName().isEmpty())
            ProgressDlg->setObjectName(QString::fromUtf8("ProgressDlg"));
        ProgressDlg->setWindowModality(Qt::NonModal);
        ProgressDlg->resize(270, 90);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        ProgressDlg->setFont(font);
        lblBackground = new QLabel(ProgressDlg);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 90));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        lblMessage = new QLabel(ProgressDlg);
        lblMessage->setObjectName(QString::fromUtf8("lblMessage"));
        lblMessage->setGeometry(QRect(18, 10, 241, 32));
        lblMessage->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar = new QProgressBar(ProgressDlg);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(17, 50, 240, 21));
        progressBar->setValue(24);
        progressBar->setTextVisible(false);

        retranslateUi(ProgressDlg);

        QMetaObject::connectSlotsByName(ProgressDlg);
    } // setupUi

    void retranslateUi(QDialog *ProgressDlg)
    {
        ProgressDlg->setWindowTitle(QApplication::translate("ProgressDlg", "Title", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblMessage->setText(QString());
        Q_UNUSED(ProgressDlg);
    } // retranslateUi

};

namespace Ui {
    class ProgressDlg: public Ui_ProgressDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROGRESS_2D_DLG_H
