/********************************************************************************
** Form generated from reading ui file 'enroll-fp.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_FP_H
#define UI_ENROLL_2D_FP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>

QT_BEGIN_NAMESPACE

class Ui_EnrollFP
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLineEdit *txtFpNumber;
    QLabel *lblEnrollStatus3;
    QLabel *lblEnrollStatus1;
    QLabel *lblFpNumber;
    QLabel *lblEnrollStatus2;
    QLabel *lblEnrollStatus;
    QLabel *lblFpArea;

    void setupUi(QDialog *EnrollFP)
    {
        if (EnrollFP->objectName().isEmpty())
            EnrollFP->setObjectName(QString::fromUtf8("EnrollFP"));
        EnrollFP->resize(320, 240);
        lblBackground = new QLabel(EnrollFP);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(EnrollFP);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 31));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(EnrollFP);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(EnrollFP);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollFP);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(6, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollFP);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(20, 200, 301, 25));
        txtFpNumber = new QLineEdit(EnrollFP);
        txtFpNumber->setObjectName(QString::fromUtf8("txtFpNumber"));
        txtFpNumber->setGeometry(QRect(221, 60, 71, 20));
        txtFpNumber->setReadOnly(true);
        lblEnrollStatus3 = new QLabel(EnrollFP);
        lblEnrollStatus3->setObjectName(QString::fromUtf8("lblEnrollStatus3"));
        lblEnrollStatus3->setEnabled(false);
        lblEnrollStatus3->setGeometry(QRect(130, 150, 16, 16));
        lblEnrollStatus3->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblEnrollStatus1 = new QLabel(EnrollFP);
        lblEnrollStatus1->setObjectName(QString::fromUtf8("lblEnrollStatus1"));
        lblEnrollStatus1->setEnabled(false);
        lblEnrollStatus1->setGeometry(QRect(130, 86, 16, 16));
        lblEnrollStatus1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblFpNumber = new QLabel(EnrollFP);
        lblFpNumber->setObjectName(QString::fromUtf8("lblFpNumber"));
        lblFpNumber->setGeometry(QRect(159, 60, 61, 21));
        lblEnrollStatus2 = new QLabel(EnrollFP);
        lblEnrollStatus2->setObjectName(QString::fromUtf8("lblEnrollStatus2"));
        lblEnrollStatus2->setEnabled(false);
        lblEnrollStatus2->setGeometry(QRect(130, 117, 16, 16));
        lblEnrollStatus2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblEnrollStatus = new QLabel(EnrollFP);
        lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
        lblEnrollStatus->setGeometry(QRect(147, 129, 161, 20));
        lblEnrollStatus->setAlignment(Qt::AlignCenter);
        lblFpArea = new QLabel(EnrollFP);
        lblFpArea->setObjectName(QString::fromUtf8("lblFpArea"));
        lblFpArea->setGeometry(QRect(18, 60, 105, 130));
        lblFpArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/area-fingerprint.png")));
        lblFpArea->setScaledContents(false);

        retranslateUi(EnrollFP);

        QMetaObject::connectSlotsByName(EnrollFP);
    } // setupUi

    void retranslateUi(QDialog *EnrollFP)
    {
        EnrollFP->setWindowTitle(QApplication::translate("EnrollFP", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollFP", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollFP", "EnrollFP Status", 0, QApplication::UnicodeUTF8));
        lblEnrollStatus3->setText(QString());
        lblEnrollStatus1->setText(QString());
        lblFpNumber->setText(QApplication::translate("EnrollFP", "FP Number :", 0, QApplication::UnicodeUTF8));
        lblEnrollStatus2->setText(QString());
        lblEnrollStatus->setText(QApplication::translate("EnrollFP", "Enroll Status", 0, QApplication::UnicodeUTF8));
        lblFpArea->setText(QString());
        Q_UNUSED(EnrollFP);
    } // retranslateUi

};

namespace Ui {
    class EnrollFP: public Ui_EnrollFP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_FP_H
