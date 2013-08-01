
#pragma once

#include "componentnode.h"

class ComponentSprite
    : public ComponentNode
{
public:
    void Populate(QTreeWidget* tree, QTreeWidgetItem* parent, cocos2d::Node* node);
};

