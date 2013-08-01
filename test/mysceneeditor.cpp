#include "mysceneeditor.h"
#include "cocos2d.h"
#include "kazmath/GL/matrix.h"
#include "kazmath/vec3.h"
#include "fileutil.h"

#include <QDebug>

USING_NS_CC;

IMPLEMENT_SINGLETON(MySceneEditor)

MySceneEditor::MySceneEditor()
    : mRootNode(nullptr)
    , mSelectedNode(nullptr)
    , mDragging(false)
{
}

void MySceneEditor::mousePressed(float x, float y)
{
    mTouchDown = mTouchLast = ccp(x, y);
    mSelectedNode = PickNode(ccp(x, y));
    if (mSelectedNode && mSelectedNode->getParent())
    {
        Point p = mSelectedNode->getParent()->convertToNodeSpace(ccp(x, y));
        mOffset = ccpSub(p, mSelectedNode->getPosition());
    }
    mDragging = true;
}

void MySceneEditor::mouseRelease(float x, float y)
{
    mTouchLast = ccp(x, y);
    mDragging = false;
}

void MySceneEditor::mouseMoved(float x, float y)
{
    if (mDragging)
    {
        if (mSelectedNode)
        {
            Node* parent = mSelectedNode->getParent();
            if (parent)
            {
                Point p = parent->convertToNodeSpace(ccp(x, y));
                p = ccpSub(p, mOffset);
                if (ccpLengthSQ(ccpSub(p, mSelectedNode->getPosition())) > FLT_EPSILON)
                {
                    emit positionChanged(mSelectedNode, p);
                }
                mSelectedNode->setPosition(p);
            }
        }
        else
        {
            Node* scene = Director::sharedDirector()->getRunningScene();
            Point diff = ccpSub(ccp(x, y), mTouchLast);
            Point p = scene->getPosition();
            p = ccpAdd(p, diff);
            scene->setPosition(p);
        }

        mTouchLast = ccp(x, y);
    }
}

void MySceneEditor::drawOverlay()
{
    // disallow drawing of the main scene nodes
    if (!IsChildOfRoot(mSelectedNode))
        return;

    if (mSelectedNode)
    {
        Rect rc;
        rc.origin = PointZero;
        rc.size   = mSelectedNode->getContentSize();
        drawRect(mSelectedNode, rc);

        drawOrigin(mSelectedNode, mSelectedNode->getAnchorPointInPoints());

        drawHandles(mSelectedNode);
    }
}

void MySceneEditor::drawOrigin(Node* node, const Point& origin, float size)
{
    const Point lines[] = {
        node->convertToWorldSpace(ccp(origin.x, origin.y + size)),
        node->convertToWorldSpace(ccp(origin.x, origin.y - size)),
        node->convertToWorldSpace(ccp(origin.x - size, origin.y)),
        node->convertToWorldSpace(ccp(origin.x + size, origin.y))
    };
    ccDrawLine(lines[0], lines[1]);
    ccDrawLine(lines[2], lines[3]);
}

void MySceneEditor::drawRect(Node* node, const Rect& rect, bool solid, const ccColor4F* color)
{
    float l(rect.origin.x), b(rect.origin.y);
    float r(l + rect.size.width), t(b + rect.size.height);

    const Point points[] = {
        node->convertToWorldSpace(ccp(l, b)),
        node->convertToWorldSpace(ccp(r, b)),
        node->convertToWorldSpace(ccp(r, t)),
        node->convertToWorldSpace(ccp(l, t))
    };
    if (solid)
    {
        ccColor4F temp = {1,1,1,1};
        if (!color)
            color = &temp;
        ccDrawSolidPoly(points, 4, *color);
    }
    else
        ccDrawPoly(points, 4, true);
}

