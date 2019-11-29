#include "bulletBase.h"

BulletBase::BulletBase(int dx, int dy): dx(dx), dy(dy)
{

}

void BulletBase::move()
{
    //move the bullets
    setPos(x()+dx,y()+dy);

    //remove the bullets once its out of bound
    if (pos().x()<0|| pos().x()>scene()->width()-rect().width()||
            pos().y()< 0 ||pos().y()+rect().height()>scene()->height())
    {
        scene()->removeItem(this);
        delete this;
    }
}
