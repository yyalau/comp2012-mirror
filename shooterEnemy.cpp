#include "shooterEnemy.h"

ShooterEnemy::ShooterEnemy(EnemyPathingType pathing_type, EnemyShootingType shooting_type,
                           int hp, int dx, int dy, int size_x, int size_y,
                           int move_freq, int coll_freq, int shoot_freq, bool shoot) :
       ShooterBase("Enemy", hp, dx, dy, size_x, size_y, move_freq, coll_freq, shoot_freq, shoot),
       pathing_type(pathing_type), shooting_type(shooting_type)
{
    QPixmap enemyimage(":/image/images/computer.png");
    setPixmap(enemyimage.scaled(ENEMY_SIZE,ENEMY_SIZE,Qt::KeepAspectRatio));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);

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

void ShooterEnemy::set_player(ShooterPlayer* shooter)
{
    this->shooter = shooter;
}

void ShooterEnemy::move()
{
    switch (pathing_type)
    {
        case Linear:
            //do nothing, should set speed in constructor already
            break;
        case BorderBounce:
            if (!(INSCREEN_LEFT(pos().x()+dx)) || !(INSCREEN_RIGHT(pos().x()+dx)))
            {
                dx = -dx;
            }
            if (!(INSCREEN_UP(pos().y()+dy)) || !(INSCREEN_DOWN(pos().y()+dy)))
            {
                dy = -dy;
            }
            break;
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

    int bullet_dx, bullet_dy;

    switch (shooting_type)
    {
        case Random:
            bullet_dx = rand()%20 - rand()%20;
            bullet_dy = 10;
            break;
        case AimAtPlayer:
            double x_diff = shooter->get_pos().x()-pos().x();
            double y_diff = shooter->get_pos().y()-pos().y();
            bullet_dx = ((x_diff > 0) ? 1 : -1) *
                    static_cast<int>(cos(atan(abs(y_diff/x_diff)))*20);
            bullet_dy = ((y_diff > 0) ? 1 : -1) *
                    static_cast<int>(sin(atan(abs(y_diff/x_diff)))*20);
            break;
    }

    BulletEnemy* bullet = new BulletEnemy(bullet_dx, bullet_dy);
    //bullet->setBrush(Qt::blue);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
