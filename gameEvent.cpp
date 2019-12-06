#include "gameEvent.h"

GameEvent::GameEvent(QGraphicsScene* parent_scene, ShooterPlayer* shooter) :
    parent_scene(parent_scene), shooter(shooter)
{

    event_timer= new QTimer();
    connect(event_timer, SIGNAL(timeout()), this, SLOT(increment_time())); //connect the timer and time increase slot
    event_timer->start(MIN_FREQ);

    connect(this, SIGNAL(time_reached(int)), this, SLOT(trigger_event(int))); //when time is reached, trigger game events

    //for pausing/unpausing the game
    connect(shooter, SIGNAL(pause_all()), this, SLOT(pause_game()));
    connect(shooter, SIGNAL(unpause_all()), this, SLOT(unpause_game()));

    //for handling game over
    connect(shooter, SIGNAL(player_dead()), this, SLOT(trigger_game_over()));

}

GameEvent::~GameEvent()
{
    if (dialogue != nullptr) delete dialogue;
    delete event_timer;
}

int GameEvent::get_time()
{
    return game_timer;
}

void GameEvent::increment_time()
{
    ++game_timer;
    //game_timer/50 = seconds that have passed in-game
    if ((game_timer /*% 200) == 0*/ == 100)) //means every 4 seconds
    {
        //emit time_reached((game_timer/200) % 6);
        emit time_reached(6);
    }
}

void GameEvent::trigger_event(int event_id)
{
    switch (event_id)
    {
        //TODO: create macro or template for enemy creation
        case 0:
        {
            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::Linear, ShooterEnemy::Random, 2, 0, 3);
            enemy->setPos(400 + rand()%300, 0);
            parent_scene->addItem(enemy);
            break;
        }
        case 1:
        {
            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::Linear, ShooterEnemy::AimAtPlayer, 3, 4, 0);
            enemy->setPos(0, 50);
            parent_scene->addItem(enemy);
            break;
        }
        case 2:
        {
            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::BorderBounce, ShooterEnemy::Random, 5, -10, 1);
            enemy->setPos(800-ENEMY_SIZE, 50);
            parent_scene->addItem(enemy);
            break;
        }
        case 3:
        {
            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::Linear, ShooterEnemy::AimAtPlayer, 2, 0, 0, DEFAULT_SHOOT_FREQ*2);
            enemy->setPos(100, 100);
            parent_scene->addItem(enemy);
            ShooterEnemy* enemy2 = new ShooterEnemy(ShooterEnemy::Linear, ShooterEnemy::AimAtPlayer, 2, 0, 0, DEFAULT_SHOOT_FREQ*2);
            enemy2->setPos(500, 100);
            parent_scene->addItem(enemy2);
            break;
        }
        case 4:
        {
            ShooterEnemy* enemy = new ShooterEnemy(ShooterEnemy::Circular, ShooterEnemy::Random, 5, 0, 0);
            //enemy->setPos(800-ENEMY_SIZE, 50);
            parent_scene->addItem(enemy);
            break;
        }
        case 5:
        {
            BulletPowerUp* bullet_powerup=new BulletPowerUp(rand()%10+1, rand()%10+1);
            bullet_powerup->setPos(rand()%SCREEN_LENGTH/2,0);
            parent_scene->addItem(bullet_powerup);
            break;
        }
        case 6:
        {
            ShooterBoss* boss = new ShooterBoss();
            boss->setPos(250, -200);
            parent_scene->addItem(boss);
            boss->show_health();
            break;
        }
        default:
            break;
        }
}

//helper template
template <typename T>
bool try_pause(QGraphicsItem* item)
{
    if (typeid(*item) == typeid(T))
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
        if (try_pause<BulletEnemy>(scene_items[i])) continue;
        if (try_pause<BulletPlayer>(scene_items[i])) continue;
        if (try_pause<BulletPowerUp>(scene_items[i])) continue;
        if (try_pause<ShooterEnemy>(scene_items[i])) continue;
        if (try_pause<ShooterPlayer>(scene_items[i])) continue;
        if (try_pause<ShooterBoss>(scene_items[i])) continue;
    }
    event_timer->stop();

    //pause screen
    //TODO: make it more interesting
    if(!shooter->get_health_var()->is_dead())
    {
        dialogue = new PopUpDialogue(parent_scene, "\t Press P to continue", PopUpDialogue::FullScreen);
    }
}

//helper template
template <typename T>
bool try_unpause(QGraphicsItem* item)
{
    if (typeid(*item) == typeid(T))
    {
        (dynamic_cast<T*>(item))->unpause();
        return true;
    }
    return false;
}
void GameEvent::unpause_game()
{
    if (dialogue != nullptr) delete dialogue;

    QList<QGraphicsItem*> scene_items = parent_scene->items(); //pause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_unpause<BulletEnemy>(scene_items[i])) continue;
        if (try_unpause<BulletPlayer>(scene_items[i])) continue;
        if (try_unpause<BulletPowerUp>(scene_items[i])) continue;
        if (try_unpause<ShooterEnemy>(scene_items[i])) continue;
        if (try_unpause<ShooterPlayer>(scene_items[i])) continue;
        if (try_unpause<ShooterBoss>(scene_items[i])) continue;
    }
    event_timer->start(MIN_FREQ);
}

//gameover part
void GameEvent::trigger_game_over()
{
    pause_game(); //TODO: if we want to do like death animation or something, add it under here
    dialogue = new PopUpDialogue(parent_scene, "\t YOU LOSE! RUNTIME ERROR!!", PopUpDialogue::FullScreen);
}

