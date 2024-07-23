#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
MainWindow::MainWindow(const QString &userType, Client *client, const QString &username, QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), client(client), userType(userType), loggedInUsername(username)
{
    ui->setupUi(this);
    setupUIForUserType();
    connect(client, &Client::responseReceived, this, &MainWindow::handleResponse);
    connect(client, &Client::connectionStatusChanged, this, &MainWindow::updateConnectionStatus);
    ui->statusBar->showMessage("Logged in as: " + loggedInUsername);
    connect(ui->userRequestTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onUserRequestTypeChanged);
    connect(ui->adminRequestTypeComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged),
            this, &MainWindow::onAdminRequestTypeChanged);
    connect(ui->userSendRequestButton, &QPushButton::clicked, this, &MainWindow::onUserSendRequestClicked);
    connect(ui->adminSendRequestButton, &QPushButton::clicked, this, &MainWindow::onAdminSendRequestClicked);
}
MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::setupUIForUserType()
{
    if (userType == "User") {
        ui->tabWidget->removeTab(1); // Remove admin tab
    } else if (userType == "Admin") {
        ui->tabWidget->removeTab(0); // Remove user tab
    }
}
void MainWindow::onUserRequestTypeChanged(int index)
{
    QString requestType = ui->userRequestTypeComboBox->currentText();
    if (requestType == "Get Account Number" || requestType == "View Balance") {
        ui->userStackedWidget->setCurrentIndex(0); // Show an empty page
    } else if (requestType == "Make Transaction") {
        ui->userStackedWidget->setCurrentIndex(1); // Show amount input
    } else if (requestType == "Transfer Amount") {
        ui->userStackedWidget->setCurrentIndex(2); // Show transfer inputs
    } else if (requestType == "View Transaction History") {
        ui->userStackedWidget->setCurrentIndex(3); // Show transaction count input
    }
}
void MainWindow::onAdminRequestTypeChanged(int index)
{
    ui->adminStackedWidget->setCurrentIndex(index);
}
void MainWindow::onUserSendRequestClicked()
{
    QString requestType = ui->userRequestTypeComboBox->currentText();
    QString request;

    if (requestType == "Get Account Number") {
        request = "GET_ACCOUNT_NUMBER:" + loggedInUsername;
    } else if (requestType == "View Balance") {
        request = "VIEW_BALANCE:" + loggedInUsername;
    } else if (requestType == "View Transaction History") {
        int count = ui->transactionCountSpinBox->value();
        request = "VIEW_TRANSACTION_HISTORY:" + loggedInUsername + ":" + QString::number(count);
    } else if (requestType == "Make Transaction") {
        QString amount = ui->amountLineEdit->text();
        if (amount.isEmpty() || currentAccountNumber.isEmpty()) {
            ui->responseTextEdit->setPlainText("Error: Amount and account number are required for Make Transaction");
            return;
        }
        request = "MAKE_TRANSACTION:" + currentAccountNumber + ":" + amount;
    } else if (requestType == "Transfer Amount") {
        QString toAccount = ui->toAccountLineEdit->text();
        QString amount = ui->transferAmountLineEdit->text();
        if (toAccount.isEmpty() || amount.isEmpty() || currentAccountNumber.isEmpty()) {
            ui->responseTextEdit->setPlainText("Error: From account, to account, and amount are required for Transfer Amount");
            return;
        }
        request = "TRANSFER_AMOUNT:" + currentAccountNumber + ":" + toAccount + ":" + amount;
    }

    if (!request.isEmpty()) {
        client->sendRequest(request);
    }
}
void MainWindow::onAdminSendRequestClicked()
{
    QString requestType = ui->adminRequestTypeComboBox->currentText();
    QString request;
    if (requestType == "View Database") {
        request = "VIEW_DATABASE:" + userType;
    } else if (requestType == "Create User") {
        QString newUsername = ui->newUsernameLineEdit->text();
        QString newPassword = ui->newPasswordLineEdit->text();
        QString accountNumber = ui->accountNumberLineEdit->text();
        QString initialBalance = ui->initialBalanceLineEdit->text();
        if (newUsername.isEmpty() || newPassword.isEmpty() || accountNumber.isEmpty() || initialBalance.isEmpty()) {
            ui->responseTextEdit->setPlainText("Error: All fields are required for Create User");
            return;
        }
        request = "CREATE_USER:" + userType + ":" + newUsername + ":" + newPassword + ":" + accountNumber + ":" + initialBalance;
    } else if (requestType == "Delete User") {
        QString deleteUsername = ui->deleteUsernameLineEdit->text();
        if (deleteUsername.isEmpty()) {
            ui->responseTextEdit->setPlainText("Error: Username is required for Delete User");
            return;
        }
        request = "DELETE_USER:" + userType + ":" + deleteUsername;
    } else if (requestType == "Update User") {
        QString updateUsername = ui->updateUsernameLineEdit->text();
        QString newPassword = ui->updatePasswordLineEdit->text();
        QString newBalance = ui->updateBalanceLineEdit->text();
        if (updateUsername.isEmpty() || newPassword.isEmpty() || newBalance.isEmpty()) {
            ui->responseTextEdit->setPlainText("Error: All fields are required for Update User");
            return;
        }
        request = "UPDATE_USER:" + userType + ":" + updateUsername + ":" + newPassword + ":" + newBalance;
    }
    if (!request.isEmpty()) {
        client->sendRequest(request);
    }
}
void MainWindow::handleResponse(const QString &response)
{
    qDebug() << "Response received in MainWindow:" << response;
    QStringList responseParts = response.split(":");
    QString responseType = responseParts.first();

    if (responseType == "GET_ACCOUNT_NUMBER") {
        onGetAccountNumberResponse(response);
    } else if (responseType == "VIEW_BALANCE") {
        if (responseParts.size() > 1) {
            ui->responseTextEdit->setPlainText("Your current balance is: $" + responseParts[1]);
        } else {
            ui->responseTextEdit->setPlainText("Unable to retrieve balance.");
        }
    } else if (responseType == "VIEW_TRANSACTION_HISTORY") {
        if (responseParts.size() > 1) {
            QString transactionHistory = responseParts.mid(1).join(":");
            ui->responseTextEdit->setPlainText("Transaction History:\n" + transactionHistory);
        } else {
            ui->responseTextEdit->setPlainText("No transaction history available.");
        }
    } else if (responseType == "MAKE_TRANSACTION") {
        onMakeTransactionResponse(response);
    } else if (responseType == "TRANSFER_AMOUNT") {
        onTransferAmountResponse(response);
    } else if (responseType == "ERROR") {
        ui->responseTextEdit->setPlainText("Error: " + responseParts.mid(1).join(":"));
    } else {
        ui->responseTextEdit->setPlainText("Response: " + response);
    }
}
void MainWindow::updateConnectionStatus(bool connected)
{
    if (connected) {
        ui->statusBar->showMessage("Connected to server | Logged in as: " + loggedInUsername);
    } else {
        ui->statusBar->showMessage("Disconnected from server | Logged in as: " + loggedInUsername);
    }
}
void MainWindow::onGetAccountNumberResponse(const QString &response)
{
    QStringList responseParts = response.split(":");
    if (responseParts.size() > 1) {
        currentAccountNumber = responseParts[1];
        ui->responseTextEdit->setPlainText("Your account number is: " + currentAccountNumber);
    } else {
        ui->responseTextEdit->setPlainText("Unable to retrieve account number.");
    }
}
void MainWindow::onMakeTransactionResponse(const QString &response)
{
    QStringList responseParts = response.split(":");
    if (responseParts.size() > 1) {
        if (responseParts[1] == "true") {
            ui->responseTextEdit->setPlainText("Transaction successful");
        } else {
            ui->responseTextEdit->setPlainText("Transaction failed: " + responseParts.mid(2).join(":"));
        }
    } else {
        ui->responseTextEdit->setPlainText("Invalid response for Make Transaction");
    }
}

void MainWindow::onTransferAmountResponse(const QString &response)
{
    QStringList responseParts = response.split(":");
    if (responseParts.size() > 1) {
        if (responseParts[1] == "true") {
            ui->responseTextEdit->setPlainText("Transfer successful");
        } else {
            ui->responseTextEdit->setPlainText("Transfer failed: " + responseParts.mid(2).join(":"));
        }
    } else {
        ui->responseTextEdit->setPlainText("Invalid response for Transfer Amount");
    }
}

