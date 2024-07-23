#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QThreadPool>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMutex>

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void startServer();

private slots:
    void onNewConnection();
    void onClientDisconnected();
    void onReadyRead();

private:
    QTcpServer *server;
    QList<QTcpSocket *> clients;
    QThreadPool *threadPool;
    QJsonObject userDatabase;
    QJsonObject adminDatabase;
    QMutex mutex;
    QFile userLogFile;
    QFile adminLogFile;

    void loadDatabase(QJsonObject &database, const QString &fileName);
    void saveDatabase(const QJsonObject &database, const QString &fileName);
    QString handleRequest(const QString &message);
    QString processLogin(const QStringList &params);
    QString processGetAccountNumber(const QStringList &params);
    QString processViewBalance(const QStringList &params);
    QString processViewTransactionHistory(const QStringList &params);
    QString processMakeTransaction(const QStringList &params);
    QString processTransferAmount(const QStringList &params);
    QString processViewDatabase(const QStringList &params);
    QString processCreateUser(const QStringList &params);
    QString processDeleteUser(const QStringList &params);
    QString processUpdateUser(const QStringList &params);
    void logOperation(const QString &message, bool isAdmin);
    void logError(const QString &error);
};

#endif // SERVER_H
