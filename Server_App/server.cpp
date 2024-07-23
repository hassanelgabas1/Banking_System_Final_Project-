#include "server.h"
#include <QThreadPool>
#include <QThread>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QFile>
#include <QMutexLocker>
#include <QDateTime>
#include <QDir>

Server::Server(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    threadPool = new QThreadPool(this);

    // Set up the database file paths
    QString userDbPath = QDir::currentPath() + "/user_database.json";
    QString adminDbPath = QDir::currentPath() + "/admin_database.json";

    // Load databases
    loadDatabase(userDatabase, userDbPath);
    loadDatabase(adminDatabase, adminDbPath);

    // Set up log file paths
    userLogFile.setFileName(QDir::currentPath() + "/user_log.txt");
    adminLogFile.setFileName(QDir::currentPath() + "/admin_log.txt");

    // Ensure log files exist
    if (!userLogFile.exists()) {
        userLogFile.open(QIODevice::WriteOnly);
        userLogFile.close();
    }
    if (!adminLogFile.exists()) {
        adminLogFile.open(QIODevice::WriteOnly);
        adminLogFile.close();
    }

    qDebug() << "Server initialized. Working directory:" << QDir::currentPath();
    qDebug() << "User database path:" << userDbPath;
    qDebug() << "Admin database path:" << adminDbPath;
    qDebug() << "User log file path:" << userLogFile.fileName();
    qDebug() << "Admin log file path:" << adminLogFile.fileName();
}

void Server::startServer()
{
    connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    if (!server->listen(QHostAddress::Any, 12345)) {
        qCritical() << "Unable to start server";
    } else {
        qDebug() << "Server started on port 12345";
    }
}

void Server::onNewConnection()
{
    QTcpSocket *clientSocket = server->nextPendingConnection();
    clients << clientSocket;
    connect(clientSocket, &QTcpSocket::disconnected, this, &Server::onClientDisconnected);
    connect(clientSocket, &QTcpSocket::readyRead, this, &Server::onReadyRead);
    qDebug() << "Client connected";
}

void Server::onClientDisconnected()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    clients.removeOne(clientSocket);
    clientSocket->deleteLater();
    qDebug() << "Client disconnected";
}

void Server::onReadyRead()
{
    QTcpSocket *clientSocket = qobject_cast<QTcpSocket *>(sender());
    while (clientSocket->canReadLine()) {
        QByteArray line = clientSocket->readLine().trimmed();
        QString message = QString::fromUtf8(line);
        qDebug() << "Received message:" << message;
        QString response = handleRequest(message);
        clientSocket->write((response + "\n").toUtf8());
        clientSocket->flush();
    }
}

void Server::loadDatabase(QJsonObject &database, const QString &fileName)
{
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray data = file.readAll();
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isNull()) {
            qWarning() << "Failed to parse JSON from file:" << fileName;
        } else {
            database = doc.object();
            qDebug() << "Successfully loaded database from:" << fileName;
        }
        file.close();
    } else {
        qWarning() << "Failed to open database file:" << fileName << "Error:" << file.errorString();
    }
    qDebug() << "Database contents:" << database;
}

void Server::saveDatabase(const QJsonObject &database, const QString &fileName)
{
    if (database.isEmpty()) {
        qWarning() << "Attempt to save empty database prevented:" << fileName;
        return;
    }
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QJsonDocument doc(database);
        qint64 bytesWritten = file.write(doc.toJson());
        if (bytesWritten == -1) {
            qWarning() << "Failed to write to database file:" << fileName << "Error:" << file.errorString();
        } else {
            qDebug() << "Successfully saved database to:" << fileName << "Bytes written:" << bytesWritten;
        }
        file.close();
    } else {
        qWarning() << "Failed to open database file for writing:" << fileName << "Error:" << file.errorString();
    }
}
QString Server::handleRequest(const QString &message)
{
    try {
        QStringList params = message.split(":");
        QString requestType = params.takeFirst();
        if (requestType == "LOGIN") {
            return processLogin(params);
        } else if (requestType == "GET_ACCOUNT_NUMBER") {
            return processGetAccountNumber(params);
        } else if (requestType == "VIEW_BALANCE") {
            return processViewBalance(params);
        } else if (requestType == "VIEW_TRANSACTION_HISTORY") {
            return processViewTransactionHistory(params);
        } else if (requestType == "MAKE_TRANSACTION") {
            return processMakeTransaction(params);
        } else if (requestType == "TRANSFER_AMOUNT") {
            return processTransferAmount(params);
        } else if (requestType == "VIEW_DATABASE") {
            return processViewDatabase(params);
        } else if (requestType == "CREATE_USER") {
            return processCreateUser(params);
        } else if (requestType == "DELETE_USER") {
            return processDeleteUser(params);
        } else if (requestType == "UPDATE_USER") {
            return processUpdateUser(params);
        } else if (requestType == "HEARTBEAT") {
            return "HEARTBEAT_ACK";
        } else {
            throw std::runtime_error("Unknown request type");
        }
    } catch (const std::exception &e) {
        logError(QString("Error processing request: %1").arg(e.what()));
        return "ERROR:" + QString(e.what());
    }
}

