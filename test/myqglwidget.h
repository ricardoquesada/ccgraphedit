#ifndef MYQGLWIDGET_H
#define MYQGLWIDGET_H

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

    // mouse handling
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);

    QTimer mTimer;
    bool mLazyInit;
};

#endif // MYQGLWIDGET_H
