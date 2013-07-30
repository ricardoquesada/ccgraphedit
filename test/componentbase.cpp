#include "componentbase.h"
#include "cocos2d.h"

USING_NS_CC;

void ComponentBase::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    // Does Nothing
}

void ComponentBase::AddNodeDriver(QWidget* widget, INodeDriver* driver)
{
    mWidgetToDriverMap.insert(tWidgetToDriverMap::value_type(widget, driver));
}

void ComponentBase::Push(QWidget* widget)
{
    tWidgetToDriverMap::iterator it = mWidgetToDriverMap.find(widget);
    if (it != mWidgetToDriverMap.end())
    {
        INodeDriver* driver = (*it).second;
        driver->Push();
    }
}
