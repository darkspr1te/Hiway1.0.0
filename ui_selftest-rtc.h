/********************************************************************************
** Form generated from reading ui file 'selftest-rtc.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELFTEST_2D_RTC_H
#define UI_SELFTEST_2D_RTC_H

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

class Ui_SelftestRtc
{
public:
    QLabel *lblBackground;
    QPushButton *btnESC;
    QLabel *lblInternal;
    QLabel *lblExternal;
    QLineEdit *txtInternalRTC;
    QLineEdit *txtExternalRTC;

    void setupUi(QDialog *SelftestRtc)
    {
        if (SelftestRtc->objectName().isEmpty())
            SelftestRtc->setObjectName(QString::fromUtf8("SelftestRtc"));
        SelftestRtc->resize(270, 120);
        lblBackground = new QLabel(SelftestRtc);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btnESC = new QPushButton(SelftestRtc);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(169, 80, 75, 24));
        lblInternal = new QLabel(SelftestRtc);
        lblInternal->setObjectName(QString::fromUtf8("lblInternal"));
        lblInternal->setGeometry(QRect(14, 20, 86, 16));
        lblExternal = new QLabel(SelftestRtc);
        lblExternal->setObjectName(QString::fromUtf8("lblExternal"));
        lblExternal->setGeometry(QRect(14, 52, 86, 16));
        txtInternalRTC = new QLineEdit(SelftestRtc);
        txtInternalRTC->setObjectName(QString::fromUtf8("txtInternalRTC"));
        txtInternalRTC->setGeometry(QRect(103, 19, 140, 20));
        txtInternalRTC->setFocusPolicy(Qt::NoFocus);
        txtExternalRTC = new QLineEdit(SelftestRtc);
        txtExternalRTC->setObjectName(QString::fromUtf8("txtExternalRTC"));
        txtExternalRTC->setGeometry(QRect(103, 49, 140, 20));
        txtExternalRTC->setFocusPolicy(Qt::NoFocus);

        retranslateUi(SelftestRtc);

        QMetaObject::connectSlotsByName(SelftestRtc);
    } // setupUi

    void retranslateUi(QDialog *SelftestRtc)
    {
        SelftestRtc->setWindowTitle(QApplication::translate("SelftestRtc", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btnESC->setText(QApplication::translate("SelftestRtc", "ESC", 0, QApplication::UnicodeUTF8));
        lblInternal->setText(QApplication::translate("SelftestRtc", "Internal RTC", 0, QApplication::UnicodeUTF8));
        lblExternal->setText(QApplication::translate("SelftestRtc", "External RTC", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SelftestRtc);
    } // retranslateUi

};

namespace Ui {
    class SelftestRtc: public Ui_SelftestRtc {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTEST_2D_RTC_H
