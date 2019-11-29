#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

BulletEnemy::BulletEnemy(int dx, int dy): BulletBase(dx,dy), dx(dx), dy(dy)
{
    setRect(0,0,20,20);

    QTimer* timer= new QTimer();

    //connect the timer and the bullet
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void BulletEnemy::move()
{
     BulletBase::move();
}
