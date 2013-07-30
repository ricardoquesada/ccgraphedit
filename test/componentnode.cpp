#include "componentnode.h"
#include "widgetpoint.h"
#include "widgetnumber.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentNode::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    CONNECT_FIELD(tree, parent, "position", widgetPoint, Node, node, Point, setPosition);
    CONNECT_FIELD(tree, parent, "anchor point", widgetPoint, Node, node, Point, setAnchorPoint);
    CONNECT_FIELD(tree, parent, "scale X", widgetFloat, Node, node, float, setScaleX);
    CONNECT_FIELD(tree, parent, "scale Y", widgetFloat, Node, node, float, setScaleY);
    CONNECT_FIELD(tree, parent, "rotation X", widgetFloat, Node, node, float, setRotationX);
    CONNECT_FIELD(tree, parent, "rotation Y", widgetFloat, Node, node, float, setRotationY);
    CONNECT_FIELD(tree, parent, "skew X", widgetFloat, Node, node, float, setSkewX);
    CONNECT_FIELD(tree, parent, "skew Y", widgetFloat, Node, node, float, setSkewX);
    CONNECT_FIELD(tree, parent, "tag", widgetInt, Node, node, int, setTag);
}
