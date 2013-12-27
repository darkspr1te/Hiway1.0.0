/********************************************************************************
** Form generated from reading ui file 't9-input.ui'
**
** Created: Fri Dec 27 15:06:07 2013
**      by: Qt User Interface Compiler version 4.5.0
**
** WARNING! All changes made in this file will be lost when recompiling ui file!
********************************************************************************/

#ifndef UI_T9_2D_INPUT_H
#define UI_T9_2D_INPUT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>

QT_BEGIN_NAMESPACE

class Ui_T9InputDlg
{
public:
    QLabel *lblStatusbar;
    QLabel *label;
    QLabel *lblStatusText;
    QLabel *lblIcon;

    void setupUi(QDialog *T9InputDlg)
    {
        if (T9InputDlg->objectName().isEmpty())
            T9InputDlg->setObjectName(QString::fromUtf8("T9InputDlg"));
        T9InputDlg->resize(320, 240);
        QFont font;
        font.setFamily(QString::fromUtf8("Tahoma"));
        T9InputDlg->setFont(font);
        lblStatusbar = new QLabel(T9InputDlg);
        lblStatusbar->setObjectName(QString::fromUtf8("lblStatusbar"));
        lblStatusbar->setGeometry(QRect(0, 200, 320, 40));
        label = new QLabel(T9InputDlg);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 200, 320, 40));
        label->setPixmap(QPixmap(QString::fromUtf8(":/images/res/bottom.png")));
        label->setScaledContents(true);
        lblStatusText = new QLabel(T9InputDlg);
        lblStatusText->setObjectName(QString::fromUtf8("lblStatusText"));
        lblStatusText->setGeometry(QRect(39, 191, 261, 41));
        lblIcon = new QLabel(T9InputDlg);
        lblIcon->setObjectName(QString::fromUtf8("lblIcon"));
        lblIcon->setEnabled(true);
        lblIcon->setGeometry(QRect(11, 201, 24, 24));
        lblIcon->setPixmap(QPixmap(QString::fromUtf8(":/images/res/t9-input.png")));

        retranslateUi(T9InputDlg);

        QMetaObject::connectSlotsByName(T9InputDlg);
    } // setupUi

    void retranslateUi(QDialog *T9InputDlg)
    {
        T9InputDlg->setWindowTitle(QApplication::translate("T9InputDlg", "Title", 0, QApplication::UnicodeUTF8));
        lblStatusbar->setText(QString());
        label->setText(QString());
        lblIcon->setText(QString());
        Q_UNUSED(T9InputDlg);
    } // retranslateUi

};

namespace Ui {
    class T9InputDlg: public Ui_T9InputDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_T9_2D_INPUT_H
