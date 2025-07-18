#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget() {}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::RightButton){
        isDrawing = true;
        startPoint = event->pos();
        curRect = QRect(startPoint, event->pos()).normalized();
        this->update();
    }

    if((event->buttons() & Qt::LeftButton) && contains()){
        //isDrawing = true;
        isSelected = true;
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() & Qt::RightButton){
        isDrawing = false;
    }

    if((event->button() & Qt::LeftButton)){
        isSelected = false;
    }

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDrawing){
        curRect = QRect(startPoint, event->pos()).normalized();
        update();
    }
    if(isSelected){
        QRect tmp = curRect;
        curRect =
    }

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;

    pen.setWidth(5);
    if(isDrawing){
        pen.setColor(Qt::green);
        pen.setStyle(Qt::SolidLine);
    }
    if(isSelected){
        pen.setColor(Qt::red);
        pen.setStyle(Qt::DashLine);
    }

    painter.setPen(pen);
    painter.drawRect(curRect);
}

bool Widget::contains() const{
    const int tolerance = 3;
    QPoint point = mapFromGlobal(QCursor::pos());
    if(((point.rx() >= curRect.topLeft().rx()) && (point.rx() <= curRect.topRight().rx()))
        && (point.ry() >= curRect.topLeft().ry() - tolerance) && (point.ry() <=  tolerance + curRect.topLeft().ry()) ){
        return true;
    }

    if(((point.rx() >= curRect.bottomLeft().rx()) && (point.rx() <= curRect.bottomRight().rx()))
        && ((point.ry() >= curRect.bottomLeft().ry() - tolerance) && (point.ry() <= tolerance + curRect.bottomLeft().ry()))){
        return true;
    }

    if(((point.ry() >= curRect.topLeft().ry()) && (point.ry() <= curRect.bottomLeft().ry()))
        && ((point.rx() >= curRect.topLeft().rx() - tolerance) && (point.rx() <= tolerance + curRect.topLeft().rx()))){
        return true;
    }

    if(((point.ry() >= curRect.topRight().ry()) && (point.ry() <= curRect.bottomRight().ry()))
        && ((point.rx() >= curRect.topRight().rx() - tolerance) && (point.rx() <= tolerance + curRect.topRight().rx()))){
        return true;
    }
    return false;
}


void Widget::resizeEvent(QResizeEvent *event)
{
}
