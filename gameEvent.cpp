#include "gameEvent.h"

GameEvent::GameEvent(QGraphicsScene* parentScene) : parentScene(parentScene)
{
    QTimer* event_timer= new QTimer();
    connect(event_timer, SIGNAL(timeout()), this, SLOT(increment_time())); //connect the timer and time increase slot
    event_timer->start(MIN_FREQ);

    connect(this, SIGNAL(time_reached(int)), this, SLOT(trigger_event(int)));
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
