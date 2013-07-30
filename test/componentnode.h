
#pragma once

#include "componentbase.h"

class ComponentNode
    : public ComponentBase
{
public:
    void Populate(QTreeWidget* tree, QTreeWidgetItem* parent, cocos2d::Node* node);
};


