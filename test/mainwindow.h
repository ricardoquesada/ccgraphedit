#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "Singleton.h"

namespace Ui {
    class MainWindow;
}

class MyQGLWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DECLARE_SINGLETON(MainWindow)

    Ui::MainWindow* UI();
    QTreeView* SceneGraph();
    QTableView* Properties();

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;
};

#endif // MAINWINDOW_H
