/********************************************************************************
** Form generated from reading ui file 'selftest-memory.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_SELFTEST_2D_MEMORY_H
#define UI_SELFTEST_2D_MEMORY_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_SelftestMemory
{
public:
    QLabel *lblBackground;
    QPushButton *btnESC;
    QProgressBar *progressBar;
    QLabel *lblStatus;

    void setupUi(QDialog *SelftestMemory)
    {
        if (SelftestMemory->objectName().isEmpty())
            SelftestMemory->setObjectName(QString::fromUtf8("SelftestMemory"));
        SelftestMemory->resize(270, 120);
        lblBackground = new QLabel(SelftestMemory);
        lblBackground->setObjectName(QString::fromUtf8("lblBackground"));
        lblBackground->setGeometry(QRect(0, 0, 270, 120));
        lblBackground->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bg-inputbox.png")));
        lblBackground->setScaledContents(true);
        btnESC = new QPushButton(SelftestMemory);
        btnESC->setObjectName(QString::fromUtf8("btnESC"));
        btnESC->setGeometry(QRect(180, 80, 75, 24));
        progressBar = new QProgressBar(SelftestMemory);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setGeometry(QRect(21, 50, 234, 16));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        lblStatus = new QLabel(SelftestMemory);
        lblStatus->setObjectName(QString::fromUtf8("lblStatus"));
        lblStatus->setGeometry(QRect(20, 20, 220, 21));

        retranslateUi(SelftestMemory);

        QMetaObject::connectSlotsByName(SelftestMemory);
    } // setupUi

    void retranslateUi(QDialog *SelftestMemory)
    {
        SelftestMemory->setWindowTitle(QApplication::translate("SelftestMemory", "Dialog", 0, QApplication::UnicodeUTF8));
        lblBackground->setText(QString());
        btnESC->setText(QApplication::translate("SelftestMemory", "ESC", 0, QApplication::UnicodeUTF8));
        lblStatus->setText(QApplication::translate("SelftestMemory", "Memory testing...", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(SelftestMemory);
    } // retranslateUi

};

namespace Ui {
    class SelftestMemory: public Ui_SelftestMemory {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SELFTEST_2D_MEMORY_H
