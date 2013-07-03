#ifndef MYQGLWIDGETTHREADED_H
#define MYQGLWIDGETTHREADED_H

#include <QGLWidget>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QCloseEvent>

#include "myglthread.h"

class MyQGLWidgetThreaded : public QGLWidget
{
public:

    explicit MyQGLWidgetThreaded(QWidget* parent = 0);

    void startRendering();
    void stopRendering();
    
    void resize(int w, int h);

protected:

    void resizeEvent(QResizeEvent *evt);
    void paintEvent(QPaintEvent *);
    void closeEvent(QCloseEvent *evt);

    MyGLThread mGLThread;
};

#endif // MYQGLWIDGETTHREADED_H
