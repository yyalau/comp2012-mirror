#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

BulletEnemy::BulletEnemy(int dx, int dy): BulletBase(dx,dy)
{
    setRect(0,0,20,20);

    QTimer* timer= new QTimer();

    //connect timer and collision slot
    connect(timer, SIGNAL(timeout()), this, SLOT(collision()));
    timer->start(50);
}

void BulletEnemy::collision()
{
    //TODO?
}
