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

#ifdef THREADED
    mQGLWidget = new MyQGLWidgetThreaded(this);
#else
    mQGLWidget = new MyQGLWidget(this);
#endif
    mQGLWidget->move(50, 50);
    mQGLWidget->resize(480, 320);
    mQGLWidget->show();

#ifdef THREADED
    mQGLWidget->startRendering();
#endif

//    QScrollArea* scrollArea = findChild<QScrollArea>("scrollArea");
//    if (scrollArea)
//    {
//        scrollArea->
//    }

    //ui->formLayout->addWidget(mQGLWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
