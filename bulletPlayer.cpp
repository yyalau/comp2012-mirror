#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include "bulletPowerUp.h"

BulletPlayer::BulletPlayer(const int& dx, const int& dy, const int size_x, const int size_y, const int& move_freq):
    BulletBase(dx, dy, size_x, size_y, move_freq)
{
    QPixmap bulletimage(":/image/images/firebullet.png");
    setPixmap(bulletimage.scaled(this->size_y, this->size_x, Qt::IgnoreAspectRatio)); //rotate 90 degrees
    setRotation(-90);
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.2);
    setOffset(45,-15);

}
