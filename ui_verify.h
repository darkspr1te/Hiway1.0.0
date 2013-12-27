/********************************************************************************
** Form generated from reading ui file 'verify.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_VERIFY_H
#define UI_VERIFY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_Verify
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblDate;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblLineTop;
    QLabel *lblLineBottom;
    QLabel *lblTrStatus;
    QLabel *lblFpArea;
    QLabel *lblID;
    QLabel *lblPriv;
    QLabel *lblName;
    QLabel *lblPart;

    void setupUi(QDialog *Verify)
    {
        if (Verify->objectName().isEmpty())
            Verify->setObjectName(QString::fromUtf8("Verify"));
        Verify->resize(320, 240);
        lblBackground = new QLabel(Verify);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(Verify);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 4, 320, 34));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblDate = new QLabel(Verify);
        lblDate->setObjectName(QString::fromUtf8("lblDate"));
        lblDate->setGeometry(QRect(58, 10, 171, 28));
        lblTitleIcon = new QLabel(Verify);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-finger.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(Verify);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(Verify);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblLineTop = new QLabel(Verify);
        lblLineTop->setObjectName(QString::fromUtf8("lblLineTop"));
        lblLineTop->setGeometry(QRect(25, 48, 280, 2));
        lblLineTop->setPixmap(QPixmap(QString::fromUtf8(":/Menu/res/line.png")));
        lblLineBottom = new QLabel(Verify);
        lblLineBottom->setObjectName(QString::fromUtf8("lblLineBottom"));
        lblLineBottom->setGeometry(QRect(25, 188, 280, 2));
        lblLineBottom->setPixmap(QPixmap(QString::fromUtf8(":/Menu/res/line.png")));
        lblTrStatus = new QLabel(Verify);
        lblTrStatus->setObjectName(QString::fromUtf8("lblTrStatus"));
        lblTrStatus->setGeometry(QRect(240, 10, 61, 28));
        lblFpArea = new QLabel(Verify);
        lblFpArea->setObjectName(QString::fromUtf8("lblFpArea"));
        lblFpArea->setGeometry(QRect(175, 56, 120, 130));
        lblFpArea->setPixmap(QPixmap(QString::fromUtf8(":/images/res/area-fingerprint.png")));
        lblFpArea->setScaledContents(false);
        lblID = new QLabel(Verify);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(30, 70, 120, 20));
        lblPriv = new QLabel(Verify);
        lblPriv->setObjectName(QString::fromUtf8("lblPriv"));
        lblPriv->setGeometry(QRect(30, 130, 120, 20));
        lblName = new QLabel(Verify);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(30, 100, 200, 20));
        lblPart = new QLabel(Verify);
        lblPart->setObjectName(QString::fromUtf8("lblPart"));
        lblPart->setGeometry(QRect(30, 170, 120, 20));

        retranslateUi(Verify);

        QMetaObject::connectSlotsByName(Verify);
    } // setupUi

    void retranslateUi(QDialog *Verify)
    {
        Verify->setWindowTitle(QApplication::translate("Verify", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblDate->setText(QApplication::translate("Verify", "DateTime", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("Verify", "Help", 0, QApplication::UnicodeUTF8));
        lblLineTop->setText(QString());
        lblLineBottom->setText(QString());
        lblTrStatus->setText(QApplication::translate("Verify", "TRStatus", 0, QApplication::UnicodeUTF8));
        lblFpArea->setText(QString());
        lblID->setText(QApplication::translate("Verify", "ID:", 0, QApplication::UnicodeUTF8));
        lblPriv->setText(QApplication::translate("Verify", "Priv:", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("Verify", "Name:", 0, QApplication::UnicodeUTF8));
        lblPart->setText(QApplication::translate("Verify", "Part:", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(Verify);
    } // retranslateUi

};

namespace Ui {
    class Verify: public Ui_Verify {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VERIFY_H
