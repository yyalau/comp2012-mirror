#include "shooterPlayer.h"

ShooterPlayer::ShooterPlayer(int hp, int speed, int dx, int dy, int size_x, int size_y,
                             int move_freq, int coll_freq, int shoot_freq, bool shoot) :
         ShooterBase("Player", hp, dx, dy, size_x, size_y, move_freq, coll_freq, shoot_freq, shoot), speed(speed)
{
    setBrush(Qt::green);
    setRect(0, 0, size_x, size_y);

    move_timer= new QTimer();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot

    coll_timer= new QTimer();
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot

    shoot_timer= new QTimer();
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot

    //start the timers
    unpause();
}


void ShooterPlayer::keyPressEvent(QKeyEvent* event)
{
    static bool paused = false;
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
        case Qt::Key_P:
            emit (paused ? unpause_all() : pause_all());
            paused = !paused;
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

void ShooterPlayer::focusOutEvent(QFocusEvent *event)
{
    scene()->setFocusItem(this);
}


void ShooterPlayer::create_health()
{
    ShooterBase::create_health(0,50);
    health->setDefaultTextColor(Qt:: green);
}

void ShooterPlayer::pause()
{
    move_timer->stop();
    coll_timer->stop();
    shoot_timer->stop();
}

void ShooterPlayer::unpause()
{
    move_timer->start(move_freq);
    coll_timer->start(coll_freq);
    shoot_timer->start(shoot_freq);
}

QPointF ShooterPlayer::get_pos()
{
    return pos();
}

void ShooterPlayer::move()
{
    qreal new_x = x() + (INSCREEN_LEFT(pos().x()+dx) && INSCREEN_RIGHT(pos().x()+dx) ? dx : 0);
    qreal new_y = y() + (INSCREEN_UP(pos().y()+dy) && INSCREEN_DOWN(pos().y()+dy) ? dy : 0);
    setPos(new_x, new_y);
}

void ShooterPlayer::collision()
{
    //collision!! edit!!!!!! create template
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletEnemy))
        {
            //delete the other bullet
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();
            if (health->is_dead()) emit player_dead();

            return;
        }
        //TODO: decrease health if hit enemy as well?
    }
}

void ShooterPlayer::shoot()
{
    if (!is_shooting) return;

    BulletPlayer* bullet = new BulletPlayer(0,-20);
    bullet->setBrush(Qt::green);
    bullet->setPos(x(),y());
    scene()->addItem(bullet);

}
