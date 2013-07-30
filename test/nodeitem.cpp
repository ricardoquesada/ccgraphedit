
#include "nodeitem.h"
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
