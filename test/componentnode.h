
#pragma once

#include "componentbase.h"

class ComponentNode
    : public IComponentBase
{
public:
    void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node);
};


