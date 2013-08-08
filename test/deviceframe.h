
#pragma once

#include "CCGeometry.h"
#include "sprite_nodes/CCSprite.h"
#include <string>
#include "stdint.h"

class DeviceFrame
{
public:

    enum eOrientation
    {
        kNone,
        kPortrait,
        kUpsideDown,
        kLandscapeLeft,
        kLandscapeRight,
    };

    DeviceFrame(const char* name, const char* image, size_t width, size_t height, eOrientation orientation)
        : mName(name)
        , mWidth(width)
        , mHeight(height)
        , mOrientation(orientation)
    {
        mSprite = cocos2d::Sprite::create(image);
        switch (mOrientation)
        {
        case kUpsideDown:
            mSprite->setRotation(180);
            break;
        case kLandscapeLeft:
            mSprite->setRotation(90);
            break;
        case kLandscapeRight:
            mSprite->setRotation(-90);
            break;
        }
    }

    const char* Name() const
    {
        return mName.c_str();
    }

    size_t Width() const
    {
        return mWidth;
    }

    size_t Height() const
    {
        return mHeight;
    }

    eOrientation Orientation() const
    {
        return mOrientation;
    }

    cocos2d::Sprite* Sprite() const
    {
        return mSprite;
    }

protected:

    std::string mName;
    size_t mWidth;
    size_t mHeight;
    eOrientation mOrientation;
    cocos2d::Sprite* mSprite;
};

