#include "shooterBase.h"
#include <QGraphicsScene>

ShooterBase::ShooterBase(QString name)
{
    health = new Health(name);
}

void ShooterBase::create_health(int posx, int posy)
{
     health->setPos(posx,posy);
     scene()->addItem(health);
}
