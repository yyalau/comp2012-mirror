#include "bulletPowerUp.h"

BulletPowerUp::BulletPowerUp(const int& dx, const int& dy, const PowerUpType& power_type,
                             const int size_x, int size_y, const int& move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq)
{

    QPixmap bulletimage(":/image/images/powerup.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setRotation(-90);
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);

    if (power_type == Random)
    {
        int random_power= RANDOM(0, 2);

        switch (random_power) {
            case 0:
                this->power_type = Breakpoint; //health increase
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
    else this->power_type = power_type;
}

BulletPowerUp::PowerUpType BulletPowerUp::get_power_type()
{
    return power_type;
}

