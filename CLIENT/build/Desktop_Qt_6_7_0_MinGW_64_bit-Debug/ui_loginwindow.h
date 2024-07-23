/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QLineEdit *userLineEdit;
    QLineEdit *passLineEdit;
    QComboBox *userTypeComboBox;
    QPushButton *loginButton;

    void setupUi(QMainWindow *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(400, 300);
        centralWidget = new QWidget(LoginWindow);
        centralWidget->setObjectName("centralWidget");
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setObjectName("verticalLayout");
        userLineEdit = new QLineEdit(centralWidget);
        userLineEdit->setObjectName("userLineEdit");

        verticalLayout->addWidget(userLineEdit);

        passLineEdit = new QLineEdit(centralWidget);
        passLineEdit->setObjectName("passLineEdit");
        passLineEdit->setEchoMode(QLineEdit::Password);

        verticalLayout->addWidget(passLineEdit);

        userTypeComboBox = new QComboBox(centralWidget);
        userTypeComboBox->addItem(QString());
        userTypeComboBox->addItem(QString());
        userTypeComboBox->setObjectName("userTypeComboBox");

        verticalLayout->addWidget(userTypeComboBox);

        loginButton = new QPushButton(centralWidget);
        loginButton->setObjectName("loginButton");

        verticalLayout->addWidget(loginButton);

        LoginWindow->setCentralWidget(centralWidget);

        retranslateUi(LoginWindow);

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QMainWindow *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Login", nullptr));
        userLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Username", nullptr));
        passLineEdit->setPlaceholderText(QCoreApplication::translate("LoginWindow", "Password", nullptr));
        userTypeComboBox->setItemText(0, QCoreApplication::translate("LoginWindow", "User", nullptr));
        userTypeComboBox->setItemText(1, QCoreApplication::translate("LoginWindow", "Admin", nullptr));

        loginButton->setText(QCoreApplication::translate("LoginWindow", "Log In", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
