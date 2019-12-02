#include "gameEvent.h"

GameEvent::GameEvent(QGraphicsScene* parentScene, ShooterPlayer* shooter) :
    parentScene(parentScene), shooter(shooter)
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

int GameEvent::get_time()
{
    return game_timer;
}

void GameEvent::increment_time()
{
    ++game_timer;
    //game_timer/20 = seconds that have passed in-game
    if ((game_timer % 100) == 0)
    {
        emit time_reached(0);
    }
}

void GameEvent::trigger_event(int event_id)
{
    switch (event_id)
    {
        default:
            ShooterEnemy* enemy = new ShooterEnemy();
            enemy->setPos(400 + rand()%300, 10);
            parentScene->addItem(enemy);
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
    QList<QGraphicsItem*> scene_items = parentScene->items(); //pause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_pause<BulletEnemy>(scene_items[i])) continue;
        if (try_pause<BulletPlayer>(scene_items[i])) continue;
        if (try_pause<ShooterEnemy>(scene_items[i])) continue;
        if (try_pause<ShooterPlayer>(scene_items[i])) continue;
    }
    event_timer->stop();
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
    QList<QGraphicsItem*> scene_items = parentScene->items(); //pause all items

    for(int i=0; i<scene_items.size(); ++i){
        if (try_unpause<BulletEnemy>(scene_items[i])) continue;
        if (try_unpause<BulletPlayer>(scene_items[i])) continue;
        if (try_unpause<ShooterEnemy>(scene_items[i])) continue;
        if (try_unpause<ShooterPlayer>(scene_items[i])) continue;
    }
    event_timer->start(MIN_FREQ);
}

//gameover part

void GameEvent::trigger_game_over()
{
    pause_game(); //TODO: if we want to do like death animation or something, add it under here
    display_gameover_scene();
}


void GameEvent::display_gameover_scene()
{
    // pop up semi transparent panel
    draw_scene(0,0,SCREEN_LENGTH,SCREEN_HEIGHT,Qt::white,1);

    QGraphicsTextItem* gameover_text = new QGraphicsTextItem("YOU LOSE!");
    gameover_text->setPos(SCREEN_LENGTH/2,SCREEN_HEIGHT/2);
    parentScene->addItem(gameover_text);
}

void GameEvent::draw_scene(int x, int y, int width, int height, QColor color, double opacity)
{
    QGraphicsRectItem* popup_scene = new QGraphicsRectItem(x,y,width,height);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    popup_scene->setBrush(brush);
    popup_scene->setOpacity(opacity);
    parentScene->addItem(popup_scene);
}

