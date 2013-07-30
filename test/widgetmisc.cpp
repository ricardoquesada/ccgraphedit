#include "widgetmisc.h"

bool widgetBool::Value() const
{
    return checkState() != Qt::Unchecked;
}
