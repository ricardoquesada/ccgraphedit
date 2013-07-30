
#pragma once

#include "CCClassRegistry.h"

#include <QTreeWidgetItem>
#include <QTreeWidget>

#include <map>

class QWidget;
class QTreeWidget;
namespace cocos2d {
    class Node;
}

#define CONNECT_FIELD(tree, parent, name, widget, node, var, method) \
    { \
        QTreeWidgetItem* item = new QTreeWidgetItem; \
        parent->addChild(item); \
        item->setText(0, QString(name)); \
        widget* w = new widget(tree); \
        tree->setItemWidget(item, 1, w); \
        NodeDriverT<widget, node, var>* driver = new NodeDriverT<widget, node, var>((void (node::*)(const var&))&node::method, w); \
        AddNodeDriver(w, fnv1_32(name), driver); \
    }

class INodeDriver
{
public:
    virtual void Push() = 0;
    virtual QWidget* Widget() = 0;
};

template <class widgetT, class nodeT, typename varT>
class NodeDriverT
    : public INodeDriver
{
public:

    typedef std::function<void(nodeT*, const varT&)> tSetter;

    NodeDriverT(tSetter setter, widgetT* widget)
        : mSetter(setter)
        , mWidget(widget)
    {}

    void Push()
    {
        mSetter(mNode, mWidget->Value());
    }

    QWidget* Widget()
    {
        return mWidget;
    }

    void setValue(const varT& value)
    {
        mSetter(mNode, value);
    }

protected:

    tSetter  mSetter;
    nodeT*   mNode;
    widgetT* mWidget;
};

class ComponentBase
{
public:
    virtual void Populate(QTreeWidget* tree, QTreeWidgetItem* parent, cocos2d::Node* node);

    // connect a widget with a node driver
    void AddNodeDriver(QWidget* widget, uint32_t nameHash, INodeDriver* driver);

    // given a widget, push its value to a node setter
    void Push(QWidget* widget);

    // find a driver by its name hash
    INodeDriver* FindDriverByHash(uint32_t nameHash);

protected:

    typedef std::map<QWidget*, INodeDriver*> tWidgetToDriverMap;
    tWidgetToDriverMap mWidgetToDriverMap;

    typedef std::map<uint32_t, INodeDriver*> tNameToDriverMap;
    tNameToDriverMap mNameToDriverMap;
};
