
#pragma once

#define IMPLEMENT_CHANGED(T) \
signals: \
    void widgetChanged(QWidget* widget); \
public slots: \
    void triggerChange(T value) \
    { \
        (void)value; \
        emit widgetChanged(this); \
    }