QString Server::processLogin(const QStringList &params)
{
    if (params.size() < 2) {
        return "ERROR:Missing parameters";
    }

    QString user = params.at(0);
    QString pass = params.at(1);
    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    QJsonArray admins = adminDatabase["users"].toArray();
    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == user && obj["password"].toString() == pass) {
            logOperation("User logged in: " + user, false);
            return "true:User";
        }
    }
    for (const QJsonValue &value : admins) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == user && obj["password"].toString() == pass) {
            logOperation("Admin logged in: " + user, true);
            return "true:Admin";
        }
    }
    return "false";
}

QString Server::processGetAccountNumber(const QStringList &params)
{
    if (params.isEmpty()) {
        return "ERROR:Missing username";
    }

    QString user = params.at(0);
    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == user) {
            return obj["account_number"].toString();
        }
    }
    return "ERROR:User not found";
}

QString Server::processViewBalance(const QStringList &params)
{
    if (params.isEmpty()) {
        return "ERROR:Missing username";
    }
    QString user = params.at(0);
    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == user) {
            return QString::number(obj["balance"].toInt());
        }
    }
    return "ERROR:User not found";
}

QString Server::processViewTransactionHistory(const QStringList &params)
{
    if (params.size() < 2) {
        return "ERROR:Missing parameters";
    }
    QString user = params.at(0);
    int count = params.at(1).toInt();
    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    QString accountNumber;
    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == user) {
            accountNumber = obj["account_number"].toString();
            break;
        }
    }
    if (accountNumber.isEmpty()) {
        return "ERROR:User not found";
    }
    QJsonArray transactions = userDatabase["transactions"].toArray();
    QJsonArray result;
    for (const QJsonValue &value : transactions) {
        QJsonObject obj = value.toObject();
        if (obj["account_number"].toString() == accountNumber) {
            result.append(obj);
        }
        if (result.size() == count) {
            break;
        }
    }
    QJsonDocument doc(result);
    return QString::fromUtf8(doc.toJson());
}

QString Server::processMakeTransaction(const QStringList &params)
{
    if (params.size() < 2) {
        return "ERROR:Invalid parameters";
    }

    QString accountNumber = params[0];
    int amount = params[1].toInt();

    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    for (int i = 0; i < users.size(); ++i) {
        QJsonObject user = users[i].toObject();
        if (user["account_number"].toString() == accountNumber) {
            int currentBalance = user["balance"].toInt();
            int newBalance = currentBalance + amount;

            if (newBalance < 0) {
                return "false:Insufficient funds";
            }

            user["balance"] = newBalance;
            users[i] = user;
            userDatabase["users"] = users;
            saveDatabase(userDatabase, "user_database.json");

            // Log the transaction
            QJsonObject transaction;
            transaction["account_number"] = accountNumber;
            transaction["amount"] = amount;
            transaction["date"] = QDateTime::currentDateTime().toString(Qt::ISODate);
            QJsonArray transactions = userDatabase["transactions"].toArray();
            transactions.append(transaction);
            userDatabase["transactions"] = transactions;
            saveDatabase(userDatabase, "user_database.json");

            return "true:Transaction successful";
        }
    }
    return "ERROR:Account not found";
}

QString Server::processTransferAmount(const QStringList &params)
{
    if (params.size() < 3) {
        return "ERROR:Invalid parameters";
    }

    QString fromAccount = params[0];
    QString toAccount = params[1];
    int amount = params[2].toInt();

    if (amount <= 0) {
        return "ERROR:Transfer amount must be positive";
    }

    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    QJsonObject fromUser, toUser;
    int fromIndex = -1, toIndex = -1;

    for (int i = 0; i < users.size(); ++i) {
        QJsonObject user = users[i].toObject();
        if (user["account_number"].toString() == fromAccount) {
            fromUser = user;
            fromIndex = i;
        }
        if (user["account_number"].toString() == toAccount) {
            toUser = user;
            toIndex = i;
        }
    }

    if (fromIndex == -1 || toIndex == -1) {
        return "ERROR:One or both accounts not found";
    }

    int fromBalance = fromUser["balance"].toInt();
    int toBalance = toUser["balance"].toInt();

    if (fromBalance < amount) {
        return "false:Insufficient funds";
    }

    fromUser["balance"] = fromBalance - amount;
    toUser["balance"] = toBalance + amount;

    users[fromIndex] = fromUser;
    users[toIndex] = toUser;
    userDatabase["users"] = users;

    // Log the transactions
    QJsonObject fromTransaction, toTransaction;
    fromTransaction["account_number"] = fromAccount;
    fromTransaction["amount"] = -amount;
    fromTransaction["date"] = QDateTime::currentDateTime().toString(Qt::ISODate);
    toTransaction["account_number"] = toAccount;
    toTransaction["amount"] = amount;
    toTransaction["date"] = QDateTime::currentDateTime().toString(Qt::ISODate);

    QJsonArray transactions = userDatabase["transactions"].toArray();
    transactions.append(fromTransaction);
    transactions.append(toTransaction);
    userDatabase["transactions"] = transactions;

    saveDatabase(userDatabase, "user_database.json");

    return "true:Transfer successful";
}

