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

    else{
        if(event->button() == Qt::LeftButton){
        for(int i = listRects.size()-1; i >= 0; i--){
            if(listRects[i].contains(event->pos())){
                selected = i;
                isSelected = true;
                prevPoint = event->pos();
                break;
            }
        }
        }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::RightButton){
        listRects.append(curRect);
        isDrawing = false;
    }

    if((event->button() ==  Qt::LeftButton)){
        curRect = curRect.normalized();
        isSelected = false;
        selected = -1;
    }

    update();

}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(isDrawing){
        curRect.setBottomRight(event->pos());
    }
    if(isSelected){
        QPoint diff = event->pos() -  prevPoint;
        listRects[selected].translate(diff);
        prevPoint = event->pos();
    }
    update();

}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);

    if(isDrawing){
        pen.setColor(Qt::green);
        pen.setStyle(Qt::SolidLine);
        painter.setPen(pen);
        painter.drawRect(curRect);
    }

    for(int i = listRects.size() -1; i >= 0; i--){
        if(i == selected){
            continue;
        }
        else{
            pen.setColor(Qt::green);
            pen.setStyle(Qt::SolidLine);
            painter.setPen(pen);
            painter.drawRect(listRects[i]);
        }
    }
    if(selected >= 0){
        pen.setColor(Qt::red);
        pen.setStyle(Qt::DashLine);
        painter.setPen(pen);
        painter.drawRect(listRects[selected]);
    }

}

void Widget::resizeEvent(QResizeEvent *event)
{
}
