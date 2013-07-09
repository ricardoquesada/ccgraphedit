#ifndef MYSCENEEDITOR_H
#define MYSCENEEDITOR_H

#include "cocos2d.h"

class kmVec3;
class QGLWidget;

class MySceneEditor
{
public:

    MySceneEditor();

    static MySceneEditor* __instance;
    static MySceneEditor* instance()
    {
        if (!__instance)
            __instance = new MySceneEditor;
        return __instance;
    }

    void mousePressed(float x, float y);
    void mouseRelease(float x, float y);
    void mouseMoved(float x, float y);

    void drawOverlay();

    void drawOrigin(cocos2d::Node* node, const cocos2d::Point& origin, float size = 10);
    void drawRect(cocos2d::Node* node, const cocos2d::Rect& rect, bool solid = false, const cocos2d::ccColor4F* color = 0);
    void drawHandles(cocos2d::Node* node);

    cocos2d::Node* PickNode(const cocos2d::Point& point);

protected:

    cocos2d::Node* PickNode(cocos2d::Node* node, const cocos2d::Point& point);
    bool PointInPolygon(const kmVec3* polygon, int numVerts, const kmVec3& point);

protected:

    cocos2d::Node* mSelectedNode;
};

#endif // MYSCENEEDITOR_H
