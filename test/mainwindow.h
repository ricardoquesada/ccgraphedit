#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "Singleton.h"

class QStandardItemModel;

namespace Ui {
    class MainWindow;
}
namespace cocos2d {
    class Node;
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

    void AddFiles(const char* root, const char* path, bool directory);
    void AddNode(const cocos2d::Node* node, const char* nodeName, const char* className);

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;

    QStandardItemModel* mItemModelSceneGraph;
};

#endif // MAINWINDOW_H
