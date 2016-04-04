#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setFixedSize(467, 304);
    bytesSent = 0;
    ui->lineEdit_localPort->setEnabled(false);
    ui->lineEdit_filePath->setEnabled(false);
    ui->lineEdit_localAddress->setEnabled(false);
    ui->lineEdit_remoteAddress->setEnabled(false);
    ui->progressBar->setValue(0);
    ui->progressBar->setRange(0, 10000);

    connect(&server, SIGNAL(currentStatus(int)), this, SLOT(setCurrentStatus(int)));
    connect(&server, SIGNAL(error(int)), this, SLOT(errorHandler(int)));
    connect(&server, SIGNAL(ipAddress(QString, quint16)),this, SLOT(displayIPAddress(QString, quint16)));
    connect(&server, SIGNAL(bytesSent(qint64)), this, SLOT(updateProgressBar(qint64)));
    connect(&server, SIGNAL(progressRange(qint64)), this, SLOT(setProgressRange(qint64)));

    QFile thePath("C:/imageFilePath_inkPresettingSystem");
    if (thePath.open(QIODevice::ReadOnly)){
        QString dir = thePath.readAll();
        ui->lineEdit_filePath->setText(dir);

        server.setFilePath(dir);
        thePath.close();
    }
}
void MainWindow::setProgressRange(qint64 m)
{
    bytesSent = 0;
    ui->progressBar->setRange(0, m);
}
void MainWindow::updateProgressBar(qint64 r)
{
    bytesSent += r;
    ui->progressBar->setValue(bytesSent);
}
void MainWindow::errorHandler(int e)
{
    QString v1, v2;
    switch(e){
    case 1:
        //choose file first
        v1 = QApplication::translate("MainWindow", "\346\217\220\347\244\272", 0, QApplication::UnicodeUTF8);
        v2 = QApplication::translate("MainWindow", "\350\257\267\345\205\210\351\200\211\345\256\232\351\234\200\350\246\201\345\217\221\351\200\201\347\232\204\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8);
        QMessageBox::information(this, v1, v2, QMessageBox::Ok);
        break;
    case 2:
        //cannot open file
        v1 = QApplication::translate("MainWindow", " \351\224\231\350\257\257", 0, QApplication::UnicodeUTF8);
        v2 = QApplication::translate("MainWindow", "\346\227\240\346\263\225\346\211\223\345\274\200\346\226\207\344\273\266", 0, QApplication::UnicodeUTF8);
        QMessageBox::critical(this, v1, v2, QMessageBox::Ok);
        break;
    case 3:
        //transmission interrupt
        v1 = QApplication::translate("MainWindow", " \351\224\231\350\257\257", 0, QApplication::UnicodeUTF8);
        v2 = QApplication::translate("MainWindow", "\346\226\207\344\273\266\344\274\240\350\276\223\345\274\202\345\270\270\343\200\202\344\274\240\350\276\223\344\270\255\346\226\255", 0, QApplication::UnicodeUTF8);
        QMessageBox::critical(this, v1, v2, QMessageBox::Ok);
        break;
    }
}
void MainWindow::displayIPAddress(QString ip, quint16 port)
{
    ui->lineEdit_localAddress->setText(ip);
    QString temp;
    temp.setNum(port);
    ui->lineEdit_localPort->setText(temp);
}
void MainWindow::setCurrentStatus(int flag)
{
    switch(flag){
    case 1:
        //connection established
        ui->pushButton_search->setEnabled(true);
        break;
    case 2:
        //transmitting...
        ui->pushButton_search->setEnabled(false);
        break;
    case 3:
        //transmission finished
        ui->progressBar->setValue(ui->progressBar->maximum());
        ui->pushButton_search->setEnabled(true);
        break;
    case 4:
        //file exists, transmission abort
        ui->progressBar->setValue(ui->progressBar->minimum());
        ui->pushButton_search->setEnabled(true);
        break;
    case 5:
        //insufficient disk space, transmission abort
        ui->progressBar->setValue(ui->progressBar->minimum());
        ui->pushButton_search->setEnabled(true);
        break;
    case 6:
        //transmission canceled by user
        ui->progressBar->setValue(ui->progressBar->minimum());
        ui->pushButton_search->setEnabled(true);
    }
}
void MainWindow::findFile()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("请选择图像文件的存放目录"),
                                                     "C:",
                                                     QFileDialog::ShowDirsOnly
                                                     | QFileDialog::DontResolveSymlinks);
    QFile thePath("C:/imageFilePath_inkPresettingSystem");
    if (thePath.open(QIODevice::WriteOnly)){
        thePath.write(dir.toUtf8());
        thePath.close();
    }
    if (dir == NULL)
        return;
    bytesSent = 0;
    ui->lineEdit_filePath->setText(dir);

    server.setFilePath(dir);
}
MainWindow::~MainWindow()
{
    delete ui;
}
