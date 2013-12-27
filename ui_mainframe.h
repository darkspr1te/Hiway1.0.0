/********************************************************************************
** Form generated from reading ui file 'mainframe.ui'
**
** Created: Fri Dec 27 16:45:58 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QLabel *lblBackground;
    QLabel *lblBackgroundFrame;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QLabel *lblTitleText1;

    void setupUi(QDialog *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(320, 240);
        lblBackground = new QLabel(MainFrame);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblBackgroundFrame = new QLabel(MainFrame);
        lblBackgroundFrame->setObjectName(QString::fromUtf8("lblBackgroundFrame"));
        lblBackgroundFrame->setGeometry(QRect(12, 10, 297, 217));
        lblBackgroundFrame->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-menu.png")));
        lblBackgroundFrame->setScaledContents(false);
        lblTitleBackground = new QLabel(MainFrame);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(MainFrame);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 8, 273, 28));
        lblTitleIcon = new QLabel(MainFrame);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(MainFrame);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 215, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(MainFrame);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 210, 275, 25));
        lblTitleText1 = new QLabel(MainFrame);
        lblTitleText1->setObjectName(QString::fromUtf8("lblTitleText1"));
        lblTitleText1->setGeometry(QRect(201, 10, 110, 28));

        retranslateUi(MainFrame);

        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
        MainFrame->setWindowTitle(QApplication::translate("MainFrame", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblBackgroundFrame->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("MainFrame", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("MainFrame", "Use Arrow & OK, ESC for return", 0, QApplication::UnicodeUTF8));
        lblTitleText1->setText(QString());
        Q_UNUSED(MainFrame);
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
