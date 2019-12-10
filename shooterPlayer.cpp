#include "shooterPlayer.h"
#include "shooterEnemy.h"
#include "shooterBoss.h"

//static member declaration
bool ShooterPlayer::paused = true;

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
}

void ShooterPlayer::process_powerup(BulletPowerUp* bullet)
{
    switch(bullet->get_power_type()){
        case(BulletPowerUp::Breakpoint): //health increase
            health->increase_health();
            break;

        case(BulletPowerUp::StackOverflow): //clear field
            emit clear_field(false);
            break;

        case(BulletPowerUp::CoutTestEndl): //increase shooter strength
            ++powerup_shooter;
            powerup_timer->start_timer(10000, true, this, SLOT(reset_shooter()));
            break;

        default:
            break;
    }

    emit powerup_text(BulletPowerUp::PowerUpType (bullet->get_power_type()));
}

void ShooterPlayer::move()
{
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
    if (typeid(*collision_item)==typeid(BulletPowerUp))
    {
        process_powerup(dynamic_cast<BulletPowerUp*>(collision_item));
    }
    else //should be either BulletEnemy, ShooterEnemy or ShooterBoss
    {
        if (immune) return false;
        //decrease own health
        health->decrease_health();
        if (health->is_dead())
        {
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
    if (!is_shooting) return;

    shoot_bullet(new BulletPlayer(0, -20));

    if (powerup_shooter > 0){
        shoot_bullet(new BulletPlayer(8, -17));
        shoot_bullet(new BulletPlayer(-8, -17));
    }
}

void ShooterPlayer::reset_shooter()
{
    if (powerup_shooter > 0) --powerup_shooter;
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
