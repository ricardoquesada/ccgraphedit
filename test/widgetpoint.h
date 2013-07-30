
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

protected:

    QDoubleSpinBox* mSpinX;
    QDoubleSpinBox* mSpinY;
};

