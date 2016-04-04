#include <QtGui/QApplication>
#include "mainwindow.h"
#include <QTextCodec>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec *localCode = QTextCodec::codecForName("System");
    QTextCodec::setCodecForLocale(localCode);
    QTextCodec::setCodecForCStrings(localCode);
    QTextCodec::setCodecForTr(localCode);
    MainWindow w;
    w.show();

    return a.exec();
}
