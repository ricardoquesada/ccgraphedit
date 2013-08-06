
#pragma once

#include <QWidget>
#include <QSpinBox>
#include "float.h"
#include "math.h"

enum
{
    kMinWidth = 60,
    kMaxWidth = 100
};

class widgetFloat
    : public QDoubleSpinBox
{
    Q_OBJECT

public:

    widgetFloat(QWidget* parent)
        : QDoubleSpinBox(parent)
    {
        setMinimumWidth(kMinWidth);
        setMaximumWidth(kMaxWidth);
        setRange(-FLT_MAX, FLT_MAX);
        connect(this, SIGNAL(valueChanged(double)), this, SLOT(triggerChange(double)));
    }

    void SetIncrement(float increment)
    {
        setSingleStep(increment);
    }

    float Value() const
    {
        return value();
    }

    void SetValue(float value, bool block = false)
    {
        bool b = blockSignals(block);
        setValue(value);
        blockSignals(b);
    }

    bool Compare(float a, float b)
    {
        return fabsf(a - b) < FLT_EPSILON;
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void triggerChange(double value)
    {
        emit widgetChanged(this);
    }
};

class widgetInt
    : public QSpinBox
{
    Q_OBJECT

public:

    widgetInt(QWidget* parent)
        : QSpinBox(parent)
    {
        setMinimumWidth(kMinWidth);
        setMaximumWidth(kMaxWidth);
        setRange(-INT_MAX, INT_MAX);
        connect(this, SIGNAL(valueChanged(int)), this, SLOT(triggerChange(int)));
    }

    void SetIncrement(int increment)
    {
        setSingleStep(increment);
    }

    int Value() const
    {
        return value();
    }

    void SetValue(int value, bool block = false)
    {
        bool b = blockSignals(block);
        setValue(value);
        blockSignals(b);
    }

    bool Compare(int a, int b)
    {
        return a == b;
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void triggerChange(int value)
    {
        emit widgetChanged(this);
    }
};

