
#pragma once

#include <QMainWindow>
#include <QTreeView>
#include <QTableView>
#include "Singleton.h"
#include "CCGeometry.h"

class MyQGLWidget;
class QToolbar;
class QTreeWidgetItem;
class QSignalMapper;
class NodeItem;
class IComponent;
class INodeDriver;
namespace Ui {
    class MainWindow;
}

NS_CC_BEGIN

class MainWindow;
class Node;
class StreamFormatted;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow* UI();

    DECLARE_SINGLETON(MainWindow)

    bool Init();

    void AddFiles(const char* root, const char* path, bool directory);
    NodeItem* AddNode(Node* parent, Node* node, const char* nodeName);

    void RegisterNodeDriver(uint32_t driverId, INodeDriver* driver);

    void RegisterComponent(uint32_t classId, IComponent* component, const char* componentName);
    IComponent* FindComponent(uint32_t classId);

    void ExportToFile(const char* file);
    void ExportToStream(StreamFormatted& stream, Node* node);

public slots:

    void importCCB();
    void selectNode();

    void setNodePosition(Node* node, Point& position);
    void pushWidget(QWidget* widget);
    void setSelectedNode(Node* node);
    void performToolbarAction();

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;
    QToolBar* mToolbar;
    Node* mSelectedNode;

    typedef std::map<Node*, NodeItem*> tNodeToNodeItemMap;
    tNodeToNodeItemMap mNodeToNodeItemMap;

    typedef std::map<uint32_t, IComponent*> tClassToComponentMap;
    tClassToComponentMap mClassToComponentMap;

    typedef std::map<uint32_t, INodeDriver*> tClassToNodeDriverMap;
    tClassToNodeDriverMap mClassToNodeDriverMap;

protected:

    NodeItem* GetNodeItemFromNode(Node* node);
    Node* GetSelectedNodeInHierarchy();
    void SetSelectedNodeInHierarchy(Node* node);
    void SetPropertyViewForNode(Node* node, Node* oldNode);
};

NS_CC_END
