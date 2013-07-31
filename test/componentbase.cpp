#include "componentbase.h"
#include "cocos2d.h"

USING_NS_CC;

void ComponentBase::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    // Does Nothing
}

void ComponentBase::AddNodeDriver(QTreeWidgetItem* item, QWidget* widget, uint32_t nameHash, INodeDriver* driver)
{
    mTreeWidgetItemsArray.push_back(item);
    mWidgetToDriverMap.insert(tWidgetToDriverMap::value_type(widget, driver));
    mNameToDriverMap.insert(tNameToDriverMap::value_type(nameHash, driver));
}

void ComponentBase::DestroyAll()
{
    // Only the item needs to be destroyed, the widget is owned by the tree widget once setItemWidget is called
    {
        tTreeWidgetItemsArray::iterator it(mTreeWidgetItemsArray.begin()), itEnd(mTreeWidgetItemsArray.end());
        for (; it != itEnd; ++it)
        {
            QTreeWidgetItem* item = *it;
            delete item;
        }
        mTreeWidgetItemsArray.clear();
    }

    {
        tWidgetToDriverMap::iterator it(mWidgetToDriverMap.begin()), itEnd(mWidgetToDriverMap.end());
        for (; it != itEnd; ++it)
        {
            INodeDriver* driver = (*it).second;
            delete driver;
        }
        mWidgetToDriverMap.clear();
    }

    mNameToDriverMap.clear();
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
