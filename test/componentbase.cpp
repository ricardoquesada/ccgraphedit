#include "componentbase.h"
#include "cocos2d.h"

USING_NS_CC;

void ComponentBase::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    // Does Nothing
}

void ComponentBase::AddNodeDriver(QWidget* widget, uint32_t nameHash, INodeDriver* driver)
{
    mWidgetToDriverMap.insert(tWidgetToDriverMap::value_type(widget, driver));
    mNameToDriverMap.insert(tNameToDriverMap::value_type(nameHash, driver));
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

INodeDriver* ComponentBase::FindDriverByHash(uint32_t nameHash)
{
    tNameToDriverMap::iterator it = mNameToDriverMap.find(nameHash);
    return it == mNameToDriverMap.end() ? nullptr : (*it).second;
}

INodeDriver* ComponentBase::FindDriverByWidget(QWidget* widget)
{
    tWidgetToDriverMap::iterator it = mWidgetToDriverMap.find(widget);
    return it == mWidgetToDriverMap.end() ? nullptr : (*it).second;
}
