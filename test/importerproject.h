
#pragma once

#include "importer.h"

namespace cocos2d {
    class StreamFormatted;
    class Node;
}
class INodeDriver;
class NodeItem;

class ImporterProject
    : public Importer
{
public:

    bool ImportFromStream(cocos2d::StreamFormatted& stream);

    // specializations that must be implemented per importer
    bool ImportProperty(cocos2d::StreamFormatted& stream, float* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, int* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, bool* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, std::string* value);
    bool ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value);

protected:

    NodeItem* ImportNode(cocos2d::StreamFormatted& stream, cocos2d::Node* parent = nullptr);
};
