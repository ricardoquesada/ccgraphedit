#include "widgetnumber.h"

float widgetFloat::Value() const
{
    return value();
}

void widgetFloat::SetValue(float value)
{
    setValue(value);
}


int widgetInt::Value() const
{
    return value();
}

void widgetInt::SetValue(int value)
{
    setValue(value);
}

