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
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1);

}

void BulletEnemy::move()
{
    switch (bullet_type)
    {
        case Normal:
            BulletBase::move();
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
            if (!(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
            {
                REMOVE_ENTITY(this)
            }
            break;
        }
        case Falling:
            ++fall_counter;
            if (fall_counter == FALL_COUNTER_MAX)
            {
                dy += 1;
                fall_counter = 0;
            }

            BulletBase::move();
            break;
        case Explode:
            if (INSCREEN_UP(pos().y())) //starts falling after reaching the screen
            {
                ++fall_counter;
                if (fall_counter == FALL_COUNTER_MAX)
                {
                    dy += 1;
                    fall_counter = 0;
                }
            }

            setPos(x()+dx,y()+dy);

            if (!(INSCREEN_DOWN(pos().y()+dy)))
            {
                double angle = 3.1415;
                while (angle < 6.2832)
                {
                    int bullet_dx = static_cast<int>(cos(angle)*12);
                    int bullet_dy = static_cast<int>(sin(angle)*12+0.01);

                    BulletEnemy* small_bullet = new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Falling);
                    small_bullet->setPos(x(), y());
                    scene()->addItem(small_bullet);

                    angle += 0.3927;    //shoot in 9 directions
                }

                REMOVE_ENTITY(this)
            }
            break;
        default:
            break;
    }

}

