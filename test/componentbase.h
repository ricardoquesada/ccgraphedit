
#pragma once

#include "CCClassRegistry.h"
#include "mainwindow.h"
#include <QObject>
#include <QTreeWidgetItem>
#include <QTreeWidget>

#include <map>

class QWidget;
class QTreeWidget;
namespace cocos2d {
    class Node;
}

#define CONNECT_FIELD(tree, parent, name, widget, classT, node, var, method) \
    { \
        QTreeWidgetItem* item = new QTreeWidgetItem; \
        parent->addChild(item); \
        item->setText(0, QString(name)); \
        widget* w = new widget(tree); \
        w->setProperty("node", QVariant((qlonglong)node)); \
        tree->setItemWidget(item, 1, w); \
        classT* instance = dynamic_cast<classT*>(node); \
        assert(nullptr != instance); \
        NodeDriverT<widget, classT, var>* driver = new NodeDriverT<widget, classT, var>((void (classT::*)(const var&))&classT::method, instance, w); \
        AddNodeDriver(w, fnv1_32(name), driver); \
        QObject::connect(w, SIGNAL(widgetChanged(QWidget*)), MainWindow::instance(), SLOT(pushWidget(QWidget*))); \
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

    NodeDriverT(tSetter setter, nodeT* node, widgetT* widget)
        : mSetter(setter)
        , mNode(node)
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

    // find a drived by its widget
    INodeDriver* FindDriverByWidget(QWidget* widget);

protected:

    typedef std::map<QWidget*, INodeDriver*> tWidgetToDriverMap;
    tWidgetToDriverMap mWidgetToDriverMap;

    typedef std::map<uint32_t, INodeDriver*> tNameToDriverMap;
    tNameToDriverMap mNameToDriverMap;
};
