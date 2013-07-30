#include "widgetmisc.h"

bool widgetBool::Value() const
{
    return checkState() != Qt::Unchecked;
}

void widgetBool::SetValue(bool value)
{
    setCheckState(value ? Qt::Checked : Qt::Unchecked);
}
