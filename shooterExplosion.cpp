#include "shooterExplosion.h"

ShooterExplosion::ShooterExplosion(const int& size_x, const int& size_y, int duration) :
    size_x(size_x), size_y(size_y)
{
    set_sprite(":/image/images/explosion_1.png");

    explosion_timer = new CustomTimer(duration, false, this, SLOT(update()));
}

ShooterExplosion::~ShooterExplosion()
{
    delete explosion_timer;
}

inline void ShooterExplosion::set_sprite(const char *sprite)
{
    QPixmap shooterimage(sprite);
    setPixmap(shooterimage.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);
}

void ShooterExplosion::pause()
{
    explosion_timer->pause();
}

void ShooterExplosion::unpause()
{
    explosion_timer->unpause();
}

void ShooterExplosion::update()
{
    switch (sprite_counter)
    {
        case 1:
            set_sprite(":/image/images/explosion_2.png");
            break;
        case 2:
            set_sprite(":/image/images/explosion_3.png");
            break;
        case 3:
            REMOVE_ENTITY(scene(), this);
            return;
        default:
            break;
    }
    ++sprite_counter;
}


