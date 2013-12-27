/********************************************************************************
** Form generated from reading ui file 'search-log.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SEARCH_2D_LOG_H
#define UI_SEARCH_2D_LOG_H

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

class Ui_LogSearch
{
public:
    QLabel *lblBackground;
    QLabel *lblTitleBackground;
    QLabel *lblTitleText;
    QLabel *lblTitleIcon;
    QLabel *lblStatusIcon;
    QLabel *lblStatusText;
    QPushButton *btnESC;
    QLabel *lblName;
    QLineEdit *txtTo;
    QLabel *lblStatus;
    QPushButton *btnOK;
    QLabel *lblID;
    QLabel *lblTo;
    QComboBox *comboDate;
    QLabel *lblDate;
    QLineEdit *txtFrom;
    QLabel *lblFrom;
    QLineEdit *txtName;
    QLineEdit *txtID;

    void setupUi(QDialog *LogSearch)
    {
        if (LogSearch->objectName().isEmpty())
            LogSearch->setObjectName(QString::fromUtf8("LogSearch"));
        LogSearch->resize(320, 240);
        lblBackground = new QLabel(LogSearch);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 320, 240));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-main.png")));
        lblTitleBackground = new QLabel(LogSearch);
        lblTitleBackground->setObjectName(QString::fromUtf8("lblTitleBackground"));
        lblTitleBackground->setGeometry(QRect(0, 6, 320, 30));
        lblTitleBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/title-1.png")));
        lblTitleText = new QLabel(LogSearch);
        lblTitleText->setObjectName(QString::fromUtf8("lblTitleText"));
        lblTitleText->setGeometry(QRect(40, 10, 273, 28));
        lblTitleIcon = new QLabel(LogSearch);
        lblTitleIcon->setObjectName(QString::fromUtf8("lblTitleIcon"));
        lblTitleIcon->setGeometry(QRect(9, 10, 26, 26));
        lblTitleIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/SEARCH_GLOG.png")));
        lblTitleIcon->setScaledContents(false);
        lblStatusIcon = new QLabel(LogSearch);
        lblStatusIcon->setObjectName(QString::fromUtf8("lblStatusIcon"));
        lblStatusIcon->setGeometry(QRect(20, 205, 16, 16));
        lblStatusIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/icon-help.png")));
        lblStatusText = new QLabel(LogSearch);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(40, 200, 270, 25));
        btnESC = new QPushButton(LogSearch);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(200, 162, 75, 24));
        lblName = new QLabel(LogSearch);
        lblName->setObjectName(QString::fromUtf8("lblName"));
        lblName->setGeometry(QRect(60, 120, 50, 21));
        txtTo = new QLineEdit(LogSearch);
        txtTo->setObjectName(QString::fromUtf8("txtTo"));
        txtTo->setEnabled(false);
        txtTo->setGeometry(QRect(70, 129, 91, 20));
        lblStatus = new QLabel(LogSearch);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(20, 47, 279, 21));
        lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        btnOK = new QPushButton(LogSearch);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(70, 162, 75, 24));
        lblID = new QLabel(LogSearch);
        lblID->setObjectName(QString::fromUtf8("lblID"));
        lblID->setGeometry(QRect(60, 90, 40, 21));
        lblTo = new QLabel(LogSearch);
        lblTo->setObjectName(QString::fromUtf8("lblTo"));
        lblTo->setGeometry(QRect(20, 129, 40, 21));
        comboDate = new QComboBox(LogSearch);
        comboDate->setObjectName(QString::fromUtf8("comboDate"));
        comboDate->setGeometry(QRect(70, 72, 231, 21));
        lblDate = new QLabel(LogSearch);
        lblDate->setObjectName(QString::fromUtf8("lblDate"));
        lblDate->setGeometry(QRect(20, 72, 40, 16));
        txtFrom = new QLineEdit(LogSearch);
        txtFrom->setObjectName(QString::fromUtf8("txtFrom"));
        txtFrom->setEnabled(false);
        txtFrom->setGeometry(QRect(70, 101, 91, 20));
        lblFrom = new QLabel(LogSearch);
        lblFrom->setObjectName(QString::fromUtf8("lblFrom"));
        lblFrom->setGeometry(QRect(20, 99, 40, 21));
        txtName = new QLineEdit(LogSearch);
        txtName->setObjectName(QString::fromUtf8("txtName"));
        txtName->setGeometry(QRect(113, 120, 131, 20));
        txtName->setMaxLength(8);
        txtName->setAlignment(Qt::AlignCenter);
        txtID = new QLineEdit(LogSearch);
        txtID->setObjectName(QString::fromUtf8("txtID"));
        txtID->setGeometry(QRect(113, 90, 131, 20));
        txtID->setMaxLength(9);
        txtID->setAlignment(Qt::AlignCenter);
        QWidget::setTabOrder(comboDate, txtFrom);
        QWidget::setTabOrder(txtFrom, txtTo);
        QWidget::setTabOrder(txtTo, txtID);
        QWidget::setTabOrder(txtID, txtName);
        QWidget::setTabOrder(txtName, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(LogSearch);

        QMetaObject::connectSlotsByName(LogSearch);
    } // setupUi

    void retranslateUi(QDialog *LogSearch)
    {
        LogSearch->setWindowTitle(QApplication::translate("LogSearch", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        lblTitleBackground->setText(QString());
        lblTitleText->setText(QApplication::translate("LogSearch", "Log Search", 0, QApplication::UnicodeUTF8));
        lblTitleIcon->setText(QString());
        lblStatusIcon->setText(QString());
        lblStatusText->setText(QApplication::translate("LogSearch", "Use Arrow & OK, ESC for return, OK for T9Input", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("LogSearch", "ESC", 0, QApplication::UnicodeUTF8));
        lblName->setText(QApplication::translate("LogSearch", "Name", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("LogSearch", "Press finger or input card", 0, QApplication::UnicodeUTF8));
        btnOK->setText(QApplication::translate("LogSearch", "Search", 0, QApplication::UnicodeUTF8));
        lblID->setText(QApplication::translate("LogSearch", "ID", 0, QApplication::UnicodeUTF8));
        lblTo->setText(QApplication::translate("LogSearch", "to", 0, QApplication::UnicodeUTF8));
        comboDate->clear();
        comboDate->insertItems(0, QStringList()
         << QApplication::translate("LogSearch", "All", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogSearch", "Last Week", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogSearch", "Past Month", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("LogSearch", "Specify Date", 0, QApplication::UnicodeUTF8)
        );
        lblDate->setText(QApplication::translate("LogSearch", "Date", 0, QApplication::UnicodeUTF8));
        lblFrom->setText(QApplication::translate("LogSearch", "from", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(LogSearch);
    } // retranslateUi

};

namespace Ui {
    class LogSearch: public Ui_LogSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCH_2D_LOG_H
