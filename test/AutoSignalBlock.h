
#pragma once

#include <QObject>

class AutoSignalBlocker
{
public:

    AutoSignalBlocker(QObject* object, bool block = false)
        : mObject(nullptr)
    {
        if (block)
        {
            mObject = object;
            mState = object->blockSignals(true);
        }
    }

    ~AutoSignalBlocker()
    {
        if (mObject)
            mObject->blockSignals(mState);
    }

    QObject* mObject;
    bool mState;
};
