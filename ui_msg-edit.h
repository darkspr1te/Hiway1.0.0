/********************************************************************************
** Form generated from reading ui file 'msg-edit.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MSG_2D_EDIT_H
#define UI_MSG_2D_EDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_MsgEdit
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnOK;
    QLabel *lblID;
    QLineEdit *txtStartTime;
    QLabel *lblValidMinutes;
    QLineEdit *txtValidMinutes;
    QLabel *lblBelong;
    QLineEdit *txtBelong;
    QLineEdit *txtContent;
    QLineEdit *txtID;
    QComboBox *comboTag;
    QLabel *lblStartTime;
    QLabel *lblTag;
    QLabel *lblUnit;
    QPushButton *btnESC;

    void setupUi(QDialog *MsgEdit)
    {
        if (MsgEdit->objectName().isEmpty())
            MsgEdit->setObjectName(QString::fromUtf8("MsgEdit"));
        MsgEdit->resize(320, 240);
        lblBackground = new QLabel(MsgEdit);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(MsgEdit);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(MsgEdit);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(MsgEdit);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(15, 12, 22, 22));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/MESSINFO.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(MsgEdit);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(MsgEdit);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 275, 25));
        btnOK = new QPushButton(MsgEdit);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setEnabled(true);
        btnOK->setGeometry(QRect(320, 240, 0, 0));
        btnOK->setFocusPolicy(Qt::StrongFocus);
        lblID = new QLabel(MsgEdit);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(28, 53, 71, 21));
        txtStartTime = new QLineEdit(MsgEdit);
        txtStartTime->setObjectName(QString::fromUtf8("txtStartTime"));
        txtStartTime->setEnabled(true);
        txtStartTime->setGeometry(QRect(100, 77, 199, 22));
        lblValidMinutes = new QLabel(MsgEdit);
        lblValidMinutes->setObjectName(QString::fromUtf8("lblValidMinutes"));
        lblValidMinutes->setGeometry(QRect(28, 102, 71, 21));
        txtValidMinutes = new QLineEdit(MsgEdit);
        txtValidMinutes->setObjectName(QString::fromUtf8("txtValidMinutes"));
        txtValidMinutes->setEnabled(true);
        txtValidMinutes->setGeometry(QRect(100, 101, 71, 22));
        lblBelong = new QLabel(MsgEdit);
        lblBelong->setObjectName(QString::fromUtf8("lblBelong"));
        lblBelong->setEnabled(true);
        lblBelong->setGeometry(QRect(172, 124, 74, 21));
        lblBelong->setAlignment(Qt::AlignCenter);
        txtBelong = new QLineEdit(MsgEdit);
        txtBelong->setObjectName(QString::fromUtf8("txtBelong"));
        txtBelong->setEnabled(false);
        txtBelong->setGeometry(QRect(248, 125, 50, 22));
        txtBelong->setMaxLength(5);
        txtContent = new QLineEdit(MsgEdit);
        txtContent->setObjectName(QString::fromUtf8("txtContent"));
        txtContent->setGeometry(QRect(28, 150, 271, 40));
        txtContent->setMaxLength(29);
        txtID = new QLineEdit(MsgEdit);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setEnabled(true);
        txtID->setGeometry(QRect(100, 53, 71, 22));
        txtID->setMaxLength(5);
        comboTag = new QComboBox(MsgEdit);
        comboTag->setObjectName(QString::fromUtf8("comboTag"));
        comboTag->setGeometry(QRect(100, 125, 71, 22));
        lblStartTime = new QLabel(MsgEdit);
        lblStartTime->setObjectName(QString::fromUtf8("lblStartTime"));
        lblStartTime->setGeometry(QRect(28, 77, 71, 21));
        lblTag = new QLabel(MsgEdit);
        lblTag->setObjectName(QString::fromUtf8("lblTag"));
        lblTag->setGeometry(QRect(28, 123, 71, 21));
        lblUnit = new QLabel(MsgEdit);
        lblUnit->setObjectName(QString::fromUtf8("lblUnit"));
        lblUnit->setEnabled(true);
        lblUnit->setGeometry(QRect(174, 102, 71, 21));
        btnESC = new QPushButton(MsgEdit);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setEnabled(true);
        btnESC->setGeometry(QRect(320, 240, 0, 0));
        btnESC->setFocusPolicy(Qt::StrongFocus);
        QWidget::setTabOrder(txtID, txtStartTime);
        QWidget::setTabOrder(txtStartTime, txtValidMinutes);
        QWidget::setTabOrder(txtValidMinutes, comboTag);
        QWidget::setTabOrder(comboTag, txtBelong);
        QWidget::setTabOrder(txtBelong, txtContent);
        QWidget::setTabOrder(txtContent, btnOK);

        retranslateUi(MsgEdit);

        QMetaObject::connectSlotsByName(MsgEdit);
    } // setupUi

    void retranslateUi(QDialog *MsgEdit)
    {
        MsgEdit->setWindowTitle(QApplication::translate("MsgEdit", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("MsgEdit", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("MsgEdit", "Use Arrow & OK, ESC for return ,OK for T9Input", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("MsgEdit", "OK", 0, QApplication::UnicodeUTF8));
        lblID->setText(QApplication::translate("MsgEdit", "SMSID", 0, QApplication::UnicodeUTF8));
        lblValidMinutes->setText(QApplication::translate("MsgEdit", "ValidMinutes", 0, QApplication::UnicodeUTF8));
        lblBelong->setText(QApplication::translate("MsgEdit", "Belong", 0, QApplication::UnicodeUTF8));
        comboTag->clear();
        comboTag->insertItems(0, QStringList()
         << QApplication::translate("MsgEdit", "General", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MsgEdit", "User", 0, QApplication::UnicodeUTF8)
        );
        lblStartTime->setText(QApplication::translate("MsgEdit", "StartTime", 0, QApplication::UnicodeUTF8));
        lblTag->setText(QApplication::translate("MsgEdit", "Tag", 0, QApplication::UnicodeUTF8));
        lblUnit->setText(QApplication::translate("MsgEdit", "Minutes", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("MsgEdit", "esc", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MsgEdit);
    } // retranslateUi

};

namespace Ui {
    class MsgEdit: public Ui_MsgEdit {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSG_2D_EDIT_H
