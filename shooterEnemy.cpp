#include "shooterEnemy.h"

ShooterEnemy::ShooterEnemy(int hp, int dx, int dy, int size_x, int size_y,
                           int move_freq, int coll_freq, int shoot_freq, bool shoot) :
       ShooterBase("Enemy", hp, dx, dy, size_x, size_y, move_freq, coll_freq, shoot_freq, shoot)
{
    setBrush(Qt::blue);
    setRect(0, 0, size_x, size_y);

    is_shooting = true;

    move_timer= new QTimer();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot

    coll_timer= new QTimer();
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot

    shoot_timer= new QTimer();
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot

    //start the timers
    unpause();
}

void ShooterEnemy::create_health()
{
    ShooterBase::create_health(0,0);
    health->setDefaultTextColor(Qt:: blue);
}

void ShooterEnemy::pause()
{
    move_timer->stop();
    coll_timer->stop();
    shoot_timer->stop();
}

void ShooterEnemy::unpause()
{
    move_timer->start(move_freq);
    coll_timer->start(coll_freq);
    shoot_timer->start(shoot_freq);
}

void ShooterEnemy::move()
{
    //TODO: Change this to just regular moving, handle how the enemy moves somewhere else
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
    if (!(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x())) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
    {
        REMOVE_ENTITY(this)
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
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();

            //remove if dead
            if (health->is_dead()) {
                REMOVE_ENTITY(this)
                return;
            }
        }
    }
}

void ShooterEnemy::shoot()
{
    if (!is_shooting) return;

    int dx = rand()%40 - rand()%40;

    BulletEnemy* bullet = new BulletEnemy(dx,20);
    bullet->setBrush(Qt::blue);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
