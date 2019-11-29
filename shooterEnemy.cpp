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

    QTimer* timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and the bullet
    timer->start(50);

    QTimer* timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(shoot_bullets())); //connect the timer and the bullet
    timer2->start(200);
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
        setPos(x()-10,0);
        if (x()<100)
            left=false;
    }
    else {
        setX(x()+10);
        if (x()>700)
            left=true;
    }
}

void ShooterEnemy::shoot_bullets()
{
    static bool created=false;
    if (created==false){
        this->create_health();
        created=true;
    }

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

    int dx= rand()%40- rand()%40;

    BulletEnemy* bullet= new BulletEnemy(dx,20);
    bullet->setBrush(Qt::blue);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
