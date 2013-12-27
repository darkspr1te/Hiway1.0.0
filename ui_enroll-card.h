/********************************************************************************
** Form generated from reading ui file 'enroll-card.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_CARD_H
#define UI_ENROLL_2D_CARD_H

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

class Ui_EnrollCard
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLineEdit *txtCardNumber;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *lblCardNumber;
    QLabel *lblEnrollStatus;

    void setupUi(QDialog *EnrollCard)
    {
        if (EnrollCard->objectName().isEmpty())
            EnrollCard->setObjectName(QString::fromUtf8("EnrollCard"));
        EnrollCard->resize(320, 240);
        lblBackground = new QLabel(EnrollCard);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(EnrollCard);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 31));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(EnrollCard);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(EnrollCard);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-card.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollCard);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollCard);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        txtCardNumber = new QLineEdit(EnrollCard);
        txtCardNumber->setObjectName(QString::fromUtf8("txtCardNumber"));
        txtCardNumber->setGeometry(QRect(147, 100, 113, 20));
        btnESC = new QPushButton(EnrollCard);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(187, 150, 75, 24));
        btnOK = new QPushButton(EnrollCard);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(77, 150, 75, 24));
        lblCardNumber = new QLabel(EnrollCard);
        lblCardNumber->setObjectName(QString::fromUtf8("lblCardNumber"));
        lblCardNumber->setGeometry(QRect(87, 100, 61, 21));
        lblEnrollStatus = new QLabel(EnrollCard);
        lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
        lblEnrollStatus->setGeometry(QRect(37, 60, 191, 21));

        retranslateUi(EnrollCard);

        QMetaObject::connectSlotsByName(EnrollCard);
    } // setupUi

    void retranslateUi(QDialog *EnrollCard)
    {
        EnrollCard->setWindowTitle(QApplication::translate("EnrollCard", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollCard", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollCard", "OK: Select  ESC: Return \342\226\262Retry", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("EnrollCard", "ESC", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("EnrollCard", "OK", 0, QApplication::UnicodeUTF8));
        lblCardNumber->setText(QApplication::translate("EnrollCard", "CardNo: ", 0, QApplication::UnicodeUTF8));
        lblEnrollStatus->setText(QApplication::translate("EnrollCard", "Input your card", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(EnrollCard);
    } // retranslateUi

};

namespace Ui {
    class EnrollCard: public Ui_EnrollCard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_CARD_H
