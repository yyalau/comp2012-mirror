#include "gameEvent.h"

//static member declaration
bool GameEvent::game_begin = false;

GameEvent::GameEvent(QGraphicsScene* parent_scene, ShooterPlayer* shooter, QString instructions) :
    parent_scene(parent_scene), shooter(shooter)
{

    event_timer = new CustomTimer(MIN_FREQ, false, this, SLOT(increment_time()));
    //connect the timer and time increase slot

    connect(this, SIGNAL(time_reached(int)), this, SLOT(trigger_event(int))); //when time is reached, trigger game events

    //start game dialogue
    dialogue = new PopUpDialogue(parent_scene, instructions, NO_DURATION, PopUpDialogue::FullScreen);

    //for pausing/unpausing the game
    connect(shooter, SIGNAL(pause_all()), this, SLOT(pause_game()));
    connect(shooter, SIGNAL(unpause_all()), this, SLOT(unpause_game()));

    //powerup clearfield/ restart
    connect(shooter, SIGNAL(clear_field(bool)), this, SLOT(trigger_clear_field(bool)));

    //for handling game over
    connect(shooter, SIGNAL(player_dead()), this, SLOT(trigger_game_over()));

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
//TODO: Use iterator on this one???
template <typename T>
QList<QGraphicsItem*> filter_items(QList<QGraphicsItem*> all_items)
{
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
    //10 DEC: COLLISION DETECTION IS NOW CENTRALISED HERE
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
                //TODO? have nullptr check for dynamic cast, although probably unnecessary
                if (enemy->collision())
                    REMOVE_ENTITY(parent_scene, enemy_colliding_items[j]);

                //Moved health == 0 check here as well, all REMOVE_ENTITY should be centralized
                //Boss here as well?
                if (enemy->get_health_var()->get_health() == 0)
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
    //game_timer/50 = seconds that have passed in-game
    if ((game_timer % 50) == 0) //means every second
    {

        switch (game_timer/50-1) {
        case 3: time_reached(0); break;         //Game starts at 3s,
        case 8: time_reached(1); break;         //for first 5 waves of enemy, each lasts for 5s,
        case 13: time_reached(2); break;        //after that, each lasts for 10s
        case 18: time_reached(3); break;
        case 23: time_reached(4); break;
        case 33: time_reached(5); break;
        case 43: time_reached(6); break;
        case 53: time_reached(7); break;
        case 63: time_reached(9); break;

        }

        //emit time_reached((game_timer/200)-1 % 5);
        //emit time_reached(6);
    }
    if ((game_timer % 300)==0) //every 6 seconds
    {
        emit time_reached(8);
    }

    collision();
}

void GameEvent::trigger_event(int event_id)
{
    switch (event_id)
    {
        //TODO: create macro or template for enemy creation
        //if macro put it in define? shooterBoss also needs it
        case 0:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            ShooterEnemy* enemy = spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random, 5, 0 ,0, 0, 0, DEFAULT_SHOOT_FREQ*4);
            ShooterEnemy* enemy2 = spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random, 5, 0 ,0, 700, 0, DEFAULT_SHOOT_FREQ*4);
            enemy->set_targetPos(250, 150);
            enemy2->set_targetPos(450, 150);
            break;
        }
        case 1:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }

            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Random, 2, 0, 2,100+rand()%200, 0);

            spawn_enemy(ShooterEnemy::Linear, ShooterEnemy::Random, 2, 0, 2,400+rand()%200, 0);
            break;
        }
        case 2:
        {
            //ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::BorderBounce, ShooterEnemy::Random, 5, -10, 0);
            //enemy->setPos(800-ENEMY_SIZE, 50);
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward, 5, -4, 0, 800-ShooterEnemy::ENEMY_SIZE, 50,DEFAULT_SHOOT_FREQ*3);
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward, 5, 3, 0, 0, 120, DEFAULT_SHOOT_FREQ*3);
            spawn_enemy(ShooterEnemy::BorderBounce, ShooterEnemy::Forward, 5, -4, 0, 800-ShooterEnemy::ENEMY_SIZE, 200,DEFAULT_SHOOT_FREQ*3);
            break;
        }
        case 3:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            QPainterPath ellipse;
            ellipse.addEllipse(100,50,600,200);
            ShooterEnemy* enemy = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward, 5, 0, 0,699,157);
            ShooterEnemy* enemy2 = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward, 5, 0, 0,254,237);
            ShooterEnemy* enemy3 = spawn_enemy(ShooterEnemy::Circular, ShooterEnemy::Forward, 5, 0, 0,238,66);
            //qDebug()<<ellipse.pointAtPercent(0.01).toPoint()<<ellipse.pointAtPercent(0.33).toPoint()<<ellipse.pointAtPercent(0.66).toPoint();
            break;
        }
        case 4:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            ShooterEnemy* enemy[6];
            for(int i=0; i<5;++i){
                enemy[i]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random, 2,0,0,160*i,0,DEFAULT_SHOOT_FREQ*6);
                enemy[i]->set_targetPos(160*i+80,150+(i>2?(4-i)*50:i*50));
            }
            ShooterEnemy* enemy2=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::Random, 3,0,0,450,0,DEFAULT_SHOOT_FREQ*4);
            enemy2->set_targetPos(400,70);
            break;
        }
        case 5:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double, 5,5,2,0,50,DEFAULT_SHOOT_FREQ*4);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double, 5,-5,2,800-ShooterEnemy::ENEMY_SIZE,50,DEFAULT_SHOOT_FREQ*4);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double, 5,5,-2,0,300,DEFAULT_SHOOT_FREQ*4);
            spawn_enemy(ShooterEnemy::BorderBounce,ShooterEnemy::Double, 5,-5,-2,800-ShooterEnemy::ENEMY_SIZE,300,DEFAULT_SHOOT_FREQ*4);
            break;
        }
        case 6:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            ShooterEnemy* enemy[4];

            enemy[0]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer, 3,0,0,50,0,DEFAULT_SHOOT_FREQ*4);
            enemy[1]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer, 3,0,0,750,0,DEFAULT_SHOOT_FREQ*4);
            enemy[2]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer, 3,0,0,150,0,DEFAULT_SHOOT_FREQ*4);
            enemy[3]=spawn_enemy(ShooterEnemy::GotoTarget, ShooterEnemy::AimAtPlayer, 3,0,0,650,0,DEFAULT_SHOOT_FREQ*4);
            enemy[0]->set_targetPos(100,100);
            enemy[1]->set_targetPos(700, 100);
            enemy[2]->set_targetPos(300,150);
            enemy[3]->set_targetPos(500,150);
            break;
        }
        case 7:
        {
            QList<QGraphicsItem*> itemsInScreen=parent_scene->items(0,0,800,600,Qt::IntersectsItemShape,Qt::AscendingOrder);
            for(int i=0; i<itemsInScreen.size();++i){
               if (typeid(*(itemsInScreen[i]))==typeid(ShooterEnemy)){
                   parent_scene->removeItem(itemsInScreen[i]);
                   delete itemsInScreen[i];
               }
            }
            ShooterEnemy* enemy[3];
            enemy[0]=spawn_enemy(ShooterEnemy::Wave,ShooterEnemy::Forward,5,0,1,0,200,DEFAULT_SHOOT_FREQ*3);
            enemy[0]->set_targetPos(0,120);
            enemy[1]=spawn_enemy(ShooterEnemy::Wave,ShooterEnemy::Forward,5,0,1,800-ShooterEnemy::ENEMY_SIZE,400,DEFAULT_SHOOT_FREQ*3);
            enemy[1]->set_targetPos(750,120);
            enemy[2]=spawn_enemy(ShooterEnemy::Wave,ShooterEnemy::Forward,3,10,0,400,300,DEFAULT_SHOOT_FREQ*3);
            enemy[2]->set_targetPos(0,250);
           break;
        }
        case 8:
        {
            BulletPowerUp* bullet_powerup=new BulletPowerUp(rand()%10+1, rand()%10+1);
            bullet_powerup->setPos(rand()%GAMEAREA_LENGTH/2,0);
            parent_scene->addItem(bullet_powerup);
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
            break;
        }
        default:
            break;
        }
}

