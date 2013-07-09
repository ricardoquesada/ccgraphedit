
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myqglwidget.h"

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

        mQGLWidget = new MyQGLWidget(parent);
        //mQGLWidget->move(50, 50);
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
