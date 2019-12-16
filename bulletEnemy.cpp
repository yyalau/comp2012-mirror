#include "bulletEnemy.h"
#include "bulletPlayer.h"

BulletEnemy::BulletEnemy(const int& dx, const int& dy, const BulletType& bullet_type,
                         const int size_x, const int size_y, const int& move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq), bullet_type(bullet_type)
{
    QPixmap bulletimage(bullet_type == Explode ? ":/image/images/chip.png" : ":/image/images/error.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setRotation(180);
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1);
}

bool BulletEnemy::out_of_bound()
{
    if (bullet_type == OutOfBound)
        return !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y(), this));
    else if (bullet_type == Explode)
        return !(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x(), this)) ||
            !(INSCREEN_DOWN(pos().y(), this));
    else
        return !(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x(), this)) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y(), this));
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
            if (!bounced && y() > 320)
            {
                bounced = true;
                dx = -dx;
                dy += 2;
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

            if (!(INSCREEN_DOWN(pos().y()+dy, this)))
            {
                double angle = 3.1415;
                int explode_speed = RANDOM(10, 13);
                while (angle < 6.2832)
                {
                    int bullet_dx = static_cast<int>(cos(angle)*explode_speed);
                    int bullet_dy = static_cast<int>(sin(angle)*explode_speed+0.5);

                    BulletEnemy* small_bullet = new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Falling);
                    small_bullet->setPos(x(), y());
                    scene()->addItem(small_bullet);

                    angle += 0.3927;    //shoot in 9 directions
                }
            }
            break;
        default:
            break;
    }

    BulletBase::move();
}

