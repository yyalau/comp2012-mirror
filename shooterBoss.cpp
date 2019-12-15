#include "shooterBoss.h"
#include "shooterEnemy.h"

//static member declaration
ShooterPlayer* ShooterBoss::player = nullptr;

ShooterBoss::ShooterBoss(const int hp, const int& dx, const int& dy, const int& shoot_freq, const bool& shoot,
                         const int size_x, const int size_y, const int& move_freq) :
     ShooterBase("Boss", hp, dx, dy, shoot_freq, shoot, size_x, size_y, move_freq)
{
    //TODO: use another sprite
    QPixmap enemyimage(":/image/images/computer.png");
    setPixmap(enemyimage.scaled(this->size_x, this->size_y, Qt::IgnoreAspectRatio));
    setShapeMode(QGraphicsPixmapItem::MaskShape);
    setTransformOriginPoint(boundingRect().width()/2,boundingRect().height()/2);
    setScale(1.5);

    music = new QMediaPlayer();
    music->setMedia(QUrl("qrc:/sounds/sounds/BossExplosion.mp3"));

    move_timer= new CustomTimer(this->move_freq, false, this, SLOT(move()));
    //connect the timer and move slot

    shoot_timer= new CustomTimer(this->shoot_freq, false, this, SLOT(shoot()));
    //connect the timer and bullet slot

    dialogue_timer = new CustomTimer(DIALOGUE_FREQ, false, this, SLOT(show_dialogue()));
    //update dialogue every 5 seconds

    flag_timer = new CustomTimer();
}

ShooterBoss::~ShooterBoss()
{
    //base destructor should be automatically called
    if (health_bar != nullptr) delete health_bar;
    delete dialogue_timer;
    delete flag_timer;
    delete music;
}


inline void ShooterBoss::set_shoot_freq(int shoot_freq)
{
    this->shoot_freq= shoot_freq;
    shoot_timer->set_interval(shoot_freq);
}

void ShooterBoss::set_phase(const BossPhase& phase)
{
    this->phase = phase;
    switch (phase)
    {
        case Entrance:
        case Dialogue:
            //do nothing
            return;
        case PhasePre1:
            set_shoot_freq(4*MIN_FREQ);
            break;
        case Phase1:
            set_shoot_freq(15*MIN_FREQ);
            break;
        case PhasePre2:
            set_shoot_freq(4*MIN_FREQ);
            break;
        case Phase2:
            set_shoot_freq(20*MIN_FREQ);
            break;
        case Phase3:
            set_shoot_freq(40*MIN_FREQ);
            emit start_phase3();
            break;
    }
    //reset phase variables
    phase_dir = 1;
    phase_angle = 0.0;
}

void ShooterBoss::set_player(ShooterPlayer* shooter)
{
    player = shooter;
}

void ShooterBoss::pause()
{
    ShooterBase::pause();
    dialogue_timer->pause();
    flag_timer->pause();
}

void ShooterBoss::unpause()
{
    ShooterBase::unpause();
    dialogue_timer->unpause();
    flag_timer->unpause();
}

void ShooterBoss::show_health()
{
    health_bar = new PopUpDialogue(scene(), "", PopUpDialogue::NO_DURATION, PopUpDialogue::BossHealth);
}

