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

    // specify the item in the scene graph tree view
    void SetSceneItem(QTreeWidgetItem* item);
    QTreeWidgetItem* SceneItem() const;

    // specify the item in the property tree view
    void SetPropertyItem(QTreeWidgetItem* item);
    QTreeWidgetItem* PropertyItem() const;

    // specify the node managed by this node item
    void SetNode(cocos2d::Node* node);
    cocos2d::Node* GetNode() const;

    // add a node property driver to this node item
    void AddDriver(INodeDriver* driver);

    // create the widgets and connect them to drivers
    void CreateWidgets(QTreeWidget* tree);

    // disconnect widgets from drivers
    void DestroyWidgets();

    // given a widget, push its value to a node setter
    void Push(QWidget* widget);

    // find a driver by its name hash
    INodeDriver* FindDriverByHash(uint32_t nameHash);

    // find a driver by its widget
    INodeDriver* FindDriverByWidget(QWidget* widget);

    // retrieve the node property drivers for this node
    typedef std::vector<INodeDriver*> tNodeDrivers;
    const tNodeDrivers& Drivers() const;

protected:

    QTreeWidgetItem* mSceneItem;
    QTreeWidgetItem* mPropertyItem;
    cocos2d::Node*   mNode;

    // maps a widget instance to a driver
    typedef std::map<QWidget*, INodeDriver*> tWidgetToDriverMap;
    tWidgetToDriverMap mWidgetToDriverMap;

    // maps a name hash to a driver
    typedef std::map<uint32_t, INodeDriver*> tNameToDriverMap;
    tNameToDriverMap mNameToDriverMap;

    // array of widgets associated with this node
    typedef std::vector<QTreeWidgetItem*> tTreeWidgetItemsArray;
    tTreeWidgetItemsArray mTreeWidgetItemsArray;

    // array of drivers associated with this node
    tNodeDrivers mNodeDrivers;
};
