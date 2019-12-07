#include "shooterBase.h"

ShooterBase::ShooterBase(QString name, int hp, bool health_title, int dx, int dy, int shoot_freq, bool shoot,
                         int size_x, int size_y, int move_freq, int coll_freq) :
    dx(dx), dy(dy), size_x(size_x), size_y(size_y),
    move_freq(move_freq), coll_freq(coll_freq), shoot_freq(shoot_freq), is_shooting(shoot)
{
    health = new Health(name, hp, health_title);
}

ShooterBase::~ShooterBase()
{
    delete health;
    delete move_timer;
    delete coll_timer;
    delete shoot_timer;
}

Health* ShooterBase::get_health_var()
{
    return health;
}

void ShooterBase::pause()
{
    move_timer->stop();
    coll_timer->stop();
    shoot_timer->stop();
}

void ShooterBase::unpause()
{
    move_timer->start(move_freq);
    coll_timer->start(coll_freq);
    shoot_timer->start(shoot_freq);
}

void ShooterBase::shoot_bullet(BulletBase *bullet)
{
    bullet->setPos(x()+size_x/2, y()+size_y/2);
    scene()->addItem(bullet);
}

