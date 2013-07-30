#pragma once

class QTreeWidgetItem;
namespace cocos2d {
    class Node;
}

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

protected:

    QTreeWidgetItem* mSceneItem;
    QTreeWidgetItem* mPropertyItem;
    cocos2d::Node*   mNode;
};
