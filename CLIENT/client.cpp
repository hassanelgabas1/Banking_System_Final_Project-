#include "client.h"
#include <QDebug>

Client::Client(QObject *parent) : QObject(parent), socket(new QTcpSocket(this)),
    heartbeatTimer(new QTimer(this)), reconnectTimer(new QTimer(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Client::onReadyRead);
    connect(socket, &QTcpSocket::connected, this, &Client::onConnected);
    connect(socket, &QTcpSocket::disconnected, this, &Client::onDisconnected);
    connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
            this, &Client::onError);
    connect(heartbeatTimer, &QTimer::timeout, this, &Client::sendHeartbeat);
    connect(reconnectTimer, &QTimer::timeout, this, &Client::reconnect);
    socket->connectToHost("127.0.0.1", 12345);
}

void Client::sendLoginRequest(const QString &username, const QString &password)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        QString request = QString("LOGIN:%1:%2").arg(username, password);
        qDebug() << "Sending login request:" << request;
        socket->write((request + "\n").toUtf8());
    } else {
        qDebug() << "Socket is not connected.";
        emit responseReceived("Connection error");
    }
}

void Client::sendRequest(const QString &request)
{
    if (socket->state() == QAbstractSocket::ConnectedState) {
        qDebug() << "Sending request:" << request;
        socket->write((request + "\n").toUtf8());
        socket->flush();
    } else {
        qDebug() << "Socket is not connected.";
        emit responseReceived("Connection error: Socket is not connected");
    }
}

void Client::onReadyRead()
{
    QString response;
    while (socket->canReadLine()) {
        QByteArray line = socket->readLine().trimmed();
        QString lineStr = QString::fromUtf8(line);
        qDebug() << "Received response:" << lineStr;
        if (lineStr != "HEARTBEAT_ACK") {
            response += lineStr;
        }
    }
    if (!response.isEmpty()) {
        emit responseReceived(response);
    }
}

void Client::onConnected()
{
    qDebug() << "Connected to server.";
    emit connectionStatusChanged(true);
    startHeartbeat();
    reconnectTimer->stop();
}

void Client::onDisconnected()
{
    qDebug() << "Disconnected from server.";
    emit connectionStatusChanged(false);
    emit responseReceived("Disconnected from server");
    heartbeatTimer->stop();
    reconnectTimer->start(5000);
}

void Client::onError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "Socket error:" << socketError << socket->errorString();
    emit responseReceived("Connection error: " + socket->errorString());
}

void Client::reconnect()
{
    qDebug() << "Attempting to reconnect...";
    if (socket->state() != QAbstractSocket::ConnectedState) {
        socket->abort();
        socket->connectToHost("127.0.0.1", 12345);
    }
}

void Client::startHeartbeat()
{
    heartbeatTimer->start(5000);
}

void Client::sendHeartbeat()
{
    sendRequest("HEARTBEAT");
}
