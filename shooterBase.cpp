#include "shooterBase.h"

ShooterBase::ShooterBase(const QString& name, const int& hp, const int& dx, const int& dy, const int& shoot_freq, const bool& shoot,
                         const int size_x, const int size_y, const int move_freq, const int& num_sound_types) :
    dx(dx), dy(dy), size_x(size_x), size_y(size_y),
    move_freq(move_freq), shoot_freq(shoot_freq), is_shooting(shoot),
    num_sound_types(num_sound_types)
{
    health = new Health(name, hp);
}

ShooterBase::~ShooterBase()
{
    delete health;
    delete move_timer;
    delete shoot_timer;
    for (int i=0; i<num_sound_types; ++i)
        delete sound[i];
    delete [] sound;
}

void ShooterBase::play_sound(QMediaPlayer *sound_to_play)
{
    sound_to_play->setPosition(0);
    sound_to_play->play();
}

void ShooterBase::pause()
{
    move_timer->pause();
    shoot_timer->pause();
}

void ShooterBase::unpause()
{
    move_timer->unpause();
    shoot_timer->unpause();
}

void ShooterBase::shoot_bullet(BulletBase *bullet)
{
    bullet->setPos(x()+size_x/2, y()+size_y/2);
    scene()->addItem(bullet);
}

