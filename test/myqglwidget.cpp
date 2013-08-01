#include "myqglwidget.h"
#include "mysceneeditor.h"
#include "mainwindow.h"

#include <QDebug>
#include <QStandardItemModel>
#include <QTreeView>

#include "cocos2d.h"
#include "CCDirector.h"
#include "CCFileUtilsMac.h"

#include <vector>

#include "Display.h"

USING_NS_CC;

MyQGLWidget::MyQGLWidget()
    : mLazyInit(false)
{
}

MyQGLWidget::MyQGLWidget(QWidget* parent)
    : QGLWidget(parent)
    , mLazyInit(false)
{}

void MyQGLWidget::initializeGL()
{
}

void MyQGLWidget::resizeGL(int w, int h)
{
    if (Display::IsRetinaDisplay())
    {
        w >>= 1;
        h >>= 1;
    }

    if (!mLazyInit)
    {
        mLazyInit = true;

        EGLView* view = EGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        Director* director = Director::sharedDirector();
        director->setContentScaleFactor(1);
        director->setProjection(kDirectorProjection2D);
        //director->setDisplayStats(true);
        director->setOpenGLView(view);

        connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
        mTimer.start();

        CCLOG("QT: Initialized cocos director\n");

        Scene* scene = Scene::create();
        director->pushScene(scene);

        setMouseTracking(true);
    }

    EGLView* view = EGLView::sharedOpenGLView();
    view->setFrameSize(w, h);
    view->setDesignResolutionSize(w, h, kResolutionNoBorder);

    CCLOG("QT: setting frame size to %d, %d\n", w, h);
}

void MyQGLWidget::paintGL()
{
#define NORM(x) ((float)x / 255.f)
    glClearColor(NORM(84), NORM(124), NORM(196), 1);
    Director::sharedDirector()->drawScene();
    MySceneEditor::instance()->drawOverlay();
}

void MyQGLWidget::mousePressEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mousePressed(event->localPos().x(), this->height() - event->localPos().y());
    //qDebug("mousePressEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}

void MyQGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mouseRelease(event->localPos().x(), this->height() - event->localPos().y());
    //qDebug("mouseReleaseEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}

void MyQGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mouseMoved(event->localPos().x(), this->height() - event->localPos().y());
    //qDebug("mouseMoveEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}

void MyQGLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->orientation() == Qt::Vertical)
    {
        float step = (float)event->delta() / 3500.f;
        Node* root = Director::sharedDirector()->getRunningScene();
        if (root)
        {
            float scale = root->getScale();
            root->setScale(scale + step);
        }
    }
}

