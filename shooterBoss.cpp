#include "shooterBoss.h"

ShooterBoss::ShooterBoss(int hp, int dx, int dy, int shoot_freq, bool shoot,
                         int size_x, int size_y, int move_freq, int coll_freq) :
     ShooterBase("Boss", hp, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq, coll_freq)
{
    //TODO: use another sprite
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

ShooterBoss::~ShooterBoss()
{
    if (health_bar != nullptr) delete health_bar;
    //TODO: add delete for timers? i forgot if overriden destructor calls base destructor
}

void ShooterBoss::show_health()
{
    health_bar = new PopUpDialogue(scene(), "", PopUpDialogue::BossHealth);

    //for debug
    health->setPos(SCREEN_LENGTH, 40);
    scene()->addItem(health);
    health->setDefaultTextColor(Qt::green);
}

void ShooterBoss::start_bossfight()
{
    if (phase != Dialogue) return; //wrong phase to call
    phase = PhasePre1;
}

void ShooterBoss::move()
{
    //TODO: for Dialogue, move to the top center. use this for transition between phases (does not attack)
    switch (phase)
    {
        case Dialogue:
        {
        //TODO: #define 250, 0 or something, basically boss's initial position (top center)
            double x_diff = 250 - pos().x();
            double y_diff = 0 - pos().y();
            if (x_diff*x_diff + y_diff*y_diff < 25)
            {
                dx = dy = 0;
                setPos(250, 0);
                if (boss_to_next_phase)
                {
                    for (int i=0; i<4; ++i)
                    {
                        if (health->get_health() == PHASE_HEALTH[i])
                        {
                            phase = static_cast<BossPhase>(i);
                            boss_to_next_phase = false;
                            return;
                        }
                    }
                }
            }
            else
            {
                dx = ((x_diff > 0) ? 1 : -1) *
                        static_cast<int>(cos(atan(abs(y_diff/x_diff)))*5);
                dy = ((y_diff > 0) ? 1 : -1) *
                        static_cast<int>(sin(atan(abs(y_diff/x_diff)))*5);
                setPos(x()+dx, y()+dy);
            }

            break;
        }
        case Phase1:
        case Phase2:
        case Phase3:
            //dont move in these phases
            break;
        case PhasePre1:
        {
            static int x_dir = 1;
            dy = 0;
            dx = x_dir * 3;
            if (x()+dx > 350) x_dir = -1;
            else if (x()+dx < 150) x_dir = 1;
            setPos(x()+dx, y());
            break;
        }
        case PhasePre2:
            break;
    }
}

void ShooterBoss::collision()
{
    if (phase == Dialogue) return;
    QList<QGraphicsItem*> colliding_items= scene()->collidingItems(this);

    for(int i=0; i<colliding_items.size(); ++i){
        if (typeid(*(colliding_items[i]))==typeid (BulletPlayer))
        {
            //delete the other bullet
            REMOVE_ENTITY(colliding_items[i])

            //decrease own health
            health->decrease_health();

            //TODO: change 1000 to max_hp
            //TODO: show health for individual phases?
            health_bar->set_width(static_cast<int>(static_cast<double>(health->get_health())/1000 * SCREEN_LENGTH));

            //TODO: do something when health reaches checkpoint, activate next phase
            if (phase == Phase3) continue;
            //phase should be from -1 to 2
            if (health->get_health() == PHASE_HEALTH[phase+1]) // use <= if decrease_health is > 1
            {
                phase = Dialogue;
                boss_to_next_phase = true;
                return;
            }

            //TODO: when health reach 0
        }
    }
}

void ShooterBoss::shoot()
{
    if (!is_shooting) return;

    int bullet_dx, bullet_dy;
    BulletEnemy::BulletType bullet_type;

    switch (phase)
    {
        case Dialogue:
            //do nothing
            return;
        case PhasePre1:
            shoot_freq = 2*MIN_FREQ;
            bullet_dx = rand()%20 - rand()%20;
            bullet_dy = 10;
            bullet_type = BulletEnemy::Normal;
            break;
        case Phase1:
        {
            static double angle = 0;
            static int dir = 1;
            shoot_freq = 6*MIN_FREQ;

            bullet_dx = static_cast<int>(sin(angle)*15);
            bullet_dy = static_cast<int>(cos(angle)*15);
            bullet_type = BulletEnemy::OutOfBound;

            if (angle > 1.4) dir = -1;  //PI/2 = 1.57
            else if (angle < 0.1) dir = 1;
            angle += dir * 0.1;
            break;
        }
        case PhasePre2:
            break;
        case Phase2:
            break;
        case Phase3:
            break;
    }

    //BulletEnemy* bullet = new BulletEnemy(bullet_dx, bullet_dy, bullet_type);
    //bullet->setBrush(Qt::blue);
    //bullet->setPos(x()+size_x/2, y()+size_y/2);
    //scene()->addItem(bullet);

    shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, bullet_type));
}
