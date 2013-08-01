
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

    cocos2d::Texture2D* Value() const
    {
        return mTexture;
    }

    void SetValue(cocos2d::Texture2D*, bool block = false)
    {
        // Does Nothing
    }

signals:

    void widgetChanged(QWidget* widget);

public slots:

    void browse()
    {
        QString path = QFileDialog::getOpenFileName(this, QString("Browse for texture"), QString(""), QString("*.png"));
        if (path.length())
        {
            mPath->setText(path);
            setPath();
        }
    }

    void setPath()
    {
        QString text = mPath->text();

        cocos2d::Image* image = new cocos2d::Image;
        image->autorelease();
        if (image->initWithImageFile(text.toUtf8()))
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

    QLineEdit* mPath;
    QPushButton* mButton;
    cocos2d::Texture2D* mTexture;
};

