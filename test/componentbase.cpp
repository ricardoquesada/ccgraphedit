
#include "componentbase.h"
#include "nodedriver.h"
#include "nodeitem.h"
#include "ccTypeInfo.h"
#include "CCClassRegistry.h"
#include "CCGeometry.h"

USING_NS_CC;

Node* ComponentBase::Instantiate(uint32_t classId)
{
    Node* node = dynamic_cast<Node*>(CCClassRegistry::instance()->instantiateClass(classId));
    if (!node)
        return nullptr;
    node->setPosition(PointZero);
    return node;
}

void ComponentBase::RegisterDrivers()
{
    // Does Nothing
}

void ComponentBase::AddDriver(INodeDriver* driver)
{
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
    nodeItem->SetName(NewNodeName());
}

INodeDriver* ComponentBase::GetDriver(uint32_t id)
{
    tDriverMap::iterator it = mDriverMap.find(id);
    return it == mDriverMap.end() ? nullptr : (*it).second;
}

const char* ComponentBase::NewNodeName() const
{
    return "INVALID";
}
