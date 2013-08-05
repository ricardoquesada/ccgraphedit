
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myqglwidget.h"
#include "fileutil.h"
#include "mysceneeditor.h"
#include "dialogimportccb.h"
#include "nodeitem.h"
#include "NodeDriver.h"
#include "widgetpoint.h"
#include "componentnode.h"
#include "componentsprite.h"

#include "cocos2d.h"
#include "CCFileUtils.h"
#include "CCClassRegistry.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"

#include <QStandardItemModel>
#include <QMenuBar>
#include <QAbstractListModel>
#include <QLineEdit>
#include <QCheckBox>
#include <QMessageBox>
#include <QToolBar>
#include <QToolButton>
#include <QSignalMapper>

USING_NS_CC;
USING_NS_CC_EXT;

namespace
{
    const uint32_t kNodeDriverPosition = fnv1_32("position");
};

IMPLEMENT_SINGLETON(MainWindow)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mQGLWidget(nullptr)
    , mToolbar(nullptr)
    , mSelectedNode(nullptr)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::UI()
{
    return ui;
}

bool MainWindow::Init()
{
    setWindowTitle(QString("Cocos2d Graph Editor"));

    // create a toolbar for the working area
    // add it to the working layout
    mToolbar = new QToolBar;
    ui->working->layout()->addWidget(mToolbar);

    // register the components
    RegisterComponent(Node::kClassId, new ComponentNode, "Node");
    RegisterComponent(Sprite::kClassId, new ComponentSprite, "Sprite");

    // connect any signals and slots
    connect(MySceneEditor::instance(), SIGNAL(positionChanged(Node*, Point&)), this, SLOT(setNodePosition(Node*,Point&)));
    connect(MySceneEditor::instance(), SIGNAL(selectedNodeChanged(Node*)), this, SLOT(setSelectedNode(Node*)));
    connect(ui->hierarchy->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(selectNode()));

    // add our cocos2dx opengl widget to the splitter in the correct place
    mQGLWidget = new MyQGLWidget;
    mQGLWidget->setSizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
    mQGLWidget->show(); // this must come before adding to the graph since it initializes cocos2d.
    ui->working->layout()->addWidget(mQGLWidget);

    // Add a path for our test sprite
    FileUtils::sharedFileUtils()->addSearchPath("../../../../../cocos2d/template/multi-platform-cpp/proj.ios");
    FileUtils::sharedFileUtils()->addSearchPath("/Users/jgraham/dev_qtTest/resources/images/frames");

    Sprite* frame = Sprite::create("frame-ipad.png");
    if (frame)
    {
        Node* scene = Director::sharedDirector()->getRunningScene();
        Node* root = Node::create();
        AddNode(scene, root, "root");
        MySceneEditor::instance()->SetRootNode(root);
        scene->addChild(frame);
    }
}

void MainWindow::AddFiles(const char* root, const char* path, bool directory)
{
    if (directory)
        FileUtils::sharedFileUtils()->addSearchPath(path);
}

void MainWindow::AddNode(Node* parent, Node* node, const char* nodeName)
{
    tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(node);
    if (it != mNodeToNodeItemMap.end())
    {
        QMessageBox::information(nullptr, QString("Error"), QString("Node cannot be added twice"), QMessageBox::Ok);
        return;
    }

    IComponentBase* plugin = MainWindow::instance()->FindComponent(node->classId());
    if (!plugin)
    {
        QMessageBox::information(nullptr, QString("Error"), QString("Component cannot be found to populate node item"), QMessageBox::Ok);
        return;
    }

    if (parent)
        parent->addChild(node);

    if (ui->hierarchy)
    {
        // Find the parent so that we can append to it in the tree view
        QTreeWidgetItem* parentItem;
        tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(parent);
        if (it == mNodeToNodeItemMap.end())
        {
            parentItem = ui->hierarchy->invisibleRootItem();
        }
        else
        {
            NodeItem* item = (*it).second;
            parentItem = item->SceneItem();
        }

        NodeItem* item = new NodeItem;

        plugin->Populate(item, ui->properties, node);

        QTreeWidgetItem* sceneItem = new QTreeWidgetItem;
        sceneItem->setText(0, QString(nodeName));

        item->SetNode(node);
        item->SetSceneItem(sceneItem);

        parentItem->addChild(sceneItem);

        mNodeToNodeItemMap.insert(tNodeToNodeItemMap::value_type(node, item));
    }
}

