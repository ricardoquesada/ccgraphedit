
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
    qDebug("Added driver %08x %s", driver->Id(), driver->Name());
    mDriverMap.insert(tDriverMap::value_type(driver->Id(), driver));
    mDriverArray.push_back(driver);
}

void ComponentBase::Populate(NodeItem *nodeItem, QTreeWidget *tree, cocos2d::Node *node)
{
    tDriverArray::iterator it(mDriverArray.begin()), itEnd(mDriverArray.end());
    for (; it != itEnd; ++it)
    {
        INodeDriver* driver = (*it)->Clone();
        driver->SetNode(node);
        driver->Update();
        nodeItem->AddDriver(driver);
    }
}

INodeDriver* ComponentBase::GetDriver(uint32_t id)
{
    tDriverMap::iterator it = mDriverMap.find(id);
    return it == mDriverMap.end() ? nullptr : (*it).second;
}
