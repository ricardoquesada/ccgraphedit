
#pragma once

#include "cocos2d.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFileDialog>

USING_NS_CC;

class widgetTexture
    : public QWidget
{
    Q_OBJECT

public:

    widgetTexture(QWidget* parent)
        : QWidget(parent)
        , mTexture(nullptr)
    {
        QHBoxLayout* layout = new QHBoxLayout;
        setLayout(layout);
        mPath = new QLineEdit;
        mButton = new QPushButton(QString("Browse"));
        layout->addWidget(mPath);
        layout->addWidget(mButton);
        connect(mPath, SIGNAL(editingFinished()), this, SLOT(setPath()));
        connect(mButton, SIGNAL(pressed()), this, SLOT(browse()));
    }

    virtual ~widgetTexture()
    {
        CC_SAFE_RELEASE(mTexture);
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
        mPath->setText(name.c_str());
    }

    bool Compare(const std::string& a, const std::string& b) const
    {
        return 0 == a.compare(b);
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void browse()
    {
        QString path = QFileDialog::getOpenFileName(this, QString("Browse for texture"), QString(""), QString("*.png"));
        if (path.length())
        {
            mValue.assign(path.toUtf8());
            mPath->setText(path);
            setPath();
        }
    }

    void setPath()
    {
        const char* text = mValue.c_str();

        cocos2d::Image* image = new cocos2d::Image;
        image->autorelease();
        if (image->initWithImageFile(text))
        {
            cocos2d::Texture2D* texture = new cocos2d::Texture2D;
            texture->autorelease();

            if (texture->initWithImage(image))
            {
                mTexture = texture;
                emit widgetChanged(this);
            }
        }
    }

protected:

    std::string mValue;
    QLineEdit* mPath;
    QPushButton* mButton;
    cocos2d::Texture2D* mTexture;
};

