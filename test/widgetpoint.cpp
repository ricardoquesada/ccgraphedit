#include "widgetpoint.h"
#include <QHBoxLayout>
#include <QSpinBox>
#include <QLabel>

USING_NS_CC;

widgetPoint::widgetPoint(QWidget* parent)
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

Point widgetPoint::Value() const
{
    return ccp(mSpinX->value(), mSpinY->value());
}

void widgetPoint::SetValue(const cocos2d::Point& value)
{
    mSpinX->setValue(value.x);
    mSpinY->setValue(value.y);
}

