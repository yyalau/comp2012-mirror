#include "shooterEnemy.h"
#include "bulletEnemy.h"
#include "bulletPlayer.h"


#include <QTimer>
#include <QGraphicsScene>
#include <stdlib.h> //rand()
#include <QDebug>


ShooterEnemy::ShooterEnemy(): ShooterBase("Enemy")
{
    setBrush(Qt:: blue);
    setRect(0,0,40,40);

    is_shooting = true;

    QTimer* timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot
    timer->start(50);

    QTimer* timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot
    timer2->start(50);

    QTimer* timer3= new QTimer();
    connect(timer3, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot
    timer3->start(200);
}

void ShooterEnemy::create_health()
{
    ShooterBase::create_health(0,0);
    health->setDefaultTextColor(Qt:: blue);
}

void ShooterEnemy::move()
{
    static bool left= true;
    if (left){
        dx = -10;
        if (x()<100)
            left=false;
    }
    else {
        dx = +10;
        if (x()>700)
            left=true;
    }

    //move
    setPos(x()+dx,y()+dy);

    //remove once its out of bound
    if (pos().x()<0|| pos().x()>scene()->width()-rect().width()||
            pos().y()< 0 ||pos().y()+rect().height()>scene()->height())
    {
        scene()->removeItem(this);
        delete this;
    }
}

void ShooterEnemy::collision()
{
    //collision!! edit!! create template!!!
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletPlayer))
        {
            //delete the other bullet
            scene()->removeItem(colliding_items[i]);
            delete colliding_items[i];

            //decrease own health
            health->decrease_health();
            return;
        }
    }
}

void ShooterEnemy::shoot()
{
    static bool created=false;
    if (created==false){
        this->create_health();
        created=true;
    }

    if (!is_shooting) return;

    int dx= rand()%40- rand()%40;

    BulletEnemy* bullet= new BulletEnemy(dx,20);
    bullet->setBrush(Qt::blue);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