ShooterEnemy* GameEvent::spawn_enemy(ShooterEnemy::EnemyPathingType pathing_type, ShooterEnemy::EnemyShootingType shooting_type, int hp, int dx, int dy,int initX, int initY, int shoot_freq){
    ShooterEnemy* enemy = new ShooterEnemy(pathing_type, shooting_type, hp, dx, dy, shoot_freq);
    enemy->setPos(initX, initY);
    parent_scene->addItem(enemy);
    parent_scene->addItem(enemy->get_health_var());
    return enemy;
}

//helper template
template <typename T>
bool try_pause(QGraphicsItem* item)
{
    if (/*typeid(*item) == typeid(T)*/dynamic_cast<T*>(item) != nullptr)
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
        if (try_pause<InfoBox>(scene_items[i])) continue;
        if (try_pause<PopUpDialogue>(scene_items[i])) continue;
    }
    event_timer->pause();

    //pause screen
    //TODO: more info?
    if (!game_begin)
    {
        game_begin = true;
    }
    else if (!shooter->get_health_var()->is_dead())
    {
        dialogue = new PopUpDialogue(parent_scene, "\t Press P to continue", NO_DURATION, PopUpDialogue::GameArea);
    }
}

//helper template
template <typename T>
bool try_unpause(QGraphicsItem* item)
{
    if (/*typeid(*item) == typeid(T)*/dynamic_cast<T*>(item) != nullptr)
    {
        (dynamic_cast<T*>(item))->unpause();
        return true;
    }
    return false;
}
void GameEvent::unpause_game()
{
    if (dialogue != nullptr) {delete dialogue; dialogue=nullptr;}

    QList<QGraphicsItem*> scene_items = parent_scene->items(); //unpause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_unpause<BulletBase>(scene_items[i])) continue;
        if (try_unpause<ShooterBase>(scene_items[i])) continue;
        if (try_unpause<InfoBox>(scene_items[i])) continue;
        if (try_unpause<PopUpDialogue>(scene_items[i])) continue;
    }
    event_timer->unpause();
}

