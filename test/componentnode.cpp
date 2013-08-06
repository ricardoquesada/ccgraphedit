#include "componentnode.h"
#include "cocos2d.h"
#include "nodeitem.h"
#include "NodeDriver.h"
#include "widgetpoint.h"
#include "widgetSize.h"
#include "widgetnumber.h"
#include "widgetmisc.h"

USING_NS_CC;

void ComponentNode::RegisterDrivers()
{
    REGISTER_DRIVER("position",     widgetPoint, Node, Point, setPosition,    getPosition,    1);
    REGISTER_DRIVER("anchor point", widgetPoint, Node, Point, setAnchorPoint, getAnchorPoint, 0.05f);
    REGISTER_DRIVER("z order",      widgetInt,   Node, int,   setZOrder,      getZOrder,      1);
    REGISTER_DRIVER("vertex z",     widgetFloat, Node, float, setVertexZ,     getVertexZ,     1);
    REGISTER_DRIVER("content size", widgetSize,  Node, Size,  setContentSize, getContentSize, 1);
    REGISTER_DRIVER("scale X",      widgetFloat, Node, float, setScaleX,      getScaleX,      0.1f);
    REGISTER_DRIVER("scale Y",      widgetFloat, Node, float, setScaleY,      getScaleY,      0.1f);
    REGISTER_DRIVER("rotation",     widgetFloat, Node, float, setRotation,    getRotation,    0.5f);
    REGISTER_DRIVER("skew X",       widgetFloat, Node, float, setSkewX,       getSkewX,       0.5f);
    REGISTER_DRIVER("skew Y",       widgetFloat, Node, float, setSkewY,       getSkewY,       0.5f);
    REGISTER_DRIVER("visible",      widgetBool,  Node, bool,  setVisible,     isVisible,      1);
    REGISTER_DRIVER("tag",          widgetInt,   Node, int,   setTag,         getTag,         1);
}
