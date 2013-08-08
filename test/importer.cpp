#include "importer.h"
#include "mainwindow.h"
#include "cocos2d.h"
#include "CCStreamFormatted.h"
#include "componentbase.h"

USING_NS_CC;

// called by editor to begin importing from stream
// allows you to import any preamble you would like
bool Importer::ImportFromStream(cocos2d::StreamFormatted& stream)
{
    NodeItem* item = ImportNode(stream);

}

// Import a single node including all children
NodeItem* Importer::ImportNode(cocos2d::StreamFormatted& stream)
{
    // export each node driver


}

// Import a node driver
INodeDriver* Importer::ImportNodeDriver(cocos2d::StreamFormatted& stream, IComponent* component)
{
    uint32_t driverId;
    if (sizeof(driverId) != stream.read(driverId))
        return false;
    return component->GetDriver(driverId);
}

// value types that must be implemented per importer
bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, float* value)
{
    return sizeof(value) == stream.read(*value);
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, int* value)
{
    return sizeof(value) == stream.read(*value);
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, bool* value)
{
    return sizeof(value) == stream.read(*value);
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value)
{
    stream.read(value->x);
    stream.read(value->y);
    return true;
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value)
{
    stream.read(value->width);
    stream.read(value->height);
    return true;
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, std::string* value)
{
    uint32_t length;
    stream.read(length);
    value->resize(length);
    stream.read(&value[0], length);
    return true;
}

bool Importer::ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value)
{
    return sizeof(value) == stream.read(*value);
}
