#pragma once

#include "stdint.h"
#include <map>
#include <vector>

class QWidget;
class QTreeWidget;
class QTreeWidgetItem;
namespace cocos2d {
    class Node;
}
class INodeDriver;

class NodeItem
{
public:

    NodeItem();

    void SetSceneItem(QTreeWidgetItem* item);
    QTreeWidgetItem* SceneItem() const;

    void SetPropertyItem(QTreeWidgetItem* item);
    QTreeWidgetItem* PropertyItem() const;

    void SetNode(cocos2d::Node* node);
    cocos2d::Node* GetNode() const;

    // add a driver to this node item
    void AddDriver(uint32_t nameHash, INodeDriver* driver);

    // create the widgets and connect them to drivers
    void CreateWidgets(QTreeWidget* tree);

    // disconnect widgets from drivers
    void DestroyWidgets();

    // given a widget, push its value to a node setter
    void Push(QWidget* widget);

    // find a driver by its name hash
    INodeDriver* FindDriverByHash(uint32_t nameHash);

    // find a drived by its widget
    INodeDriver* FindDriverByWidget(QWidget* widget);

protected:

    QTreeWidgetItem* mSceneItem;
    QTreeWidgetItem* mPropertyItem;
    cocos2d::Node*   mNode;

    typedef std::map<QWidget*, INodeDriver*> tWidgetToDriverMap;
    tWidgetToDriverMap mWidgetToDriverMap;

    typedef std::map<uint32_t, INodeDriver*> tNameToDriverMap;
    tNameToDriverMap mNameToDriverMap;

    typedef std::vector<QTreeWidgetItem*> tTreeWidgetItemsArray;
    tTreeWidgetItemsArray mTreeWidgetItemsArray;

    typedef std::vector<INodeDriver*> tNodeDrivers;
    tNodeDrivers mNodeDrivers;
};
