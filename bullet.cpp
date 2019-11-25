#include <bullet.h>
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

Bullet::Bullet(int dx, int dy): dx(dx), dy(dy)
{
    setRect(0,0,20,20);

    QTimer* timer= new QTimer();

    //connect the timer and the bullet
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void Bullet::move()
{
    //collision with other bullets
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (Bullet))
        {
            //delete the other bullet
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];

            //delete yourself
            scene()->removeItem(this);
            delete this;

            return;
        }
    }

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
