/********************************************************************************
** Form generated from reading ui file 'msgbox-dlg.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MSGBOX_2D_DLG_H
#define UI_MSGBOX_2D_DLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MsgboxDlg
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblStatus;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *Moretextlabel;

    void setupUi(QDialog *MsgboxDlg)
    {
        if (MsgboxDlg->objectName().isEmpty())
            MsgboxDlg->setObjectName(QString::fromUtf8("MsgboxDlg"));
        MsgboxDlg->setWindowModality(Qt::NonModal);
        MsgboxDlg->resize(270, 120);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        MsgboxDlg->setFont(font);
        lblBackground = new QLabel(MsgboxDlg);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        lblIcon = new QLabel(MsgboxDlg);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setGeometry(QRect(10, 20, 40, 40));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-ok.png")));
        lblStatus = new QLabel(MsgboxDlg);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(60, 30, 200, 41));
        lblStatus->setTextFormat(Qt::LogText);
        lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        btnESC = new QPushButton(MsgboxDlg);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(150, 80, 75, 24));
        btnOK = new QPushButton(MsgboxDlg);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(30, 80, 75, 24));
        Moretextlabel = new QLabel(MsgboxDlg);
        Moretextlabel->setObjectName(QString::fromUtf8("Moretextlabel"));
        Moretextlabel->setGeometry(QRect(50, 10, 211, 101));
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(MsgboxDlg);

        QMetaObject::connectSlotsByName(MsgboxDlg);
    } // setupUi

    void retranslateUi(QDialog *MsgboxDlg)
    {
        MsgboxDlg->setWindowTitle(QApplication::translate("MsgboxDlg", "Title", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblIcon->setText(QString());
        lblStatus->setText(QApplication::translate("MsgboxDlg", "Status", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("MsgboxDlg", "ESC", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("MsgboxDlg", "OK", 0, QApplication::UnicodeUTF8));
        Moretextlabel->setText(QApplication::translate("MsgboxDlg", "TextLabel", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MsgboxDlg);
    } // retranslateUi

};

namespace Ui {
    class MsgboxDlg: public Ui_MsgboxDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGBOX_2D_DLG_H
