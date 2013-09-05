#include "componentsprite.h"
#include "cocos2d.h"
#include "NodeDriver.h"
#include "nodeitem.h"
#include "widgetmisc.h"
#include "widgetnumber.h"
#include "widgetTexture.h"

namespace
{
    const char* kDefaultTextureName = "Icon-144.png";
    const uint32_t kDriverHashTexture = fnv1_32("texture");
}

USING_NS_CC;

Node* ComponentSprite::Instantiate(uint32_t classId)
{
    Sprite* sprite = dynamic_cast<Sprite*>(ComponentBase::Instantiate(classId));
    if (!sprite)
        return nullptr;

    Image* image = new Image;
    image->autorelease();
    if (image->initWithImageFile(kDefaultTextureName))
    {
        Texture2D* texture = new Texture2D;
        if (texture->initWithImage(image))
        {
            sprite->setTexture(texture);
            sprite->setTextureRect(Rect(0, 0, texture->getPixelsWide(), texture->getPixelsHigh()));
        }
    }

    return sprite;
}

void ComponentSprite::RegisterDrivers()
{
    ComponentNodeRGBA::RegisterDrivers();
    REGISTER_DRIVER("flip X",  widgetBool, Sprite, bool,    setFlipX,   isFlipX,    1);
    REGISTER_DRIVER("flip Y",  widgetBool, Sprite, bool,    setFlipY,   isFlipY,    1);
    REGISTER_DRIVER("opacity", widgetInt,  Sprite, uint8_t, setOpacity, getOpacity, 1);

    // custom setter for texture which creates the texture from the string path
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

void ComponentSprite::Populate(NodeItem* nodeItem, QTreeWidget* tree, cocos2d::Node* node)
{
    ComponentBase::Populate(nodeItem, tree, node);

    // fill in the texture name since we cannot get it from the node in this case
    typedef NodeDriverT<widgetTexture, Sprite, std::string> tTextureDriver;
    tTextureDriver* textureDriver = dynamic_cast<tTextureDriver*>(nodeItem->FindDriverByHash(kDriverHashTexture));
    if (textureDriver)
        textureDriver->SetValue(std::string(kDefaultTextureName));
}
