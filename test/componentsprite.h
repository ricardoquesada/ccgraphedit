
#pragma once

#include "componentnodergba.h"

class ComponentSprite
    : public ComponentNodeRGBA
{
public:
    cocos2d::Node* Instantiate(uint32_t classId);
    void RegisterDrivers();
    void Populate(NodeItem *nodeItem, QTreeWidget *tree, cocos2d::Node *node);
    DECLARE_NEW_NODE_NAME("New Sprite")
};

