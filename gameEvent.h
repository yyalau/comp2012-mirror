#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>

#include "define.h"
#include "shooterEnemy.h"

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
    int game_timer {0};

public:
    GameEvent(QGraphicsScene* parentScene);
    int get_time();

public slots:
    void increment_time();
    void trigger_event(int event_id);

signals:
    void time_reached(int event_id);
};

#endif // GAMEEVENT_H
