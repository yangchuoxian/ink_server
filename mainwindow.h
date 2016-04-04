#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "inkpresetingserver.h"
#include "clientthread.h"
#include <QMainWindow>
#include <QFileDialog>
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QTcpServer>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QIcon>
#include <QCloseEvent>
namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    Ui::MainWindow *ui;
    QString fileName;
    quint64 fileSize;
    InkPresetingServer server;
    qint64 bytesSent;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

    //void createTrayIcon();
    //void createActions();
public slots:
    void findFile();
    void setCurrentStatus(int);
    void errorHandler(int);
    void displayIPAddress(QString, quint16);
    void updateProgressBar(qint64);
    void setProgressRange(qint64);

};

#endif // MAINWINDOW_H
