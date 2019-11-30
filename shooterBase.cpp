#include "shooterBase.h"
#include <QGraphicsScene>

ShooterBase::ShooterBase(QString name, int dx, int dy, bool shoot) : dx(dx), dy(dy), is_shooting(shoot)
{
    health = new Health(name);
}

ShooterBase::~ShooterBase()
{
    delete health;
}

void ShooterBase::create_health(int posx, int posy)
{
     health->setPos(posx,posy);
     scene()->addItem(health);
}
