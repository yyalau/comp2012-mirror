#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include <QObject>
#include <QGraphicsScene>
#include <QList>

#include "define.h"
#include "customTimer.h"
#include "bulletEnemy.h"
#include "bulletPlayer.h"
#include "bulletPowerUp.h"
#include "shooterEnemy.h"
#include "shooterPlayer.h"
#include "shooterBoss.h"
#include "infoBox.h"
#include "popUpDialogue.h"

/**
 * @brief The GameEvent class
 * Has a timer to trigger events at certain time
 *
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include parent_scene: The main scene (need this to call addItem)
 * @include dialogue: Game's dialogue, used for boss dialogues and gameover screens
 * @include shooter: Pointer to the player (for receiving signals)
 * @include event_timer: CustomTimer for triggering increment_time()
 * @include game_timer: Goes up by 1 every MIN_TIME ms.
 *                      Only goes up to 70 seconds in normal gameplay, higher values reserved for gameover sequences.
 * @include game_begin: Static bool for pause_game() used in gameover/game start to avoid pause screen
 * @include spawn_enemy(): Convenience function for spawning enemy
 * @include collision(): Called by increment_time() to check for shooter/bullet collisions
 * @include game_over(): Generate the game over screen, called by increment_time();
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include get_time(): Returns the value of game_timer
 *
 * PUBLIC SLOTS
 * @include increment_time(): Increase game_timer by 1 when triggered
 * @include trigger_event(): Trigger time-based game events, such as spawning enemies, when called
 * @include pause_game(), unpause_game(): Pause/Unpause the game, connect with signals sent by shooterPlayer
 * @include trigger_clear_field(): delete all the enemies in the screen, connect with clear_field signal sent by shooterPlayer
 * @include trigger_game_over(): Set game_timer beyond the maximum time to trigger game over after some time
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
    CustomTimer* event_timer;
    int game_timer {0};
    static bool game_begin;
    ShooterEnemy* spawn_enemy(ShooterEnemy::EnemyPathingType pathing_type, ShooterEnemy::EnemyShootingType shooting_type,
                              int hp, int dx, int dy,const int& initX, const int& initY, int shoot_freq = DEFAULT_SHOOT_FREQ);
    void collision();
    void game_over(const bool& win);

public:
    GameEvent(QGraphicsScene* parent_scene, ShooterPlayer* shooter, const QString& instructions);
    ~GameEvent();
    int get_time();

public slots:
    void increment_time();
    void trigger_event(const int& event_id);
    void pause_game();
    void unpause_game();
    void trigger_clear_field(const bool& restart);
    void trigger_game_over(const bool& win);

signals:
    void time_reached(const int& event_id);
};

#endif // GAMEEVENT_H
