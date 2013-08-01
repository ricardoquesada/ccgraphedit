
#pragma once

#include "cocos2d.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

class QDoubleSpinBox;

USING_NS_CC;

class widgetPoint
    : public QWidget
{
    Q_OBJECT

public:

    widgetPoint(QWidget* parent)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        QLabel* labelx = new QLabel(QString("x"));
        QLabel* labely = new QLabel(QString("y"));
        const int kWidth = 10;
        labelx->setMaximumWidth(kWidth);
        labely->setMaximumWidth(kWidth);
        mSpinX = new QDoubleSpinBox;
        mSpinY = new QDoubleSpinBox;
        mSpinX->setRange(-FLT_MAX, FLT_MAX);
        mSpinY->setRange(-FLT_MAX, FLT_MAX);
        layout->addWidget(labelx);
        layout->addWidget(mSpinX);
        layout->addWidget(labely);
        layout->addWidget(mSpinY);
        connect(mSpinX, SIGNAL(valueChanged(double)), this, SLOT(triggerChange(double)));
        connect(mSpinY, SIGNAL(valueChanged(double)), this, SLOT(triggerChange(double)));
    }

    void SetIncrement(float increment)
    {
        mSpinX->setSingleStep(increment);
        mSpinY->setSingleStep(increment);
    }

    cocos2d::Point Value() const
    {
        return ccp(mSpinX->value(), mSpinY->value());
    }

    void SetValue(const cocos2d::Point& value, bool block = false)
    {
        {
            bool b = mSpinX->blockSignals(block);
            mSpinX->setValue(value.x);
            mSpinX->blockSignals(b);
        }
        {
            bool b = mSpinY->blockSignals(block);
            mSpinY->setValue(value.y);
            mSpinY->blockSignals(b);
        }
    }

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

