#include "importerproject.h"
#include "mainwindow.h"
#include "mysceneeditor.h"
#include "cocos2d.h"
#include "CCStreamFormatted.h"
#include "CCClassRegistry.h"
#include "componentbase.h"
#include "nodeitem.h"
#include "NodeDriver.h"

USING_NS_CC;

bool ImporterProject::ImportFromStream(cocos2d::StreamFormatted& stream)
{
    // sentinel
    uint32_t sentinel;
    stream.read(sentinel);

    // version
    uint32_t version;
    stream.read(version);

    Node* scene = Director::sharedDirector()->getRunningScene();

    NodeItem* item = ImportNode(stream, scene);
    if (item)
    {
        Node* root = item->GetNode();
        MySceneEditor::instance()->SetRootNode(root);
    }

    return item != nullptr;
}

//
// specializations
//

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, float* value)
{
    return sizeof(*value) == stream.read(*value);
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, int* value)
{
    return sizeof(*value) == stream.read(*value);
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, bool* value)
{
    return sizeof(*value) == stream.read(*value);
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

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::_ccColor3B* value)
{
    stream.read(value->r);
    stream.read(value->g);
    stream.read(value->b);
    return true;
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, std::string* value)
{
    uint32_t length;
    stream.read(length);
    value->resize(length);
    char* temp = (char*)alloca(length + 1);
    stream.read(temp, length);
    temp[length] = 0;
    value->assign(temp);
    return true;
}

bool ImporterProject::ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value)
{
    return sizeof(*value) == stream.read(*value);
}

//
// Protected Methods
//

// Import a single node including all children
NodeItem* ImporterProject::ImportNode(cocos2d::StreamFormatted& stream, Node* parent)
{
    if (!parent)
        parent = MySceneEditor::instance()->GetRootNode();

    // class id
    uint32_t classId;
    stream.read(classId);

    // read name
    std::string name;
    ImportProperty(stream, &name);

    // add the node to the scene and create all drivers etc.
    NodeItem* item = MainWindow::instance()->AddNode(parent, classId);
    if (!item)
    {
        // logging
        return nullptr;
    }

    Node* node = item->GetNode();

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
