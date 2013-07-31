#include "widgetmisc.h"

bool widgetBool::Value() const
{
    return checkState() != Qt::Unchecked;
}

void widgetBool::SetValue(bool value, bool block)
{
    bool b = blockSignals(block);
    setCheckState(value ? Qt::Checked : Qt::Unchecked);
    blockSignals(b);
}
