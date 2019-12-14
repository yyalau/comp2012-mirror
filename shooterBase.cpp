#include "shooterBase.h"

ShooterBase::ShooterBase(const QString& name, const int& hp, const int& dx, const int& dy, const int& shoot_freq, const bool& shoot,
                         const int size_x, const int size_y, const int move_freq) :
    dx(dx), dy(dy), size_x(size_x), size_y(size_y),
    move_freq(move_freq), shoot_freq(shoot_freq), is_shooting(shoot)
{
    health = new Health(name, hp);
}

ShooterBase::~ShooterBase()
{
    delete health;
    delete move_timer;
    delete shoot_timer;
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

