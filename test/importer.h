
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
class IComponent;

class Importer
{
public:

    // called by editor to begin importing from stream
    // allows you to import any preamble you would like
    virtual bool ImportFromStream(cocos2d::StreamFormatted& stream);

    // Import a single node including all children
    virtual NodeItem* ImportNode(cocos2d::StreamFormatted& stream);

    // Import a node driver
    virtual INodeDriver* ImportNodeDriver(cocos2d::StreamFormatted& stream, IComponent* component);

    // value types that must be implemented per importer
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, float* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, int* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, bool* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, std::string* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value) = 0;
};
