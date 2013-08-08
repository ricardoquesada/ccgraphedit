
#pragma once

#include "exporter.h"
class INodeDriver;

namespace cocos2d {
    class StreamFormatted;
}

class ExporterProject
    : public Exporter
{
public:

    bool ExportToStream(cocos2d::StreamFormatted& stream);
    bool ExportNodeBegin(cocos2d::StreamFormatted& stream, NodeItem* item);
    bool ExportNodeEnd(cocos2d::StreamFormatted& stream, NodeItem* item);
    bool ExportNodeDriver(cocos2d::StreamFormatted& stream, INodeDriver* driver);

    // specializations
    bool ExportProperty(cocos2d::StreamFormatted& stream, float* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, int* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, bool* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, std::string* value);
    bool ExportProperty(cocos2d::StreamFormatted& stream, uint8_t* value);
};
