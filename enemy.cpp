#include <enemy.h>
#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> //rand()
#include "bullet.h"
//#include <QDebug>

Enemy::Enemy()
{
    setBrush(Qt:: blue);
    setRect(0,0,40,40);

    QTimer* timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and the bullet
    timer->start(50);

    QTimer* timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(shootbullets())); //connect the timer and the bullet
    timer2->start(200);

}

void Enemy::move()
{
    static bool left= true;
    if (left){
        setPos(x()-10,0);
        if (x()<100)
            left=false;
    }
    else {
        setX(x()+10);
        if (x()>700)
            left=true;
    }

}

void Enemy::shootbullets()
{
    int dx= rand()%40- rand()%40;

    Bullet* bullet= new Bullet(dx,20);
    bullet->setBrush(Qt::blue);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);
}