void GameEvent::trigger_clear_field(bool restart)
{
    QList<QGraphicsItem*> scene_items = parent_scene->items();
    for(int i=0; i<scene_items.size(); i++)
    {
        if (typeid(*(scene_items[i]))==typeid (BulletEnemy)
                || typeid(*(scene_items[i]))==typeid (ShooterEnemy))
        {
            parent_scene->removeItem(scene_items[i]);
            delete scene_items[i];
        }

        if (restart && (typeid(*(scene_items[i]))==typeid (BulletPowerUp)
                        || typeid(*(scene_items[i]))==typeid (BulletPlayer)
                        || typeid(*(scene_items[i]))==typeid (ShooterBoss))){
            parent_scene->removeItem(scene_items[i]);
            delete scene_items[i];
        }
    }

    if (restart)
    {
        if (dialogue != nullptr) {delete dialogue; dialogue=nullptr;}
        game_timer=0;
        shooter->get_health_var()->reset_health();
        shooter->setPos(START_POS_X, START_POS_Y);
        unpause_game();
    }
}

//gameover part
void GameEvent::trigger_game_over()
{
    pause_game(); //TODO: if we want to do like death animation or something, add it under here
    dialogue = new PopUpDialogue(parent_scene, "\t YOU LOSE! RUNTIME ERROR!!", NO_DURATION, PopUpDialogue::GameArea);
}

