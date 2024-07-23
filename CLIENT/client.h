#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QTimer>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    void sendLoginRequest(const QString &username, const QString &password);
    void sendRequest(const QString &request);

signals:
    void responseReceived(const QString &response);
    void connectionStatusChanged(bool connected);

private slots:
    void onReadyRead();
    void onConnected();
    void onDisconnected();
    void onError(QAbstractSocket::SocketError socketError);
    void reconnect();
    void sendHeartbeat();

private:
    QTcpSocket *socket;
    QTimer *heartbeatTimer;
    QTimer *reconnectTimer;
    void startHeartbeat();
};

#endif // CLIENT_H
