
#pragma once

#include <QWidget>
#include <QSpinBox>

class widgetFloat
    : public QDoubleSpinBox
{
public:
    widgetFloat(QWidget* parent)
        : QDoubleSpinBox(parent)
    {}
    float Value() const;
};

class widgetInt
    : public QSpinBox
{
public:
    widgetInt(QWidget* parent)
        : QSpinBox(parent)
    {}
    int Value() const;
};

