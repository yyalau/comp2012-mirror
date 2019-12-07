#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include "bulletPowerUp.h"

BulletPlayer::BulletPlayer(int dx, int dy, int size_x, int size_y, int move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq)
{
    QPixmap bulletimage(":/image/images/firebullet.png");
    setPixmap(bulletimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setRotation(-90);
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);

    //start the timers
    unpause();
}
