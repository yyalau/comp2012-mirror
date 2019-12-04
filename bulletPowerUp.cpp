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

    unpause();
}
