
#include "componentbase.h"
#include "nodedriver.h"
#include "nodeitem.h"

void ComponentBase::RegisterDrivers()
{
    // Does Nothing
}

void ComponentBase::AddDriver(uint32_t driverId, INodeDriver *driver)
{
    qDebug("register driver %s", driver->Name());
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