void MainWindow::RegisterComponent(uint32_t classId, IComponentBase* component, const char* componentName)
{
    mClassToComponentMap.insert(tClassToComponentMap::value_type(classId, component));

    QAction* action = new QAction(QString(componentName), mToolbar);
    mToolbar->addAction(action);
    action->setData(QVariant((int)classId));
    connect(action, SIGNAL(triggered()), this, SLOT(performToolbarAction()));
}

IComponentBase* MainWindow::FindComponent(uint32_t classId)
{
    tClassToComponentMap::iterator it = mClassToComponentMap.find(classId);
    return it == mClassToComponentMap.end() ? nullptr : (*it).second;
}

//
// Public Slots
//

void MainWindow::importCCB()
{
    DialogImportCCB* dialog = new DialogImportCCB(this);
    dialog->setModal(true);
    dialog->show();
    dialog->exec();

    FileUtil::EnumerateDirectoryT(dialog->ccbPath().toUtf8(), 0, this, &MainWindow::AddFiles);
    FileUtil::EnumerateDirectoryT(dialog->resourcesPath().toUtf8(), 0, this, &MainWindow::AddFiles);

    CCBReader* ccbReader = new CCBReader(NodeLoaderLibrary::sharedNodeLoaderLibrary());
    Node* node = ccbReader->readNodeGraphFromFile(dialog->ccbPath().toUtf8());
    if (node)
    {
        AddNode(0, node, "");
    }
}

void MainWindow::selectNode()
{
    Node* selectedNode = GetSelectedNodeInHierarchy();
    MySceneEditor::instance()->SetSelectedNode(selectedNode);
    SetPropertyViewForNode(selectedNode, mSelectedNode);
    mSelectedNode = selectedNode;
}

void MainWindow::setNodePosition(Node* node, Point& position)
{
    NodeItem* nodeItem = GetNodeItemFromNode(node);
    if (nodeItem)
    {
        INodeDriver* driver = nodeItem->FindDriverByHash(kNodeDriverPosition);
        if (driver)
        {
            QWidget* widget = driver->Widget();
            widgetPoint* wp = dynamic_cast<widgetPoint*>(widget);
            if (wp)
            {
                wp->SetValue(position, true);
            }
        }
    }
}

void MainWindow::pushWidget(QWidget* widget)
{
    QVariant var = widget->property("node");
    Node* node = (Node*)var.toLongLong();
    if (node)
    {
        NodeItem* nodeItem = GetNodeItemFromNode(node);
        if (nodeItem)
        {
            INodeDriver* driver = nodeItem->FindDriverByWidget(widget);
            if (driver)
            {
                driver->Push();
            }
        }
    }
}

void MainWindow::setSelectedNode(Node* node)
{
    if (node)
        SetSelectedNodeInHierarchy(node);
}

