
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
        QWidget* w = new widget(tree); \
        tree->setItemWidget(item, 1, w); \
        AddNodeDriver(w, new NodeDriverT<widget, node, var>((void (node::*)(const var&))&node::method)); \
    }

class INodeDriver
{
public:
    virtual void Push() = 0;
};

template <class widgetT, class nodeT, typename varT>
class NodeDriverT
    : public INodeDriver
{
public:

    typedef std::function<void(nodeT*, const varT&)> tSetter;

    NodeDriverT(tSetter setter)
        : mSetter(setter)
    {}

    void Push()
    {
        mSetter(mNode, mWidget->Value());
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
    void AddNodeDriver(QWidget* widget, INodeDriver* driver);

    // given a widget, push its value to a node setter
    void Push(QWidget* widget);

protected:

    typedef std::map<QWidget*, INodeDriver*> tWidgetToDriverMap;
    tWidgetToDriverMap mWidgetToDriverMap;
};
