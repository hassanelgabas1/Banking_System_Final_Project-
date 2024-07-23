#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H
#include <QMainWindow>
#include "client.h"
#include "mainwindow.h"
namespace Ui {
class LoginWindow;
}
class LoginWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();
private slots:
    void on_loginButton_clicked();
    void handleLoginResponse(const QString &response);
private:
    Ui::LoginWindow *ui;
    Client *client;
    MainWindow *mainWindow;
    QString userType;
};
#endif // LOGINWINDOW_H
