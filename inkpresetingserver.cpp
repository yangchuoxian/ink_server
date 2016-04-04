#include "inkpresetingserver.h"

InkPresetingServer::InkPresetingServer(QObject *parent) :
        QTcpServer(parent)
{

}
InkPresetingServer::~InkPresetingServer()
{

}
void InkPresetingServer::setFilePath(QString name)
{
    filePath = name;
    listen(QHostAddress::Any, 1234);
    qDebug() << "Server started on port 0.0.0.0:1234";
}
void InkPresetingServer::incomingConnection(int handle)
{
    qDebug() << "connection established";

    QString serverAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            serverAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (serverAddress.isEmpty())
        serverAddress = QHostAddress(QHostAddress::LocalHost).toString();

    ClientThread *clientThread = new ClientThread(handle, this);
    clientThread->setFilePath(filePath);
    connect(clientThread, SIGNAL(error(int)), this, SIGNAL(error(int)));
    connect(clientThread, SIGNAL(bytesSent(qint64)), this, SIGNAL(bytesSent(qint64)));
    connect(clientThread, SIGNAL(progressRange(qint64)), this, SIGNAL(progressRange(qint64)));
    connect(clientThread, SIGNAL(status(int)), this, SIGNAL(currentStatus(int)));
    emit ipAddress(serverAddress, 1234);
    emit currentStatus(1);

    clientThread->start();
}
