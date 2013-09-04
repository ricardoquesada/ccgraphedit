#include "componentlayer.h"
#include "cocos2d.h"
#include "nodeitem.h"
#include "NodeDriver.h"
#include "widgetpoint.h"
#include "widgetSize.h"
#include "widgetnumber.h"
#include "widgetmisc.h"

USING_NS_CC;

void ComponentLayer::RegisterDrivers()
{
    ComponentNode::RegisterDrivers();
    REGISTER_DRIVER("position", widgetBool, Layer, bool, setTouchEnabled, isTouchEnabled, 1);
}
