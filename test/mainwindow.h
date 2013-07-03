#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//#define THREADED

namespace Ui {
class MainWindow;
}

#ifdef THREADED
class MyQGLWidgetThreaded;
#else
class MyQGLWidget;
#endif

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
#ifdef THREADED
    MyQGLWidgetThreaded* mQGLWidget;
#else
    MyQGLWidget* mQGLWidget;
#endif
};

#endif // MAINWINDOW_H
