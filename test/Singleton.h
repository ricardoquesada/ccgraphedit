
#pragma once

#define DECLARE_SINGLETON(_class_) \
    static _class_* instance(); \
    static _class_* singleton_instance;

#define IMPLEMENT_SINGLETON(_class_) \
_class_* _class_::singleton_instance = 0; \
_class_* _class_::instance() \
{ \
    if (!singleton_instance) \
        singleton_instance = new _class_; \
    return singleton_instance; \
}

#define IMPLEMENT_SINGLETON_INIT(_class_) \
_class_* _class_::singleton_instance = 0; \
_class_* _class_::instance() \
{ \
    if (!singleton_instance) \
    { \
        singleton_instance = new _class_; \
        singleton_instance->Init(); \
    } \
    return singleton_instance; \
}
