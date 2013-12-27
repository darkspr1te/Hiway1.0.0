/********************************************************************************
** Form generated from reading ui file 'selftest-sensor.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELFTEST_2D_SENSOR_H
#define UI_SELFTEST_2D_SENSOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelftestSensor
{
public:
    QLabel *lblBackground;
    QPushButton *btnESC;
    QLabel *lblFpArea;
    QLabel *lblStatus;

    void setupUi(QDialog *SelftestSensor)
    {
        if (SelftestSensor->objectName().isEmpty())
            SelftestSensor->setObjectName(QString::fromUtf8("SelftestSensor"));
        SelftestSensor->resize(270, 120);
        lblBackground = new QLabel(SelftestSensor);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btnESC = new QPushButton(SelftestSensor);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 90, 75, 24));
        lblFpArea = new QLabel(SelftestSensor);
        lblFpArea->setObjectName(QString::fromUtf8("lblFpArea"));
        lblFpArea->setGeometry(QRect(20, 10, 100, 100));
        lblFpArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/area-fingerprint.png")));
        lblFpArea->setScaledContents(true);
        lblStatus = new QLabel(SelftestSensor);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(156, 40, 110, 21));

        retranslateUi(SelftestSensor);

        QMetaObject::connectSlotsByName(SelftestSensor);
    } // setupUi

    void retranslateUi(QDialog *SelftestSensor)
    {
        SelftestSensor->setWindowTitle(QApplication::translate("SelftestSensor", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btnESC->setText(QApplication::translate("SelftestSensor", "ESC", 0, QApplication::UnicodeUTF8));
        lblFpArea->setText(QString());
        lblStatus->setText(QApplication::translate("SelftestSensor", "Press finger", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SelftestSensor);
    } // retranslateUi

};

namespace Ui {
    class SelftestSensor: public Ui_SelftestSensor {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTEST_2D_SENSOR_H
