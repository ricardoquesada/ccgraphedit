
#pragma once

#include "cocos2d.h"
#include "AutoSignalBlock.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

class QDoubleSpinBox;

USING_NS_CC;

class widgetSize
    : public QWidget
{
    Q_OBJECT

public:

    widgetSize(QWidget* parent)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        QLabel* labelx = new QLabel(QString("width"));
        QLabel* labely = new QLabel(QString("height"));
        const int kWidth = 40;
        labelx->setFixedWidth(kWidth);
        labely->setFixedWidth(kWidth);
        mSpinWidth = new QDoubleSpinBox;
        mSpinHeight = new QDoubleSpinBox;
        mSpinWidth->setRange(-FLT_MAX, FLT_MAX);
        mSpinHeight->setRange(-FLT_MAX, FLT_MAX);
        layout->addWidget(labelx);
        layout->addWidget(mSpinWidth);
        layout->addWidget(labely);
        layout->addWidget(mSpinHeight);
        connect(mSpinWidth, SIGNAL(valueChanged(double)), this, SLOT(triggerChange(double)));
        connect(mSpinHeight, SIGNAL(valueChanged(double)), this, SLOT(triggerChange(double)));
    }

    void SetIncrement(float increment)
    {
        mSpinWidth->setSingleStep(increment);
        mSpinHeight->setSingleStep(increment);
    }

    cocos2d::Point Value() const
    {
        return ccp(mSpinWidth->value(), mSpinHeight->value());
    }

    void SetValue(const cocos2d::Point& value, bool block = false)
    {
        {
            AutoSignalBlocker autoblock(mSpinWidth, block);
            mSpinWidth->setValue(value.x);
        }
        {
            AutoSignalBlocker autoblock(mSpinHeight, block);
            mSpinHeight->setValue(value.y);
        }
    }

    bool Compare(const cocos2d::Point& a, const cocos2d::Point& b) const
    {
        return a.equals(b);
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void triggerChange(double value)
    {
        emit widgetChanged(this);
    }

protected:

    QDoubleSpinBox* mSpinWidth;
    QDoubleSpinBox* mSpinHeight;
};

