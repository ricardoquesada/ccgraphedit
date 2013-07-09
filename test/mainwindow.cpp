
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myqglwidget.h"

IMPLEMENT_SINGLETON(MainWindow)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mQGLWidget(0)
{
    ui->setupUi(this);

    // we find a placeholder widget in the ui so that we know where to put the
    // cocos2d qglwidget. We don't really use it's position since the layout
    // handles that, but we do need it's parent which we add our widget to.
    QWidget* placeholder = ui->cocosView->findChild<QWidget*>(QString("placeholder"));
    if (placeholder)
    {
        QWidget* parent = dynamic_cast<QWidget*>(placeholder->parent());

        mQGLWidget = new MyQGLWidget(parent);
        mQGLWidget->resize(480, 320);
        mQGLWidget->show();

        // remove the placeholder from the layout
        parent->layout()->removeWidget(placeholder);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

Ui::MainWindow* MainWindow::UI()
{
    return ui;
}

QTreeView* MainWindow::SceneGraph()
{
    return ui->scenegraph;
}

QTableView* MainWindow::Properties()
{
    return ui->properties;
}

