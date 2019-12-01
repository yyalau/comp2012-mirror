#include "bulletEnemy.h"
#include "bulletPlayer.h"

#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

BulletEnemy::BulletEnemy(int dx, int dy, int size_x, int size_y, int move_freq, int coll_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq, coll_freq)
{
    setRect(0, 0, size_x, size_y);

    QTimer* coll_timer= new QTimer();

    //connect timer and collision slot
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision()));
    coll_timer->start(coll_freq);
}

void BulletEnemy::collision()
{
    //TODO?
}
