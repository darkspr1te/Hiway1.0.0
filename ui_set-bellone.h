/********************************************************************************
** Form generated from reading ui file 'set-bellone.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SET_2D_BELLONE_H
#define UI_SET_2D_BELLONE_H

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

class Ui_BellSetOne
{
public:
    QLabel *lblBackground;
    QPushButton *btnOK;
    QPushButton *btnESC;
    QLabel *lblBellTime;
    QLabel *lblBellLength;
    QLabel *lblBellType;
    QLineEdit *txtBellTime;
    QLineEdit *txtBellLength;
    QComboBox *comboBellType;

    void setupUi(QDialog *BellSetOne)
    {
        if (BellSetOne->objectName().isEmpty())
            BellSetOne->setObjectName(QString::fromUtf8("BellSetOne"));
        BellSetOne->resize(270, 120);
        lblBackground = new QLabel(BellSetOne);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btnOK = new QPushButton(BellSetOne);
        btnOK->setObjectName(QString::fromUtf8("btnOK"));
        btnOK->setGeometry(QRect(40, 80, 75, 24));
        btnESC = new QPushButton(BellSetOne);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(160, 80, 75, 24));
        lblBellTime = new QLabel(BellSetOne);
        lblBellTime->setObjectName(QString::fromUtf8("lblBellTime"));
        lblBellTime->setGeometry(QRect(54, 30, 70, 14));
        lblBellLength = new QLabel(BellSetOne);
        lblBellLength->setObjectName(QString::fromUtf8("lblBellLength"));
        lblBellLength->setGeometry(QRect(54, 53, 70, 16));
        lblBellType = new QLabel(BellSetOne);
        lblBellType->setObjectName(QString::fromUtf8("lblBellType"));
        lblBellType->setGeometry(QRect(90, 0, 70, 14));
        txtBellTime = new QLineEdit(BellSetOne);
        txtBellTime->setObjectName(QString::fromUtf8("txtBellTime"));
        txtBellTime->setGeometry(QRect(124, 24, 91, 20));
        txtBellLength = new QLineEdit(BellSetOne);
        txtBellLength->setObjectName(QString::fromUtf8("txtBellLength"));
        txtBellLength->setGeometry(QRect(124, 50, 91, 20));
        txtBellLength->setMaxLength(3);
        comboBellType = new QComboBox(BellSetOne);
        comboBellType->setObjectName(QString::fromUtf8("comboBellType"));
        comboBellType->setGeometry(QRect(160, 0, 90, 22));
        QWidget::setTabOrder(txtBellTime, txtBellLength);
        QWidget::setTabOrder(txtBellLength, comboBellType);
        QWidget::setTabOrder(comboBellType, btnOK);
        QWidget::setTabOrder(btnOK, btnESC);

        retranslateUi(BellSetOne);

        QMetaObject::connectSlotsByName(BellSetOne);
    } // setupUi

    void retranslateUi(QDialog *BellSetOne)
    {
        BellSetOne->setWindowTitle(QApplication::translate("BellSetOne", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btnOK->setText(QApplication::translate("BellSetOne", "OK", 0, QApplication::UnicodeUTF8));
        btnESC->setText(QApplication::translate("BellSetOne", "ESC", 0, QApplication::UnicodeUTF8));
        lblBellTime->setText(QApplication::translate("BellSetOne", "BellTime", 0, QApplication::UnicodeUTF8));
        lblBellLength->setText(QApplication::translate("BellSetOne", "Length(s)", 0, QApplication::UnicodeUTF8));
        lblBellType->setText(QApplication::translate("BellSetOne", "BellType", 0, QApplication::UnicodeUTF8));
        txtBellTime->setInputMask(QString());
        txtBellLength->setText(QApplication::translate("BellSetOne", "0", 0, QApplication::UnicodeUTF8));
        comboBellType->clear();
        comboBellType->insertItems(0, QStringList()
         << QApplication::translate("BellSetOne", "BellType-1", 0, QApplication::UnicodeUTF8)
        );
        Q_UNUSED(BellSetOne);
    } // retranslateUi

};

namespace Ui {
    class BellSetOne: public Ui_BellSetOne {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SET_2D_BELLONE_H
