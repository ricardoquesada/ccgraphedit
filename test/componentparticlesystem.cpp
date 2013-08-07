#include "componentparticlesystem.h"
#include "cocos2d.h"
#include "NodeDriver.h"
#include "nodeitem.h"
#include "widgetmisc.h"
#include "widgetpoint.h"
#include "widgetnumber.h"
#include "widgetTexture.h"

void ComponentParticleSystem::RegisterDrivers()
{
    ComponentNode::RegisterDrivers();

    REGISTER_DRIVER("gravity",                 widgetPoint, ParticleSystemQuad, Point, setGravity,            getGravity,            .1f);
    REGISTER_DRIVER("speed",                   widgetFloat, ParticleSystemQuad, float, setSpeed,              getSpeed,              .1f);
    REGISTER_DRIVER("speed variance",          widgetFloat, ParticleSystemQuad, float, setSpeedVar,           getSpeedVar,           .1f);
    REGISTER_DRIVER("tangent accel",           widgetFloat, ParticleSystemQuad, float, setTangentialAccel,    getTangentialAccel,    .1f);
    REGISTER_DRIVER("tangent accel variance",  widgetFloat, ParticleSystemQuad, float, setTangentialAccelVar, getTangentialAccelVar, .1f);
    REGISTER_DRIVER("radial accel",            widgetFloat, ParticleSystemQuad, float, setRadialAccel,        getRadialAccel,        .1f);
    REGISTER_DRIVER("radial accel variance",   widgetFloat, ParticleSystemQuad, float, setRadialAccelVar,     getRadialAccelVar,     .1f);
    REGISTER_DRIVER("rotation directional",    widgetBool,  ParticleSystemQuad, bool,  setRotationIsDir,      getRotationIsDir,      1);
    REGISTER_DRIVER("start size",              widgetFloat, ParticleSystemQuad, float, setStartSize,          getStartSize,          .1f);
    REGISTER_DRIVER("start size variance",     widgetFloat, ParticleSystemQuad, float, setStartSizeVar,       getStartSizeVar,       .1f);
    REGISTER_DRIVER("end size",                widgetFloat, ParticleSystemQuad, float, setEndSize,            getEndSize,            .1f);
    REGISTER_DRIVER("end size variance",       widgetFloat, ParticleSystemQuad, float, setEndSizeVar,         getEndSizeVar,         .1f);
    REGISTER_DRIVER("start spin",              widgetFloat, ParticleSystemQuad, float, setStartSpin,          getStartSpin,          .1f);
    REGISTER_DRIVER("start spin variance",     widgetFloat, ParticleSystemQuad, float, setStartSpinVar,       getStartSpinVar,       .1f);
    REGISTER_DRIVER("end spin",                widgetFloat, ParticleSystemQuad, float, setEndSpin,            getEndSpin,            .1f);
    REGISTER_DRIVER("end spin variance",       widgetFloat, ParticleSystemQuad, float, setEndSpinVar,         getEndSpinVar,         .1f);
    REGISTER_DRIVER("emission rate",           widgetFloat, ParticleSystemQuad, float, setEmissionRate,       getEmissionRate,       .1f);
    REGISTER_DRIVER("duration",                widgetFloat, ParticleSystemQuad, float, setDuration,           getDuration,           .1f);
    REGISTER_DRIVER("lifetime",                widgetFloat, ParticleSystemQuad, float, setLife,               getLife,               .1f);

    {
        auto setter = [] (ParticleSystemQuad* node, const bool& value)
        {
            node->setStartColor(ccc4f(1,1,1,1));
            node->setEndColor(ccc4f(1,1,1,1));
            node->resetSystem();
        };
        AddDriver(NodeDriverT<widgetBool, ParticleSystemQuad, bool>::create("running", setter, nullptr));
    }

    {
        auto setter = [] (ParticleSystemQuad* node, const int& value)
        {
            node->unscheduleUpdate();
            node->initWithTotalParticles(value);
            node->setTotalParticles(value);
        };
        AddDriver(NodeDriverT<widgetInt, ParticleSystemQuad, int>::create("total particles", setter, GETTER(ParticleSystemQuad, int, getTotalParticles)));
    }

    {
        // custom setter for texture which creates the texture from the string path
        auto setter = [] (ParticleSystemQuad* node, const std::string& value)
        {
            cocos2d::Image* image = new cocos2d::Image;
            image->autorelease();
            if (image->initWithImageFile(value.c_str()))
            {
                cocos2d::Texture2D* texture = new cocos2d::Texture2D;
                texture->autorelease();

                if (texture->initWithImage(image))
                    node->setTexture(texture);
            }
        };
        AddDriver(NodeDriverT<widgetTexture, ParticleSystemQuad, std::string>::create("texture", setter, nullptr));
    }
}
