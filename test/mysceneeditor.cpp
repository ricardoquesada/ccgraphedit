#include "mysceneeditor.h"
#include "cocos2d.h"
#include "kazmath/GL/matrix.h"
#include "kazmath/vec3.h"

#include <QDebug>

USING_NS_CC;

MySceneEditor* MySceneEditor::__instance = 0;

MySceneEditor::MySceneEditor()
{
}

void MySceneEditor::mousePressed(float x, float y)
{
    CCNode* node = PickNode(ccp(x, y));
    qDebug("Pressed: picked node %p\n", node);
}

void MySceneEditor::mouseRelease(float x, float y)
{
    CCNode* node = PickNode(ccp(x, y));
    qDebug("Released: picked node %p\n", node);
}

void MySceneEditor::mouseMoved(float x, float y)
{
    CCNode* node = PickNode(ccp(x, y));
    qDebug("Moved: picked node %p\n", node);
}

void MySceneEditor::drawOverlay()
{

}

//
// Protected Methods
//

CCNode* MySceneEditor::PickNode(const CCPoint& point)
{
    kmGLMatrixMode(KM_GL_MODELVIEW);

    kmGLPushMatrix();
    kmGLLoadIdentity();

    CCScene* root = CCDirector::sharedDirector()->getRunningScene();
    CCNode* node = PickNode(root, point);

    kmGLPopMatrix();

    return node;
}

CCNode* MySceneEditor::PickNode(CCNode* node, const CCPoint& point)
{
    if (!node)
        return 0;

    node->transform();

    CCArray* children = node->getChildren();
    if (children)
    {
        CCObject* object;
        CCARRAY_FOREACH(children, object)
        {
            CCNode* child = (CCNode*)object;
            child = PickNode(child, point);
            if (child)
                return child;
        }
    }

    kmMat4 matrixMV;
    kmGLGetMatrix(KM_GL_MODELVIEW, &matrixMV);

    CCSize s = node->getContentSize();
    kmVec3 verts[4] = {{0, s.height, 0}, {s.width, s.height, 0}, {s.width, 0, 0}, {0, 0, 0}};
    for (int i = 0; i < 4; ++i)
        kmVec3Transform(&verts[i], &verts[i], &matrixMV);

    kmVec3 p;
    p.x = point.x;
    p.y = point.y;
    p.z = 0;
    bool inside = PointInPolygon(verts, 4, p);

    return inside ? node : 0;
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

