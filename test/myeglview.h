#ifndef MYEGLVIEW_H
#define MYEGLVIEW_H

#include "platform/CCEGLViewProtocol.h"

class MyEGLView
    : public cocos2d::CCEGLViewProtocol
{
public:

    /** Force destroying EGL view, subclass must implement this method. */
    virtual void end()
    {}

    /** Get whether opengl render system is ready, subclass must implement this method. */
    virtual bool isOpenGLReady()
    {
        return true;
    }

    /** Exchanges the front and back buffers, subclass must implement this method. */
    virtual void swapBuffers()
    {}

    /** Open or close IME keyboard , subclass must implement this method. */
    virtual void setIMEKeyboardState(bool bOpen)
    {}
};

#endif // MYEGLVIEW_H
