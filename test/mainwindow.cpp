
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myqglwidget.h"
#include "fileutil.h"
#include "mysceneeditor.h"
#include "dialogimportccb.h"
#include "nodeitem.h"
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
    , mQGLWidget(0)
{
    ui->setupUi(this);

    // register the components
    RegisterComponent(Node::kClassId, new ComponentNode);
    RegisterComponent(Sprite::kClassId, new ComponentSprite);

    // connect any signals and slots
    auto ret = connect(MySceneEditor::instance(), SIGNAL(positionChanged(Node*, Point&)), this, SLOT(setNodePosition(Node*,Point&)));

    // add our cocos2dx opengl widget to the splitter in the correct place
    mQGLWidget = new MyQGLWidget;
    mQGLWidget->show(); // this must come before adding to the graph since it initializes cocos2d.
    ui->splitter->insertWidget(1, mQGLWidget);

    if (ui->hierarchy)
    {
        QStringList labels;
        labels << "Scene Graph";
        ui->hierarchy->setHeaderLabels(labels);

        connect(ui->hierarchy->selectionModel(), SIGNAL(selectionChanged(const QItemSelection&, const QItemSelection&)), this, SLOT(selectNode()));
    }

    if (ui->properties)
    {
        QStringList labels;
        labels << "Properties" << "Value";
        ui->properties->setHeaderLabels(labels);
    }

    // Add the root scene node to the graph
    AddNode(nullptr, Director::sharedDirector()->getRunningScene(), "Scene");

#define INCLUDE_SOME_DEMO_SPRITES
#ifdef INCLUDE_SOME_DEMO_SPRITES
    FileUtils::sharedFileUtils()->addSearchPath("../../../../../cocos2d/template/multi-platform-cpp/proj.ios");
    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(500, 500));
        RepeatForever* action2 = RepeatForever::create(RotateBy::create(4, 360));
        sprite->runAction(action2);
        AddNode(nullptr, sprite, "Sprite");
    }
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::UI()
{
    return ui;
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

    // add the node to the graph
    // avoid special case where we are adding the root scene node
    Node* const root = Director::sharedDirector()->getRunningScene();
    if (node != root)
    {
        if (!parent)
            parent = root;
        parent->addChild(node);
    }

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

        String* className = CCClassRegistry::instance()->getClassName(node->classId());

        NodeItem* item = new NodeItem;

        QTreeWidgetItem* sceneItem = new QTreeWidgetItem;
        sceneItem->setText(0, QString(className->getCString()));

        item->SetNode(node);
        item->SetSceneItem(sceneItem);

        parentItem->addChild(sceneItem);

        mNodeToNodeItemMap.insert(tNodeToNodeItemMap::value_type(node, item));
    }
}

void MainWindow::RegisterComponent(uint32_t classId, ComponentBase* component)
{
    mClassToComponentMap.insert(tClassToComponentMap::value_type(classId, component));
}

ComponentBase* MainWindow::FindComponent(uint32_t classId)
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
    SetPropertyViewForNode(selectedNode);
}

void MainWindow::setNodePosition(Node* node, Point& position)
{
    ComponentBase* plugin = FindComponent(node->classId());
    if (plugin)
    {
        INodeDriver* driver = plugin->FindDriverByHash(kNodeDriverPosition);
        if (driver)
        {
            widgetPoint* wp = dynamic_cast<widgetPoint*>(driver->Widget());
            if (wp)
            {
                wp->SetValue(position);
            }
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

    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(.5f * size.width, .5f * size.height));
        AddNode(parent, sprite, "Sprite");
    }
}

void MainWindow::on_actionCCNode_triggered()
{
    qDebug("new node\n");
}

//
// Protected Methods
//

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

void MainWindow::SetPropertyViewForNode(Node* node)
{
    if (ui->properties)
    {
        tNodeToNodeItemMap::iterator it = mNodeToNodeItemMap.find(node);
        if (it == mNodeToNodeItemMap.end())
        {
            QMessageBox::information(nullptr, QString("Error"), QString("Node cannot be found in the map"), QMessageBox::Ok);
            return;
        }

        const NodeItem* item = (*it).second;

        QTreeWidgetItem* root = ui->properties->invisibleRootItem();

        // remove the child if there is one, we have it in a map for later
        while (root->childCount())
        {
            if (root->child(0) == item->PropertyItem())
                return;
            root->takeChild(0);
        }

        ComponentBase* plugin = FindComponent(node->classId());
        if (plugin)
        {
            plugin->Populate(ui->properties, root, node);
        }
        else
        {
            QMessageBox::information(nullptr, QString("Error"), QString("Component cannot be found to populate node"), QMessageBox::Ok);
        }
    }
}
