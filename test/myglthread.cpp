#include "myglthread.h"
#include "myqglwidgetthreaded.h"
#include "myeglview.h"

#include "cocos2d.h"
#include "CCDirector.h"
#include "CCFileUtilsMac.h"

#include <vector>

USING_NS_CC;

MyGLThread::MyGLThread(MyQGLWidgetThreaded* glWidget)
    : QThread()
    , mbInitialized(false)
    , mbRender(true)
    , mGLWidget(glWidget)
{
}

void MyGLThread::resizeViewport(int width, int height)
{
    mWidth  = width;
    mHeight = height;
}

void MyGLThread::run()
{
    mGLWidget->makeCurrent();

    if (!mbInitialized)
    {
        mbInitialized = true;

        CCEGLView* view = CCEGLView::sharedOpenGLView();
        view->setFrameSize(mWidth, mHeight);

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

        CCScene* scene = CCScene::create();
        director->pushScene(scene);

        CCSprite* sprite = CCSprite::create("bingo_called_bingo.png");
        if (sprite)
        {
            sprite->setPosition(ccp(mWidth/2, mHeight/2));
            scene->addChild(sprite);

            CCRepeatForever* action = CCRepeatForever::create(CCSequence::create(CCScaleTo::create(.5f, -1, 1), CCScaleTo::create(.5f, 1, 1), 0));
            sprite->runAction(action);
        }
    }

    while (mbRender)
    {
        CCDirector::sharedDirector()->drawScene();
    }
}

void MyGLThread::stop()
{
    mbRender = false;
}
