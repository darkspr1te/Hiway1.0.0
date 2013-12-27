/********************************************************************************
** Form generated from reading ui file 'enroll-voice.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_VOICE_H
#define UI_ENROLL_2D_VOICE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EnrollVoice
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *label;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblEnrollStatus;
    QLabel *lblFilename;
    QPushButton *btnESC;
    QPushButton *btnOK;
    QLabel *lblRecoredStat1;
    QLabel *lblRecoredStat2;
    QLabel *lblLeftSecond;

    void setupUi(QDialog *EnrollVoice)
    {
        if (EnrollVoice->objectName().isEmpty())
            EnrollVoice->setObjectName(QString::fromUtf8("EnrollVoice"));
        EnrollVoice->resize(320, 240);
        lblBackground = new QLabel(EnrollVoice);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblBackgroundFrame = new QLabel(EnrollVoice);
        lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
        lblBackgroundFrame->setGeometry(QRect(12, 10, 297, 217));
        lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-mask2.png")));
        lblTitleBackground = new QLabel(EnrollVoice);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 4, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        label = new QLabel(EnrollVoice);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 176, 320, 63));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        lblTitleText = new QLabel(EnrollVoice);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(EnrollVoice);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 6, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-voice.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollVoice);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(13, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollVoice);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(32, 200, 280, 25));
        lblEnrollStatus = new QLabel(EnrollVoice);
        lblEnrollStatus->setObjectName(QString::fromUtf8("lblEnrollStatus"));
        lblEnrollStatus->setGeometry(QRect(30, 60, 191, 21));
        lblEnrollStatus->setFocusPolicy(Qt::StrongFocus);
        lblFilename = new QLabel(EnrollVoice);
        lblFilename->setObjectName(QString::fromUtf8("lblFilename"));
        lblFilename->setGeometry(QRect(41, 102, 111, 21));
        btnESC = new QPushButton(EnrollVoice);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 150, 75, 24));
        btnOK = new QPushButton(EnrollVoice);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 150, 75, 24));
        lblRecoredStat1 = new QLabel(EnrollVoice);
        lblRecoredStat1->setObjectName(QString::fromUtf8("lblRecoredStat1"));
        lblRecoredStat1->setGeometry(QRect(160, 100, 26, 26));
        lblRecoredStat1->setPixmap(QPixmap(QString::fromUtf8(":/images/res/voice-play.png")));
        lblRecoredStat2 = new QLabel(EnrollVoice);
        lblRecoredStat2->setObjectName(QString::fromUtf8("lblRecoredStat2"));
        lblRecoredStat2->setGeometry(QRect(200, 100, 26, 26));
        lblRecoredStat2->setPixmap(QPixmap(QString::fromUtf8(":/images/res/voice-flow1.png")));
        lblLeftSecond = new QLabel(EnrollVoice);
        lblLeftSecond->setObjectName(QString::fromUtf8("lblLeftSecond"));
        lblLeftSecond->setGeometry(QRect(240, 102, 46, 20));

        retranslateUi(EnrollVoice);

        QMetaObject::connectSlotsByName(EnrollVoice);
    } // setupUi

    void retranslateUi(QDialog *EnrollVoice)
    {
        EnrollVoice->setWindowTitle(QApplication::translate("EnrollVoice", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblBackgroundFrame->setText(QString());
        lblTitleBackground->setText(QString());
        label->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollVoice", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollVoice", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
        lblEnrollStatus->setText(QApplication::translate("EnrollVoice", "Speak you name", 0, QApplication::UnicodeUTF8));
        lblFilename->setText(QApplication::translate("EnrollVoice", "voice file name", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("EnrollVoice", "ESC", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("EnrollVoice", "OK", 0, QApplication::UnicodeUTF8));
        lblRecoredStat1->setText(QString());
        lblRecoredStat2->setText(QString());
        lblLeftSecond->setText(QString());
        Q_UNUSED(EnrollVoice);
    } // retranslateUi

};

namespace Ui {
    class EnrollVoice: public Ui_EnrollVoice {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_VOICE_H
