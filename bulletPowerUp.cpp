#include "bulletPowerUp.h"

BulletPowerUp::BulletPowerUp(int dx, int dy, PowerUpType power_type, int size_x, int size_y, int move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq), power_type(power_type)
{

    QPixmap bulletimage(":/image/images/powerup.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setRotation(-90);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);

    int random_power= rand()%3;

    switch (random_power) {
    case 0:
        this->power_type= Breakpoint; //health increase
    break;
    case 1:
        this->power_type = StackOverflow; //clear field
    break;
    case 2:
        this->power_type = CoutTestEndl; //increase shooter strength
    break;
    default:
            break;
    }
}

BulletPowerUp::PowerUpType BulletPowerUp::get_power_type()
{
    return power_type;
}

