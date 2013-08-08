#include "mainwindow.h"
#include <QApplication>
#include <QString>

int main(int argc, char *argv[])
{
    QString temp(argv[0]);
    QString workingDirectory = temp.left(temp.lastIndexOf('/'));

    qDebug("Working directory: %s", (const char*)workingDirectory.toUtf8());
    QApplication a(argc, argv);

    cocos2d::MainWindow* window = cocos2d::MainWindow::instance();
    //window->SetWorkingDirectory(workingDirectory);
    window->Init();
    window->show();
    
    return a.exec();
}
