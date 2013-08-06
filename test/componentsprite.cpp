#include "componentsprite.h"
#include "cocos2d.h"
#include "NodeDriver.h"
#include "nodeitem.h"
#include "widgetmisc.h"
#include "widgetnumber.h"
#include "widgetTexture.h"

USING_NS_CC;

void ComponentSprite::RegisterDrivers()
{
    ComponentNodeRGBA::RegisterDrivers();
    REGISTER_DRIVER("flip X",  widgetBool, Sprite, bool,    setFlipX,   isFlipX,    1);
    REGISTER_DRIVER("flip Y",  widgetBool, Sprite, bool,    setFlipY,   isFlipY,    1);
    REGISTER_DRIVER("opacity", widgetInt,  Sprite, uint8_t, setOpacity, getOpacity, 1);

    auto setter = [] (Sprite* node, const std::string& value)
    {
        cocos2d::Image* image = new cocos2d::Image;
        image->autorelease();
        if (image->initWithImageFile(value.c_str()))
        {
            cocos2d::Texture2D* texture = new cocos2d::Texture2D;
            texture->autorelease();

            if (texture->initWithImage(image))
            {
                node->setTexture(texture);
                Size size = texture->getContentSizeInPixels();
                node->setTextureRect(Rect(0, 0, size.width, size.height));
            }
        }
    };
    AddDriver(NodeDriverT<widgetTexture, Sprite, std::string>::create("texture", setter, nullptr));
}
