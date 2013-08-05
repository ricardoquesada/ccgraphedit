
#include "NodeDriver.h"
#include "cocos2d.h"
#include "nodeitem.h"

USING_NS_CC;

// stub method to avoid having to include NodeItem in header
void AddDriver(NodeItem* nodeItem, uint32_t nameHash, INodeDriver* driver)
{
    nodeItem->AddDriver(nameHash, driver);
}

