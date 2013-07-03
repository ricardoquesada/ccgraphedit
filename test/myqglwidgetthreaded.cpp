#include "myqglwidgetthreaded.h"

MyQGLWidgetThreaded::MyQGLWidgetThreaded(QWidget* parent)
    : QGLWidget(parent)
    , mGLThread(this)
{
    setAutoBufferSwap(false);
}

void MyQGLWidgetThreaded::startRendering()
{
    mGLThread.start();
}

void MyQGLWidgetThreaded::stopRendering()
{
    mGLThread.stop();
    mGLThread.wait();
}

void MyQGLWidgetThreaded::resize(int w, int h)
{
    mGLThread.resizeViewport(w, h);
}

void MyQGLWidgetThreaded::resizeEvent(QResizeEvent* evt)
{
    mGLThread.resizeViewport(evt->size().width(), evt->size().height());
}

void MyQGLWidgetThreaded::paintEvent(QPaintEvent*)
{
    // Handled by the GLThread.
}

void MyQGLWidgetThreaded::closeEvent(QCloseEvent* evt)
{
    stopRendering();
    QGLWidget::closeEvent(evt);
}

