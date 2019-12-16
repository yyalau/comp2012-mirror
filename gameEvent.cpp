#include "gameEvent.h"

//static member declaration
bool GameEvent::game_begin = false;

GameEvent::GameEvent(QGraphicsScene* parent_scene, ShooterPlayer* shooter, const QString& instructions) :
    parent_scene(parent_scene), shooter(shooter)
{

    event_timer = new CustomTimer(MIN_FREQ, false, this, SLOT(increment_time()));

    //connect the timer and time increase slot
    connect(this, SIGNAL(time_reached(int)), this, SLOT(trigger_event(int))); //when time is reached, trigger game events

    //start game dialogue
    dialogue = new PopUpDialogue(parent_scene, instructions, PopUpDialogue::NO_DURATION, PopUpDialogue::FullScreen,50,100);

    //for starting/pausing/unpausing the game
    connect(shooter, SIGNAL(start_signal()), this, SLOT(start_game()));
    connect(shooter, SIGNAL(pause_all()), this, SLOT(pause_game()));
    connect(shooter, SIGNAL(unpause_all()), this, SLOT(unpause_game()));

    //powerup clearfield/ restart
    connect(shooter, SIGNAL(clear_field(bool)), this, SLOT(trigger_clear_field(bool)));

    //for handling game over
    connect(shooter, SIGNAL(player_dead(bool)), this, SLOT(trigger_game_over(bool)));

    //Game is paused at the beginning
    pause_game();
}

GameEvent::~GameEvent()
{
    if (dialogue != nullptr) {delete dialogue; dialogue=nullptr;}
    delete event_timer;
}

int GameEvent::get_time()
{
    return game_timer;
}

//helper template
template <typename T>
QList<QGraphicsItem*> filter_items(QList<QGraphicsItem*> all_items)
{
    //From a QList, remove all items except ones of type T
    for (int i=0; i<all_items.size(); ++i)
    {
        if (dynamic_cast<T*>(all_items[i]) == nullptr)
        {
            all_items.removeAt(i);
            --i;
        }
    }
    return all_items;
}

void GameEvent::collision()
{
    //COLLISION DETECTION IS CENTRALISED HERE
    //COLLISION IS DONE ON PLAYER FIRST, THEN BOSS AND ENEMY (depending on "Ascending Order")

    //shooter
    QList<QGraphicsItem*> shooter_colliding_items= parent_scene->collidingItems(shooter);

    for(int i=0; i<shooter_colliding_items.size(); ++i)
    {
        if(typeid(*(shooter_colliding_items[i]))==typeid(BulletPowerUp)
                    || typeid(*(shooter_colliding_items[i]))==typeid(BulletEnemy))
        {
            if (shooter->collision(shooter_colliding_items[i]))
                REMOVE_ENTITY(parent_scene, shooter_colliding_items[i]);
        }
        else if(typeid(*(shooter_colliding_items[i]))==typeid(ShooterEnemy)
                    || typeid(*(shooter_colliding_items[i]))==typeid(ShooterBoss))
        {
            shooter->collision(shooter_colliding_items[i]);
        }
    }

    //get a list of enemies and boss
    QList<QGraphicsItem*> boss = filter_items<ShooterBoss>(
                parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder));
    QList<QGraphicsItem*> enemies = filter_items<ShooterEnemy>(
                parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder));
    if (boss.size() > 0) enemies.push_back(boss[0]); //should be 1 boss only

    for(int i=0; i<enemies.size();++i)
    {
        //boss and enemy
        ShooterBase* enemy = dynamic_cast<ShooterBase*>(enemies[i]);
        QList<QGraphicsItem*> enemy_colliding_items = parent_scene->collidingItems(enemy);

        for(int j=0; j<enemy_colliding_items.size(); ++j)
        {
            if(typeid(*(enemy_colliding_items[j]))==typeid(BulletPlayer))
            {
                if (enemy->collision())
                    REMOVE_ENTITY(parent_scene, enemy_colliding_items[j]);

                //Moved health == 0 check here as well
                if (enemy->health->get_health() == 0)
                {
                    REMOVE_ENTITY(parent_scene, enemy);
                    break; //exit the enemy_colliding_items loop, continue with the itemsInScreen loop
                }
            }
        }
    }
}

