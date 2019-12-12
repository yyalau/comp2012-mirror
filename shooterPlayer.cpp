#include "shooterPlayer.h"
#include "shooterEnemy.h"
#include "shooterBoss.h"

//static member declaration
bool ShooterPlayer::paused = true;
bool ShooterPlayer::dead = false;

ShooterPlayer::ShooterPlayer(int hp, int dx, int dy, int shoot_freq,  bool shoot,
                             int size_x, int size_y, int move_freq) :
         ShooterBase("Player", hp, true, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq)
{
    set_sprite(":/image/images/shooter.png");

    move_timer= new CustomTimer(move_freq, false, this, SLOT(move()));
    //connect the timer and move slot

    shoot_timer= new CustomTimer(shoot_freq, false, this, SLOT(shoot()));
    //connect the timer and bullet slot

    powerup_timer = new CustomTimer();
    immune_timer = new CustomTimer();
}

inline void ShooterPlayer::set_sprite(const char *sprite)
{
    QPixmap shooterimage(sprite);
    setPixmap(shooterimage.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.3);
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
        case Qt::Key_P:
            emit (paused ? unpause_all() : pause_all());
            break;
        case Qt::Key_R:
            //only enable this at pause/gameover, also resets the player's position
            if (!paused) break;
            emit clear_field(true);
            nullptr_phase = false;
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

QPointF ShooterPlayer::get_pos()
{
    return pos();
}

void ShooterPlayer::pause()
{
    ShooterBase::pause();
    powerup_timer->pause();
    immune_timer->pause();
    paused = true;
}

void ShooterPlayer::unpause()
{
    ShooterBase::unpause();
    powerup_timer->unpause();
    immune_timer->unpause();
    paused = false;
    if (dead)
    {
        set_sprite(":/image/images/shooter.png");
        dead = false;
    }
}

void ShooterPlayer::process_powerup(BulletPowerUp* bullet)
{
    switch(bullet->get_power_type()){
        case(BulletPowerUp::Breakpoint): //health increase
            health->set_health(+1);
            break;

        case(BulletPowerUp::StackOverflow): //clear field
            emit clear_field(false);
            break;

        case(BulletPowerUp::CoutTestEndl): //increase shooter strength
            if(powerup_shooter>0) powerup_timer->stop(); //stop the previous powerup_timer call first
            powerup_shooter+=10;
            powerup_timer->start_timer(1000, false, this, SLOT(reset_shooter()));
            break;

        default:
            break;
    }

    emit powerup_text(BulletPowerUp::PowerUpType (bullet->get_power_type()));
}

void ShooterPlayer::move()
{
    if (dead) return;
    if (nullptr_phase)   //move to initial position
    {
        double x_diff = START_POS_X - pos().x();
        double y_diff = START_POS_Y - pos().y();
        if (x_diff*x_diff + y_diff*y_diff < 100)
        {
            dx = dy = 0;
            setPos(START_POS_X, START_POS_Y);
        }
        else
        {
            dx = ((x_diff > 0) ? 1 : -1) *
                    static_cast<int>(cos(atan(abs(y_diff/x_diff)))*10);
            dy = ((y_diff > 0) ? 1 : -1) *
                    static_cast<int>(sin(atan(abs(y_diff/x_diff)))*10);
            setPos(x()+dx, y()+dy);
        }
        return;
    }
    double new_x = x() + (INSCREEN_LEFT_RIGID(pos().x()+dx) && INSCREEN_RIGHT_RIGID(pos().x()+dx) ? dx : 0);
    double new_y = y() + (INSCREEN_UP_RIGID(pos().y()+dy) && INSCREEN_DOWN_RIGID(pos().y()+dy) ? dy : 0);
    setPos(new_x, new_y);
}

bool ShooterPlayer::collision()
{
    //do nothing, should not use this collision
    return false;
}

bool ShooterPlayer::collision(QGraphicsItem* collision_item)
{
    if (dead) return false;
    if (typeid(*collision_item)==typeid(BulletPowerUp))
    {
        process_powerup(dynamic_cast<BulletPowerUp*>(collision_item));
    }
    else //should be either BulletEnemy, ShooterEnemy or ShooterBoss
    {
        if (immune) return false;
        //decrease own health
        health->set_health(-1);

        if (health->is_dead())
        {
            dead = true;
            //set pixmap as null
            setPixmap(QPixmap());
            //TODO: use another explosion image idk
            ShooterExplosion* explosion = new ShooterExplosion(size_x, size_y);
            explosion->setPos(x(), y());
            scene()->addItem(explosion);
            emit player_dead(false);
        }
        else
        {
            immune = true;
            set_sprite(":/image/images/shooter_hurt.png");
            immune_timer->start_timer(1000, true, this, SLOT(reset_immunity()));
        }
    }
    //return true if item is a bullet (delete), false if item is an enemy
    return (dynamic_cast<ShooterBase*>(collision_item) == nullptr);
}

void ShooterPlayer::shoot()
{
    if (!is_shooting || dead) return;

    shoot_bullet(new BulletPlayer(0, -20));

    if (powerup_shooter > 0){
        if (powerup_shooter_counter == 2)
        {
            shoot_bullet(new BulletPlayer(8, -17));
            shoot_bullet(new BulletPlayer(-8, -17));
            powerup_shooter_counter = 0;
        }
        else ++powerup_shooter_counter;
    }
}

void ShooterPlayer::reset_shooter()
{
    if (powerup_shooter > 0)
    {
        emit shooter_text(--powerup_shooter);
        //TODO: remove ALL qDebug()
        qDebug()<<powerup_shooter;
    }
    else{
        powerup_timer->stop();
    }
}

void ShooterPlayer::reset_immunity()
{
    immune = false;
    set_sprite(":/image/images/shooter.png");
}

void ShooterPlayer::begin_phase3()
{
    nullptr_phase = true;
}
