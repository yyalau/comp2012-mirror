#include "shooterExplosion.h"

ShooterExplosion::ShooterExplosion(const int& size_x, const int& size_y, bool boss, int duration) :
    size_x(size_x), size_y(size_y)
{
    set_sprite(":/image/images/explosion_1.png");

    explosion_timer = new CustomTimer(duration, false, this, SLOT(update()));

    sound = new QMediaPlayer();
    if (boss)
        sound->setMedia(QUrl("qrc:/sounds/sounds/BossExplosion.mp3"));
    else
        sound->setMedia(QUrl("qrc:/sounds/sounds/explosion.mp3"));
    sound->play();

}

ShooterExplosion::~ShooterExplosion()
{
    delete explosion_timer;
    delete sound;
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
            setPixmap(QPixmap());
            break;
        case 8: //delete later to allow the media to play
            REMOVE_ENTITY(scene(), this);
            return;
        default:
            break;
    }
    ++sprite_counter;
}


