
#include "nodeitem.h"
#include "NodeDriver.h"
#include "componentbase.h"
#include "cocos2d.h"
#include <QTreeWidgetItem>

USING_NS_CC;

NodeItem::NodeItem()
    : mSceneItem(nullptr)
    , mPropertyItem(nullptr)
    , mNode(nullptr)
{}

void NodeItem::SetSceneItem(QTreeWidgetItem* item)
{
    if (mSceneItem)
        mSceneItem->setData(0, Qt::UserRole, QVariant((qlonglong)0));
    mSceneItem = item;
    mSceneItem->setData(0, Qt::UserRole, QVariant((qlonglong)this));
}

QTreeWidgetItem* NodeItem::SceneItem() const
{
    return mSceneItem;
}

void NodeItem::SetPropertyItem(QTreeWidgetItem* item)
{
    if (mPropertyItem)
        mPropertyItem->setData(0, Qt::UserRole, QVariant((qlonglong)0));
    mPropertyItem = item;
    mPropertyItem->setData(0, Qt::UserRole, QVariant((qlonglong)this));
}

QTreeWidgetItem* NodeItem::PropertyItem() const
{
    return mPropertyItem;
}

void NodeItem::SetNode(Node* node)
{
    mNode = node;
}

cocos2d::Node* NodeItem::GetNode() const
{
    return mNode;
}

void NodeItem::AddDriver(INodeDriver* driver)
{
    uint32_t nameHash = fnv1_32(driver->Name());
    mNameToDriverMap.insert(tNameToDriverMap::value_type(nameHash, driver));
    mNodeDrivers.push_back(driver);
}

void NodeItem::CreateWidgets(QTreeWidget* tree)
{
    mTreeWidgetItemsArray.clear();

    tNodeDrivers::iterator it(mNodeDrivers.begin()), itEnd(mNodeDrivers.end());
    for (; it != itEnd; ++it)
    {
        INodeDriver* driver = *it;
        driver->SetupWidgets(tree);
        mTreeWidgetItemsArray.push_back(driver->Item());
        mWidgetToDriverMap.insert(tWidgetToDriverMap::value_type(driver->Widget(), driver));
    }
}

void NodeItem::DestroyWidgets()
{
    // Only the item needs to be destroyed, the widget is owned by the tree widget once setItemWidget is called
    tTreeWidgetItemsArray::iterator it(mTreeWidgetItemsArray.begin()), itEnd(mTreeWidgetItemsArray.end());
    for (; it != itEnd; ++it)
    {
        QTreeWidgetItem* item = *it;
        delete item;
    }
    mTreeWidgetItemsArray.clear();
    mWidgetToDriverMap.clear();
}

void NodeItem::Push(QWidget* widget)
{
    tWidgetToDriverMap::iterator it(mWidgetToDriverMap.begin()), itEnd(mWidgetToDriverMap.end());
    for (; it != itEnd; ++it)
    {
        INodeDriver* driver = (*it).second;
        if (driver->Widget() == widget)
            driver->Push();
        else
            driver->Update();
    }
}

INodeDriver* NodeItem::FindDriverByHash(uint32_t nameHash)
{
    tNameToDriverMap::iterator it = mNameToDriverMap.find(nameHash);
    return it == mNameToDriverMap.end() ? nullptr : (*it).second;
}

INodeDriver* NodeItem::FindDriverByWidget(QWidget* widget)
{
    tWidgetToDriverMap::iterator it = mWidgetToDriverMap.find(widget);
    return it == mWidgetToDriverMap.end() ? nullptr : (*it).second;
}

const NodeItem::tNodeDrivers& NodeItem::Drivers() const
{
    return mNodeDrivers;
}
