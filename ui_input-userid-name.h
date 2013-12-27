/********************************************************************************
** Form generated from reading ui file 'input-userid-name.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_INPUT_2D_USERID_2D_NAME_H
#define UI_INPUT_2D_USERID_2D_NAME_H

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

class Ui_InputUserIDName
{
public:
    QLabel *lblBackground;
    QLabel *lblIcon;
    QLabel *lblID;
    QLineEdit *txtID;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLabel *lblName;
    QLineEdit *txtName;
    QLabel *lblPrivilege;
    QComboBox *comboLevel;
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusText;
    QLabel *lblStatusIcon;

    void setupUi(QDialog *InputUserIDName)
    {
        if (InputUserIDName->objectName().isEmpty())
            InputUserIDName->setObjectName(QString::fromUtf8("InputUserIDName"));
        InputUserIDName->resize(320, 240);
        lblBackground = new QLabel(InputUserIDName);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(20, 50, 270, 141));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        lblIcon = new QLabel(InputUserIDName);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setGeometry(QRect(30, 70, 40, 40));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/input-userid.png")));
        lblIcon->setScaledContents(true);
        lblID = new QLabel(InputUserIDName);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(80, 62, 61, 21));
        txtID = new QLineEdit(InputUserIDName);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(150, 62, 127, 20));
        txtID->setMaxLength(9);
        lblStatus = new QLabel(InputUserIDName);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(55, 137, 221, 21));
        lblStatus->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        btnOK = new QPushButton(InputUserIDName);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 160, 75, 24));
        btnESC = new QPushButton(InputUserIDName);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 160, 75, 24));
        lblName = new QLabel(InputUserIDName);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(80, 86, 61, 21));
        txtName = new QLineEdit(InputUserIDName);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(150, 86, 127, 20));
        txtName->setMaxLength(8);
        lblPrivilege = new QLabel(InputUserIDName);
        lblPrivilege->setObjectName(QString::fromUtf8("lblPrivilege"));
        lblPrivilege->setGeometry(QRect(80, 110, 61, 21));
        comboLevel = new QComboBox(InputUserIDName);
        comboLevel->setObjectName(QString::fromUtf8("comboLevel"));
        comboLevel->setGeometry(QRect(150, 110, 127, 22));
        lblStatusbar = new QLabel(InputUserIDName);
        lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
        lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
        label = new QLabel(InputUserIDName);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 200, 320, 40));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        label->setScaledContents(true);
        lblStatusText = new QLabel(InputUserIDName);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblStatusIcon = new QLabel(InputUserIDName);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        QWidget::setTabOrder(txtID, txtName);
        QWidget::setTabOrder(txtName, comboLevel);
        QWidget::setTabOrder(comboLevel, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(InputUserIDName);

        comboLevel->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(InputUserIDName);
    } // setupUi

    void retranslateUi(QDialog *InputUserIDName)
    {
        InputUserIDName->setWindowTitle(QApplication::translate("InputUserIDName", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblIcon->setText(QString());
        lblID->setText(QApplication::translate("InputUserIDName", "User ID", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("InputUserIDName", "Please input user ID and name", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("InputUserIDName", "OK", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("InputUserIDName", "ESC", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("InputUserIDName", "Name", 0, QApplication::UnicodeUTF8));
        lblPrivilege->setText(QApplication::translate("InputUserIDName", "Privilege", 0, QApplication::UnicodeUTF8));
        comboLevel->clear();
        comboLevel->insertItems(0, QStringList()
         << QApplication::translate("InputUserIDName", "User", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InputUserIDName", "Manager", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("InputUserIDName", "SManager", 0, QApplication::UnicodeUTF8)
        );
        lblStatusbar->setText(QString());
        label->setText(QString());
        lblStatusText->setText(QApplication::translate("InputUserIDName", "OK: Select Or T9Input ,  ESC: Return ", 0, QApplication::UnicodeUTF8));
        lblStatusIcon->setText(QString());
        Q_UNUSED(InputUserIDName);
    } // retranslateUi

};

namespace Ui {
    class InputUserIDName: public Ui_InputUserIDName {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUT_2D_USERID_2D_NAME_H
