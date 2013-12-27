/********************************************************************************
** Form generated from reading ui file 'main.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAIN_H
#define UI_MAIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWidget
{
public:
    QLabel *lblBackground;
    QLabel *lblClock;
    QLabel *lblstatUSB;
    QLabel *lblstatCard;
    QLabel *lblstatFingerprint;
    QLabel *lblstatUDisk;
    QLabel *lblstatWebserver;
    QLabel *lblStatbarFingerprint;
    QLabel *lblStatusbarText;
    QLabel *lblMonth;
    QLabel *lblWeekday;
    QLabel *lblTime;
    QLabel *lblMessageArea;
    QLabel *lblAMPM;
    QLabel *lblComText;
    QLabel *lblNet;

    void setupUi(QWidget *MainWidget)
    {
        if (MainWidget->objectName().isEmpty())
            MainWidget->setObjectName(QString::fromUtf8("MainWidget"));
        MainWidget->resize(320, 240);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        font.setPointSize(10);
        MainWidget->setFont(font);
        lblBackground = new QLabel(MainWidget);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblClock = new QLabel(MainWidget);
        lblClock->setObjectName(QString::fromUtf8("lblClock"));
        lblClock->setGeometry(QRect(27, 36, 112, 112));
        lblClock->setPixmap(QPixmap(QString::fromUtf8(":/images/res/clock.png")));
        lblClock->setScaledContents(false);
        lblstatUSB = new QLabel(MainWidget);
        lblstatUSB->setObjectName(QString::fromUtf8("lblstatUSB"));
        lblstatUSB->setEnabled(false);
        lblstatUSB->setGeometry(QRect(21, 120, 40, 40));
        lblstatUSB->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-usb.png")));
        lblstatCard = new QLabel(MainWidget);
        lblstatCard->setObjectName(QString::fromUtf8("lblstatCard"));
        lblstatCard->setEnabled(false);
        lblstatCard->setGeometry(QRect(80, 120, 40, 40));
        lblstatCard->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-card.png")));
        lblstatFingerprint = new QLabel(MainWidget);
        lblstatFingerprint->setObjectName(QString::fromUtf8("lblstatFingerprint"));
        lblstatFingerprint->setEnabled(false);
        lblstatFingerprint->setGeometry(QRect(139, 120, 40, 40));
        lblstatFingerprint->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-fingerprint.png")));
        lblstatUDisk = new QLabel(MainWidget);
        lblstatUDisk->setObjectName(QString::fromUtf8("lblstatUDisk"));
        lblstatUDisk->setEnabled(false);
        lblstatUDisk->setGeometry(QRect(198, 120, 40, 40));
        lblstatUDisk->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-udisk.png")));
        lblstatWebserver = new QLabel(MainWidget);
        lblstatWebserver->setObjectName(QString::fromUtf8("lblstatWebserver"));
        lblstatWebserver->setEnabled(false);
        lblstatWebserver->setGeometry(QRect(257, 120, 40, 40));
        lblstatWebserver->setPixmap(QPixmap(QString::fromUtf8(":/images/res/stat-webserver.png")));
        lblStatbarFingerprint = new QLabel(MainWidget);
        lblStatbarFingerprint->setObjectName(QString::fromUtf8("lblStatbarFingerprint"));
        lblStatbarFingerprint->setGeometry(QRect(159, 130, 32, 32));
        lblStatbarFingerprint->setPixmap(QPixmap(QString::fromUtf8(":/images/res/check-in.png")));
        lblStatusbarText = new QLabel(MainWidget);
        lblStatusbarText->setObjectName(QString::fromUtf8("lblStatusbarText"));
        lblStatusbarText->setGeometry(QRect(200, 130, 110, 32));
        QPalette palette;
        QBrush brush(QColor(204, 216, 62, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(106, 104, 100, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblStatusbarText->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\215\216\346\226\207\346\226\260\351\255\217"));
        font1.setPointSize(14);
        font1.setBold(true);
        font1.setWeight(75);
        font1.setKerning(false);
        lblStatusbarText->setFont(font1);
        lblStatusbarText->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lblMonth = new QLabel(MainWidget);
        lblMonth->setObjectName(QString::fromUtf8("lblMonth"));
        lblMonth->setGeometry(QRect(180, 190, 91, 31));
        lblMonth->setAlignment(Qt::AlignCenter);
        lblWeekday = new QLabel(MainWidget);
        lblWeekday->setObjectName(QString::fromUtf8("lblWeekday"));
        lblWeekday->setGeometry(QRect(190, 210, 71, 23));
        lblWeekday->setAlignment(Qt::AlignCenter);
        lblTime = new QLabel(MainWidget);
        lblTime->setObjectName(QString::fromUtf8("lblTime"));
        lblTime->setGeometry(QRect(20, 190, 130, 40));
        QPalette palette1;
        QBrush brush2(QColor(220, 222, 96, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblTime->setPalette(palette1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(32);
        font2.setBold(true);
        font2.setWeight(75);
        lblTime->setFont(font2);
        lblTime->setAlignment(Qt::AlignCenter);
        lblMessageArea = new QLabel(MainWidget);
        lblMessageArea->setObjectName(QString::fromUtf8("lblMessageArea"));
        lblMessageArea->setGeometry(QRect(10, 164, 300, 26));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Times New Roman"));
        font3.setPointSize(12);
        lblMessageArea->setFont(font3);
        lblAMPM = new QLabel(MainWidget);
        lblAMPM->setObjectName(QString::fromUtf8("lblAMPM"));
        lblAMPM->setGeometry(QRect(150, 190, 30, 31));
        QPalette palette2;
        QBrush brush3(QColor(208, 235, 69, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush3);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblAMPM->setPalette(palette2);
        lblAMPM->setAlignment(Qt::AlignCenter);
        lblComText = new QLabel(MainWidget);
        lblComText->setObjectName(QString::fromUtf8("lblComText"));
        lblComText->setGeometry(QRect(20, 130, 110, 32));
        lblComText->setAlignment(Qt::AlignCenter);
        lblNet = new QLabel(MainWidget);
        lblNet->setObjectName(QString::fromUtf8("lblNet"));
        lblNet->setGeometry(QRect(270, 200, 41, 31));
        lblNet->setPixmap(QPixmap(QString::fromUtf8(":/images/res/net-err.png")));
        lblNet->setScaledContents(true);
        lblNet->setAlignment(Qt::AlignCenter);

        retranslateUi(MainWidget);

        QMetaObject::connectSlotsByName(MainWidget);
    } // setupUi

    void retranslateUi(QWidget *MainWidget)
    {
        MainWidget->setWindowTitle(QApplication::translate("MainWidget", "Main Window", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblClock->setText(QString());
        lblstatUSB->setText(QString());
        lblstatCard->setText(QString());
        lblstatFingerprint->setText(QString());
        lblstatUDisk->setText(QString());
        lblstatWebserver->setText(QString());
        lblStatbarFingerprint->setText(QString());
        lblMessageArea->setText(QString());
        lblComText->setText(QString());
        lblNet->setText(QString());
        Q_UNUSED(MainWidget);
    } // retranslateUi

};

namespace Ui {
    class MainWidget: public Ui_MainWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_H
