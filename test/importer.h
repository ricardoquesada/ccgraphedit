
#pragma once

#include "stdint.h"
#include <string>

namespace cocos2d {
    class StreamFormatted;
    class Point;
    class Size;
    struct _ccColor3B;
}

class Importer
{
public:

    virtual bool ImportFromStream(cocos2d::StreamFormatted& stream) = 0;

    // specializations that must be implemented per importer
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, float* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, int* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, bool* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Point* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::Size* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, cocos2d::_ccColor3B* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, std::string* value) = 0;
    virtual bool ImportProperty(cocos2d::StreamFormatted& stream, uint8_t* value) = 0;
};
