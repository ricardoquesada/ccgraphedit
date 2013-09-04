
#pragma once

#include "AutoSignalBlock.h"
#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QColorDialog>
#include "cocos2d.h"

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
        AutoSignalBlocker autoblock(this, block);
        setCheckState(value ? Qt::Checked : Qt::Unchecked);
    }

    bool Compare(bool a, bool b) const
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

//
// widgetColor3
//

class widgetColor3
    : public QWidget
{
    Q_OBJECT

public:

    typedef cocos2d::_ccColor3B value_type;

    widgetColor3(QWidget* parent)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        mButton = new QPushButton(QString("Choose"));
        layout->addWidget(mButton);
        connect(mButton, SIGNAL(pressed()), this, SLOT(choose()));
    }

    void SetIncrement(int)
    {
        // Does Nothing
    }

    const value_type& Value() const
    {
        return mValue;
    }

    void SetValue(const value_type& value, bool block = false)
    {
        mValue = value;
    }

    bool Compare(const value_type& a, const value_type& b) const
    {
        return a.r == b.r && a.g == b.g && a.b == b.b;
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void choose()
    {
        QColorDialog* dialog = new QColorDialog(QColor(mValue.r, mValue.g, mValue.b), this);
        dialog->setModal(false);
        dialog->setOptions(QColorDialog::NoButtons | QColorDialog::DontUseNativeDialog);
        connect(dialog, SIGNAL(currentColorChanged(const QColor&)), this, SLOT(colorChanged(const QColor&)));
        dialog->open();
    }

    void colorChanged(const QColor& color)
    {
        mValue.r = color.red();
        mValue.g = color.green();
        mValue.b = color.blue();
        emit widgetChanged(this);
    }

protected:

    value_type mValue;
    QPushButton* mButton;
};

class widgetString
    : public QWidget
{
    Q_OBJECT

public:

    widgetString(QWidget* parent)
        : QWidget(parent)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        mEdit = new QLineEdit;
        layout->addWidget(mEdit);
        connect(mEdit, SIGNAL(textChanged(QString)), this, SLOT(setString(QString)));
    }

    void SetIncrement(int)
    {
        // Does Nothing
    }

    const std::string& Value() const
    {
        return mValue;
    }

    void SetValue(const std::string& name, bool block = false)
    {
        mValue = name;
        mEdit->setText(name.c_str());
    }

    bool Compare(const std::string& a, const std::string& b) const
    {
        return 0 == a.compare(b);
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void setString(QString text)
    {
        mValue.assign(text.toUtf8());
        emit widgetChanged(this);
    }

protected:

    std::string mValue;
    QLineEdit* mEdit;
};
