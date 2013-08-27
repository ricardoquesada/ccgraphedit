
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

    virtual bool ExportToStream(cocos2d::StreamFormatted& stream) = 0;

    // value types that must be implemented per exporter
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, float* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, int* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, bool* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, std::string* value) = 0;
    virtual bool ExportProperty(cocos2d::StreamFormatted& stream, uint8_t* value) = 0;
};

