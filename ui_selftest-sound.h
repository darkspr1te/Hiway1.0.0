/********************************************************************************
** Form generated from reading ui file 'selftest-sound.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELFTEST_2D_SOUND_H
#define UI_SELFTEST_2D_SOUND_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelftestSound
{
public:
    QLabel *lblBackground;
    QPushButton *btnPlay;
    QPushButton *btnESC;
    QComboBox *comboBox;
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;

    void setupUi(QDialog *SelftestSound)
    {
        if (SelftestSound->objectName().isEmpty())
            SelftestSound->setObjectName(QString::fromUtf8("SelftestSound"));
        SelftestSound->resize(320, 240);
        lblBackground = new QLabel(SelftestSound);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(20, 50, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btnPlay = new QPushButton(SelftestSound);
        btnPlay->setObjectName(QString::fromUtf8("btnPlay"));
        btnPlay->setGeometry(QRect(50, 130, 75, 24));
        btnPlay->setFocusPolicy(Qt::NoFocus);
        btnESC = new QPushButton(SelftestSound);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(190, 130, 75, 24));
        btnESC->setFocusPolicy(Qt::NoFocus);
        comboBox = new QComboBox(SelftestSound);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(70, 80, 180, 22));
        lblStatusbar = new QLabel(SelftestSound);
        lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
        lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
        label = new QLabel(SelftestSound);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 200, 320, 40));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        label->setScaledContents(true);
        lblStatusIcon = new QLabel(SelftestSound);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(SelftestSound);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        QWidget::setTabOrder(btnPlay, btnESC);

        retranslateUi(SelftestSound);

        QMetaObject::connectSlotsByName(SelftestSound);
    } // setupUi

    void retranslateUi(QDialog *SelftestSound)
    {
        SelftestSound->setWindowTitle(QApplication::translate("SelftestSound", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btnPlay->setText(QApplication::translate("SelftestSound", "Play", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("SelftestSound", "ESC", 0, QApplication::UnicodeUTF8));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("SelftestSound", "Channel 1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SelftestSound", "Channel 2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SelftestSound", "Channel 3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SelftestSound", "Channel 4", 0, QApplication::UnicodeUTF8)
        );
        lblStatusbar->setText(QString());
        label->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("SelftestSound", "OK: Play  ESC: Return", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SelftestSound);
    } // retranslateUi

};

namespace Ui {
    class SelftestSound: public Ui_SelftestSound {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTEST_2D_SOUND_H
