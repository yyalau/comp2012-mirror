#include "shooterPlayer.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QDebug>
#include <QTimer>
#include <QGraphicsRectItem>
#include "bulletPlayer.h"
#include "bulletEnemy.h"

ShooterPlayer::ShooterPlayer(): ShooterBase("Player")
{
    setBrush(Qt::green);
    setRect(0,0,50,40);

    QTimer* timer= new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(check_health())); //connect the timer and the bullet
    timer->start(50);
}

void ShooterPlayer::create_health()
{
    ShooterBase::create_health(0,50);
    health->setDefaultTextColor(Qt:: green);

}
void ShooterPlayer::keyPressEvent(QKeyEvent* event) //try to implement arrow keys and space bar tgt!!!!
{

    if (event->key() ==Qt::Key_Left){
        if (pos().x()>0)
            setPos(x()-10,y());
    }
    if(event->key()==Qt::Key_Right){
        if (pos().x()+rect().width()<scene()->width())
            setPos(x()+10,y());
    }
    if(event->key()==Qt::Key_Up){
        if (pos().y()>0)
            setPos(x(), y()-10);
    }
    if(event->key()==Qt::Key_Down){
        if (pos().y()+rect().height()<scene()->height())
        setPos(x(),y()+10);
    }
    if(event->key()==Qt::Key_Space){
        BulletPlayer* bullet=new BulletPlayer(0,-10);
        bullet->setBrush(Qt::green);
        bullet->setPos(x(),y());
        scene()->addItem(bullet);
    }
}

void ShooterPlayer::check_health()
{
    static bool created=false;
    if (created==false){
        create_health();
        created=true;
    }

    //collision!! edit!!!!!! create template
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletEnemy))
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
