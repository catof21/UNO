/********************************************************************************
** Form generated from reading UI file 'startdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_STARTDIALOG_H
#define UI_STARTDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_startDialog
{
public:
    QPushButton *pushButton;
    QWidget *widget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *serverAddr;
    QLabel *label_2;
    QLineEdit *portNumber;
    QLabel *label_3;
    QLineEdit *username;

    void setupUi(QDialog *startDialog)
    {
        if (startDialog->objectName().isEmpty())
            startDialog->setObjectName(QStringLiteral("startDialog"));
        startDialog->resize(329, 201);
        pushButton = new QPushButton(startDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(140, 150, 75, 23));
        widget = new QWidget(startDialog);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(25, 33, 261, 91));
        formLayout = new QFormLayout(widget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        serverAddr = new QLineEdit(widget);
        serverAddr->setObjectName(QStringLiteral("serverAddr"));

        formLayout->setWidget(0, QFormLayout::FieldRole, serverAddr);

        label_2 = new QLabel(widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        portNumber = new QLineEdit(widget);
        portNumber->setObjectName(QStringLiteral("portNumber"));

        formLayout->setWidget(1, QFormLayout::FieldRole, portNumber);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        username = new QLineEdit(widget);
        username->setObjectName(QStringLiteral("username"));

        formLayout->setWidget(2, QFormLayout::FieldRole, username);


        retranslateUi(startDialog);

        QMetaObject::connectSlotsByName(startDialog);
    } // setupUi

    void retranslateUi(QDialog *startDialog)
    {
        startDialog->setWindowTitle(QApplication::translate("startDialog", "Dialog", 0));
        pushButton->setText(QApplication::translate("startDialog", "Connect", 0));
        label->setText(QApplication::translate("startDialog", "Server:", 0));
        label_2->setText(QApplication::translate("startDialog", "Port:", 0));
        label_3->setText(QApplication::translate("startDialog", "Username:", 0));
    } // retranslateUi

};

namespace Ui {
    class startDialog: public Ui_startDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_STARTDIALOG_H
