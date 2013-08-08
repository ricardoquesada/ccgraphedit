#include "mainwindow.h"
#include "mysceneeditor.h"
#include "exporter.h"
#include "nodeitem.h"
#include "NodeDriver.h"
#include "cocos2d.h"
#include "CCStreamFormatted.h"

USING_NS_CC;

// called by editor to begin exporting graph to stream
// allows you to export any preamble you would like.
bool Exporter::ExportToStream(StreamFormatted& stream)
{
    Node* rootNode = MySceneEditor::instance()->GetRootNode();
    NodeItem* rootItem = MainWindow::instance()->GetNodeItemFromNode(rootNode);
    return ExportNode(stream, rootItem);
}

// called by editor for each node in graph. calls may be
// nested in which case they are considered to be children.
bool Exporter::ExportNode(StreamFormatted& stream, NodeItem* item)
{
    // export each node driver
    const NodeItem::tNodeDrivers& drivers = item->Drivers();
    NodeItem::tNodeDrivers::const_iterator it(drivers.begin()), itEnd(drivers.end());
    for (; it != itEnd; ++it)
    {
        INodeDriver* driver = *it;
        if (!ExportNodeDriver(stream, driver))
        {
            // insert logging here
            return false;
        }
    }

    // export children
    Node* node = item->GetNode();
    Array* children = node->getChildren();
    Object* object;
    CCARRAY_FOREACH(children, object)
    {
        Node* child = (Node*)object;
        NodeItem* childItem = MainWindow::instance()->GetNodeItemFromNode(child);
        if (childItem)
        {
            if (!ExportNode(stream, childItem))
            {
                // insert logging
                return false;
            }
        }
    }

    return true;
}

// called by editor for each driver on a node item
bool Exporter::ExportNodeDriver(StreamFormatted &stream, INodeDriver *driver)
{
    stream.write(driver->Id());
    return driver->Export(stream, this);
}
