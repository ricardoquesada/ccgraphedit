#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qDebug("Working directory: %s", argv[0]);
    QApplication a(argc, argv);

    MainWindow::instance()->show();
    
    return a.exec();
}
