
#pragma once

#include <QWidget>
#include <QSpinBox>
#include "float.h"

enum
{
    kMinWidth = 60,
    kMaxWidth = 100
};

class widgetFloat
    : public QDoubleSpinBox
{
public:
    widgetFloat(QWidget* parent)
        : QDoubleSpinBox(parent)
    {
        setMinimumWidth(kMinWidth);
        setMaximumWidth(kMaxWidth);
        setRange(-FLT_MAX, FLT_MAX);
    }
    float Value() const;
};

class widgetInt
    : public QSpinBox
{
public:
    widgetInt(QWidget* parent)
        : QSpinBox(parent)
    {
        setMinimumWidth(kMinWidth);
        setMaximumWidth(kMaxWidth);
        setRange(-INT_MAX, INT_MAX);
    }
    int Value() const;
};

