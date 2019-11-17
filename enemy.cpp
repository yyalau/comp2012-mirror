#include <enemy.h>
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> //rand()
//#include <QDebug>

Enemy::Enemy()
{
    int rNum=rand()%700;
    setPos(rNum,0);
    setRect(0,0,40,40);

    QTimer* timer= new QTimer();

    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and the bullet
    timer->start(50);

}

void Enemy::move()
{
    setPos(x(),y()-10);

    if (pos().y()+rect().height()<0)
    {
        scene()->removeItem(this);
        delete this;
    }
}
