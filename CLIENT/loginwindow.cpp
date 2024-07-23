#include "loginwindow.h"
#include "ui_loginwindow.h"
#include <QMessageBox>
LoginWindow::LoginWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::LoginWindow), client(new Client(this)), mainWindow(nullptr)
{
    ui->setupUi(this);
    connect(client, &Client::responseReceived, this, &LoginWindow::handleLoginResponse);
}
LoginWindow::~LoginWindow()
{
    delete ui;
}
void LoginWindow::on_loginButton_clicked()
{
    QString user = ui->userLineEdit->text();
    QString pass = ui->passLineEdit->text();
    userType = ui->userTypeComboBox->currentText();
    client->sendLoginRequest(user, pass);
}
void LoginWindow::handleLoginResponse(const QString &response)
{
    qDebug() << "Login response received:" << response;
    QStringList responseParts = response.split(":");
    if (responseParts[0] == "true") {
        QString serverUserType = responseParts[1];
        if (userType.toLower() == serverUserType.toLower()) {
            QString username = ui->userLineEdit->text();
            mainWindow = new MainWindow(userType, client, username);
            mainWindow->show();
            this->hide();
        } else {
            QMessageBox::warning(this, "Login Failed", "You are not authorized to log in as " + userType);
        }
    } else if (responseParts[0] == "false") {
        QMessageBox::warning(this, "Login Failed", "Invalid credentials. Please try again.");
    } /*else {
        QMessageBox::warning(this, "Error", "An error occurred: " + response);
    }*/
}
