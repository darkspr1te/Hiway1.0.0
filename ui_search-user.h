/********************************************************************************
** Form generated from reading ui file 'search-user.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SEARCH_2D_USER_H
#define UI_SEARCH_2D_USER_H

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

class Ui_UserSearch
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
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusText;
    QLabel *lblStatusIcon;

    void setupUi(QDialog *UserSearch)
    {
        if (UserSearch->objectName().isEmpty())
            UserSearch->setObjectName(QString::fromUtf8("UserSearch"));
        UserSearch->resize(320, 240);
        lblBackground = new QLabel(UserSearch);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(20, 51, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        lblIcon = new QLabel(UserSearch);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setGeometry(QRect(30, 84, 40, 40));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/DATAVIEW.png")));
        lblIcon->setScaledContents(true);
        lblID = new QLabel(UserSearch);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(80, 83, 61, 21));
        txtID = new QLineEdit(UserSearch);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(150, 83, 113, 20));
        txtID->setMaxLength(9);
        lblStatus = new QLabel(UserSearch);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(40, 60, 221, 21));
        lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnOK = new QPushButton(UserSearch);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 140, 75, 24));
        btnESC = new QPushButton(UserSearch);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 140, 75, 24));
        lblName = new QLabel(UserSearch);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(80, 110, 61, 21));
        txtName = new QLineEdit(UserSearch);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(150, 110, 113, 20));
        txtName->setMaxLength(8);
        lblStatusbar = new QLabel(UserSearch);
        lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
        lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
        label = new QLabel(UserSearch);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 200, 320, 40));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        label->setScaledContents(true);
        lblStatusText = new QLabel(UserSearch);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        lblStatusIcon = new QLabel(UserSearch);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        QWidget::setTabOrder(txtID, txtName);
        QWidget::setTabOrder(txtName, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(UserSearch);

        QMetaObject::connectSlotsByName(UserSearch);
    } // setupUi

    void retranslateUi(QDialog *UserSearch)
    {
        UserSearch->setWindowTitle(QApplication::translate("UserSearch", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblIcon->setText(QString());
        lblID->setText(QApplication::translate("UserSearch", "User ID", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("UserSearch", "Press finger or input card", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("UserSearch", "OK", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("UserSearch", "ESC", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("UserSearch", "Name", 0, QApplication::UnicodeUTF8));
        lblStatusbar->setText(QString());
        label->setText(QString());
        lblStatusText->setText(QApplication::translate("UserSearch", "OK: Search Or T9Input, ESC: Return ", 0, QApplication::UnicodeUTF8));
        lblStatusIcon->setText(QString());
        Q_UNUSED(UserSearch);
    } // retranslateUi

};

namespace Ui {
    class UserSearch: public Ui_UserSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_2D_USER_H
