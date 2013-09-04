#include "componentlabel.h"
#include "widgetmisc.h"
#include "nodedriver.h"

USING_NS_CC;

void ComponentLabelTTF::RegisterDrivers()
{
    ComponentSprite::RegisterDrivers();

    auto setter = [] (LabelTTF* node, const std::string& value)
    {
        qDebug("setString %s\n", value.c_str());
        node->setString(value.c_str());
    };
    AddDriver(NodeDriverT<widgetString, LabelTTF, std::string>::create("text", setter, nullptr));
}

void ComponentLabelBMF::RegisterDrivers()
{
    ComponentNode::RegisterDrivers();
}
