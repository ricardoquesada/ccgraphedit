#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "Singleton.h"

namespace Ui {
    class MainWindow;
}
namespace cocos2d {
    class Node;
}

class MyQGLWidget;
class QTreeWidgetItem;
class NodeItem;
class ComponentBase;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DECLARE_SINGLETON(MainWindow)

    Ui::MainWindow* UI();

    void AddFiles(const char* root, const char* path, bool directory);
    void AddNode(cocos2d::Node* parent, cocos2d::Node* node, const char* nodeName);

    void RegisterComponent(uint32_t classId, ComponentBase* component);
    ComponentBase* FindComponent(uint32_t classId);

public slots:

    void importCCB();
    void selectNode();

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;

    typedef std::map<cocos2d::Node*, NodeItem*> tNodeToNodeItemMap;
    tNodeToNodeItemMap mNodeToNodeItemMap;

    typedef std::map<uint32_t, ComponentBase*> tClassToComponentMap;
    tClassToComponentMap mClassToComponentMap;

private slots:

    void on_actionCCSprite_triggered();
    void on_actionCCNode_triggered();

protected:

    cocos2d::Node* GetSelectedNodeInHierarchy();
    void SetPropertyViewForNode(cocos2d::Node* node);
};

#endif // MAINWINDOW_H
