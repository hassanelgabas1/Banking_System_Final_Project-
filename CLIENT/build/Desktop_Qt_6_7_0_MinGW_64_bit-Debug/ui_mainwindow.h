/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *userTab;
    QVBoxLayout *verticalLayout_2;
    QComboBox *userRequestTypeComboBox;
    QStackedWidget *userStackedWidget;
    QWidget *emptyPage;
    QWidget *makeTransactionPage;
    QFormLayout *formLayout;
    QLabel *label_2;
    QLineEdit *amountLineEdit;
    QWidget *transferPage;
    QFormLayout *formLayout_2;
    QLabel *label;
    QLineEdit *toAccountLineEdit;
    QLabel *label_3;
    QLineEdit *transferAmountLineEdit;
    QWidget *transactionHistoryPage;
    QFormLayout *formLayout_3;
    QLabel *label_4;
    QSpinBox *transactionCountSpinBox;
    QPushButton *userSendRequestButton;
    QWidget *adminTab;
    QVBoxLayout *verticalLayout_3;
    QComboBox *adminRequestTypeComboBox;
    QStackedWidget *adminStackedWidget;
    QWidget *viewDatabasePage;
    QWidget *createUserPage;
    QFormLayout *formLayout_31;
    QLabel *label_41;
    QLineEdit *newUsernameLineEdit;
    QLabel *label_5;
    QLineEdit *newPasswordLineEdit;
    QLabel *label_6;
    QLineEdit *accountNumberLineEdit;
    QLabel *label_7;
    QLineEdit *initialBalanceLineEdit;
    QWidget *deleteUserPage;
    QFormLayout *formLayout_4;
    QLabel *label_8;
    QLineEdit *deleteUsernameLineEdit;
    QWidget *updateUserPage;
    QFormLayout *formLayout_5;
    QLabel *label_9;
    QLineEdit *updateUsernameLineEdit;
    QLabel *label_10;
    QLineEdit *updatePasswordLineEdit;
    QLabel *label_11;
    QLineEdit *updateBalanceLineEdit;
    QPushButton *adminSendRequestButton;
    QTextEdit *responseTextEdit;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setObjectName("horizontalLayout");
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName("tabWidget");
        userTab = new QWidget();
        userTab->setObjectName("userTab");
        verticalLayout_2 = new QVBoxLayout(userTab);
        verticalLayout_2->setObjectName("verticalLayout_2");
        userRequestTypeComboBox = new QComboBox(userTab);
        userRequestTypeComboBox->addItem(QString());
        userRequestTypeComboBox->addItem(QString());
        userRequestTypeComboBox->addItem(QString());
        userRequestTypeComboBox->addItem(QString());
        userRequestTypeComboBox->addItem(QString());
        userRequestTypeComboBox->setObjectName("userRequestTypeComboBox");

        verticalLayout_2->addWidget(userRequestTypeComboBox);

        userStackedWidget = new QStackedWidget(userTab);
        userStackedWidget->setObjectName("userStackedWidget");
        emptyPage = new QWidget();
        emptyPage->setObjectName("emptyPage");
        userStackedWidget->addWidget(emptyPage);
        makeTransactionPage = new QWidget();
        makeTransactionPage->setObjectName("makeTransactionPage");
        formLayout = new QFormLayout(makeTransactionPage);
        formLayout->setObjectName("formLayout");
        label_2 = new QLabel(makeTransactionPage);
        label_2->setObjectName("label_2");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        amountLineEdit = new QLineEdit(makeTransactionPage);
        amountLineEdit->setObjectName("amountLineEdit");

        formLayout->setWidget(0, QFormLayout::FieldRole, amountLineEdit);

        userStackedWidget->addWidget(makeTransactionPage);
        transferPage = new QWidget();
        transferPage->setObjectName("transferPage");
        formLayout_2 = new QFormLayout(transferPage);
        formLayout_2->setObjectName("formLayout_2");
        label = new QLabel(transferPage);
        label->setObjectName("label");

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label);

        toAccountLineEdit = new QLineEdit(transferPage);
        toAccountLineEdit->setObjectName("toAccountLineEdit");

        formLayout_2->setWidget(0, QFormLayout::FieldRole, toAccountLineEdit);

        label_3 = new QLabel(transferPage);
        label_3->setObjectName("label_3");

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_3);

        transferAmountLineEdit = new QLineEdit(transferPage);
        transferAmountLineEdit->setObjectName("transferAmountLineEdit");

        formLayout_2->setWidget(1, QFormLayout::FieldRole, transferAmountLineEdit);

        userStackedWidget->addWidget(transferPage);
        transactionHistoryPage = new QWidget();
        transactionHistoryPage->setObjectName("transactionHistoryPage");
        formLayout_3 = new QFormLayout(transactionHistoryPage);
        formLayout_3->setObjectName("formLayout_3");
        label_4 = new QLabel(transactionHistoryPage);
        label_4->setObjectName("label_4");

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_4);

        transactionCountSpinBox = new QSpinBox(transactionHistoryPage);
        transactionCountSpinBox->setObjectName("transactionCountSpinBox");

        formLayout_3->setWidget(0, QFormLayout::FieldRole, transactionCountSpinBox);

        userStackedWidget->addWidget(transactionHistoryPage);

        verticalLayout_2->addWidget(userStackedWidget);

        userSendRequestButton = new QPushButton(userTab);
        userSendRequestButton->setObjectName("userSendRequestButton");

        verticalLayout_2->addWidget(userSendRequestButton);

        tabWidget->addTab(userTab, QString());
        adminTab = new QWidget();
        adminTab->setObjectName("adminTab");
        verticalLayout_3 = new QVBoxLayout(adminTab);
        verticalLayout_3->setObjectName("verticalLayout_3");
        adminRequestTypeComboBox = new QComboBox(adminTab);
        adminRequestTypeComboBox->addItem(QString());
        adminRequestTypeComboBox->addItem(QString());
        adminRequestTypeComboBox->addItem(QString());
        adminRequestTypeComboBox->addItem(QString());
        adminRequestTypeComboBox->setObjectName("adminRequestTypeComboBox");

        verticalLayout_3->addWidget(adminRequestTypeComboBox);

        adminStackedWidget = new QStackedWidget(adminTab);
        adminStackedWidget->setObjectName("adminStackedWidget");
        viewDatabasePage = new QWidget();
        viewDatabasePage->setObjectName("viewDatabasePage");
        adminStackedWidget->addWidget(viewDatabasePage);
        createUserPage = new QWidget();
        createUserPage->setObjectName("createUserPage");
        formLayout_31 = new QFormLayout(createUserPage);
        formLayout_31->setObjectName("formLayout_31");
        label_41 = new QLabel(createUserPage);
        label_41->setObjectName("label_41");

        formLayout_31->setWidget(0, QFormLayout::LabelRole, label_41);

        newUsernameLineEdit = new QLineEdit(createUserPage);
        newUsernameLineEdit->setObjectName("newUsernameLineEdit");

        formLayout_31->setWidget(0, QFormLayout::FieldRole, newUsernameLineEdit);

        label_5 = new QLabel(createUserPage);
        label_5->setObjectName("label_5");

        formLayout_31->setWidget(1, QFormLayout::LabelRole, label_5);

        newPasswordLineEdit = new QLineEdit(createUserPage);
        newPasswordLineEdit->setObjectName("newPasswordLineEdit");

        formLayout_31->setWidget(1, QFormLayout::FieldRole, newPasswordLineEdit);

        label_6 = new QLabel(createUserPage);
        label_6->setObjectName("label_6");

        formLayout_31->setWidget(2, QFormLayout::LabelRole, label_6);

        accountNumberLineEdit = new QLineEdit(createUserPage);
        accountNumberLineEdit->setObjectName("accountNumberLineEdit");

        formLayout_31->setWidget(2, QFormLayout::FieldRole, accountNumberLineEdit);

        label_7 = new QLabel(createUserPage);
        label_7->setObjectName("label_7");

        formLayout_31->setWidget(3, QFormLayout::LabelRole, label_7);

        initialBalanceLineEdit = new QLineEdit(createUserPage);
        initialBalanceLineEdit->setObjectName("initialBalanceLineEdit");

        formLayout_31->setWidget(3, QFormLayout::FieldRole, initialBalanceLineEdit);

        adminStackedWidget->addWidget(createUserPage);
        deleteUserPage = new QWidget();
        deleteUserPage->setObjectName("deleteUserPage");
        formLayout_4 = new QFormLayout(deleteUserPage);
        formLayout_4->setObjectName("formLayout_4");
        label_8 = new QLabel(deleteUserPage);
        label_8->setObjectName("label_8");

        formLayout_4->setWidget(0, QFormLayout::LabelRole, label_8);

        deleteUsernameLineEdit = new QLineEdit(deleteUserPage);
        deleteUsernameLineEdit->setObjectName("deleteUsernameLineEdit");

        formLayout_4->setWidget(0, QFormLayout::FieldRole, deleteUsernameLineEdit);

        adminStackedWidget->addWidget(deleteUserPage);
        updateUserPage = new QWidget();
        updateUserPage->setObjectName("updateUserPage");
        formLayout_5 = new QFormLayout(updateUserPage);
        formLayout_5->setObjectName("formLayout_5");
        label_9 = new QLabel(updateUserPage);
        label_9->setObjectName("label_9");

        formLayout_5->setWidget(0, QFormLayout::LabelRole, label_9);

        updateUsernameLineEdit = new QLineEdit(updateUserPage);
        updateUsernameLineEdit->setObjectName("updateUsernameLineEdit");

        formLayout_5->setWidget(0, QFormLayout::FieldRole, updateUsernameLineEdit);

        label_10 = new QLabel(updateUserPage);
        label_10->setObjectName("label_10");

        formLayout_5->setWidget(1, QFormLayout::LabelRole, label_10);

        updatePasswordLineEdit = new QLineEdit(updateUserPage);
        updatePasswordLineEdit->setObjectName("updatePasswordLineEdit");

        formLayout_5->setWidget(1, QFormLayout::FieldRole, updatePasswordLineEdit);

        label_11 = new QLabel(updateUserPage);
        label_11->setObjectName("label_11");

        formLayout_5->setWidget(2, QFormLayout::LabelRole, label_11);

        updateBalanceLineEdit = new QLineEdit(updateUserPage);
        updateBalanceLineEdit->setObjectName("updateBalanceLineEdit");

        formLayout_5->setWidget(2, QFormLayout::FieldRole, updateBalanceLineEdit);

        adminStackedWidget->addWidget(updateUserPage);

        verticalLayout_3->addWidget(adminStackedWidget);

        adminSendRequestButton = new QPushButton(adminTab);
        adminSendRequestButton->setObjectName("adminSendRequestButton");

        verticalLayout_3->addWidget(adminSendRequestButton);

        tabWidget->addTab(adminTab, QString());

        horizontalLayout->addWidget(tabWidget);

        responseTextEdit = new QTextEdit(centralWidget);
        responseTextEdit->setObjectName("responseTextEdit");
        responseTextEdit->setReadOnly(true);

        horizontalLayout->addWidget(responseTextEdit);

        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Banking System", nullptr));
        userRequestTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Get Account Number", nullptr));
        userRequestTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "View Balance", nullptr));
        userRequestTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "View Transaction History", nullptr));
        userRequestTypeComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Make Transaction", nullptr));
        userRequestTypeComboBox->setItemText(4, QCoreApplication::translate("MainWindow", "Transfer Amount", nullptr));

        label_2->setText(QCoreApplication::translate("MainWindow", "Amount:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "To Account Number:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Transfer Amount:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Number of Transactions:", nullptr));
        userSendRequestButton->setText(QCoreApplication::translate("MainWindow", "Send Request", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(userTab), QCoreApplication::translate("MainWindow", "User Operations", nullptr));
        adminRequestTypeComboBox->setItemText(0, QCoreApplication::translate("MainWindow", "View Database", nullptr));
        adminRequestTypeComboBox->setItemText(1, QCoreApplication::translate("MainWindow", "Create User", nullptr));
        adminRequestTypeComboBox->setItemText(2, QCoreApplication::translate("MainWindow", "Delete User", nullptr));
        adminRequestTypeComboBox->setItemText(3, QCoreApplication::translate("MainWindow", "Update User", nullptr));

        label_41->setText(QCoreApplication::translate("MainWindow", "Username:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Password:", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Account Number:", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Initial Balance:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Username to Delete:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Username to Update:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "New Password:", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "New Balance:", nullptr));
        adminSendRequestButton->setText(QCoreApplication::translate("MainWindow", "Send Admin Request", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(adminTab), QCoreApplication::translate("MainWindow", "Admin Operations", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
