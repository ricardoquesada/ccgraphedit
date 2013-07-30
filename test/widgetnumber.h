
#pragma once

#include <QWidget>
#include <QLineEdit>

class widgetFloat
    : public QLineEdit
{
public:
    widgetFloat(QWidget* parent)
        : QLineEdit(parent)
    {
        const int kWidth = 50;
        setMaximumWidth(kWidth);
    }
    float Value() const;
};

class widgetInt
    : public QLineEdit
{
public:
    widgetInt(QWidget* parent)
        : QLineEdit(parent)
    {
        const int kWidth = 50;
        setMaximumWidth(kWidth);
    }
    int Value() const;
};

