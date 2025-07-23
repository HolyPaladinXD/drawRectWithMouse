#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QPainter>

class Widget : public QWidget
{
    Q_OBJECT
    bool isDrawing = false;
    bool isSelected = false;

    QList<QRect> listRects;
    QRect curRect = QRect();
    QPoint startPoint;
    QPoint prevPoint;
    int selected = -1;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
    virtual void resizeEvent(QResizeEvent *event);
};
#endif // WIDGET_H
