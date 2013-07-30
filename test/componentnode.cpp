#include "componentnode.h"
#include "widgetpoint.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentNode::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    CONNECT_FIELD(tree, parent, "position", widgetPoint, Node, Point, setPosition);
}
