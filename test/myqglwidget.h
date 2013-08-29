#ifndef MYQGLWIDGET_H
#define MYQGLWIDGET_H

#include "cocos2d.h"

#include <QGLWidget>
#include <QTimer>
#include <QMouseEvent>

class MyQGLWidget : public QGLWidget
{
public:
    MyQGLWidget();
    MyQGLWidget(QWidget* parent);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

    QSize sizeHint() const;

    cocos2d::Rect screenInWorld() const;

    // mouse handling
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    void mouseMoveEvent(QMouseEvent*);
    void wheelEvent(QWheelEvent*);

    QTimer mTimer;
    bool mLazyInit;
};

#endif // MYQGLWIDGET_H
