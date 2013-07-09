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

        EGLView* view = EGLView::sharedOpenGLView();
        view->setFrameSize(mWidth, mHeight);

        Director* director = Director::sharedDirector();
        director->setContentScaleFactor(1);
        director->setProjection(kDirectorProjection2D);
        director->setDisplayStats(true);
        director->setOpenGLView(view);

        glClearColor(0, 0, 0, 1);

        std::vector<std::string> searchPaths;
        searchPaths.push_back(std::string("/Users/jgraham/dev_casino3/Assets/ccbResources/Bingo/resources-auto"));
        FileUtils* fileUtils = FileUtils::sharedFileUtils();
        fileUtils->setSearchPaths(searchPaths);

        Scene* scene = Scene::create();
        director->pushScene(scene);

        Sprite* sprite = Sprite::create("bingo_called_bingo.png");
        if (sprite)
        {
            sprite->setPosition(ccp(mWidth/2, mHeight/2));
            scene->addChild(sprite);

            RepeatForever* action = RepeatForever::create(Sequence::create(ScaleTo::create(.5f, -1, 1), ScaleTo::create(.5f, 1, 1), 0));
            sprite->runAction(action);
        }
    }

    while (mbRender)
    {
        Director::sharedDirector()->drawScene();
    }
}

void MyGLThread::stop()
{
    mbRender = false;
}