void GameEvent::increment_time()
{
    ++game_timer;
    //game_timer/FREQ_PER_SEC = seconds that have passed in-game (FREQ_PER_SEC == 50)
    if ((game_timer % FREQ_PER_SEC) == 0) //means every second
    {

        switch (game_timer/FREQ_PER_SEC) {
        case 3: time_reached(0); break;         //Game starts at 3s,
        case 8: time_reached(1); break;         //for first 5 waves of enemy, each lasts for 5s,
        case 13: time_reached(2); break;        //after that, each lasts for 8s
        case 18: time_reached(3); break;
        case 23: time_reached(4); break;
        case 31: time_reached(5); break;
        case 39: time_reached(6); break;
        case 47: time_reached(7); break;
        case 55: time_reached(8); break;
        case 63: time_reached(9); break;
        case 70: game_timer -= FREQ_PER_SEC; break;       //halt the timer, higher values will be used for game over events
        case 80: game_over(false); break;       //game_timer set to 3950 to trigger lose screen after 2 seconds
        case 90: game_over(true); break;        //game_timer set to 4350 to trigger win screen after 4 seconds
        default: break;

        }



    }
    collision();
}

void GameEvent::trigger_event(const int& event_id)
{
    switch (event_id)
    {
        case 0:
        {
            ShooterEnemy* enemy = spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random,
                                              3, 0 ,0, 0, 0, DEFAULT_SHOOT_FREQ*8);
            ShooterEnemy* enemy2 = spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random,
                                               3, 0 ,0, 700, 0, DEFAULT_SHOOT_FREQ*8);
            enemy->set_targetPos(250, 150);
            enemy2->set_targetPos(450, 150);
            break;
        }
        case 1:
        {
            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Random,
                        6, 0, 2, RANDOM(100, 300), 0, DEFAULT_SHOOT_FREQ*3);
            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Random,
                        6, 0, 2, RANDOM(400, 600), 0, DEFAULT_SHOOT_FREQ*3);
            break;
        }
        case 2:
        {
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward,
                        6, -4, 0, 800-ShooterEnemy::ENEMY_SIZE, 50,DEFAULT_SHOOT_FREQ*5);
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward,
                        7, 3, 0, 0, 120, DEFAULT_SHOOT_FREQ*5);
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward,
                        6, -4, 0, 800-ShooterEnemy::ENEMY_SIZE, 200,DEFAULT_SHOOT_FREQ*5);
            break;
        }
        case 3:
        {
            QPainterPath ellipse;
            ellipse.addEllipse(100, 50, 600, 200);
            ShooterEnemy* enemy = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward,
                                              7, 0, 0, 699, 157, DEFAULT_SHOOT_FREQ*6);
            ShooterEnemy* enemy2 = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward,
                                               9, 0, 0, 254, 237, DEFAULT_SHOOT_FREQ*5);
            ShooterEnemy* enemy3 = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward,
                                               5, 0, 0, 238, 66, DEFAULT_SHOOT_FREQ*7);
            enemy2->set_drop_powerup();
            break;
        }
        case 4:
        {
            ShooterEnemy* enemy[6];
            for(int i=0; i<5;++i){
                enemy[i]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random,
                                     4, 0, 0, 160*i, 0, DEFAULT_SHOOT_FREQ*7);
                enemy[i]->set_targetPos(160*i+80,150+(i>2?(4-i)*50:i*50));
            }
            enemy[4]->set_drop_powerup();
            ShooterEnemy* enemy2=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random,
                                             15, 0, 0, 450, 0, DEFAULT_SHOOT_FREQ*5);
            enemy2->set_targetPos(400, 70);
            break;
        }
        case 5:
        {
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double,
                        7, 5, 2, 0, 50, DEFAULT_SHOOT_FREQ*6);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double,
                        8, -5, 2, 800-ShooterEnemy::ENEMY_SIZE, 50, DEFAULT_SHOOT_FREQ*6);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double,
                        6, 5, -2, 0, 300, DEFAULT_SHOOT_FREQ*6);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double,
                        9, -5, -2, 800-ShooterEnemy::ENEMY_SIZE, 300, DEFAULT_SHOOT_FREQ*6);
            break;
        }
        case 6:
        {
            ShooterEnemy* enemy[4];

            enemy[0]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer,
                                 4, 0, 0, 50, 0, DEFAULT_SHOOT_FREQ*6);
            enemy[1]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer,
                                 4, 0, 0, 750, 0, DEFAULT_SHOOT_FREQ*7);
            enemy[2]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer,
                                 7, 0, 0, 150, 0, DEFAULT_SHOOT_FREQ*8);
            enemy[3]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer,
                                 7, 0, 0, 650, 0, DEFAULT_SHOOT_FREQ*9);
            enemy[0]->set_targetPos(100, 100);
            enemy[1]->set_targetPos(700, 100);
            enemy[2]->set_targetPos(300, 150);
            enemy[3]->set_targetPos(500, 150);
            enemy[3]->set_drop_powerup();
            break;
        }
        case 7:
        {
            ShooterEnemy* enemy[3];
            enemy[0]=spawn_enemy(ShooterEnemy::Wave, ShooterEnemy::Forward,
                                 6, 0, 1, 0, 120, DEFAULT_SHOOT_FREQ*4);
            enemy[0]->set_targetPos(0,120);
            enemy[1]=spawn_enemy(ShooterEnemy::Wave, ShooterEnemy::Forward,
                                 6, 0, 1, 750, 120, DEFAULT_SHOOT_FREQ*4);
            enemy[1]->set_targetPos(750,120);
            enemy[2]=spawn_enemy(ShooterEnemy::Wave, ShooterEnemy::Forward,
                                 12, 1, 0, 0, 250, DEFAULT_SHOOT_FREQ*3);
            enemy[2]->set_targetPos(0, 250);
            enemy[0]->set_drop_powerup();
            break;
        }
        case 8:
        {
            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Circle,
                        8, 0, 1, 250, 0, DEFAULT_SHOOT_FREQ*9);
            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Circle,
                        13, 0, 4, 400, 0, DEFAULT_SHOOT_FREQ*6);
            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Circle,
                        8, 0, 1, 550, 0, DEFAULT_SHOOT_FREQ*9);
            break;
        }
        case 9:
        {
            ShooterBoss* boss = new ShooterBoss();
            boss->setPos(250, -200);
            parent_scene->addItem(boss);
            boss->show_health();
            //boss emits a signal at phase 3 to player
            connect(boss, SIGNAL(start_phase3()), shooter, SLOT(begin_phase3()));
            connect(boss, SIGNAL(boss_dead(bool)), this, SLOT(trigger_game_over(bool)));
            break;
        }
        default:
            break;
        }
}