QString Server::processViewDatabase(const QStringList &params)
{
    bool isAdmin = params.at(0).toLower() == "admin";
    if (isAdmin) {
        QMutexLocker locker(&mutex);
        QJsonDocument doc(userDatabase);  // Always return user database for admins
        return QString::fromUtf8(doc.toJson());
    }
    return "ERROR:Unauthorized access";
}

QString Server::processCreateUser(const QStringList &params)
{
    if (params.size() < 5) {
        return "ERROR:Insufficient parameters";
    }

    QString userType = params.at(0);
    QString username = params.at(1);
    QString password = params.at(2);
    QString accountNumber = params.at(3);
    int initialBalance = params.at(4).toInt();

    QMutexLocker locker(&mutex);

    // Check if the username or account number already exists
    QJsonArray users = userDatabase["users"].toArray();
    for (const QJsonValue &value : users) {
        QJsonObject obj = value.toObject();
        if (obj["username"].toString() == username || obj["account_number"].toString() == accountNumber) {
            return "ERROR:Username or account number already exists";
        }
    }

    QJsonObject newUser{
        {"username", username},
        {"password", password},
        {"account_number", accountNumber},
        {"balance", initialBalance}
    };

    users.append(newUser);
    userDatabase["users"] = users;
    saveDatabase(userDatabase, "user_database.json");

    logOperation("Admin created new user: " + username, true);
    return "SUCCESS:User created successfully";
}
QString Server::processDeleteUser(const QStringList &params)
{
    if (params.size() < 2) {
        qWarning() << "Delete user attempt with insufficient parameters";
        return "ERROR:Insufficient parameters for user deletion";
    }

    QString userType = params.at(0);
    QString username = params.at(1);

    qDebug() << "Attempting to delete user:" << username << "by" << userType;

    if (userType.toLower() != "admin") {
        qWarning() << "Unauthorized delete user attempt by non-admin";
        return "ERROR:Unauthorized access";
    }

    QMutexLocker locker(&mutex);
    QJsonArray users = userDatabase["users"].toArray();
    bool userFound = false;

    for (int i = 0; i < users.size(); ++i) {
        QJsonObject user = users[i].toObject();
        if (user["username"].toString() == username) {
            users.removeAt(i);
            userDatabase["users"] = users;
            saveDatabase(userDatabase, "user_database.json");
            logOperation("Admin deleted user: " + username, true);
            qDebug() << "User" << username << "successfully deleted";
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        qWarning() << "Failed to delete user. User" << username << "not found";
        return "ERROR:User not found";
    }

    return "SUCCESS:User deleted successfully";
}
QString Server::processUpdateUser(const QStringList &params)
{
    if (params.size() < 4) {
        return "ERROR:Insufficient parameters";
    }

    QString userType = params.at(0);
    QString username = params.at(1);
    QString newPassword = params.at(2);
    int newBalance = params.at(3).toInt();

    QMutexLocker locker(&mutex);

    QJsonArray users = userDatabase["users"].toArray();
    for (int i = 0; i < users.size(); ++i) {
        QJsonObject user = users[i].toObject();
        if (user["username"].toString() == username) {
            // Update user information
            user["password"] = newPassword;
            user["balance"] = newBalance;

            users[i] = user;
            userDatabase["users"] = users;
            saveDatabase(userDatabase, "user_database.json");

            logOperation("Admin updated user: " + username, true);
            return "SUCCESS:User updated successfully";
        }
    }

    return "ERROR:User not found";
}

void Server::logOperation(const QString &message, bool isAdmin)
{
    QFile &logFile = isAdmin ? adminLogFile : userLogFile;
    if (logFile.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&logFile);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << ": " << message << "\n";
        logFile.close();
    }
}

void Server::logError(const QString &error)
{
    qCritical() << "Error:" << error;
    QFile errorLog("error_log.txt");
    if (errorLog.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&errorLog);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss") << ": " << error << "\n";
        errorLog.close();
    }
}
