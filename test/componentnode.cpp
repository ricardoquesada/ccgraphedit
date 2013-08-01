#include "componentnode.h"
#include "widgetpoint.h"
#include "widgetSize.h"
#include "widgetnumber.h"
#include "widgetmisc.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentNode::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    //CONNECT_FIELD(tree, parent, "position",     widgetPoint, Node, node, Point, setPosition,    getPosition,    1);
    CONNECT_FIELD(tree, parent, "anchor point", widgetPoint, Node, node, Point, setAnchorPoint, getAnchorPoint, 0.05f);
    CONNECT_FIELD(tree, parent, "z order",      widgetInt,   Node, node, int,   setZOrder,      getZOrder,      1);
    CONNECT_FIELD(tree, parent, "vertex z",     widgetFloat, Node, node, float, setVertexZ,     getVertexZ,     1);
    CONNECT_FIELD(tree, parent, "content size", widgetSize,  Node, node, Size,  setContentSize, getContentSize, 1);
    CONNECT_FIELD(tree, parent, "scale X",      widgetFloat, Node, node, float, setScaleX,      getScaleX,      0.1f);
    CONNECT_FIELD(tree, parent, "scale Y",      widgetFloat, Node, node, float, setScaleY,      getScaleY,      0.1f);
    CONNECT_FIELD(tree, parent, "rotation",     widgetFloat, Node, node, float, setRotation,    getRotation,    0.5f);
    CONNECT_FIELD(tree, parent, "skew X",       widgetFloat, Node, node, float, setSkewX,       getSkewX,       0.5f);
    CONNECT_FIELD(tree, parent, "skew Y",       widgetFloat, Node, node, float, setSkewY,       getSkewY,       0.5f);
    CONNECT_FIELD(tree, parent, "visible",      widgetBool,  Node, node, bool,  setVisible,     isVisible,      1);
    CONNECT_FIELD(tree, parent, "tag",          widgetInt,   Node, node, int,   setTag,         getTag,         1);
}
