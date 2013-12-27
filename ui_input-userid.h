/********************************************************************************
** Form generated from reading ui file 'input-userid.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INPUT_2D_USERID_H
#define UI_INPUT_2D_USERID_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_UserIDInput
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblID;
    QLineEdit *txtID;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLabel *lblIconPWD;
    QLabel *lblPWD;
    QLineEdit *txtPWD;

    void setupUi(QDialog *UserIDInput)
    {
        if (UserIDInput->objectName().isEmpty())
            UserIDInput->setObjectName(QString::fromUtf8("UserIDInput"));
        UserIDInput->resize(270, 120);
        lblBackground = new QLabel(UserIDInput);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        lblIcon = new QLabel(UserIDInput);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setGeometry(QRect(10, 20, 40, 40));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-userid.png")));
        lblIcon->setScaledContents(true);
        lblID = new QLabel(UserIDInput);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(60, 29, 65, 21));
        txtID = new QLineEdit(UserIDInput);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(130, 29, 113, 20));
        txtID->setMaxLength(5);
        lblStatus = new QLabel(UserIDInput);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(60, 57, 181, 21));
        lblStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnOK = new QPushButton(UserIDInput);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 80, 75, 24));
        btnOK->setFocusPolicy(Qt::StrongFocus);
        btnESC = new QPushButton(UserIDInput);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(160, 80, 75, 24));
        btnESC->setFocusPolicy(Qt::StrongFocus);
        lblIconPWD = new QLabel(UserIDInput);
        lblIconPWD->setObjectName(QString::fromUtf8("lblIconPWD"));
        lblIconPWD->setGeometry(QRect(10, 20, 40, 40));
        lblIconPWD->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-pwd.png")));
        lblPWD = new QLabel(UserIDInput);
        lblPWD->setObjectName(QString::fromUtf8("lblPWD"));
        lblPWD->setGeometry(QRect(60, 29, 65, 21));
        txtPWD = new QLineEdit(UserIDInput);
        txtPWD->setObjectName(QString::fromUtf8("txtPWD"));
        txtPWD->setGeometry(QRect(130, 29, 113, 20));
        txtPWD->setMaxLength(9);
        txtPWD->setEchoMode(QLineEdit::Password);
        QWidget::setTabOrder(txtID, txtPWD);
        QWidget::setTabOrder(txtPWD, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(UserIDInput);

        QMetaObject::connectSlotsByName(UserIDInput);
    } // setupUi

    void retranslateUi(QDialog *UserIDInput)
    {
        UserIDInput->setWindowTitle(QApplication::translate("UserIDInput", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblIcon->setText(QString());
        lblID->setText(QApplication::translate("UserIDInput", "User ID", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("UserIDInput", "Status", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("UserIDInput", "OK", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("UserIDInput", "ESC", 0, QApplication::UnicodeUTF8));
        lblIconPWD->setText(QString());
        lblPWD->setText(QApplication::translate("UserIDInput", "User PWD", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(UserIDInput);
    } // retranslateUi

};

namespace Ui {
    class UserIDInput: public Ui_UserIDInput {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_2D_USERID_H
