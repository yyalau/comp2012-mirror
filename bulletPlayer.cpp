#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include <QTimer>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

BulletPlayer::BulletPlayer(int dx, int dy):BulletBase(dx,dy), dx(dx), dy(dy)
{
    setRect(0,0,20,20);

    QTimer* timer= new QTimer();

    //connect the timer and the bullet
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    timer->start(50);
}

void BulletPlayer::move()
{
    //collision with other bullets
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletEnemy))
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

    BulletBase::move();

}
