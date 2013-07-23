#ifndef MYSCENEEDITOR_H
#define MYSCENEEDITOR_H

#include "cocos2d.h"
#include "Singleton.h"

class kmVec3;
class QGLWidget;

class MySceneEditor
{
public:

    DECLARE_SINGLETON(MySceneEditor)

    MySceneEditor();

    // mouse input methods
    void mousePressed(float x, float y);
    void mouseRelease(float x, float y);
    void mouseMoved(float x, float y);

    // drawing methods
    void drawOverlay();
    void drawOrigin(cocos2d::Node* node, const cocos2d::Point& origin, float size = 10);
    void drawRect(cocos2d::Node* node, const cocos2d::Rect& rect, bool solid = false, const cocos2d::ccColor4F* color = 0);
    void drawHandles(cocos2d::Node* node);

    // pick the cocos node under point
    cocos2d::Node* PickNode(const cocos2d::Point& point);

    // retrieve the currently selected scene graph node
    cocos2d::Node* GetSelectedNode() const;

protected:

    cocos2d::Node* PickNode(cocos2d::Node* node, const cocos2d::Point& point);
    bool PointInPolygon(const kmVec3* polygon, int numVerts, const kmVec3& point);

protected:

    cocos2d::Node* mSelectedNode;
    bool mDragging;
};

#endif // MYSCENEEDITOR_H
