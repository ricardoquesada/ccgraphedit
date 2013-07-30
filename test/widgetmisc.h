
#pragma once

#include <QWidget>
#include <QCheckBox>
#include "widgetbase.h"

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
    //IMPLEMENT_CHANGED(int)
signals:
    void widgetChanged(QWidget* widget);
public slots:
    void triggerChange(double value)
    {
        emit widgetChanged(this);
    }
};
