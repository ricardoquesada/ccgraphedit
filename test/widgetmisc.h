
#pragma once

#include <QWidget>
#include <QCheckBox>

class widgetBool
    : public QCheckBox
{
public:
    widgetBool(QWidget* parent)
        : QCheckBox(parent)
    {}
    bool Value() const;
};