ShooterEnemy* GameEvent::spawn_enemy(ShooterEnemy::EnemyPathingType pathing_type, ShooterEnemy::EnemyShootingType shooting_type, int hp,
                                     int dx, int dy, const int& initX, const int& initY, int shoot_freq)
{
    ShooterEnemy* enemy = new ShooterEnemy(pathing_type, shooting_type, hp, dx, dy, shoot_freq);
    enemy->setPos(initX, initY);
    parent_scene->addItem(enemy);
    parent_scene->addItem(enemy->health);
    return enemy;
}

void GameEvent::start_game()
{
    if (game_begin) return;
    game_begin = true;
    trigger_clear_field(true);
}

//helper template
template <typename T>
bool try_pause(QGraphicsItem* item)
{
    if (dynamic_cast<T*>(item) != nullptr)
    {
        (dynamic_cast<T*>(item))->pause();
        return true;
    }
    return false;
}

void GameEvent::pause_game()
{
    QList<QGraphicsItem*> scene_items = parent_scene->items(); //pause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_pause<BulletBase>(scene_items[i])) continue;
        if (try_pause<ShooterBase>(scene_items[i])) continue;
        if (try_pause<ShooterExplosion>(scene_items[i])) continue;
        if (try_pause<PopUpDialogue>(scene_items[i])) continue;
    }
    event_timer->pause();

    //display pause screen during game only
    if (game_begin)
        dialogue = new PopUpDialogue(parent_scene, "Press P to continue.\nPress R to restart.", PopUpDialogue::NO_DURATION, PopUpDialogue::GameArea);
}

