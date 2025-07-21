#include "widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
}

Widget::~Widget() {}


void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        isDrawing = true;
        startPoint = event->pos();
        curRect = QRect(startPoint, startPoint);
        this->update();
    }

    else if(event->button() == Qt::LeftButton){
        if(curRect.contains(event->pos())){
            prevPoint = event->position().toPoint();
            isSelected = true;

        }
        else{
            isSelected = false;
        }
        update();
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        isDrawing = false;
    }

    if((event->button() ==  Qt::LeftButton)){
        curRect = curRect.normalized();
        isSelected = false;
    }

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDrawing){
        curRect.setBottomRight(event->pos());
        update();
    }
    if(isSelected){
        QPoint diff = event->pos() -  prevPoint;
        curRect.translate(diff);
        prevPoint = event->pos();
        update();
    }

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;

    pen.setWidth(5);

    if(isSelected){
        pen.setColor(Qt::red);
        pen.setStyle(Qt::DashLine);
    }
    else{
        pen.setColor(Qt::green);
        pen.setStyle(Qt::SolidLine);
    }
    painter.setPen(pen);
    painter.drawRect(curRect);
}

void Widget::resizeEvent(QResizeEvent *event)
{
}
