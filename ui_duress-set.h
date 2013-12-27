/********************************************************************************
** Form generated from reading ui file 'duress-set.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_DURESS_2D_SET_H
#define UI_DURESS_2D_SET_H

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

class Ui_DuressFP
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLineEdit *txtFpNumber;
    QPushButton *btnESC;
    QLabel *lblFpNumber;
    QLabel *lblFpArea;
    QLabel *lblEnrollStatus;

    void setupUi(QDialog *DuressFP)
    {
        if (DuressFP->objectName().isEmpty())
            DuressFP->setObjectName(QString::fromUtf8("DuressFP"));
        DuressFP->resize(320, 240);
        lblBackground = new QLabel(DuressFP);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblBackgroundFrame = new QLabel(DuressFP);
        lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
        lblBackgroundFrame->setGeometry(QRect(12, 10, 297, 217));
        lblBackgroundFrame->setScaledContents(true);
        lblTitleBackground = new QLabel(DuressFP);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(DuressFP);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(DuressFP);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(DuressFP);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(DuressFP);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        txtFpNumber = new QLineEdit(DuressFP);
        txtFpNumber->setObjectName(QString::fromUtf8("txtFpNumber"));
        txtFpNumber->setGeometry(QRect(210, 70, 71, 20));
        txtFpNumber->setReadOnly(true);
        btnESC = new QPushButton(DuressFP);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(239, 155, 50, 25));
        btnESC->setAutoDefault(false);
        lblFpNumber = new QLabel(DuressFP);
        lblFpNumber->setObjectName(QString::fromUtf8("lblFpNumber"));
        lblFpNumber->setGeometry(QRect(148, 70, 61, 21));
        lblFpArea = new QLabel(DuressFP);
        lblFpArea->setObjectName(QString::fromUtf8("lblFpArea"));
        lblFpArea->setGeometry(QRect(27, 59, 100, 100));
        lblFpArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/area-fingerprint.png")));
        lblFpArea->setScaledContents(true);
        lblEnrollStatus = new QLabel(DuressFP);
        lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
        lblEnrollStatus->setGeometry(QRect(45, 163, 160, 20));

        retranslateUi(DuressFP);

        QMetaObject::connectSlotsByName(DuressFP);
    } // setupUi

    void retranslateUi(QDialog *DuressFP)
    {
        DuressFP->setWindowTitle(QApplication::translate("DuressFP", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblBackgroundFrame->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("DuressFP", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("DuressFP", "EnrollFP Status", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("DuressFP", "ESC", 0, QApplication::UnicodeUTF8));
        lblFpNumber->setText(QApplication::translate("DuressFP", "FP Number :", 0, QApplication::UnicodeUTF8));
        lblFpArea->setText(QString());
        lblEnrollStatus->setText(QApplication::translate("DuressFP", "Enroll Status", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(DuressFP);
    } // retranslateUi

};

namespace Ui {
    class DuressFP: public Ui_DuressFP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DURESS_2D_SET_H
