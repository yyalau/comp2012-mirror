#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>
#include <QGraphicsScene>
#include <QTimer>
#include <QList>

#include "define.h"
#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include "shooterEnemy.h"
#include "shooterPlayer.h"

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
 * @include display_gameover_scene(): //TODO, draw a game over screen?
 * @include draw_scene(): //TODO, draw a generic rectangle for dialogue?
 *
 * PUBLIC SLOTS:
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
    QGraphicsScene* parentScene;
    ShooterPlayer* shooter;
    QTimer* event_timer;
    int game_timer {0};

public:
    GameEvent(QGraphicsScene* parentScene, ShooterPlayer* shooter);
    int get_time();

    void display_gameover_scene();
    void draw_scene(int x =SCREEN_LENGTH/2, int y=SCREEN_HEIGHT/2, int width=SCREEN_LENGTH, int height=SCREEN_HEIGHT, QColor color=Qt::yellow, double opacity=100);

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
