
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

    void SetIncrement(int increment)
    {
        // Does Nothing
    }

    bool Value() const
    {
        return checkState() == Qt::Checked;
    }

    void SetValue(bool value, bool block = false)
    {
        bool b = blockSignals(block);
        setCheckState(value ? Qt::Checked : Qt::Unchecked);
        blockSignals(b);
    }

    bool Compare(bool a, bool b)
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
