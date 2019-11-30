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
    connect(timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot
    timer->start(50);

    QTimer* timer2= new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot
    timer2->start(50);

    QTimer* timer3= new QTimer();
    connect(timer3, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot
    timer3->start(200);
}

void ShooterPlayer::create_health()
{
    ShooterBase::create_health(0,50);
    health->setDefaultTextColor(Qt:: green);

}

void ShooterPlayer::keyPressEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Left:
            dx = -speed;
            break;
        case Qt::Key_Right:
            dx = speed;
            break;
        case Qt::Key_Up:
            dy = -speed;
            break;
        case Qt::Key_Down:
            dy = speed;
            break;
        case Qt::Key_Space:
            is_shooting = true;
            break;
        default:
            break;
    }
}

void ShooterPlayer::keyReleaseEvent(QKeyEvent* event)
{
    switch (event->key()) {
        case Qt::Key_Left:
        case Qt::Key_Right:
            dx = 0;
            break;
        case Qt::Key_Up:
        case Qt::Key_Down:
            dy = 0;
            break;
        case Qt::Key_Space:
            is_shooting = false;
            break;
        default:
            break;
    }
}

void ShooterPlayer::move()
{
    qreal new_x = x() + (pos().x()+dx>0 && pos().x()+rect().width()+dx<scene()->width() ? dx : 0);
    qreal new_y = y() + (pos().y()+dy>0 && pos().y()+rect().height()+dy<scene()->height() ? dy : 0);
    setPos(new_x, new_y);
}

void ShooterPlayer::collision()
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

void ShooterPlayer::shoot()
{
    static bool created=false;
    if (created==false){
        this->create_health();
        created=true;
    }

    if (!is_shooting) return;

    BulletPlayer* bullet=new BulletPlayer(0,-10);
    bullet->setBrush(Qt::green);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
