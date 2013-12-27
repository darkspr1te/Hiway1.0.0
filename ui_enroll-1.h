/********************************************************************************
** Form generated from reading ui file 'enroll-1.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_ENROLL_2D_1_H
#define UI_ENROLL_2D_1_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_EnrollStep1
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QComboBox *comboPart;
    QLabel *lblID;
    QComboBox *comboLevel;
    QLineEdit *txtID;
    QLineEdit *txtName;
    QPushButton *btnOK;
    QLabel *lblPart;
    QLabel *lblLevel;
    QLabel *lblName;
    QPushButton *btnESC;

    void setupUi(QDialog *EnrollStep1)
    {
        if (EnrollStep1->objectName().isEmpty())
            EnrollStep1->setObjectName(QString::fromUtf8("EnrollStep1"));
        EnrollStep1->resize(320, 240);
        lblBackground = new QLabel(EnrollStep1);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(EnrollStep1);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(EnrollStep1);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(58, 10, 240, 28));
        lblTitleIcon = new QLabel(EnrollStep1);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(20, 9, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-normal.png")));
        lblTitleIcon->setScaledContents(true);
        lblStatusIcon = new QLabel(EnrollStep1);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(EnrollStep1);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        comboPart = new QComboBox(EnrollStep1);
        comboPart->setObjectName(QString::fromUtf8("comboPart"));
        comboPart->setGeometry(QRect(130, 40, 181, 22));
        lblID = new QLabel(EnrollStep1);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(37, 50, 62, 20));
        comboLevel = new QComboBox(EnrollStep1);
        comboLevel->setObjectName(QString::fromUtf8("comboLevel"));
        comboLevel->setGeometry(QRect(100, 120, 181, 22));
        txtID = new QLineEdit(EnrollStep1);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(100, 50, 131, 22));
        txtID->setMaxLength(9);
        txtID->setAlignment(Qt::AlignCenter);
        txtName = new QLineEdit(EnrollStep1);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(100, 85, 131, 22));
        txtName->setMaxLength(8);
        txtName->setAlignment(Qt::AlignCenter);
        btnOK = new QPushButton(EnrollStep1);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 160, 71, 25));
        lblPart = new QLabel(EnrollStep1);
        lblPart->setObjectName(QString::fromUtf8("lblPart"));
        lblPart->setGeometry(QRect(240, 70, 62, 20));
        lblLevel = new QLabel(EnrollStep1);
        lblLevel->setObjectName(QString::fromUtf8("lblLevel"));
        lblLevel->setGeometry(QRect(37, 120, 62, 20));
        lblName = new QLabel(EnrollStep1);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(37, 85, 62, 20));
        btnESC = new QPushButton(EnrollStep1);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 160, 71, 25));
        QWidget::setTabOrder(txtID, txtName);
        QWidget::setTabOrder(txtName, comboLevel);
        QWidget::setTabOrder(comboLevel, comboPart);
        QWidget::setTabOrder(comboPart, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(EnrollStep1);

        comboLevel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(EnrollStep1);
    } // setupUi

    void retranslateUi(QDialog *EnrollStep1)
    {
        EnrollStep1->setWindowTitle(QApplication::translate("EnrollStep1", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("EnrollStep1", "Title", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("EnrollStep1", "OK:Select Or T9Input,  ESC:Back ", 0, QApplication::UnicodeUTF8));
        lblID->setText(QApplication::translate("EnrollStep1", "ID        ", 0, QApplication::UnicodeUTF8));
        comboLevel->clear();
        comboLevel->insertItems(0, QStringList()
         << QApplication::translate("EnrollStep1", "User", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EnrollStep1", "Manager", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("EnrollStep1", "SManager", 0, QApplication::UnicodeUTF8)
        );
        btnOK->setText(QApplication::translate("EnrollStep1", "OK", 0, QApplication::UnicodeUTF8));
        lblPart->setText(QApplication::translate("EnrollStep1", "Part      ", 0, QApplication::UnicodeUTF8));
        lblLevel->setText(QApplication::translate("EnrollStep1", "Level     ", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("EnrollStep1", "Name      ", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("EnrollStep1", "ESC", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(EnrollStep1);
    } // retranslateUi

};

namespace Ui {
    class EnrollStep1: public Ui_EnrollStep1 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENROLL_2D_1_H
