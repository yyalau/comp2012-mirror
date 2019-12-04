#include "shooterBoss.h"

ShooterBoss::ShooterBoss(int hp, int dx, int dy, int shoot_freq, bool shoot,
                         int size_x, int size_y, int move_freq, int coll_freq) :
     ShooterBase("Enemy", hp, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, coll_freq)
{
    //TODO: set sprite? i forgot how

    move_timer= new QTimer();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot

    coll_timer= new QTimer();
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot

    shoot_timer= new QTimer();
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot

    //start the timers
    unpause();
}

void ShooterBoss::show_health()
{
    //TODO: we could just print Health: <number>, but maybe it could look better if we have a bar at the bottom
    //of the screen that gets shorter according to the remaining health of the boss
}

void ShooterBoss::pause()
{
    move_timer->stop();
    coll_timer->stop();
    shoot_timer->stop();
}

void ShooterBoss::unpause()
{
    move_timer->start(move_freq);
    coll_timer->start(coll_freq);
    shoot_timer->start(shoot_freq);
}

void ShooterBoss::move()
{
    //TODO: idk probably wont move much anyway
}

void ShooterBoss::collision()
{
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletPlayer))
        {
            //delete the other bullet
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();

            //TODO: do something when health reaches checkpoint, activate next phase or something
        }
    }
}

void ShooterBoss::shoot()
{
    switch (phase)
    {
        //TODO
        default:
            break;
    }
}
