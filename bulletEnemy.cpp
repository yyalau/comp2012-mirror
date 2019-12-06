#include "bulletEnemy.h"
#include "bulletPlayer.h"

BulletEnemy::BulletEnemy(int dx, int dy, BulletType bullet_type,
                         int size_x, int size_y, int move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq), bullet_type(bullet_type)
{
    //setRect(0, 0, size_x, size_y);
    QPixmap bulletimage(":/image/images/bugbullet2.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setRotation(180);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1);

    //start timers
    unpause();
}

void BulletEnemy::move()
{
    switch (bullet_type)
    {
        case Normal:
            break;
        case OutOfBound:
        {
            //this type is only used for the boss. the following segment handles creating the pattern
            //TODO
            if (!bounced && y() > 350)
            {
                bounced = true;
                dx = -dx;
            }

            //move the bullets
            setPos(x()+dx,y()+dy);

            //remove the bullets once its out of bound
            if (!(INSCREEN_LEFT_OOB(pos().x())) || !(INSCREEN_RIGHT_OOB(pos().x())) ||
                    !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
            {
                REMOVE_ENTITY(this)
            }
            return; //in other cases, move() using base class after the switch case statement
        }
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

