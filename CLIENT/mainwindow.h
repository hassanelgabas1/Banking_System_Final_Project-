#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "client.h"
namespace Ui {
class MainWindow;
}
class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(const QString &userType, Client *client, const QString &username, QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void handleResponse(const QString &response);
    void updateConnectionStatus(bool connected);
    void onUserRequestTypeChanged(int index);
    void onAdminRequestTypeChanged(int index);
    void onUserSendRequestClicked();
    void onAdminSendRequestClicked();
    void onGetAccountNumberResponse(const QString &response);
    void onMakeTransactionResponse(const QString &response);
    void onTransferAmountResponse(const QString &response);
private:
    Ui::MainWindow *ui;
    Client *client;
    QString userType;
    QString loggedInUsername;
    void setupUIForUserType();
    QString currentAccountNumber;

};
#endif // MAINWINDOW_H
