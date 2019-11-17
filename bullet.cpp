#include <bullet.h>
#include <QTimer>
#include <QGraphicsScene>
//#include <QDebug>

Bullet::Bullet()
{
    setRect(0,0,20,20);

    QTimer* timer= new QTimer();

    //connect the timer and the bullet
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);

}

void Bullet::move()
{
    setPos(x(),y()-10);

    if (pos().y()+rect().height()<0)
    {
        scene()->removeItem(this);
        delete this;

    }
}
