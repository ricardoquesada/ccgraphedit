#include "componentnode.h"
#include "widgetpoint.h"
#include "widgetnumber.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentNode::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    CONNECT_FIELD(tree, parent, "position", widgetPoint, Node, Point, setPosition);
    CONNECT_FIELD(tree, parent, "anchor point", widgetPoint, Node, Point, setAnchorPoint);
    CONNECT_FIELD(tree, parent, "scale X", widgetFloat, Node, float, setScaleX);
    CONNECT_FIELD(tree, parent, "scale Y", widgetFloat, Node, float, setScaleY);
    CONNECT_FIELD(tree, parent, "rotation X", widgetFloat, Node, float, setRotationX);
    CONNECT_FIELD(tree, parent, "rotation Y", widgetFloat, Node, float, setRotationY);
    CONNECT_FIELD(tree, parent, "skew X", widgetFloat, Node, float, setSkewX);
    CONNECT_FIELD(tree, parent, "skew Y", widgetFloat, Node, float, setSkewX);
    CONNECT_FIELD(tree, parent, "tag", widgetInt, Node, int, setTag);
}
