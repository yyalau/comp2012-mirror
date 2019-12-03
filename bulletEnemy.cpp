#include "bulletEnemy.h"
#include "bulletPlayer.h"

BulletEnemy::BulletEnemy(int dx, int dy, BulletType bullet_type,
                         int size_x, int size_y, int move_freq/*, int coll_freq*/):
    BulletBase(dx, dy, size_x, size_y, move_freq/*, coll_freq*/), bullet_type(bullet_type)
{
    //setRect(0, 0, size_x, size_y);
    QPixmap bulletimage(":/image/images/bugbullet2.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setRotation(180);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);

    //coll_timer = new QTimer();

    //connect timer and collision slot
    //connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision()));

    //start timers
    unpause();
}

void BulletEnemy::pause()
{
    move_timer->stop();
    //coll_timer->stop();
}

void BulletEnemy::unpause()
{
    move_timer->start(move_freq);
    //coll_timer->start(coll_freq);
}

void BulletEnemy::move()
{
    switch (bullet_type)
    {
        case Normal:
            break;
        case OutOfBound:
            //this type is only used for the boss. the following segment handles creating the pattern
            //TODO

            //move the bullets
            setPos(x()+dx,y()+dy);

            //remove the bullets once its out of bound
            if (!(INSCREEN_LEFT_OOB(pos().x())) || !(INSCREEN_RIGHT_OOB(pos().x())) ||
                    !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
            {
                REMOVE_ENTITY(this)
            }
            return; //in other cases, move() using base class after the switch case statement
        case Falling:
            dy += 1;
            break;
        case Explode:
            if (!(INSCREEN_DOWN(pos().y()+dy)))
            {
                //TODO: REMOVE_ENTITY, spawn a bunch of Falling bullets in different directions
            }
            break;
        default:
            break;
    }

    BulletBase::move();
}

//void BulletEnemy::collision()
//{
    //TODO?
    // i dont think we should implement anything
    // i tried to do the collision function for bulletEnemy and bulletShooter, and delete only itself
    // but idk why it doesnt work
//}

