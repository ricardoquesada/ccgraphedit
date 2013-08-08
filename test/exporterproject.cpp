#include "exporterproject.h"
#include "nodeitem.h"
#include "NodeDriver.h"
#include "cocos2d.h"
#include "CCStreamFormatted.h"

namespace
{
    const uint32_t kExporterFormatMagicNumber = 0xdeadbeef;
}

USING_NS_CC;

bool ExporterProject::ExportToStream(StreamFormatted& stream)
{
    // write out file format sentinel
    stream.write(kExporterFormatMagicNumber);

    return Exporter::ExportToStream(stream);
}

bool ExporterProject::ExportNodeBegin(StreamFormatted& stream, NodeItem* item)
{
    Node* node = item->GetNode();

    // write out the node class id
    stream.write(node->classId());

    // write out the count of items
    stream.write(uint32_t(item->Drivers().size()));

    return Exporter::ExportNodeBegin(stream, item);
}

bool ExporterProject::ExportNodeEnd(StreamFormatted& stream, NodeItem* item)
{
    return Exporter::ExportNodeEnd(stream, item);
}

bool ExporterProject::ExportNodeDriver(StreamFormatted& stream, INodeDriver* driver)
{
    // write out id of driver
    stream.write(driver->Id());

    return Exporter::ExportNodeDriver(stream, driver);
}

//
// Specializations
//

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, float* value)
{
    return sizeof(value) == stream.write(*value);
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, int* value)
{
    return sizeof(value) == stream.write(*value);
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, bool* value)
{
    return sizeof(value) == stream.write(*value);
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value)
{
    stream.write(value->x);
    stream.write(value->y);
    return true;
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value)
{
    stream.write(value->width);
    stream.write(value->height);
    return true;
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, std::string* value)
{
    uint32_t length = value->length();
    stream.write(length);
    stream.write(value->c_str(), length);
    return true;
}

bool ExporterProject::ExportProperty(cocos2d::StreamFormatted& stream, uint8_t* value)
{
    return sizeof(value) == stream.write(*value);
}
