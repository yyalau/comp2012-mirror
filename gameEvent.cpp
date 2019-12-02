#include "gameEvent.h"
#include <QList>
#include <QGraphicsView>
#include "define.h"

GameEvent::GameEvent(QGraphicsScene* parentScene, ShooterPlayer* shooter) :
    parentScene(parentScene), shooter(shooter)
{

    event_timer= new QTimer();
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
    //gameover part
//    if (shooter->get_health_var()->get_health()==0){
//        event_timer->stop();
//        display_gameover_scene();
//        return;
//    }

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

    //gameover part

//void GameEvent::display_gameover_scene()
//{
//    QList<QGraphicsItem *> scene_items=parentScene->items();

//    for(int i=0; i<scene_items.size(); ++i){
//        if (typeid(*(scene_items[i]))==typeid (ShooterEnemy))
//        {
//            parentScene->removeItem(scene_items[i]);
//        }
//    }

//    // pop up semi transparent panel
//    draw_scene(0,0,SCREEN_LENGTH,SCREEN_HEIGHT,Qt::white,1);

//    QGraphicsTextItem* gameover_text = new QGraphicsTextItem("YOU LOSE!");
//    gameover_text->setPos(SCREEN_LENGTH/2,SCREEN_HEIGHT/2);
//    parentScene->addItem(gameover_text);
//}

//void GameEvent::draw_scene(int x, int y, int width, int height, QColor color, double opacity)
//{
//    QGraphicsRectItem* popup_scene = new QGraphicsRectItem(x,y,width,height);
//    QBrush brush;
//    brush.setStyle(Qt::SolidPattern);
//    brush.setColor(color);
//    popup_scene->setBrush(brush);
//    popup_scene->setOpacity(opacity);
//    parentScene->addItem(popup_scene);
//}

