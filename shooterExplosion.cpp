#include "shooterExplosion.h"

ShooterExplosion::ShooterExplosion(int size_x, int size_y, int duration)
{
    QPixmap image(":/image/images/computer_dead.png");
    setPixmap(image.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);

    explosion_timer = new CustomTimer(duration, true, this, SLOT(remove_this()));
}

ShooterExplosion::~ShooterExplosion()
{
    delete explosion_timer;
}

void ShooterExplosion::pause()
{
    explosion_timer->pause();
}

void ShooterExplosion::unpause()
{
    explosion_timer->unpause();
}

void ShooterExplosion::remove_this()
{
    REMOVE_ENTITY(scene(), this);
}


