#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include <QDebug>

BulletEnemy::BulletEnemy(int dx, int dy, int size_x, int size_y, int move_freq, int coll_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq, coll_freq)
{
    //setRect(0, 0, size_x, size_y);
    QPixmap bulletimage(":/image/images/bugbullet2.png");
    setPixmap(bulletimage.scaled(BULLET_SIZE,BULLET_SIZE,Qt::KeepAspectRatio));
    setRotation(180);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);

    coll_timer = new QTimer();

    //connect timer and collision slot
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision()));

    //start timers
    unpause();
}

void BulletEnemy::pause()
{
    move_timer->stop();
    coll_timer->stop();
}

void BulletEnemy::unpause()
{
    move_timer->start(move_freq);
    coll_timer->start(coll_freq);
}

void BulletEnemy::collision()
{
    //TODO?
    // i dont think we should implement anything
    // i tried to do the collision function for bulletEnemy and bulletShooter, and delete only itself
    // but idk why it doesnt work
}

