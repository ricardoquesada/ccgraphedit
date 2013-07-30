#include "componentnode.h"
#include "widgetpoint.h"
#include "widgetnumber.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentNode::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    CONNECT_FIELD(tree, parent, "position", widgetPoint, Node, node, Point, setPosition, getPosition);
    CONNECT_FIELD(tree, parent, "anchor point", widgetPoint, Node, node, Point, setAnchorPoint, getAnchorPoint);
    CONNECT_FIELD(tree, parent, "scale X", widgetFloat, Node, node, float, setScaleX, getScaleX);
    CONNECT_FIELD(tree, parent, "scale Y", widgetFloat, Node, node, float, setScaleY, getScaleY);
    CONNECT_FIELD(tree, parent, "rotation", widgetFloat, Node, node, float, setRotation, getRotation);
    CONNECT_FIELD(tree, parent, "skew X", widgetFloat, Node, node, float, setSkewX, getSkewX);
    CONNECT_FIELD(tree, parent, "skew Y", widgetFloat, Node, node, float, setSkewY, getSkewY);
    CONNECT_FIELD(tree, parent, "tag", widgetInt, Node, node, int, setTag, getTag);
}