void ShooterBoss::move()
{
    switch (phase)
    {
        case Entrance:
            setPos(x()+dx, y()+dy);
            if (y() >= BOSS_POS_Y)
            {
                set_phase(Dialogue);
                dialogue_counter = 1;
            }
            break;
        case Dialogue:
        {
            //chase after player before PhasePre2 begin, else just moves back to original position
            double target_pos_x = (health->get_health() == PHASE_HEALTH[PhasePre2]) ?
                        player->get_pos().x()-size_x/2 : BOSS_POS_X;
            if (target_pos_x < 0) target_pos_x = 0;
            double x_diff = target_pos_x - pos().x();
            double y_diff = BOSS_POS_Y - pos().y();
            if (x_diff*x_diff + y_diff*y_diff < 100)
            {
                dx = dy = 0;
                setPos(target_pos_x, BOSS_POS_Y);
                if (boss_to_next_phase)
                {
                    for (int i=1; i<5; ++i)
                    {
                        if (health->get_health() == PHASE_HEALTH[i])
                        {
                            set_phase(static_cast<BossPhase>(i));
                            boss_to_next_phase = false;
                            return;
                        }
                    }
                }
            }
            else
            {
                dx = ((x_diff > 0) ? 1 : -1) *
                        static_cast<int>(cos(atan(abs(y_diff/x_diff)))*10);
                dy = ((y_diff > 0) ? 1 : -1) *
                        static_cast<int>(sin(atan(abs(y_diff/x_diff)))*10);
                setPos(x()+dx, y()+dy);
            }

            break;
        }
        case Phase1:
        case Phase3:
            //dont move in these phases
            break;
        case PhasePre1:
        case PhasePre2:
        case Phase2:
        {
            dx = phase_dir * (phase == PhasePre1 ? 4 : 2);
            if (x()+dx > BOSS_POS_X+100) phase_dir = -1;
            else if (x()+dx < BOSS_POS_X-100) phase_dir = 1;

            if (phase == Phase2)
            {
                dy = static_cast<int>(4.5*sin(phase_angle));
                phase_angle += 0.1;
            }
            else dy = 0;

            setPos(x()+dx, y()+dy);
            break;
        }
    }
}

bool ShooterBoss::collision()
{
    if (phase == Entrance || phase == Dialogue /*|| phase == Dead*/) return false;

    //decrease own health
    health->set_health(-1);

    //change the health bar's width
    double current_phase_hp = 0.0;
    for (int i=1; i<6; ++i)
    {
        if (health->get_health() >= PHASE_HEALTH[i])
        {
            current_phase_hp = static_cast<double>(health->get_health()-PHASE_HEALTH[i])/(PHASE_HEALTH[i-1]-PHASE_HEALTH[i]);
            break;
        }
    }
    health_bar->set_width(static_cast<int>(current_phase_hp * GAMEAREA_LENGTH));

    //for phase 2, increase shoot frequency
    if (health->get_health() == (PHASE_HEALTH[Phase2]+PHASE_HEALTH[Phase3])/2)
        set_shoot_freq(12*MIN_FREQ);

    //do something when health reaches checkpoint, activate next phase
    if (health->get_health() == PHASE_HEALTH[phase+1]) // use <= if decrease_health is > 1
    {
        switch (phase)
        {
            case PhasePre1: //show Phase1's pattern name
                new PopUpDialogue(scene(), "IndexOutOfBoundException", 1500, PopUpDialogue::Dialogue);
                flag_timer->start_timer(2000, true, this, SLOT(enable_flag()));
                break;
            case Phase1:    //just enable flag after 1 second
                flag_timer->start_timer(1000, true, this, SLOT(enable_flag()));
                break;
            case PhasePre2: //show Phase2's pattern name
            {
                QString text = "ERROR #2: LEAK " + QString::number(100+rand()%100) + " DIRECT BYTES";
                new PopUpDialogue(scene(), text, 1500, PopUpDialogue::Dialogue);
                flag_timer->start_timer(2000, true, this, SLOT(enable_flag()));
                break;
            }
            case Phase2:    //show Phase3's pattern name
                new PopUpDialogue(scene(), "NullPointerException\nYou cannot move in this phase!", 2500, PopUpDialogue::Dialogue);
                flag_timer->start_timer(3000, true, this, SLOT(enable_flag()));
                break;
            default:
                break;
        }

        //drop a powerup bullet
        if (phase != Phase3) shoot_bullet(new BulletPowerUp(0, 4, BulletPowerUp::Breakpoint));

        set_phase(Dialogue);
    }

    //when health reach 0
    if (health->get_health() == 0)
    {
        //TODO: use another image
        ShooterExplosion* explosion = new ShooterExplosion(size_x, size_y, 2000);
        explosion->setPos(x(), y());
        scene()->addItem(explosion);

        music->play();
        emit boss_dead(true);
    }

    return true;
}

