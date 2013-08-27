#include "importerproject.h"
#include "mainwindow.h"
#include "cocos2d.h"
#include "CCStreamFormatted.h"
#include "CCClassRegistry.h"
#include "componentbase.h"
#include "nodeitem.h"
#include "NodeDriver.h"

USING_NS_CC;

// called by editor to begin importing from stream
// allows you to import any preamble you would like
bool ImporterProject::ImportFromStream(cocos2d::StreamFormatted& stream)
{
    // sentinel
    uint32_t sentinel;
    stream.read(sentinel);

    // version
    uint32_t version;
    stream.read(version);

    NodeItem* item = ImportNode(stream);

    return item != nullptr;
}

//
// specializations
//

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, float* value)
{
    return sizeof(value) == stream.read(*value);
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, int* value)
{
    return sizeof(value) == stream.read(*value);
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, bool* value)
{
    return sizeof(value) == stream.read(*value);
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value)
{
    stream.read(value->x);
    stream.read(value->y);
    return true;
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value)
{
    stream.read(value->width);
    stream.read(value->height);
    return true;
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, std::string* value)
{
    uint32_t length;
    stream.read(length);
    value->resize(length);
    stream.read(&value[0], length);
    return true;
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value)
{
    return sizeof(value) == stream.read(*value);
}

//
// Protected Methods
//

// Import a single node including all children
NodeItem* ImporterProject::ImportNode(cocos2d::StreamFormatted& stream, Node* parent)
{
    // class id
    uint32_t classId;
    stream.read(classId);

    // instantiate class
    Node* node = dynamic_cast<Node*>(CCClassRegistry::instance()->instantiateClass(classId));
    if (!node)
    {
        // logging
        return nullptr;
    }

    // add the node to the scene and create all drivers etc.
    NodeItem* item = MainWindow::instance()->AddNode(parent, node, "NODENAME");
    if (!item)
    {
        // logging
        return nullptr;
    }

    // driver count
    uint32_t driverCount;
    stream.read(driverCount);

    // drivers
    for (uint32_t dc = 0; dc < driverCount; ++dc)
    {
        uint32_t driverId;
        if (sizeof(driverId) != stream.read(driverId))
        {
            // logging
            return nullptr;
        }

        INodeDriver* driver = item->FindDriverByHash(driverId);
        if (!driver)
        {
            // logging
            return nullptr;
        }

        if (!driver->Import(stream, this))
        {
            // logging
            return nullptr;
        }

        // push the driver value to the node
        driver->Push();
    }

    // child count
    uint32_t childCount;
    stream.read(childCount);

    // children
    for (uint32_t cc = 0; cc < childCount; ++cc)
    {
        if (!ImportNode(stream, node))
        {
            // logging
            return nullptr;
        }
    }

    return item;
}
