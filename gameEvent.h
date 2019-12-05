#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "define.h"
#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include "bulletPowerUp.h"
#include "shooterEnemy.h"
#include "shooterPlayer.h"
#include "shooterBoss.h"
#include "popUpDialogue.h"

/**
 * @brief The GameEvent class
 * Has a timer to trigger events at certain time
 *
 * PRIVATE DATA MEMBERS
 * @include parentScene: //TODO, see setup.h (need this to call addItem)
 * @include shooter: Pointer to the player (for receiving signals)
 * @include event_timer: QTimer for triggering increment_time()
 * @include game_timer: Goes up by 1 every MIN_TIME ms
 *
 * PUBLIC MEMBER FUNCTIONS:
 * @include get_time(): Returns the value of game_timer
 *
 * PUBLIC SLOTS:
 * @include collision_powerup(): If the shooter collides with the BulletPowerUp, it gets certain health/ shooter improvements
 * @include increment_time(): Increase game_timer by 1 when triggered
 * @include trigger_event(): Trigger time-based game events, such as spawning enemies, when called
 * @include pause_game(), unpause_game(): Pause/Unpause the game, connect with signals sent by shooterPlayer
 * @include trigger_game_over(): Start the game over sequence, connect with player_dead() signal sent by shooterPlayer
 *
 * SIGNALS:
 * @include time_reached(): Sent when game_timer reaches time for triggering events in trigger_event()
 */

class GameEvent : public QObject
{
    Q_OBJECT

private:
    QGraphicsScene* parent_scene;
    PopUpDialogue* dialogue;
    ShooterPlayer* shooter;
    QTimer* event_timer;
    int game_timer {0};

public:
    GameEvent(QGraphicsScene* parent_scene, ShooterPlayer* shooter);
    ~GameEvent();

    int get_time();

public slots:
    void increment_time();
    void trigger_event(int event_id);
    void pause_game();
    void unpause_game();
    void trigger_game_over();

signals:
    void time_reached(int event_id);
};

#endif // GAMEEVENT_H
