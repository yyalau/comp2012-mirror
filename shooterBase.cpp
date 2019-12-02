#include "shooterBase.h"

#include <QGraphicsScene>

ShooterBase::ShooterBase(QString name, int hp, int dx, int dy, int size_x, int size_y,
                         int move_freq, int coll_freq, int shoot_freq, bool shoot) :
    dx(dx), dy(dy), size_x(size_x), size_y(size_y),
    move_freq(move_freq), coll_freq(coll_freq), shoot_freq(shoot_freq), is_shooting(shoot)
{
    health = new Health(name, hp);
}

ShooterBase::~ShooterBase()
{
    delete health;
}

Health* ShooterBase::get_health_var()
{
    return health;
}

void ShooterBase::create_health(int posx, int posy)
{
     health->setPos(posx,posy);
     scene()->addItem(health);
}
