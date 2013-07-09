#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef THREADED
#include "myqglwidgetthreaded.h"
#else
#include "myqglwidget.h"
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mQGLWidget(0)
{
    ui->setupUi(this);

    QWidget* placeholder = ui->cocosView->findChild<QWidget*>(QString("placeholder"));
    if (placeholder)
    {
        QWidget* parent = dynamic_cast<QWidget*>(placeholder->parent());

#ifdef THREADED
        mQGLWidget = new MyQGLWidgetThreaded(parent);
#else
        mQGLWidget = new MyQGLWidget(parent);
#endif
        //mQGLWidget->move(50, 50);
        mQGLWidget->resize(480, 320);
        mQGLWidget->show();

#ifdef THREADED
        mQGLWidget->startRendering();
#endif

        // remove the placeholder from the layout
        parent->layout()->removeWidget(placeholder);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