void MainWindow::performToolbarAction()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action)
    {
        QVariant v = action->data();
        uint32_t classId = v.toInt();

        Node* node = dynamic_cast<Node*>(CCClassRegistry::instance()->instantiateClass(classId));
        if (node)
        {
            Size size = Director::sharedDirector()->getWinSize();

            Node* parent = GetSelectedNodeInHierarchy();
            if (!parent)
                parent = MySceneEditor::instance()->GetRootNode();

            node->setPosition(ccp(.5f * size.width, .5f * size.height));

            Sprite* sprite = dynamic_cast<Sprite*>(node);
            if (sprite)
            {
                Image* image = new Image;
                image->autorelease();
                if (image->initWithImageFile("Icon-144.png"))
                {
                    Texture2D* texture = new Texture2D;
                    if (texture->initWithImage(image))
                    {
                        sprite->setTexture(texture);
                        sprite->setTextureRect(Rect(0, 0, texture->getPixelsWide(), texture->getPixelsHigh()));
                    }
                }
            }

            AddNode(parent, node, "New Node");
        }
    }
}

//
// Toolbar Actions
//

void MainWindow::on_actionCCSprite_triggered()
{
    Size size = Director::sharedDirector()->getWinSize();

    Node* parent = GetSelectedNodeInHierarchy();
    if (!parent)
        parent = MySceneEditor::instance()->GetRootNode();

    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(.5f * size.width, .5f * size.height));
        AddNode(parent, sprite, "Sprite");
    }
}

void MainWindow::on_actionCCNode_triggered()
{
    Size size = Director::sharedDirector()->getWinSize();

    Node* parent = GetSelectedNodeInHierarchy();

    Node* node = Node::create();
    if (node)
    {
        node->setPosition(ccp(.5f * size.width, .5f * size.height));
        AddNode(parent, node, "Node");
    }
}

//
// Protected Methods
//

NodeItem* MainWindow::GetNodeItemFromNode(Node* node)
{
    tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(node);
    if (it == mNodeToNodeItemMap.end())
    {
        QMessageBox::information(nullptr, QString("Error"), QString("Node item cannot be found in the map"), QMessageBox::Ok);
        return nullptr;
    }

    NodeItem* nodeItem = (*it).second;
    return nodeItem;
}

Node* MainWindow::GetSelectedNodeInHierarchy()
{
    QList<QTreeWidgetItem*> nodes = ui->hierarchy->selectedItems();
    if (nodes.empty())
        return nullptr;

    QTreeWidgetItem* widget = nodes.front();
    QVariant var = widget->data(0, Qt::UserRole);
    NodeItem* item = (NodeItem*)var.toLongLong();

    return item->GetNode();
}

void MainWindow::SetSelectedNodeInHierarchy(Node* node)
{
    tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(node);
    if (it == mNodeToNodeItemMap.end())
    {
        QMessageBox::information(nullptr, QString("Error"), QString("Node cannot be found in the map"), QMessageBox::Ok);
        return;
    }
    NodeItem* nodeItem = (*it).second;
    ui->hierarchy->setCurrentItem(nodeItem->SceneItem());
}

void MainWindow::SetPropertyViewForNode(Node* node, Node* oldNode)
{
    if (node == oldNode)
        return;

    if (ui->properties)
    {
        // first unmap the widgets for the old node since we cannot recycle them
        // and they will be destroyed by the owning widgets or tree view widget.
        if (oldNode)
        {
            tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(oldNode);
            if (it == mNodeToNodeItemMap.end())
            {
                QMessageBox::information(nullptr, QString("Error"), QString("Old node cannot be found in the map"), QMessageBox::Ok);
            }
            else
            {
                NodeItem* nodeItem = (*it).second;
                nodeItem->DestroyWidgets();
            }
        }

        // remove all children of the root node
        QTreeWidgetItem* root = ui->properties->invisibleRootItem();
        while (root->childCount())
            root->takeChild(0);

        // Don't allow editing of the nodes above/next to root
        if (!MySceneEditor::instance()->IsChildOfRoot(node))
            return;

        tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(node);
        if (it == mNodeToNodeItemMap.end())
        {
            QMessageBox::information(nullptr, QString("Error"), QString("Node cannot be found in the map"), QMessageBox::Ok);
            return;
        }

        NodeItem* nodeItem = (*it).second;
        nodeItem->CreateWidgets(ui->properties);
    }
}
