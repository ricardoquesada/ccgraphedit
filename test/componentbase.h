
#pragma once

class QTreeWidget;
namespace cocos2d {
    class Node;
}
class NodeItem;

class IComponentBase
{
public:
    virtual void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node) = 0;
};