void MySceneEditor::drawHandles(Node* node)
{
    const float kHandleSize = 5;
    #define RectAtPoint(p,hs) Rect(p.x-hs,p.y-hs,hs+hs,hs+hs)
    Size size = node->getContentSize();
    drawRect(node, RectAtPoint(Point(0,         0), kHandleSize),           true);
    drawRect(node, RectAtPoint(Point(size.width,0), kHandleSize),           true);
    drawRect(node, RectAtPoint(Point(size.width,size.height), kHandleSize), true);
    drawRect(node, RectAtPoint(Point(0,         size.height), kHandleSize), true);
}

Node* MySceneEditor::PickNode(const Point& point)
{
    kmGLMatrixMode(KM_GL_MODELVIEW);

    kmGLPushMatrix();
    kmGLLoadIdentity();

    // build transform from scene
    IncludeParentTransforms(mRootNode);

    Node* node = PickNode(mRootNode, point);

    kmGLPopMatrix();

    return node;
}

void MySceneEditor::SetSelectedNode(Node* node)
{
    mSelectedNode = node;
}

Node* MySceneEditor::GetSelectedNode() const
{
    return mSelectedNode;
}

void MySceneEditor::SetRootNode(cocos2d::Node* root)
{
    mRootNode = root;
}

cocos2d::Node* MySceneEditor::GetRootNode() const
{
    return mRootNode;
}

bool MySceneEditor::IsChildOfRoot(Node* node)
{
    while (node)
    {
        Node* parent = node->getParent();
        if (parent == mRootNode)
            return true;
        node = parent;
    }
    return false;
}

//
// Protected Methods
//

Node* MySceneEditor::PickNode(Node* node, const Point& point)
{
    if (!node)
        return 0;

    kmGLPushMatrix();

    node->transform();

    Array* children = node->getChildren();
    if (children)
    {
        Object* object;
        CCARRAY_FOREACH_REVERSE(children, object)
        {
            Node* child = (Node*)object;
            child = PickNode(child, point);
            if (child)
            {
                kmGLPopMatrix();
                return child;
            }
        }
    }

    kmMat4 matrixMV;
    kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);

    kmGLPopMatrix();

    Size s = node->getContentSize();

//#define USE_INVERSE_TRANSFORM
#ifdef USE_INVERSE_TRANSFORM
    kmVec3 p;
    p.x = point.x;
    p.y = point.y;
    p.z = 0;

    kmVec3 localPoint;
    kmVec3InverseTransform(&localPoint, &p, &matrixMV);

    bool outside = localPoint.x < 0 ||
                   localPoint.y < 0 ||
                   localPoint.x > s.width ||
                   localPoint.y > s.height;

    return outside ? 0 : node;
#else
    kmVec3 verts[4] = {{0, s.height, 0}, {s.width, s.height, 0}, {s.width, 0, 0}, {0, 0, 0}};
    for (int i = 0; i < 4; ++i)
        kmVec3Transform(&verts[i], &verts[i], &matrixMV);

    kmVec3 p;
    p.x = point.x;
    p.y = point.y;
    p.z = 0;
    bool inside = PointInPolygon(verts, 4, p);

    return inside ? node : 0;
#endif
}

bool MySceneEditor::PointInPolygon(const kmVec3* polygon, int numVerts, const kmVec3& point)
{
    int counter = 0;
    float xinters;
    const kmVec3* p1;
    const kmVec3* p2;

    p1 = &polygon[0];
    for (int i = 1; i <= numVerts; ++i)
    {
        p2 = &polygon[i % numVerts];
        if (point.y > MIN(p1->y, p2->y)) {
            if (point.y <= MAX(p1->y, p2->y)) {
                if (point.x <= MAX(p1->x, p2->x)) {
                    if (p1->y != p2->y) {
                        xinters = (point.y - p1->y) * (p2->x - p1->x) / (p2->y - p1->y) + p1->x;
                        if (p1->x == p2->x || point.x <= xinters)
                            counter++;
                    }
                }
            }
        }
        p1 = p2;
    }

    return counter % 2 != 0;
}

void MySceneEditor::IncludeParentTransforms(Node* node)
{
    if (node->getParent())
        IncludeParentTransforms(node->getParent());
    node->transform();
}
