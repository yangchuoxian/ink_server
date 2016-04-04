#ifndef INKPRESETINGSERVER_H
#define INKPRESETINGSERVER_H
#include <QTcpServer>
#include <QHostAddress>
#include <QTcpSocket>
#include <QFile>
#include <QList>
#include <QNetworkInterface>
#include "clientthread.h"
class InkPresetingServer: public QTcpServer
{
    Q_OBJECT

public:
    explicit InkPresetingServer(QObject *parent = 0);
    ~InkPresetingServer();
    QString filePath;
    void setFilePath(QString);
signals:
    void percentageSent(int);
    void currentStatus(int);
    void error(int);
    void ipAddress(QString, quint16);
    void progressRange(qint64);
    void bytesSent(qint64);
protected:
    void incomingConnection(int);
};

#endif // INKPRESETINGSERVER_H
