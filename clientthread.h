#ifndef CLIENTTHREAD_H
#define CLIENTTHREAD_H
#include <QThread>
#include <QFile>
#include <QDir>
#include <QTcpSocket>
#include <QApplication>
class ClientThread : public QThread
{
    Q_OBJECT
public:
    explicit ClientThread(int h, QObject *parent = 0);
    bool isCanceled;
    //QFile file;
    QString filePath;
    QStringList fileNames;
    QStringList folderNames;
    QStringList fileFilters;
    QStringList folderFilters;

    QString imageFolderPath;
    QString imageFilePath;
    int numberOfFilesSent;
    int numberOfFilesToBeTransmit;

    qint64 numberOfBytesToBeTransmit;
    bool isFolderSelected;
    bool isFileSelected;
    int indexOfEntry;
    QTcpSocket client;
    qint64 blockSize;
    qint64 blockNumber;
    void setFilePath(QString);

public slots:
    void getSignalFromClient();
protected:
    void run();
signals:
    void error(int);
    void status(int);
    void progressRange(qint64);
    void bytesSent(qint64);
};

#endif // CLIENTTHREAD_H
