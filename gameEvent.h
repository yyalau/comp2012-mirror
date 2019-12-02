#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>

#include "define.h"
#include "shooterEnemy.h"
#include "shooterPlayer.h"

/**
 * @brief The GameEvent class
 * Has a timer to trigger events at certain time
 * @include parentScene: //TODO, see setup.h (need this to call addItem)
 * @include time: Goes up by 1 every MIN_TIME ms
 * TODO: easy way is to continuously check the time and call enemy creation functions, but can we do it automatically in here?
 * lmao i figured out how to do it automatically
 */

class GameEvent : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene* parentScene;
    ShooterPlayer* shooter;
    QTimer* event_timer;
    int game_timer {0};

public:
    GameEvent(QGraphicsScene* parentScene, ShooterPlayer* shooter);
    int get_time();

    //void display_gameover_scene();
    //void draw_scene(int x =SCREEN_LENGTH/2, int y=SCREEN_HEIGHT/2, int width=SCREEN_LENGTH, int height=SCREEN_HEIGHT, QColor color=Qt::yellow, double opacity=100);

public slots:
    void increment_time();
    void trigger_event(int event_id);

signals:
    void time_reached(int event_id);
};

#endif // GAMEEVENT_H