//helper template
template <typename T>
bool try_unpause(QGraphicsItem* item)
{
    if (dynamic_cast<T*>(item) != nullptr)
    {
        (dynamic_cast<T*>(item))->unpause();
        return true;
    }
    return false;
}
void GameEvent::unpause_game()
{
    if (!game_begin) return;
    if (dialogue != nullptr) {delete dialogue; dialogue=nullptr;}

    QList<QGraphicsItem*> scene_items = parent_scene->items(); //unpause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_unpause<BulletBase>(scene_items[i])) continue;
        if (try_unpause<ShooterBase>(scene_items[i])) continue;
        if (try_unpause<ShooterExplosion>(scene_items[i])) continue;
        if (try_unpause<PopUpDialogue>(scene_items[i])) continue;
    }
    event_timer->unpause();
}

void GameEvent::trigger_clear_field(const bool& restart)
{
    if (!game_begin) return;
    QList<QGraphicsItem*> scene_items = parent_scene->items();
    for(int i=0; i<scene_items.size(); i++)
    {
        if (typeid(*(scene_items[i]))==typeid (BulletEnemy))
        {
            REMOVE_ENTITY(parent_scene, scene_items[i]);
        }

        if (typeid(*(scene_items[i]))==typeid (ShooterEnemy))
        {
            if (restart) //just remove enemies if restart
                REMOVE_ENTITY(parent_scene, scene_items[i]);
            else        //else, kill the enemies but still have the explosion + sound effects
                dynamic_cast<ShooterEnemy*>(scene_items[i])->safe_kill();
        }

        if (restart && (typeid(*(scene_items[i]))==typeid (BulletPowerUp)
                        || typeid(*(scene_items[i]))==typeid (BulletPlayer)
                        || typeid(*(scene_items[i]))==typeid (ShooterBoss))){
            REMOVE_ENTITY(parent_scene, scene_items[i]);
        }
    }

    if (restart)
    {
        game_timer=0;
        shooter->health->reset_health();
        shooter->reset_nullptr();
        shooter->setPos(START_POS_X, START_POS_Y);
        unpause_game();
    }
}

//gameover part
void GameEvent::trigger_game_over(const bool& win)
{
    game_timer = win ? 4350 : 3950; //see increment_time()
}

void GameEvent::game_over(const bool& win)
{
    //prevent the case of winning and losing at the same time
    if (dialogue != nullptr) return;
    if (win)
    {
        QString dialogue_text {
            "ShootTheBugs.exe exited with code 0.\n\n"
            "Congratulations! You have won the game!\n"
            "Press S to start again."
        };
        dialogue = new PopUpDialogue(parent_scene, dialogue_text, PopUpDialogue::NO_DURATION, PopUpDialogue::GameArea);
    }
    else
    {
        QString dialogue_text {
            "SEGMENTATION FAULT\n"
            "ShootTheBugs.exe exited unexpectedly.\n\n"
            "Oh no! You have lost the game!\n"
            "Press S to start again."
        };
        dialogue = new PopUpDialogue(parent_scene, dialogue_text, PopUpDialogue::NO_DURATION, PopUpDialogue::GameArea);
    }
    game_begin = false;
    pause_game();
}

