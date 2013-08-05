
#pragma once

#include "componentnode.h"

class ComponentSprite
    : public ComponentNode
{
public:
    void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node);
};

