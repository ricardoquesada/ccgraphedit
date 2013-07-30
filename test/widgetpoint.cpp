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
    mSpinX = new QSpinBox;
    mSpinY = new QSpinBox;
    layout->addWidget(labelx);
    layout->addWidget(mSpinX);
    layout->addWidget(labely);
    layout->addWidget(mSpinY);
}

Point widgetPoint::Value() const
{
    return Point();
}

