/********************************************************************************
** Form generated from reading ui file 'input-userid2.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INPUT_2D_USERID2_H
#define UI_INPUT_2D_USERID2_H

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

class Ui_UserIDInput2
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLineEdit *txtID;
    QLabel *lblID;
    QLabel *lblIcon;

    void setupUi(QDialog *UserIDInput2)
    {
        if (UserIDInput2->objectName().isEmpty())
            UserIDInput2->setObjectName(QString::fromUtf8("UserIDInput2"));
        UserIDInput2->resize(320, 240);
        lblBackground = new QLabel(UserIDInput2);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(UserIDInput2);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(UserIDInput2);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(58, 10, 240, 28));
        lblTitleIcon = new QLabel(UserIDInput2);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(20, 9, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(UserIDInput2);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(UserIDInput2);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        btnOK = new QPushButton(UserIDInput2);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 160, 71, 25));
        btnESC = new QPushButton(UserIDInput2);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 160, 71, 25));
        txtID = new QLineEdit(UserIDInput2);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(160, 90, 121, 20));
        txtID->setMaxLength(8);
        txtID->setEchoMode(QLineEdit::Normal);
        lblID = new QLabel(UserIDInput2);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(90, 90, 65, 21));
        lblIcon = new QLabel(UserIDInput2);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setGeometry(QRect(30, 80, 40, 40));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-userid.png")));
        lblIcon->setScaledContents(true);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(UserIDInput2);

        QMetaObject::connectSlotsByName(UserIDInput2);
    } // setupUi

    void retranslateUi(QDialog *UserIDInput2)
    {
        UserIDInput2->setWindowTitle(QApplication::translate("UserIDInput2", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("UserIDInput2", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("UserIDInput2", "OK:Select Or T9Input,  ESC:Back ", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("UserIDInput2", "OK", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("UserIDInput2", "ESC", 0, QApplication::UnicodeUTF8));
        lblID->setText(QApplication::translate("UserIDInput2", "User ID", 0, QApplication::UnicodeUTF8));
        lblIcon->setText(QString());
        Q_UNUSED(UserIDInput2);
    } // retranslateUi

};

namespace Ui {
    class UserIDInput2: public Ui_UserIDInput2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_2D_USERID2_H
