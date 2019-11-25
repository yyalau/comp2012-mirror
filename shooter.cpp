#include "shooter.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QGraphicsRectItem>
#include "bullet.h"

Shooter::Shooter()
{
    setBrush(Qt::green);
    setRect(0,0,50,40);
}

void Shooter::keyPressEvent(QKeyEvent* event) //try to implement arrow keys and space bar tgt!!!!
{

    if (event->key() ==Qt::Key_Left){
        if (pos().x()>0)
            setPos(x()-10,y());
    }
    if(event->key()==Qt::Key_Right){
        if (pos().x()+rect().width()<scene()->width())
            setPos(x()+10,y());
    }
    if(event->key()==Qt::Key_Up){
        if (pos().y()>0)
            setPos(x(), y()-10);
    }
    if(event->key()==Qt::Key_Down){
        if (pos().y()+rect().height()<scene()->height())
        setPos(x(),y()+10);
    }
    if(event->key()==Qt::Key_Space){
        Bullet* bullet=new Bullet(0,-10);
        bullet->setBrush(Qt::green);
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}
