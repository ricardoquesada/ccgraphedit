
#pragma once

#include "stdint.h"
#include <string>

namespace cocos2d {
    class StreamFormatted;
    class Point;
    class Size;
}
class NodeItem;
class INodeDriver;

class Exporter
{
public:

    // called by editor to begin exporting graph to stream
    // allows you to export any preamble you would like.
    virtual bool ExportToStream(cocos2d::StreamFormatted& stream);

    // called by editor for each node in graph. Is reentrant for children.
    virtual bool ExportNode(cocos2d::StreamFormatted& stream, NodeItem* item);

    // called by editor for each driver on a node item
    virtual bool ExportNodeDriver(cocos2d::StreamFormatted& stream, INodeDriver* driver);

    // value types that must be implemented per exporter
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, float* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, int* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, bool* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, std::string* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, uint8_t* value) = 0;
};

