
#pragma once

#include "cocos2d.h"
#include "Singleton.h"
#include <QObject>

struct kmVec3;
class QGLWidget;

NS_CC_BEGIN

class MySceneEditor
    : public QObject
{
    Q_OBJECT

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

    // specify the selected node in the scene graph
    void SetSelectedNode(cocos2d::Node* node);

    // retrieve the currently selected scene graph node
    cocos2d::Node* GetSelectedNode() const;

    // specify the root node in the graph (only nodes above this will be editable)
    void SetRootNode(cocos2d::Node* root);

    // retrieve the root node
    cocos2d::Node* GetRootNode() const;

    // returns true if node is a child of the root node
    bool IsChildOfRoot(cocos2d::Node* node);

signals:

    void positionChanged(Node* node, Point& position);

protected:

    cocos2d::Node* PickNode(cocos2d::Node* node, const cocos2d::Point& point);
    bool PointInPolygon(const kmVec3* polygon, int numVerts, const kmVec3& point);
    void IncludeParentTransforms(cocos2d::Node* node);

protected:

    cocos2d::Point mTouchDown;
    cocos2d::Point mTouchLast;
    cocos2d::Point mOffset;
    cocos2d::Node* mRootNode;
    cocos2d::Node* mSelectedNode;
    bool mDragging;
};

NS_CC_END
