#include "componentnode.h"
#include "cocos2d.h"
#include "nodeitem.h"
#include "widgetpoint.h"
#include "widgetSize.h"
#include "widgetnumber.h"
#include "widgetmisc.h"

USING_NS_CC;

void ComponentNode::Populate(NodeItem* nodeItem, QTreeWidget* tree, Node* node)
{
    ADD_FIELD(nodeItem, tree, "position",     widgetPoint, Node, node, Point, setPosition,    getPosition,    1);
    ADD_FIELD(nodeItem, tree, "anchor point", widgetPoint, Node, node, Point, setAnchorPoint, getAnchorPoint, 0.05f);
    ADD_FIELD(nodeItem, tree, "z order",      widgetInt,   Node, node, int,   setZOrder,      getZOrder,      1);
    ADD_FIELD(nodeItem, tree, "vertex z",     widgetFloat, Node, node, float, setVertexZ,     getVertexZ,     1);
    ADD_FIELD(nodeItem, tree, "content size", widgetSize,  Node, node, Size,  setContentSize, getContentSize, 1);
    ADD_FIELD(nodeItem, tree, "scale X",      widgetFloat, Node, node, float, setScaleX,      getScaleX,      0.1f);
    ADD_FIELD(nodeItem, tree, "scale Y",      widgetFloat, Node, node, float, setScaleY,      getScaleY,      0.1f);
    ADD_FIELD(nodeItem, tree, "rotation",     widgetFloat, Node, node, float, setRotation,    getRotation,    0.5f);
    ADD_FIELD(nodeItem, tree, "skew X",       widgetFloat, Node, node, float, setSkewX,       getSkewX,       0.5f);
    ADD_FIELD(nodeItem, tree, "skew Y",       widgetFloat, Node, node, float, setSkewY,       getSkewY,       0.5f);
    ADD_FIELD(nodeItem, tree, "visible",      widgetBool,  Node, node, bool,  setVisible,     isVisible,      1);
    ADD_FIELD(nodeItem, tree, "tag",          widgetInt,   Node, node, int,   setTag,         getTag,         1);
}
