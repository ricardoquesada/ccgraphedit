
#pragma once

#include "cocos2d.h"
#include <QWidget>

class QDoubleSpinBox;

class widgetPoint
    : public QWidget
{
public:

    widgetPoint(QWidget* parent);

    cocos2d::Point Value() const;
    void SetValue(cocos2d::Point& value);

Q_SIGNALS:
    void valueChanged(double);

protected:

    QDoubleSpinBox* mSpinX;
    QDoubleSpinBox* mSpinY;
};

