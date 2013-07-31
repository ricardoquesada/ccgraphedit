
#pragma once

#include <QWidget>
#include <QCheckBox>

class widgetBool
    : public QCheckBox
{
    Q_OBJECT
public:
    widgetBool(QWidget* parent)
        : QCheckBox(parent)
    {
        connect(this, SIGNAL(stateChanged(int)), this, SLOT(triggerChange(int)));
    }
    bool Value() const;
    void SetValue(bool value, bool block = false);

signals:
    void widgetChanged(QWidget* widget);
public slots:
    void triggerChange(int value)
    {
        emit widgetChanged(this);
    }
};
