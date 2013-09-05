
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
class QComboBox;
class NodeItem;
class IComponent;
class INodeDriver;
class DeviceFrame;
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

    void SetWorkingDirectory(const char* path);

    void AddFiles(const char* root, const char* path, bool directory);

    NodeItem* AddNode(Node* parent, uint32_t classId);
    void ClearScene();

    void RegisterNodeDriver(uint32_t driverId, INodeDriver* driver);
    void RegisterComponent(uint32_t classId, IComponent* component, const char* componentName);
    IComponent* FindComponent(uint32_t classId);

    NodeItem* GetNodeItemFromNode(Node* node);

    DeviceFrame* GetCurrentDeviceFrame() const;

public slots:

    void selectDeviceFrame(int comboIndex);
    void saveProject();
    void loadProject();
    void dumpScene();
    void selectNode();

    void setNodePosition(Node* node, Point& position);
    void pushWidget(QWidget* widget);
    void setSelectedNode(Node* node);
    void performToolbarAction();

protected:

    void AddDeviceFrame(DeviceFrame* frame);
    void SetCurrentDeviceFrame(DeviceFrame* frame);
    Node* GetSelectedNodeInHierarchy();
    void SetSelectedNodeInHierarchy(Node* node);
    void SetPropertyViewForNode(Node* node, Node* oldNode);
    void DumpSceneGraph(Node* node, int indent = 0);

protected:

    Ui::MainWindow *ui;
    MyQGLWidget* mQGLWidget;
    QToolBar* mToolbar;
    QComboBox* mDeviceCombo;

    Node* mSelectedNode;

    typedef std::map<Node*, NodeItem*> tNodeToNodeItemMap;
    tNodeToNodeItemMap mNodeToNodeItemMap;

    typedef std::map<uint32_t, IComponent*> tClassToComponentMap;
    tClassToComponentMap mClassToComponentMap;

    typedef std::map<uint32_t, INodeDriver*> tClassToNodeDriverMap;
    tClassToNodeDriverMap mClassToNodeDriverMap;

    QString mWorkingDirectory;

    typedef std::vector<DeviceFrame*> tDeviceFrames;
    tDeviceFrames mDeviceFrames;
    DeviceFrame* mCurrentDeviceFrame;
};

NS_CC_END
