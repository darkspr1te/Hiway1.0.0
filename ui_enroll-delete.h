/********************************************************************************
** Form generated from reading ui file 'enroll-delete.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_DELETE_H
#define UI_ENROLL_2D_DELETE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EnrollDelete
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblPwdIcon;
    QLabel *lblFinger2;
    QLabel *lblFinger1;
    QLabel *lblFinger9;
    QLabel *lblFinger4;
    QLabel *lblFinger8;
    QLabel *lblFinger6;
    QLabel *lblFinger7;
    QPushButton *btnDeleteCard;
    QPushButton *btnDeleteAll;
    QLabel *lblFingerIcon;
    QLabel *lblFinger5;
    QLabel *lblFinger10;
    QPushButton *btnDeleteFP;
    QLabel *lblCardIcon;
    QLabel *lblFinger3;
    QPushButton *btnDeletePwd;

    void setupUi(QDialog *EnrollDelete)
    {
        if (EnrollDelete->objectName().isEmpty())
            EnrollDelete->setObjectName(QString::fromUtf8("EnrollDelete"));
        EnrollDelete->resize(320, 240);
        lblBackground = new QLabel(EnrollDelete);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(EnrollDelete);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(EnrollDelete);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(EnrollDelete);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollDelete);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollDelete);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblPwdIcon = new QLabel(EnrollDelete);
        lblPwdIcon->setObjectName(QString::fromUtf8("lblPwdIcon"));
        lblPwdIcon->setEnabled(false);
        lblPwdIcon->setGeometry(QRect(124, 127, 16, 16));
        lblPwdIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-pwd.png")));
        lblPwdIcon->setScaledContents(true);
        lblFinger2 = new QLabel(EnrollDelete);
        lblFinger2->setObjectName(QString::fromUtf8("lblFinger2"));
        lblFinger2->setEnabled(false);
        lblFinger2->setGeometry(QRect(158, 59, 16, 16));
        lblFinger2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger1 = new QLabel(EnrollDelete);
        lblFinger1->setObjectName(QString::fromUtf8("lblFinger1"));
        lblFinger1->setEnabled(false);
        lblFinger1->setGeometry(QRect(143, 59, 16, 16));
        lblFinger1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger9 = new QLabel(EnrollDelete);
        lblFinger9->setObjectName(QString::fromUtf8("lblFinger9"));
        lblFinger9->setEnabled(false);
        lblFinger9->setGeometry(QRect(263, 59, 16, 16));
        lblFinger9->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger4 = new QLabel(EnrollDelete);
        lblFinger4->setObjectName(QString::fromUtf8("lblFinger4"));
        lblFinger4->setEnabled(false);
        lblFinger4->setGeometry(QRect(188, 59, 16, 16));
        lblFinger4->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger8 = new QLabel(EnrollDelete);
        lblFinger8->setObjectName(QString::fromUtf8("lblFinger8"));
        lblFinger8->setEnabled(false);
        lblFinger8->setGeometry(QRect(248, 59, 16, 16));
        lblFinger8->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger6 = new QLabel(EnrollDelete);
        lblFinger6->setObjectName(QString::fromUtf8("lblFinger6"));
        lblFinger6->setEnabled(false);
        lblFinger6->setGeometry(QRect(218, 59, 16, 16));
        lblFinger6->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger7 = new QLabel(EnrollDelete);
        lblFinger7->setObjectName(QString::fromUtf8("lblFinger7"));
        lblFinger7->setEnabled(false);
        lblFinger7->setGeometry(QRect(233, 59, 16, 16));
        lblFinger7->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        btnDeleteCard = new QPushButton(EnrollDelete);
        btnDeleteCard->setObjectName(QString::fromUtf8("btnDeleteCard"));
        btnDeleteCard->setGeometry(QRect(31, 90, 85, 22));
        btnDeleteAll = new QPushButton(EnrollDelete);
        btnDeleteAll->setObjectName(QString::fromUtf8("btnDeleteAll"));
        btnDeleteAll->setGeometry(QRect(31, 157, 85, 22));
        lblFingerIcon = new QLabel(EnrollDelete);
        lblFingerIcon->setObjectName(QString::fromUtf8("lblFingerIcon"));
        lblFingerIcon->setEnabled(false);
        lblFingerIcon->setGeometry(QRect(124, 60, 16, 16));
        lblFingerIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblFingerIcon->setScaledContents(true);
        lblFinger5 = new QLabel(EnrollDelete);
        lblFinger5->setObjectName(QString::fromUtf8("lblFinger5"));
        lblFinger5->setEnabled(false);
        lblFinger5->setGeometry(QRect(203, 59, 16, 16));
        lblFinger5->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        lblFinger10 = new QLabel(EnrollDelete);
        lblFinger10->setObjectName(QString::fromUtf8("lblFinger10"));
        lblFinger10->setEnabled(false);
        lblFinger10->setGeometry(QRect(278, 59, 16, 16));
        lblFinger10->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        btnDeleteFP = new QPushButton(EnrollDelete);
        btnDeleteFP->setObjectName(QString::fromUtf8("btnDeleteFP"));
        btnDeleteFP->setGeometry(QRect(31, 56, 85, 22));
        lblCardIcon = new QLabel(EnrollDelete);
        lblCardIcon->setObjectName(QString::fromUtf8("lblCardIcon"));
        lblCardIcon->setEnabled(false);
        lblCardIcon->setGeometry(QRect(124, 94, 16, 16));
        lblCardIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-card.png")));
        lblCardIcon->setScaledContents(true);
        lblFinger3 = new QLabel(EnrollDelete);
        lblFinger3->setObjectName(QString::fromUtf8("lblFinger3"));
        lblFinger3->setEnabled(false);
        lblFinger3->setGeometry(QRect(173, 59, 16, 16));
        lblFinger3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-fingerenrolled.png")));
        btnDeletePwd = new QPushButton(EnrollDelete);
        btnDeletePwd->setObjectName(QString::fromUtf8("btnDeletePwd"));
        btnDeletePwd->setGeometry(QRect(30, 124, 85, 22));
        QWidget::setTabOrder(btnDeleteFP, btnDeleteCard);
        QWidget::setTabOrder(btnDeleteCard, btnDeletePwd);
        QWidget::setTabOrder(btnDeletePwd, btnDeleteAll);

        retranslateUi(EnrollDelete);

        QMetaObject::connectSlotsByName(EnrollDelete);
    } // setupUi

    void retranslateUi(QDialog *EnrollDelete)
    {
        EnrollDelete->setWindowTitle(QApplication::translate("EnrollDelete", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollDelete", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollDelete", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
        lblPwdIcon->setText(QString());
        lblFinger2->setText(QString());
        lblFinger1->setText(QString());
        lblFinger9->setText(QString());
        lblFinger4->setText(QString());
        lblFinger8->setText(QString());
        lblFinger6->setText(QString());
        lblFinger7->setText(QString());
        btnDeleteCard->setText(QApplication::translate("EnrollDelete", "2. Delete Card", 0, QApplication::UnicodeUTF8));
        btnDeleteAll->setText(QApplication::translate("EnrollDelete", "4. Delete All   ", 0, QApplication::UnicodeUTF8));
        lblFingerIcon->setText(QString());
        lblFinger5->setText(QString());
        lblFinger10->setText(QString());
        btnDeleteFP->setText(QApplication::translate("EnrollDelete", "1. Delete FP    ", 0, QApplication::UnicodeUTF8));
        lblCardIcon->setText(QString());
        lblFinger3->setText(QString());
        btnDeletePwd->setText(QApplication::translate("EnrollDelete", "3. Delete Pwd", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(EnrollDelete);
    } // retranslateUi

};

namespace Ui {
    class EnrollDelete: public Ui_EnrollDelete {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_DELETE_H
