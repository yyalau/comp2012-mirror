#include "shooterPlayer.h"
#include "shooterEnemy.h"
#include "bulletEnemy.h"

ShooterPlayer::ShooterPlayer(int hp, int dx, int dy, int shoot_freq,  bool shoot,
                             int size_x, int size_y, int move_freq, int coll_freq) :
         ShooterBase("Player", hp, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, coll_freq)
{
    QPixmap shooterimage(":/image/images/shooter.png");
    setPixmap(shooterimage.scaled(size_x, size_y, Qt::KeepAspectRatio));
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.3);

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

QPointF ShooterPlayer::get_pos()
{
    return pos();
}

void ShooterPlayer::process_powerup(BulletPowerUp* bullet)
{
    switch(bullet->get_power_type()){

        case(BulletPowerUp::PowerUpType::Breakpoint): //health increase
            health->increase_health();
            qDebug()<<"increase health";
            break;

        case(BulletPowerUp::PowerUpType::CoutTestEndl): //increase shooter strength
            qDebug()<<"increase shooter strength";
            powerup_shooter=true;
            QTimer::singleShot(10000,this,SLOT(normal_shooter()));
            break;

        case(BulletPowerUp::PowerUpType::StackOverflow): //clear field
            qDebug()<<"clear field";    //TODO: Put as separate function in gameEvent, in case we need field clear for restart?
        {   QList<QGraphicsItem*> scene_items = scene()->items();

            for(int i=0; i<scene_items.size(); i++){
                if (typeid(*(scene_items[i]))==typeid (BulletEnemy)||typeid(*(scene_items[i]))==typeid (ShooterEnemy))
                    REMOVE_ENTITY(scene_items[i]);

            }
        }
            break;


         default: break;
    }
}

void ShooterPlayer::move()
{
    double new_x = x() + (INSCREEN_LEFT(pos().x()+dx) && INSCREEN_RIGHT(pos().x()+dx) ? dx : 0);
    double new_y = y() + (INSCREEN_UP(pos().y()+dy) && INSCREEN_DOWN(pos().y()+dy) ? dy : 0);
    setPos(new_x, new_y);
}

void ShooterPlayer::collision()
{

    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    //handling powerup
    for(int i=0; i<colliding_items.size(); i++){
        if(typeid(*(colliding_items[i]))==typeid (BulletPowerUp)){

            scene()->removeItem(colliding_items[i]);
            BulletPowerUp* temp= dynamic_cast<BulletPowerUp*>(colliding_items[i]);
            process_powerup(temp);
            delete colliding_items[i];
        }
    }


    //immune handling. if immune_counter > 0, count up until 50 then set back to 0
    if (immune_counter > 0)
    {
        ++immune_counter;
        //TODO: do something with the sprite? blink?
        if (immune_counter == 50) immune_counter = 0;
        return;
    }

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletEnemy))
        {
            //delete the enemies bullet
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();
            if (health->is_dead()) emit player_dead();

            immune_counter = 1;
            return;
        }
        else if (typeid(*(colliding_items[i]))==typeid (ShooterEnemy))
        {
            //decrease own health
            health->decrease_health();
            if (health->is_dead()) emit player_dead();

            immune_counter = 1;
            return;
        }
    }

}

void ShooterPlayer::shoot()
{
    if (!is_shooting) return;

    //BulletPlayer* bullet = new BulletPlayer(0,-20);
    //bullet->setPos(x()-size_x/6, y()-size_y);
    //scene()->addItem(bullet);
    shoot_bullet(new BulletPlayer(0, -20));

    if (powerup_shooter==true){
        BulletPlayer* bullet2 = new BulletPlayer(-10,-20);
        bullet2->setPos(x()-size_x/6, y()-size_y);
        scene()->addItem(bullet2);

        BulletPlayer* bullet3 = new BulletPlayer(10,-20);
        bullet3->setPos(x()-size_x/6, y()-size_y);
        scene()->addItem(bullet3);
    }

}

void ShooterPlayer::normal_shooter()
{
    powerup_shooter=false;
}
