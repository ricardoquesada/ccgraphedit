
#pragma once

#include "cocos2d.h"
#include <QWidget>

class QDoubleSpinBox;

class widgetPoint
    : public QWidget
{
    Q_OBJECT
public:

    widgetPoint(QWidget* parent);

    cocos2d::Point Value() const;
    void SetValue(const cocos2d::Point& value);

signals:
    void widgetChanged(QWidget* widget);
public slots:
    void triggerChange(double value)
    {
        emit widgetChanged(this);
    }

protected:

    QDoubleSpinBox* mSpinX;
    QDoubleSpinBox* mSpinY;
};

