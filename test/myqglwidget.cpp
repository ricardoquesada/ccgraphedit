#include "myqglwidget.h"
#include "myeglview.h"
#include "mysceneeditor.h"

#include <QDebug>

#include "cocos2d.h"
#include "CCDirector.h"
#include "CCFileUtilsMac.h"

#include <vector>

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
    w >>= 1;
    h >>= 1;

    if (!mLazyInit)
    {
        mLazyInit = true;

        CCEGLView* view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(w, h);

        CCDirector* director = CCDirector::sharedDirector();
        director->setContentScaleFactor(1);
        director->setProjection(kCCDirectorProjection2D);
        director->setDisplayStats(true);
        director->setOpenGLView(view);

        glClearColor(0, 0, 0, 1);

        std::vector<std::string> searchPaths;
        searchPaths.push_back(std::string("/Users/jgraham/dev_casino3/Assets/ccbResources/Bingo/resources-auto"));
        CCFileUtils* fileUtils = CCFileUtils::sharedFileUtils();
        fileUtils->setSearchPaths(searchPaths);

        connect(&mTimer, SIGNAL(timeout()), this, SLOT(updateGL()));
        mTimer.start();

        CCLOG("QT: Initialized cocos director\n");

        CCScene* scene = CCScene::create();
        director->pushScene(scene);

        CCSprite* sprite = CCSprite::create("bingo_called_bingo.png");
        if (sprite)
        {
            sprite->setPosition(ccp(w/2, h/2));
            scene->addChild(sprite);

            CCRepeatForever* action = CCRepeatForever::create(CCSequence::create(CCScaleTo::create(.5f, -1, 1), CCScaleTo::create(.5f, 1, 1), 0));
            sprite->runAction(action);
        }

        setMouseTracking(true);
    }

    CCLOG("QT: setting frame size to %d, %d\n", w, h);
}

void MyQGLWidget::paintGL()
{
    CCDirector::sharedDirector()->drawScene();
    MySceneEditor::instance()->drawOverlay();
}

void MyQGLWidget::mousePressEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mousePressed(event->localPos().x(), this->height() - event->localPos().y());
    qDebug("mousePressEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}

void MyQGLWidget::mouseReleaseEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mouseRelease(event->localPos().x(), this->height() - event->localPos().y());
    qDebug("mouseReleaseEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}

void MyQGLWidget::mouseMoveEvent(QMouseEvent* event)
{
    MySceneEditor::instance()->mouseMoved(event->localPos().x(), this->height() - event->localPos().y());
    qDebug("mouseMoveEvent %.2f, %.2f", event->localPos().x(), this->height() - event->localPos().y());
}
