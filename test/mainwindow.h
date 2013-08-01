
#pragma once

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "Singleton.h"
#include "CCGeometry.h"

class MyQGLWidget;
class QTreeWidgetItem;
class NodeItem;
class ComponentBase;
namespace Ui {
    class MainWindow;
}

NS_CC_BEGIN

class MainWindow;
class Node;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    DECLARE_SINGLETON(MainWindow)

    Ui::MainWindow* UI();

    void AddFiles(const char* root, const char* path, bool directory);
    void AddNode(Node* parent, Node* node, const char* nodeName);

    void RegisterComponent(uint32_t classId, ComponentBase* component);
    ComponentBase* FindComponent(uint32_t classId);

public slots:

    void importCCB();
    void selectNode();

    void setNodePosition(Node* node, Point& position);
    void pushWidget(QWidget* widget);
    void setSelectedNode(Node* node);

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;
    Node* mSelectedNode;

    typedef std::map<Node*, NodeItem*> tNodeToNodeItemMap;
    tNodeToNodeItemMap mNodeToNodeItemMap;

    typedef std::map<uint32_t, ComponentBase*> tClassToComponentMap;
    tClassToComponentMap mClassToComponentMap;

private slots:

    void on_actionCCSprite_triggered();
    void on_actionCCNode_triggered();

protected:

    Node* GetSelectedNodeInHierarchy();
    void SetSelectedNodeInHierarchy(Node* node);
    void SetPropertyViewForNode(Node* node, Node* oldNode);
};

NS_CC_END
