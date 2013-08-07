
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
    Exporter();

    // called by editor to begin exporting graph to stream
    // allows you to export any preamble you would like.
    virtual bool ExportToStream(cocos2d::StreamFormatted& stream);

    // called by editor for each node in graph. calls may be
    // nested in which case they are considered to be children.
    virtual bool ExportNodeBegin(cocos2d::StreamFormatted& stream, NodeItem* item);

    // called by editor for each node to close that node.
    // the next call to begin starts exporting a new node.
    virtual bool ExportNodeEnd(cocos2d::StreamFormatted& stream, NodeItem* item);

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


