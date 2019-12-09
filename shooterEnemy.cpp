#include "shooterEnemy.h"

//static member declaration
ShooterPlayer* ShooterEnemy::player = nullptr;

ShooterEnemy::ShooterEnemy(EnemyPathingType pathing_type, EnemyShootingType shooting_type,
                           int hp, int dx, int dy, int shoot_freq, bool shoot,
                           int size_x, int size_y, int move_freq, int coll_freq) :
       ShooterBase("Enemy", hp, false, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, coll_freq),
       pathing_type(pathing_type), shooting_type(shooting_type)
{
    QPixmap enemyimage(":/image/images/computer.png");
    setPixmap(enemyimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);

    move_timer= new QTimer();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot

    coll_timer= new QTimer();
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot

    shoot_timer= new QTimer();
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot

    //start the timers
    unpause();
}

void ShooterEnemy::set_player(ShooterPlayer* shooter)
{
    player = shooter;
}

void ShooterEnemy::move()
{
    switch (pathing_type)
    {
        case Linear:
            //do nothing, should set speed in constructor already
            setPos(x()+dx,y()+dy);
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
            setPos(x()+dx,y()+dy);
        break;
        case Circular:
            QPainterPath circularpath;
            circularpath.addEllipse(100,50,400,200);
            QPoint temp=circularpath.pointAtPercent(circular_angle).toPoint();
            setPos(temp);
            circular_angle+=0.007;
            if(circular_angle>1){circular_angle=0;}
        break;
    }

    //show and move health
    health->setPos(x()+size_x,y());

    //remove once its out of bound
    if (!(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x())) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
    {
        REMOVE_ENTITY(this)
    }
}

void ShooterEnemy::collision()
{
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
                if (shooting_type == ExplodeOnDeath)
                {
                    double x_diff = player->get_pos().x()-pos().x();
                    double y_diff = player->get_pos().y()-pos().y();
                    int bullet_dx = ((x_diff > 0) ? 1 : -1) *
                            static_cast<int>(cos(atan(abs(y_diff/x_diff)))*20);
                    int bullet_dy = ((y_diff > 0) ? 1 : -1) *
                            static_cast<int>(sin(atan(abs(y_diff/x_diff)))*20);

                    shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
                }

                REMOVE_ENTITY(this)

                return;
            }
        }
    }
}

void ShooterEnemy::shoot()
{
    if (!is_shooting) return;

    switch (shooting_type)
    {
        case Random:
        {
            int bullet_dx = rand()%20 - rand()%20;
            int bullet_dy = 12;

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            break;
        }
        case AimAtPlayer:
        {
            double x_diff = player->get_pos().x()-pos().x();
            double y_diff = player->get_pos().y()-pos().y();
            int bullet_dx = ((x_diff > 0) ? 1 : -1) *
                    static_cast<int>(cos(atan(abs(y_diff/x_diff)))*16);
            int bullet_dy = ((y_diff > 0) ? 1 : -1) *
                    static_cast<int>(sin(atan(abs(y_diff/x_diff)))*16);

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            break;
        }
        case Circle:
        {
            double angle = 0.0;
            while (angle < 6.2831)
            {
                int bullet_dx = static_cast<int>(cos(angle)*8);
                int bullet_dy = static_cast<int>(sin(angle)*8);

                shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));

                angle += 0.5236;    //shoot in 12 directions
            }
            break;
        }
        case ExplodeOnDeath:    //this type does not shoot in boss's 3rd phase
        case NoShooting:
            break;
        default:
            break;
    }

}
