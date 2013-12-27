/********************************************************************************
** Form generated from reading ui file 'selftest-keyboard.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELFTEST_2D_KEYBOARD_H
#define UI_SELFTEST_2D_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelftestKeyboard
{
public:
    QLabel *lblBackground;
    QPushButton *btn8;
    QPushButton *btn2;
    QPushButton *btn5;
    QPushButton *btnMENU;
    QPushButton *btn7;
    QPushButton *btn1;
    QPushButton *btn9;
    QPushButton *btn0;
    QPushButton *btnESC;
    QPushButton *btn4;
    QPushButton *btn3;
    QPushButton *btn6;
    QPushButton *btnOK;
    QPushButton *btnUP;
    QPushButton *btnDOWN;
    QPushButton *btnPOWER;
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;

    void setupUi(QDialog *SelftestKeyboard)
    {
        if (SelftestKeyboard->objectName().isEmpty())
            SelftestKeyboard->setObjectName(QString::fromUtf8("SelftestKeyboard"));
        SelftestKeyboard->resize(320, 240);
        lblBackground = new QLabel(SelftestKeyboard);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(30, 38, 261, 161));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btn8 = new QPushButton(SelftestKeyboard);
        btn8->setObjectName(QString::fromUtf8("btn8"));
        btn8->setGeometry(QRect(109, 123, 49, 26));
        btn2 = new QPushButton(SelftestKeyboard);
        btn2->setObjectName(QString::fromUtf8("btn2"));
        btn2->setGeometry(QRect(109, 51, 49, 26));
        btn5 = new QPushButton(SelftestKeyboard);
        btn5->setObjectName(QString::fromUtf8("btn5"));
        btn5->setGeometry(QRect(109, 87, 49, 26));
        btnMENU = new QPushButton(SelftestKeyboard);
        btnMENU->setObjectName(QString::fromUtf8("btnMENU"));
        btnMENU->setGeometry(QRect(215, 87, 49, 26));
        btn7 = new QPushButton(SelftestKeyboard);
        btn7->setObjectName(QString::fromUtf8("btn7"));
        btn7->setGeometry(QRect(55, 123, 50, 26));
        btn1 = new QPushButton(SelftestKeyboard);
        btn1->setObjectName(QString::fromUtf8("btn1"));
        btn1->setGeometry(QRect(55, 51, 50, 26));
        btn9 = new QPushButton(SelftestKeyboard);
        btn9->setObjectName(QString::fromUtf8("btn9"));
        btn9->setGeometry(QRect(162, 123, 49, 26));
        btn0 = new QPushButton(SelftestKeyboard);
        btn0->setObjectName(QString::fromUtf8("btn0"));
        btn0->setGeometry(QRect(109, 159, 49, 26));
        btnESC = new QPushButton(SelftestKeyboard);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(215, 51, 49, 26));
        btn4 = new QPushButton(SelftestKeyboard);
        btn4->setObjectName(QString::fromUtf8("btn4"));
        btn4->setGeometry(QRect(55, 87, 50, 26));
        btn3 = new QPushButton(SelftestKeyboard);
        btn3->setObjectName(QString::fromUtf8("btn3"));
        btn3->setGeometry(QRect(162, 51, 49, 26));
        btn6 = new QPushButton(SelftestKeyboard);
        btn6->setObjectName(QString::fromUtf8("btn6"));
        btn6->setGeometry(QRect(162, 87, 49, 26));
        btnOK = new QPushButton(SelftestKeyboard);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(162, 159, 49, 26));
        btnUP = new QPushButton(SelftestKeyboard);
        btnUP->setObjectName(QString::fromUtf8("btnUP"));
        btnUP->setGeometry(QRect(215, 123, 49, 26));
        btnDOWN = new QPushButton(SelftestKeyboard);
        btnDOWN->setObjectName(QString::fromUtf8("btnDOWN"));
        btnDOWN->setGeometry(QRect(215, 159, 49, 26));
        btnPOWER = new QPushButton(SelftestKeyboard);
        btnPOWER->setObjectName(QString::fromUtf8("btnPOWER"));
        btnPOWER->setGeometry(QRect(55, 159, 50, 26));
        lblStatusbar = new QLabel(SelftestKeyboard);
        lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
        lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
        label = new QLabel(SelftestKeyboard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 200, 320, 40));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        label->setScaledContents(true);
        lblStatusIcon = new QLabel(SelftestKeyboard);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(SelftestKeyboard);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 261, 40));

        retranslateUi(SelftestKeyboard);

        QMetaObject::connectSlotsByName(SelftestKeyboard);
    } // setupUi

    void retranslateUi(QDialog *SelftestKeyboard)
    {
        SelftestKeyboard->setWindowTitle(QApplication::translate("SelftestKeyboard", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btn8->setText(QApplication::translate("SelftestKeyboard", "8", 0, QApplication::UnicodeUTF8));
        btn2->setText(QApplication::translate("SelftestKeyboard", "2", 0, QApplication::UnicodeUTF8));
        btn5->setText(QApplication::translate("SelftestKeyboard", "5", 0, QApplication::UnicodeUTF8));
        btnMENU->setText(QApplication::translate("SelftestKeyboard", "MENU", 0, QApplication::UnicodeUTF8));
        btn7->setText(QApplication::translate("SelftestKeyboard", "7", 0, QApplication::UnicodeUTF8));
        btn1->setText(QApplication::translate("SelftestKeyboard", "1", 0, QApplication::UnicodeUTF8));
        btn9->setText(QApplication::translate("SelftestKeyboard", "9", 0, QApplication::UnicodeUTF8));
        btn0->setText(QApplication::translate("SelftestKeyboard", "0", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("SelftestKeyboard", "ESC", 0, QApplication::UnicodeUTF8));
        btn4->setText(QApplication::translate("SelftestKeyboard", "4", 0, QApplication::UnicodeUTF8));
        btn3->setText(QApplication::translate("SelftestKeyboard", "3", 0, QApplication::UnicodeUTF8));
        btn6->setText(QApplication::translate("SelftestKeyboard", "6", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("SelftestKeyboard", "OK", 0, QApplication::UnicodeUTF8));
        btnUP->setText(QApplication::translate("SelftestKeyboard", "Up", 0, QApplication::UnicodeUTF8));
        btnDOWN->setText(QApplication::translate("SelftestKeyboard", "Down", 0, QApplication::UnicodeUTF8));
        btnPOWER->setText(QApplication::translate("SelftestKeyboard", "#", 0, QApplication::UnicodeUTF8));
        lblStatusbar->setText(QString());
        label->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("SelftestKeyboard", "Press any key to check", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SelftestKeyboard);
    } // retranslateUi

};

namespace Ui {
    class SelftestKeyboard: public Ui_SelftestKeyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTEST_2D_KEYBOARD_H
