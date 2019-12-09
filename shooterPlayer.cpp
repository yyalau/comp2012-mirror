#include "shooterPlayer.h"
#include "shooterEnemy.h"
#include "shooterBoss.h"

//static member declaration
bool ShooterPlayer::paused = true;

ShooterPlayer::ShooterPlayer(int hp, int dx, int dy, int shoot_freq,  bool shoot,
                             int size_x, int size_y, int move_freq, int coll_freq) :
         ShooterBase("Player", hp, true, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, coll_freq)
{
    QPixmap shooterimage(":/image/images/shooter.png");
    setPixmap(shooterimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.3);

    move_timer= new QTimer();
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move())); //connect the timer and move slot

    coll_timer= new QTimer();
    connect(coll_timer, SIGNAL(timeout()), this, SLOT(collision())); //connect the timer and collision slot

    shoot_timer= new QTimer();
    connect(shoot_timer, SIGNAL(timeout()), this, SLOT(shoot())); //connect the timer and bullet slot

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
            paused = !paused;
            break;
        case Qt::Key_R:
            //only enable this at pause/gameover, also resets the player's position
            if (!paused) break;
            emit clear_field(true);
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

void ShooterPlayer::process_powerup(BulletPowerUp* bullet)
{
    switch(bullet->get_power_type()){
        //TODO: dialogue (just call new PopUpDialogue and put the dialogue lifetime in)
        case(BulletPowerUp::Breakpoint): //health increase
            health->increase_health();
            qDebug()<<"increase health";
            break;

        case(BulletPowerUp::StackOverflow): //clear field
            qDebug()<<"clear field";
            emit clear_field(false);
            break;

        case(BulletPowerUp::CoutTestEndl): //increase shooter strength
            qDebug()<<"increase shooter strength";
            powerup_shooter=true;
            QTimer::singleShot(10000, this, SLOT(reset_shooter()));
            break;

         default: break;
    }

    emit powerup_text(BulletPowerUp::PowerUpType (bullet->get_power_type()));
}

void ShooterPlayer::move()
{
    if (nullptr_phase)   //move to initial position
    {
        double x_diff = START_POS_X - pos().x();
        double y_diff = START_POS_Y - pos().y();
        if (x_diff*x_diff + y_diff*y_diff < 25)
        {
            dx = dy = 0;
            setPos(START_POS_X, START_POS_Y);
        }
        else
        {
            dx = ((x_diff > 0) ? 1 : -1) *
                    static_cast<int>(cos(atan(abs(y_diff/x_diff)))*5);
            dy = ((y_diff > 0) ? 1 : -1) *
                    static_cast<int>(sin(atan(abs(y_diff/x_diff)))*5);
            setPos(x()+dx, y()+dy);
        }
        return;
    }
    double new_x = x() + (INSCREEN_LEFT(pos().x()+dx) && INSCREEN_RIGHT(pos().x()+dx) ? dx : 0);
    double new_y = y() + (INSCREEN_UP(pos().y()+dy) && INSCREEN_DOWN(pos().y()+dy) ? dy : 0);
    setPos(new_x, new_y);
}

void ShooterPlayer::collision()
{
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    //power up bullet should not be affected by immunity?
    for (int i=0;i<colliding_items.size(); ++i ){
    if(typeid(*(colliding_items[i]))==typeid (BulletPowerUp)){
                process_powerup(dynamic_cast<BulletPowerUp*>(colliding_items[i]));
                REMOVE_ENTITY(colliding_items[i])
            }
    }

    if (immune) return;

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletEnemy))
        {
            //delete the enemies bullet
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();
            if (health->is_dead())
            {
                emit player_dead();
                return;
            }
            else
            {
                immune = true;
                QTimer::singleShot(1000, this, SLOT(reset_immunity()));
            }
        }
        else if (typeid(*(colliding_items[i]))==typeid (ShooterEnemy) || typeid(*(colliding_items[i]))==typeid (ShooterBoss))
        {
            //decrease own health
            health->decrease_health();
            if (health->is_dead())
            {
                emit player_dead();
                return;
            }
            else
            {
                immune = true;
                QTimer::singleShot(1000, this, SLOT(reset_immunity()));
            }
        }
    }
}

void ShooterPlayer::shoot()
{
    if (!is_shooting) return;

    shoot_bullet(new BulletPlayer(0, -20));

    if (powerup_shooter==true){
        shoot_bullet(new BulletPlayer(10, -20));
        shoot_bullet(new BulletPlayer(-10, -20));
    }
}

void ShooterPlayer::reset_shooter()
{
    powerup_shooter=false;
}

void ShooterPlayer::reset_immunity()
{
    immune = false;
}

void ShooterPlayer::begin_phase3()
{
    nullptr_phase = true;
}
