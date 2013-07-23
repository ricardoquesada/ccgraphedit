
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "myqglwidget.h"
#include "fileutil.h"
#include "mysceneeditor.h"
#include "dialogimportccb.h"

#include "cocos2d.h"
#include "CCFileUtils.h"
#include "CCBReader/CCBReader.h"
#include "CCBReader/CCNodeLoaderLibrary.h"

#include <QStandardItemModel>
#include <QMenuBar>
#include <QAbstractListModel>

USING_NS_CC;
USING_NS_CC_EXT;

IMPLEMENT_SINGLETON(MainWindow)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mQGLWidget(0)
    , mItemModelSceneGraph(0)
{
    ui->setupUi(this);

    // add our cocos2dx opengl widget to the splitter in the correct place
    mQGLWidget = new MyQGLWidget;
    mQGLWidget->show(); // this must come before adding to the graph since it initializes cocos2d.
    ui->splitter->insertWidget(1, mQGLWidget);

    // setup the headers for the scene graph tree view
    QTreeView* tv = ui->hierarchy;
    if (tv)
    {
        // columns are node, type
        mItemModelSceneGraph = new QStandardItemModel(0, 2);
        mItemModelSceneGraph->setHorizontalHeaderItem(0, new QStandardItem(QString("Name")));
        mItemModelSceneGraph->setHorizontalHeaderItem(1, new QStandardItem(QString("Class")));
        tv->setModel(mItemModelSceneGraph);
    }

    // setup menu bar
//    QMenuBar* pMenuBar = new QMenuBar(this);
//    setMenuBar(pMenuBar);

//    QMenu* menu = new QMenu("File", this);
//    menuBar()->addMenu(menu);
//    menu->addAction("New Node", this, SLOT(newNode()));
//    menu->addAction("Import CocosBuilder File", this, SLOT(importCCB()));

    // Add the root scene node to the graph
    AddNode(nullptr, Director::sharedDirector()->getRunningScene(), "Scene", "Scene");

#define INCLUDE_SOME_DEMO_SPRITES
#ifdef INCLUDE_SOME_DEMO_SPRITES
    FileUtils::sharedFileUtils()->addSearchPath("../../../../../cocos2d/template/multi-platform-cpp/proj.ios");
    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(500, 500));
        RepeatForever* action2 = RepeatForever::create(RotateBy::create(4, 360));
        sprite->runAction(action2);
        AddNode(nullptr, sprite, "Sprite", "Sprite");
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

void MainWindow::AddNode(Node* parent, Node* node, const char* nodeName, const char* className)
{
    // add the node to the graph
    // avoid special case where we are adding the root scene node
    Node* const root = Director::sharedDirector()->getRunningScene();
    if (node != root)
    {
        if (!parent)
            parent = root;
        parent->addChild(node);
    }

    if (mItemModelSceneGraph)
    {
        QStandardItem* item = new QStandardItem(QString(nodeName));

        // Find the parent so that we can append to it in the tree view
        tNodeToTreeviewEntryMap::iterator it = mNodeToTreeviewEntryMap.find(parent);
        if (it == mNodeToTreeviewEntryMap.end())
        {
            mItemModelSceneGraph->appendRow(item);
            //mItemModelSceneGraph->setItem(0, 1, new QStandardItem(QString(className)));
            qDebug("adding %p to root", item);
        }
        else
        {
            tTreeviewEntry& entry = (*it).second;
            QStandardItem* parent = entry.mItem;
            parent->appendRow(item);
            qDebug("adding %p to parent %p", item, parent);
        }

        item->setData(QVariant((qlonglong)node));
        mNodeToTreeviewEntryMap.insert(tNodeToTreeviewEntryMap::value_type(node, tTreeviewEntry(item, node)));
    }

    ui->hierarchy->expandAll();
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
        AddNode(0, node, "", "");
    }
}

//
// Toolbar Actions
//

void MainWindow::on_actionCCSprite_triggered()
{
    Size size = Director::sharedDirector()->getWinSize();

    Node* parent = nullptr;

    QModelIndexList nodes = ui->hierarchy->selectionModel()->selectedIndexes();
    if (!nodes.empty())
    {
        QModelIndexList::Iterator it = nodes.begin();
        QModelIndex& index = *it;
        QStandardItem* item = mItemModelSceneGraph->itemFromIndex(index);
        QVariant var = item->data();
        parent = (Node*)var.toLongLong();
    }

    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(.5f * size.width, .5f * size.height));
        AddNode(parent, sprite, "Sprite", "Sprite");
    }
}

void MainWindow::on_actionCCNode_triggered()
{
    qDebug("new node\n");
}
