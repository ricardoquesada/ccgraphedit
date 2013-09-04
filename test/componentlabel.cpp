#include "componentlabel.h"
#include "widgetmisc.h"
#include "widgetSize.h"
#include "nodedriver.h"

USING_NS_CC;

void ComponentLabelTTF::RegisterDrivers()
{
    ComponentSprite::RegisterDrivers();
    REGISTER_DRIVER("dimensions", widgetSize, LabelTTF, Size, setDimensions, getDimensions, 1);

    {
        auto setter = [] (LabelTTF* node, const std::string& value)
        {
            node->setString(value.c_str());
        };
        AddDriver(NodeDriverT<widgetString, LabelTTF, std::string>::create("text", setter, nullptr));
    }
}

void ComponentLabelBMF::RegisterDrivers()
{
    ComponentNode::RegisterDrivers();
}
