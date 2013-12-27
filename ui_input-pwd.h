/********************************************************************************
** Form generated from reading ui file 'input-pwd.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INPUT_2D_PWD_H
#define UI_INPUT_2D_PWD_H

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

class Ui_InputPWD
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleIcon;
    QLabel *lblTitleText;
    QLabel *lblStatusText;
    QLabel *lblStatusIcon;
    QPushButton *btnOK;
    QLineEdit *txtPasswordConfirm;
    QLabel *lblStatus;
    QLineEdit *txtPassword;
    QLabel *lblPassword;
    QPushButton *btnESC;
    QLabel *lblConfirm;

    void setupUi(QDialog *InputPWD)
    {
        if (InputPWD->objectName().isEmpty())
            InputPWD->setObjectName(QString::fromUtf8("InputPWD"));
        InputPWD->resize(320, 240);
        lblBackground = new QLabel(InputPWD);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(InputPWD);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 31));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleIcon = new QLabel(InputPWD);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-pwd.png")));
        lblTitleIcon->setScaledContents(true);
        lblTitleText = new QLabel(InputPWD);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblStatusText = new QLabel(InputPWD);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblStatusIcon = new QLabel(InputPWD);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        btnOK = new QPushButton(InputPWD);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(63, 159, 75, 24));
        txtPasswordConfirm = new QLineEdit(InputPWD);
        txtPasswordConfirm->setObjectName(QString::fromUtf8("txtPasswordConfirm"));
        txtPasswordConfirm->setGeometry(QRect(133, 99, 140, 20));
        txtPasswordConfirm->setMaxLength(4);
        txtPasswordConfirm->setEchoMode(QLineEdit::Password);
        txtPasswordConfirm->setReadOnly(false);
        lblStatus = new QLabel(InputPWD);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(93, 126, 181, 21));
        lblStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        txtPassword = new QLineEdit(InputPWD);
        txtPassword->setObjectName(QString::fromUtf8("txtPassword"));
        txtPassword->setGeometry(QRect(133, 59, 140, 20));
        txtPassword->setMaxLength(4);
        txtPassword->setEchoMode(QLineEdit::Password);
        txtPassword->setReadOnly(false);
        lblPassword = new QLabel(InputPWD);
        lblPassword->setObjectName(QString::fromUtf8("lblPassword"));
        lblPassword->setGeometry(QRect(32, 59, 100, 21));
        btnESC = new QPushButton(InputPWD);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(173, 159, 75, 24));
        lblConfirm = new QLabel(InputPWD);
        lblConfirm->setObjectName(QString::fromUtf8("lblConfirm"));
        lblConfirm->setGeometry(QRect(32, 99, 100, 21));
        QWidget::setTabOrder(txtPassword, txtPasswordConfirm);
        QWidget::setTabOrder(txtPasswordConfirm, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(InputPWD);

        QMetaObject::connectSlotsByName(InputPWD);
    } // setupUi

    void retranslateUi(QDialog *InputPWD)
    {
        InputPWD->setWindowTitle(QApplication::translate("InputPWD", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleIcon->setText(QString());
        lblTitleText->setText(QApplication::translate("InputPWD", "Title", 0, QApplication::UnicodeUTF8));
        lblStatusText->setText(QApplication::translate("InputPWD", "OK: Select  ESC: Return", 0, QApplication::UnicodeUTF8));
        lblStatusIcon->setText(QString());
        btnOK->setText(QApplication::translate("InputPWD", "OK", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("InputPWD", "Status", 0, QApplication::UnicodeUTF8));
        lblPassword->setText(QApplication::translate("InputPWD", "Password", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("InputPWD", "ESC", 0, QApplication::UnicodeUTF8));
        lblConfirm->setText(QApplication::translate("InputPWD", "Confirm", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(InputPWD);
    } // retranslateUi

};

namespace Ui {
    class InputPWD: public Ui_InputPWD {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_2D_PWD_H
