
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myqglwidget.h"
#include "fileutil.h"
#include "mysceneeditor.h"
#include "cocos2d.h"
#include <QStandardItemModel>

USING_NS_CC;

IMPLEMENT_SINGLETON(MainWindow)

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mQGLWidget(0)
    , mItemModelSceneGraph(0)
{
    ui->setupUi(this);

    mQGLWidget = new MyQGLWidget;
    mQGLWidget->show();
    ui->splitter->insertWidget(1, mQGLWidget);

    // setup the headers for the scene graph tree view
    QTreeView* tv = ui->scenegraph;
    if (tv)
    {
        // columns are node, type
        mItemModelSceneGraph = new QStandardItemModel(0, 2);
        mItemModelSceneGraph->setHorizontalHeaderItem(0, new QStandardItem(QString("Node")));
        mItemModelSceneGraph->setHorizontalHeaderItem(1, new QStandardItem(QString("Class")));
        tv->setModel(mItemModelSceneGraph);
    }

    // setup menu bar
    QMenuBar* pMenuBar = new QMenuBar(this);
    setMenuBar(pMenuBar);

    QMenu* menu = new QMenu("File", this);
    menu->addAction(new QAction("New Graph", this));
    menuBar()->addMenu(menu);

    // build a file list
    FileUtil::EnumerateDirectoryT("/Users/jgraham/dev_casino3/Assets/ccbResources", 0, this, &MainWindow::AddFiles);

#define INCLUDE_SOME_DEMO_SPRITES
#ifdef INCLUDE_SOME_DEMO_SPRITES
    MySceneEditor* editor = MySceneEditor::instance();
    editor->AddSearchPath("../../../../../cocos2d/template/multi-platform-cpp/proj.ios");
    Sprite* sprite = Sprite::create("Icon-144.png");
    if (sprite)
    {
        sprite->setPosition(ccp(500, 500));

        //RepeatForever* action = RepeatForever::create(Sequence::create(ScaleTo::create(.5f, -1, 1), ScaleTo::create(.5f, 1, 1), 0));
        //sprite->runAction(action);
        RepeatForever* action2 = RepeatForever::create(RotateBy::create(4, 360));
        sprite->runAction(action2);

        editor->AddNode(0, sprite);
        AddNode(sprite, "Sprite", "Sprite");
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
    printf("%s %s\n", directory ? "Directory" : "File", path);
}

void MainWindow::AddNode(const Node* node, const char* nodeName, const char* className)
{
    if (mItemModelSceneGraph)
    {
        mItemModelSceneGraph->appendRow(new QStandardItem(QString(nodeName)));
        mItemModelSceneGraph->setItem(0, 1, new QStandardItem(QString(className)));
    }
}
