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
    ComponentNode::RegisterDrivers();
    REGISTER_DRIVER("flip X",  widgetBool, Sprite, bool,    setFlipX,   isFlipX,    1);
    REGISTER_DRIVER("flip Y",  widgetBool, Sprite, bool,    setFlipY,   isFlipY,    1);
    REGISTER_DRIVER("opacity", widgetInt,  Sprite, uint8_t, setOpacity, getOpacity, 1);

    // for textures we use a lambda for two reasons
    // 1. we need to remove the const qualifier since the method takes a non-const texture.
    // 2. we need to adjust the texture rect of the sprite to match the texture size.
    auto setter = [] (Sprite* node, Texture2D* const& value)
    {
        node->setTexture(const_cast<Texture2D*>(value));
        Size size = value->getContentSizeInPixels();
        node->setTextureRect(Rect(0, 0, size.width, size.height));
    };
    AddDriver(DRIVER_HASH(Texture2D, "texture"), NodeDriverT<widgetTexture, Sprite, Texture2D*>::create("texture", setter, GETTER(Sprite, Texture2D*, getTexture)));
}
