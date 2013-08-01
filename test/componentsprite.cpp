#include "componentsprite.h"
#include "widgetmisc.h"
#include "widgetnumber.h"
#include "widgetTexture.h"
#include "cocos2d.h"
#include "CCGeometry.h"
#include <functional>

USING_NS_CC;

void ComponentSprite::Populate(QTreeWidget* tree, QTreeWidgetItem* parent, Node* node)
{
    ComponentNode::Populate(tree, parent, node);
    CONNECT_FIELD(tree, parent, "flip X",  widgetBool, Sprite, node, bool,    &Sprite::setFlipX,   isFlipX,    1);
    CONNECT_FIELD(tree, parent, "flip Y",  widgetBool, Sprite, node, bool,    &Sprite::setFlipY,   isFlipY,    1);
    CONNECT_FIELD(tree, parent, "opacity", widgetInt,  Sprite, node, uint8_t, &Sprite::setOpacity, getOpacity, 1);
    CONNECT_FIELD(tree, parent, "texture", widgetTexture,  Sprite, node, Texture2D*, &Sprite::setTexture, getTexture, 1);
}
