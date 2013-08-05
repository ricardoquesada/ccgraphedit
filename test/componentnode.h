
#pragma once

#include "componentbase.h"

class ComponentNode
    : public ComponentBase
{
public:
    void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node);
};


