
#pragma once

#include <map>
#include <vector>

class QTreeWidget;
namespace cocos2d {
    class Node;
}
class NodeItem;
class INodeDriver;

class IComponent
{
public:
    virtual void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node) = 0;
    virtual void RegisterDrivers() = 0;
    virtual INodeDriver* GetDriver(uint32_t id) = 0;
};

#define SETTER(classT, varT, setter) [] (classT* node, const varT& value) { node->setter(value); }
#define GETTER(classT, varT, getter) [] (classT* node, varT& value) { value = node->getter(); }

#define REGISTER_DRIVER(name, widgetT, classT, varT, setter, getter, increment) \
    AddDriver(NodeDriverT<widgetT, classT, varT>::create(name, SETTER(classT, varT, setter), GETTER(classT, varT, getter), increment))

class ComponentBase
    : public IComponent
{
public:

    void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node);
    void RegisterDrivers();
    INodeDriver* GetDriver(uint32_t id);

protected:

    void AddDriver(INodeDriver* driver);

protected:

    typedef std::map<uint32_t, INodeDriver*> tDriverMap;
    tDriverMap mDriverMap;

    typedef std::vector<INodeDriver*> tDriverArray;
    tDriverArray mDriverArray;
};

