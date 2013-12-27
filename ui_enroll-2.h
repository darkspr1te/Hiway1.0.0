/********************************************************************************
** Form generated from reading ui file 'enroll-2.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_2_H
#define UI_ENROLL_2D_2_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EnrollStep2
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnEnrollFP;
    QLabel *lblFinger4;
    QLabel *lblFinger1;
    QLabel *lblFinger5;
    QLabel *lblFingerIcon;
    QPushButton *btnEnrollPWD;
    QLabel *lblFinger2;
    QLabel *lblFinger3;
    QPushButton *btnEnrollCard;
    QLabel *lblFinger8;
    QLabel *lblPwdIcon;
    QPushButton *btnUserEdit;
    QLabel *lblCardIcon;
    QLabel *lblFinger7;
    QLabel *lblFinger10;
    QLabel *lblFinger6;
    QLabel *lblFinger9;

    void setupUi(QDialog *EnrollStep2)
    {
        if (EnrollStep2->objectName().isEmpty())
            EnrollStep2->setObjectName(QString::fromUtf8("EnrollStep2"));
        EnrollStep2->resize(320, 240);
        lblBackground = new QLabel(EnrollStep2);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(EnrollStep2);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(EnrollStep2);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(EnrollStep2);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollStep2);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollStep2);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        btnEnrollFP = new QPushButton(EnrollStep2);
        btnEnrollFP->setObjectName(QString::fromUtf8("btnEnrollFP"));
        btnEnrollFP->setGeometry(QRect(29, 58, 83, 26));
        lblFinger4 = new QLabel(EnrollStep2);
        lblFinger4->setObjectName(QString::fromUtf8("lblFinger4"));
        lblFinger4->setEnabled(false);
        lblFinger4->setGeometry(QRect(185, 62, 16, 16));
        lblFinger4->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger1 = new QLabel(EnrollStep2);
        lblFinger1->setObjectName(QString::fromUtf8("lblFinger1"));
        lblFinger1->setEnabled(false);
        lblFinger1->setGeometry(QRect(140, 62, 16, 16));
        lblFinger1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger5 = new QLabel(EnrollStep2);
        lblFinger5->setObjectName(QString::fromUtf8("lblFinger5"));
        lblFinger5->setEnabled(false);
        lblFinger5->setGeometry(QRect(200, 62, 16, 16));
        lblFinger5->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFingerIcon = new QLabel(EnrollStep2);
        lblFingerIcon->setObjectName(QString::fromUtf8("lblFingerIcon"));
        lblFingerIcon->setEnabled(false);
        lblFingerIcon->setGeometry(QRect(121, 62, 16, 16));
        lblFingerIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblFingerIcon->setScaledContents(true);
        btnEnrollPWD = new QPushButton(EnrollStep2);
        btnEnrollPWD->setObjectName(QString::fromUtf8("btnEnrollPWD"));
        btnEnrollPWD->setGeometry(QRect(29, 122, 83, 26));
        lblFinger2 = new QLabel(EnrollStep2);
        lblFinger2->setObjectName(QString::fromUtf8("lblFinger2"));
        lblFinger2->setEnabled(false);
        lblFinger2->setGeometry(QRect(155, 62, 16, 16));
        lblFinger2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger3 = new QLabel(EnrollStep2);
        lblFinger3->setObjectName(QString::fromUtf8("lblFinger3"));
        lblFinger3->setEnabled(false);
        lblFinger3->setGeometry(QRect(170, 62, 16, 16));
        lblFinger3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        btnEnrollCard = new QPushButton(EnrollStep2);
        btnEnrollCard->setObjectName(QString::fromUtf8("btnEnrollCard"));
        btnEnrollCard->setGeometry(QRect(29, 90, 83, 26));
        lblFinger8 = new QLabel(EnrollStep2);
        lblFinger8->setObjectName(QString::fromUtf8("lblFinger8"));
        lblFinger8->setEnabled(false);
        lblFinger8->setGeometry(QRect(245, 62, 16, 16));
        lblFinger8->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblPwdIcon = new QLabel(EnrollStep2);
        lblPwdIcon->setObjectName(QString::fromUtf8("lblPwdIcon"));
        lblPwdIcon->setEnabled(false);
        lblPwdIcon->setGeometry(QRect(121, 127, 16, 16));
        lblPwdIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-pwd.png")));
        lblPwdIcon->setScaledContents(true);
        btnUserEdit = new QPushButton(EnrollStep2);
        btnUserEdit->setObjectName(QString::fromUtf8("btnUserEdit"));
        btnUserEdit->setGeometry(QRect(29, 154, 83, 26));
        lblCardIcon = new QLabel(EnrollStep2);
        lblCardIcon->setObjectName(QString::fromUtf8("lblCardIcon"));
        lblCardIcon->setEnabled(false);
        lblCardIcon->setGeometry(QRect(121, 96, 16, 16));
        lblCardIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-card.png")));
        lblCardIcon->setScaledContents(true);
        lblFinger7 = new QLabel(EnrollStep2);
        lblFinger7->setObjectName(QString::fromUtf8("lblFinger7"));
        lblFinger7->setEnabled(false);
        lblFinger7->setGeometry(QRect(230, 62, 16, 16));
        lblFinger7->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger10 = new QLabel(EnrollStep2);
        lblFinger10->setObjectName(QString::fromUtf8("lblFinger10"));
        lblFinger10->setEnabled(false);
        lblFinger10->setGeometry(QRect(275, 62, 16, 16));
        lblFinger10->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger6 = new QLabel(EnrollStep2);
        lblFinger6->setObjectName(QString::fromUtf8("lblFinger6"));
        lblFinger6->setEnabled(false);
        lblFinger6->setGeometry(QRect(215, 62, 16, 16));
        lblFinger6->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger9 = new QLabel(EnrollStep2);
        lblFinger9->setObjectName(QString::fromUtf8("lblFinger9"));
        lblFinger9->setEnabled(false);
        lblFinger9->setGeometry(QRect(260, 62, 16, 16));
        lblFinger9->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        QWidget::setTabOrder(btnEnrollFP, btnEnrollCard);
        QWidget::setTabOrder(btnEnrollCard, btnEnrollPWD);
        QWidget::setTabOrder(btnEnrollPWD, btnUserEdit);

        retranslateUi(EnrollStep2);

        QMetaObject::connectSlotsByName(EnrollStep2);
    } // setupUi

    void retranslateUi(QDialog *EnrollStep2)
    {
        EnrollStep2->setWindowTitle(QApplication::translate("EnrollStep2", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollStep2", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollStep2", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
        btnEnrollFP->setText(QApplication::translate("EnrollStep2", "1. Enroll FP    ", 0, QApplication::UnicodeUTF8));
        lblFinger4->setText(QString());
        lblFinger1->setText(QString());
        lblFinger5->setText(QString());
        lblFingerIcon->setText(QString());
        btnEnrollPWD->setText(QApplication::translate("EnrollStep2", "3. Password  ", 0, QApplication::UnicodeUTF8));
        lblFinger2->setText(QString());
        lblFinger3->setText(QString());
        btnEnrollCard->setText(QApplication::translate("EnrollStep2", "2. Enroll Card", 0, QApplication::UnicodeUTF8));
        lblFinger8->setText(QString());
        lblPwdIcon->setText(QString());
        btnUserEdit->setText(QApplication::translate("EnrollStep2", "4. Edit          ", 0, QApplication::UnicodeUTF8));
        lblCardIcon->setText(QString());
        lblFinger7->setText(QString());
        lblFinger10->setText(QString());
        lblFinger6->setText(QString());
        lblFinger9->setText(QString());
        Q_UNUSED(EnrollStep2);
    } // retranslateUi

};

namespace Ui {
    class EnrollStep2: public Ui_EnrollStep2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_2_H
