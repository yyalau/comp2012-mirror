#include "shooterEnemy.h"
#include "bulletPowerUp.h"

//static member declaration
ShooterPlayer* ShooterEnemy::player = nullptr;

ShooterEnemy::ShooterEnemy(const EnemyPathingType& pathing_type, const EnemyShootingType& shooting_type,
                           const int& hp, const int& dx, const int& dy, const int& shoot_freq, const bool& shoot,
                           const int size_x, const int size_y, const int& move_freq) :
       ShooterBase("Enemy", hp, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, NUM_SOUND_TYPES),
       pathing_type(pathing_type), shooting_type(shooting_type)
{
    QPixmap enemyimage(":/image/images/bugbullet2.png");
    setPixmap(enemyimage.scaled(size_x, size_y, Qt::IgnoreAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);

    //type-specific variables initialization
    cirPathCounter=0.00;
    target_pos.setX(pos().toPoint().x());
    target_pos.setY(pos().toPoint().y());


    move_timer= new CustomTimer(this->move_freq, false, this, SLOT(move()));
    //connect the timer and move slot

    shoot_timer= new CustomTimer(this->shoot_freq, false, this, SLOT(shoot()));
    //connect the timer and bullet slot

    sound = new QMediaPlayer*[NUM_SOUND_TYPES];
    sound[Hurt] = new QMediaPlayer();
    sound[Hurt]->setMedia(QUrl("qrc:/sounds/sounds/enemygetshot.mp3"));

}

void ShooterEnemy::set_player(ShooterPlayer* shooter)
{
    player = shooter;
}

void ShooterEnemy::set_drop_powerup()
{
    drop_powerup = true;
}

void ShooterEnemy::set_targetPos(int x, int y)
{
    target_pos.setX(x);
    target_pos.setY(y);
}

bool ShooterEnemy::out_of_bound()
{
    //remove once its out of bound
    return !(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x(), this)) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y(), this));
}

void ShooterEnemy::safe_kill()
{
    //set health = 0
    health->set_health(-health->get_health());
    //still drop powerup and create explosion
    if (drop_powerup)
    {
        shoot_bullet(new BulletPowerUp(0, 4));
    }
    ShooterExplosion* explosion = new ShooterExplosion(size_x, size_y);
    explosion->setPos(x(), y());
    scene()->addItem(explosion);
    //remove
    REMOVE_ENTITY(scene(), this);
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
            if (!(INSCREEN_LEFT_RIGID(pos().x()+dx)) || !(INSCREEN_RIGHT_RIGID(pos().x()+dx, this)))
            {
                dx = -dx;
            }
            if (!(INSCREEN_UP_RIGID(pos().y()+dy)) || !(INSCREEN_DOWN_RIGID(pos().y()+dy, this)))
            {
                dy = -dy;
            }
            setPos(x()+dx,y()+dy);
        break;
        case Circular:
          {
            QPainterPath circularpath;
            circularpath.addEllipse(100,50,600,200);

            if(pos().toPoint().x()==699&&pos().toPoint().y()==157)
                cirPathCounter=0.01;
            else if(pos().toPoint().x()==254&&pos().toPoint().y()==237)
                cirPathCounter=0.33;
            else if(pos().toPoint().x()==238&&pos().toPoint().y()==66)
            cirPathCounter=0.67;

            cirPathCounter+=0.004;
            if(cirPathCounter>1){cirPathCounter=0;}
            QPoint temp=circularpath.pointAtPercent(cirPathCounter).toPoint();
            setPos(temp);

          }
        break;
        case GotoTarget:
            {
                int x_diff = target_pos.x() - pos().toPoint().x();
                int y_diff = target_pos.y() - pos().toPoint().y();
                if(abs(x_diff)>=10){
                    dx = (x_diff>0?1:-1) * static_cast<int>(cos(atan(abs(y_diff/x_diff)))*5);
                } else dx=0;
                if(abs(y_diff)>10){
                    dy = (y_diff>0?1:-1) * static_cast<int>(sin(atan(abs(y_diff/x_diff)))*5);
                } else dy=0;
                setPos(x()+dx,y()+dy);
                break;
            }
        case Wave:
            {
                QPainterPath path;
                if(target_pos.x()<400){
                    path.moveTo(target_pos);
                    path.quadTo(target_pos.x()+133,target_pos.y()-100,target_pos.x()+266,target_pos.y());
                    path.quadTo(target_pos.x()+399,target_pos.y()+100,target_pos.x()+532,target_pos.y());
                    path.quadTo(target_pos.x()+660,target_pos.y()-100,target_pos.x()+750,target_pos.y());
                }else{
                    path.moveTo(target_pos);
                    path.quadTo(target_pos.x()-133,target_pos.y()+100,target_pos.x()-266,target_pos.y());
                    path.quadTo(target_pos.x()-399,target_pos.y()-100,target_pos.x()-532,target_pos.y());
                    path.quadTo(target_pos.x()-660,target_pos.y()+100,target_pos.x()-750,target_pos.y());
                }
                cirPathCounter+=(dy/120.000);
                if (cirPathCounter>=0.99){dy=-1;}
                else if(cirPathCounter<=0.01){dy=1;}

                setPos(path.pointAtPercent(cirPathCounter).toPoint().x(),path.pointAtPercent(cirPathCounter).toPoint().y());
                break;

            }
    }

    //show and move health, the additional values are for health number placement on the sprite
    health->setPos(x() + 4 + (health->get_health()<10?4:0), y() - 9);

    if (out_of_bound())
        REMOVE_ENTITY(scene(), this);
}

bool ShooterEnemy::collision()
{
    //decrease own health
    health->set_health(-1);

    if (health->get_health() == 0)
    {
        if (shooting_type == ExplodeOnDeath)
        {
            double x_diff = player->get_pos().x()-pos().x()-size_x/2;
            double y_diff = player->get_pos().y()-pos().y()-size_y/2;
            int bullet_dx = ((x_diff > 0) ? 1 : -1) *
                    static_cast<int>(cos(atan(abs(y_diff/x_diff)))*20);
            int bullet_dy = ((y_diff > 0) ? 1 : -1) *
                    static_cast<int>(sin(atan(abs(y_diff/x_diff)))*20);

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
        }
        if (drop_powerup)
        {
            shoot_bullet(new BulletPowerUp(0, 4));
        }
        //call explosion
        ShooterExplosion* explosion = new ShooterExplosion(size_x, size_y);
        explosion->setPos(x(), y());
        scene()->addItem(explosion);

    }
    else
    {
        play_sound(sound[Hurt]);
    }

    return true;
}

void ShooterEnemy::shoot()
{
    if (!is_shooting) return;

    switch (shooting_type)
    {
        case Random:
        {
            int bullet_dx = RANDOM(-20, 20);
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
        case Forward:
        {
            int bullet_dx = 0;
            int bullet_dy = 10;

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            break;
        }
        case Triple:
        {
            int bullet_dx = 0;
            int bullet_dy = 10;

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            shoot_bullet(new BulletEnemy(5, bullet_dy, BulletEnemy::Normal));
            shoot_bullet(new BulletEnemy(-5, bullet_dy, BulletEnemy::Normal));
            break;
        }
        case Double:
        {
            int bullet_dx = 5;
            int bullet_dy = 10;
            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            shoot_bullet(new BulletEnemy(-bullet_dx, bullet_dy, BulletEnemy::Normal));
      
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
