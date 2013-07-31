#include "widgetnumber.h"

float widgetFloat::Value() const
{
    return value();
}

void widgetFloat::SetValue(float value, bool block)
{
    bool b = blockSignals(block);
    setValue(value);
    blockSignals(b);
}


int widgetInt::Value() const
{
    return value();
}

void widgetInt::SetValue(int value, bool block)
{
    bool b = blockSignals(block);
    setValue(value);
    blockSignals(b);
}

