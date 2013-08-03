
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

#define SETTER(classT, varT, setter) [] (classT* node, const varT& value) { node->setter(value); }
#define GETTER(classT, varT, getter) [] (classT* node, varT& value) { value = node->getter(); }

#define ADD_FIELD(tree, parent, name, widgetT, classT, node, varT, setter, getter, increment) \
        connectFieldT<widgetT, classT, varT>(this, tree, parent, name, node, SETTER(classT, varT, setter), GETTER(classT, varT, getter), increment)

class INodeDriver
{
public:
    virtual void Push() = 0;
    virtual QWidget* Widget() const = 0;
    virtual cocos2d::Node* Node() const = 0;
};

template <class widgetT, class nodeT, typename varT>
class NodeDriverT
    : public INodeDriver
{
public:

    NodeDriverT(void (*setter)(nodeT*, const varT&), void (*getter)(nodeT*, varT&), nodeT* node, widgetT* widget)
        : mSetter(setter)
        , mGetter(getter)
        , mNode(node)
        , mWidget(widget)
    {}

    void Push()
    {
        mSetter(mNode, mWidget->Value());
    }

    QWidget* Widget() const
    {
        return mWidget;
    }

    cocos2d::Node* Node() const
    {
        return mNode;
    }

    void SetValue(const varT& value)
    {
        mSetter(mNode, value);
    }

protected:

    std::function<void(nodeT*, const varT&)> mSetter;
    std::function<void(nodeT*, varT&)> mGetter;
    nodeT*   mNode;
    widgetT* mWidget;
};

class ComponentBase
{
public:
    virtual void Populate(QTreeWidget* tree, QTreeWidgetItem* parent, cocos2d::Node* node);

    // connect a widget with a node driver
    void AddNodeDriver(QTreeWidgetItem* item, QWidget* widget, uint32_t nameHash, INodeDriver* driver);

    // destroy items and node drivers
    void DestroyAll();

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

    typedef std::vector<QTreeWidgetItem*> tTreeWidgetItemsArray;
    tTreeWidgetItemsArray mTreeWidgetItemsArray;
};

template <class widgetT, class nodeT, typename varT, class componentT = ComponentBase>
NodeDriverT<widgetT, nodeT, varT>* connectFieldT(componentT* component, QTreeWidget* tree, QTreeWidgetItem* parent, const char* name, cocos2d::Node* node, void (*setter)(nodeT*, const varT&), void (*getter)(nodeT*, varT&), float increment = 1)
{
    QTreeWidgetItem* item = new QTreeWidgetItem;
    item->setText(0, QString(name));
    parent->addChild(item);

    widgetT* w = new widgetT(tree);
    w->SetIncrement(increment);
    w->setProperty("node", QVariant((qlonglong)node));
    item->setData(0, Qt::UserRole, QVariant((qlonglong)w));

    nodeT* instance = dynamic_cast<nodeT*>(node);
    assert(nullptr != instance);
    varT value;
    getter(instance, value);
    w->SetValue(value);
    tree->setItemWidget(item, 1, w);

    typedef NodeDriverT<widgetT, nodeT, varT> tNodeDriver;
    tNodeDriver* driver = new tNodeDriver(setter, getter, instance, w);

    component->AddNodeDriver(item, w, cocos2d::fnv1_32(name), driver);

    QObject::connect(w, SIGNAL(widgetChanged(QWidget*)), cocos2d::MainWindow::instance(), SLOT(pushWidget(QWidget*)));

    return driver;
}
