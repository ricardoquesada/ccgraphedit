#include "componentnodergba.h"
#include "NodeDriver.h"
#include "nodeitem.h"
#include "widgetmisc.h"
#include "cocos2d.h"

USING_NS_CC;

void ComponentNodeRGBA::RegisterDrivers()
{
    ComponentNode::RegisterDrivers();
    REGISTER_DRIVER("cascade color",    widgetBool,   NodeRGBA, bool,       setCascadeColorEnabled,   isCascadeColorEnabled,   1);
    REGISTER_DRIVER("cascade opacity",  widgetBool,   NodeRGBA, bool,       setCascadeOpacityEnabled, isCascadeOpacityEnabled, 1);
    REGISTER_DRIVER("color",            widgetColor3, NodeRGBA, _ccColor3B, setColor,                 getColor,                1);
}
