
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
class NodeItem;

#define SETTER(classT, varT, setter) [] (classT* node, const varT& value) { node->setter(value); }
#define GETTER(classT, varT, getter) [] (classT* node, varT& value) { value = node->getter(); }

#define ADD_FIELD(nodeItem, tree, name, widgetT, classT, node, varT, setter, getter, increment) \
        connectFieldT<widgetT, classT, varT>(nodeItem, tree, name, node, SETTER(classT, varT, setter), GETTER(classT, varT, getter), increment)

class INodeDriver
{
public:
    virtual void Push() = 0;
    virtual QTreeWidgetItem* Item() const = 0;
    virtual QWidget* Widget() const = 0;
    virtual cocos2d::Node* Node() const = 0;
    virtual void SetupWidgets(QTreeWidget* tree) = 0;
};

template <class widgetT, class nodeT, typename varT>
class NodeDriverT
    : public INodeDriver
{
public:

    NodeDriverT(void (*setter)(nodeT*, const varT&), void (*getter)(nodeT*, varT&), nodeT* node, const char* name)
        : mSetter(setter)
        , mGetter(getter)
        , mNode(node)
        , mItem(nullptr)
        , mWidget(nullptr)
        , mName(name)
        , mIncrement(1)
    {}

    // this has to be done each time it is added to the tree since the tree takes
    // ownership of it, and there is no way to get it back, so it is recreated.
    void SetupWidgets(QTreeWidget* tree)
    {
        QTreeWidgetItem* parent = tree->invisibleRootItem();

        mItem = new QTreeWidgetItem;
        mItem->setText(0, mName);
        parent->addChild(mItem);

        mWidget = new widgetT(tree);
        mWidget->SetIncrement(mIncrement);
        mWidget->setProperty("node", QVariant((qlonglong)mNode));
        mItem->setData(0, Qt::UserRole, QVariant((qlonglong)mWidget));

        tree->setItemWidget(mItem, 1, mWidget);

        // set the default value
        varT value;
        mGetter(mNode, value);
        mWidget->SetValue(value);

        QObject::connect(mWidget, SIGNAL(widgetChanged(QWidget*)), cocos2d::MainWindow::instance(), SLOT(pushWidget(QWidget*)));
    }

    void SetIncrement(float increment)
    {
        mIncrement = increment;
    }

    void Push()
    {
        mSetter(mNode, mWidget->Value());
    }

    QTreeWidgetItem* Item() const
    {
        return mItem;
    }

    QWidget* Widget() const
    {
        return mWidget;
    }

    cocos2d::Node* Node() const
    {
        return mNode;
    }

    const char* Name() const
    {
        return mName.toUtf8();
    }

    void SetValue(const varT& value)
    {
        mSetter(mNode, value);
    }

protected:

    std::function<void(nodeT*, const varT&)> mSetter;
    std::function<void(nodeT*, varT&)> mGetter;
    nodeT*   mNode;
    QTreeWidgetItem* mItem;
    widgetT* mWidget;
    QString  mName;
    float    mIncrement;
};

class ComponentBase
{
public:

    virtual void Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node) = 0;
};

void AddDriver(NodeItem* nodeItem, uint32_t nameHash, INodeDriver* driver);

template <class widgetT, class nodeT, typename varT, class componentT = ComponentBase>
NodeDriverT<widgetT, nodeT, varT>* connectFieldT(NodeItem* nodeItem, QTreeWidget* tree, const char* name, cocos2d::Node* node, void (*setter)(nodeT*, const varT&), void (*getter)(nodeT*, varT&), float increment = 1)
{
    nodeT* typedNode = dynamic_cast<nodeT*>(node);
    Q_ASSERT(nullptr != typedNode);

    typedef NodeDriverT<widgetT, nodeT, varT> tNodeDriver;
    tNodeDriver* driver = new tNodeDriver(setter, getter, typedNode, name);
    driver->SetIncrement(increment);

    AddDriver(nodeItem, cocos2d::fnv1_32(name), driver);

    return driver;
}
