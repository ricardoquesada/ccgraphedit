
#include "componentbase.h"
#include "nodedriver.h"
#include "nodeitem.h"
#include "ccTypeInfo.h"

USING_NS_CC;

void ComponentBase::RegisterDrivers()
{
    // Does Nothing
}

void ComponentBase::AddDriver(INodeDriver* driver)
{
    uint32_t driverId = fnv1_32(driver->Name());
    mDriverMap.insert(tDriverMap::value_type(driverId, driver));
    mDriverArray.push_back(driver);
}

void ComponentBase::Populate(NodeItem *nodeItem, QTreeWidget *tree, cocos2d::Node *node)
{
    tDriverArray::iterator it(mDriverArray.begin()), itEnd(mDriverArray.end());
    for (; it != itEnd; ++it)
    {
        INodeDriver* driver = (*it)->Clone();
        driver->SetNode(node);
        nodeItem->AddDriver(driver);
    }
}
