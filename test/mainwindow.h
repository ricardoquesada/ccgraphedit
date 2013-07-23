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
    void AddNode(cocos2d::Node* node, const char* nodeName, const char* className);

public slots:

    void importCCB();

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;

    QStandardItemModel* mItemModelSceneGraph;

private slots:

    void on_actionCCSprite_triggered();
    void on_actionCCNode_triggered();
};

#endif // MAINWINDOW_H
