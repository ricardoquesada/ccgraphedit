#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug("Working directory: %s", argv[0]);
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
