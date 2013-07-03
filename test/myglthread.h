#ifndef MYGLTHREAD_H
#define MYGLTHREAD_H

#include <QThread>
#include <QGLWidget>

class MyQGLWidgetThreaded;

class MyGLThread : public QThread
{
public:
    MyGLThread(MyQGLWidgetThreaded* glWidget);
    void resizeViewport(int width, int height);
    void run();
    void stop();

protected:
    bool mbInitialized;
    bool mbRender;
    MyQGLWidgetThreaded* mGLWidget;
    int mWidth;
    int mHeight;
};

#endif // MYGLTHREAD_H