void ShooterBoss::shoot()
{
    if (!is_shooting) return;

    switch (phase)
    {
        case Entrance:
        case Dialogue:
            //do nothing
            return;
        case PhasePre1:
        {
            int bullet_dx = rand()%20 - rand()%20;
            int bullet_dy = 10;
            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            break;
        }
        case Phase1:
        {
            int bullet_dx = static_cast<int>(sin(phase_angle)*15);
            int bullet_dy = 5;

            if (phase_angle > 1.5) phase_dir = -1;  //PI/2 = 1.57
            else if (phase_angle < 0.1) phase_dir = 1;
            phase_angle += phase_dir * 0.08;

            shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::OutOfBound));
            shoot_bullet(new BulletEnemy(-bullet_dx, bullet_dy, BulletEnemy::OutOfBound));
            break;
        }
        case PhasePre2:
        {
            int x_increase = static_cast<int>(40*sin(phase_angle));

            BulletEnemy* bullet_left = new BulletEnemy(0, 10, BulletEnemy::Normal);
            bullet_left->setPos(x()+x_increase, y()+size_y);
            scene()->addItem(bullet_left);

            BulletEnemy* bullet_right = new BulletEnemy(0, 10, BulletEnemy::Normal);
            bullet_right->setPos(x()+size_x-x_increase, y()+size_y);
            scene()->addItem(bullet_right);

            phase_angle += 0.6283;
            if (phase_angle > 6.283)
            {
                phase_angle -= 6.283;
                double x_diff = player->get_pos().x()-pos().x()-size_x/2;
                double y_diff = player->get_pos().y()-pos().y()-size_y/2;
                int bullet_dx = ((x_diff > 0) ? 1 : -1) *
                        static_cast<int>(cos(atan(abs(y_diff/x_diff)))*16);
                int bullet_dy = ((y_diff > 0) ? 1 : -1) *
                        static_cast<int>(sin(atan(abs(y_diff/x_diff)))*16);

                shoot_bullet(new BulletEnemy(bullet_dx, bullet_dy, BulletEnemy::Normal));
            }
            break;
        }
        case Phase2:
        {
            int bullet_x = 100 + rand()%600;
            BulletEnemy* bullet = new BulletEnemy(0, 3, BulletEnemy::Explode);
            bullet->setPos(bullet_x, -20);
            scene()->addItem(bullet);
            break;
        }
        case Phase3:
        {
            int dummy_dir_x = (rand()%2) * 2 - 1; //1 or -1
            int dummy_x = (dummy_dir_x == 1) ? 10 : GAMEAREA_LENGTH-ShooterEnemy::ENEMY_SIZE-10;
            int dummy_y = 200 + rand()%150;

            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::Linear, ShooterEnemy::ExplodeOnDeath, 1, 7*dummy_dir_x, 0);
            enemy->setPos(dummy_x, dummy_y);
            scene()->addItem(enemy);
            scene()->addItem(enemy->health);

            //randomize the enemy spawn rate
            set_shoot_freq((40+rand()%50)*MIN_FREQ);
            break;
        }
    }

}

void ShooterBoss::enable_flag()
{
    boss_to_next_phase = true;
}

void ShooterBoss::show_dialogue()
{
    if (dialogue_counter < 1 || dialogue_counter > 6) return;
    switch (dialogue_counter)
    {
        case 1:
            new PopUpDialogue(scene(), "Looks like you have found me at last.", DIALOGUE_FREQ, PopUpDialogue::Dialogue, 30);
            break;
        case 2:
            new PopUpDialogue(scene(), "I am the massive underlying bug that is \nmaking your program running into \nproblems, crashing left and right.", DIALOGUE_FREQ, PopUpDialogue::Dialogue, 30,SCREEN_HEIGHT/2-35);
            break;
        case 3:
            new PopUpDialogue(scene(), "All because of your unorganized data \nstructures, unhandled dynamic memory \nand lack of documentation.", DIALOGUE_FREQ, PopUpDialogue::Dialogue, 30,SCREEN_HEIGHT/2-35);
            break;
        case 4:
            new PopUpDialogue(scene(), "If you want to get out of here alive, \nyou will have to defeat me.", DIALOGUE_FREQ, PopUpDialogue::Dialogue, 30,SCREEN_HEIGHT/2-20);
            break;
        case 5:
            //the TODO in the dialogue is deliberate
            new PopUpDialogue(scene(), "And I won't go down without a good fight!\nGive it all you've\n//TODO: Finish the dialogues", DIALOGUE_FREQ, PopUpDialogue::Dialogue, 30, SCREEN_HEIGHT/2-35);
            break;
        case 6:
            set_phase(PhasePre1);
            break;
        default:
            return;
    }
    ++dialogue_counter;
}
