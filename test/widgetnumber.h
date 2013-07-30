
#pragma once

#include <QWidget>
#include <QSpinBox>
#include "widgetbase.h"
#include "float.h"

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
    float Value() const;
    void SetValue(float value);
    //IMPLEMENT_CHANGED(double)
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
    int Value() const;
    void SetValue(int value);
    //IMPLEMENT_CHANGED(double)
signals:
    void widgetChanged(QWidget* widget);
public slots:
    void triggerChange(int value)
    {
        emit widgetChanged(this);
    }
};

