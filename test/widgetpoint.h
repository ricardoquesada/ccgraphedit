
#pragma once

#include "cocos2d.h"
#include <QWidget>

class QSpinBox;

class widgetPoint
    : public QWidget
{
public:

    widgetPoint(QWidget* parent);

    cocos2d::Point Value() const;

protected:

    QSpinBox* mSpinX;
    QSpinBox* mSpinY;
};

