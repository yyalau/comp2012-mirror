#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include <QMediaPlayer>
#include <QPauseAnimation>
#include <QKeyEvent>
#include <QDebug>
#include <QList>


#include "shooterBase.h"
#include "bulletEnemy.h"
#include "bulletPowerUp.h"

/**
 * @brief The ShooterPlayer class
 * Class for player
 *
 * ENUMs
 * @enum MusicType: different sound made by the shooter for different actions
 *
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include sound: play music for different MusicType
 * @include speed: player's moving speed
 * @include immune: set to true if the player is immune (for 1 second after being hit)
 * @include powerup_shooter: is greater than 0 if the shooter has been improved
 * @include paused: static variable storing the pause state of the game, changed with keyboard P
 * @include dead: boolean of whether player is dead or not, to allow for 3-second break before game over screen
 * @include nullptr_phase: for boss's phase 3, remove the player's ability to move
 * @include powerup_shooter_counter: if in powerup mode, shoot extra bullets once every 3 shoot()
 * @include powerup_timer, immune_timer: CustomTimer for keeping track of StackOverflow powerup and immunity's time
 * @include set_sprite(): Change the sprite to indicate immunity
 *
 * FUNCTION RE-IMPLEMENTATIONS
 * @implements keyPressEvent(QKeyEvent*): handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): handles keyboard input, resets player velocity and is_shooting
 * @implements focusOutEvent(QFocusEvent*): keeps the shooter to be focused
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Overrides ShooterBase's functions
 * @include get_pos(): return the player's position
 * @include process_powerup(BulletPowerUp*): handles power-up tasks when ShooterPlayer/BulletPlayer collided with BulletPowerUp
 * @include collision():
 *              No parameter: overrides shooterBase's function (do NOTHING)
 *              1 argument (collision_item): Call this function instead and pass the collision item (bullet/enemy/boss)
 * @include reset_nullptr(): Call in gameEvent's restart function to set nullptr_phase to false
 *
 * SIGNALS
 * @include start_signal(), pause_all(), unpause_all(): signals to send to the main game
 * @include player_dead(): signal triggered when health reaches 0
 * @include powerup_text(int), shooter_text(int): signal to send to infoBox, to display the correct power-up message in infoBox
 * @include clear_field(bool): signal triggered when player pressed 'R' key or hit BulletPowerUp with clear field function
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, prevents going out of bound
 * @include shoot(): overrides shooterBase's function
 * @include reset_shooter(): sets powerup_shooter to false after 10 seconds
 * @include reset_immune(): reset immunity after 1 second
 * @include begin_phase3(): set null_pointer to true when boss's phase 3 starts
 */

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

public:
    constexpr static const int DEFAULT_SPEED {10};
    constexpr static const int PLAYER_SIZE_X {24};
    constexpr static const int PLAYER_SIZE_Y {38};
    constexpr static const int DEFAULT_PLAYER_HP {25};

private:
    enum MusicType{
        hitBullet,
        powerUp,
        Shoot
    };
    QMediaPlayer* sound[3];
    int speed {DEFAULT_SPEED};
    bool immune {false};
    int powerup_shooter {0};
    static bool paused, dead;
    bool nullptr_phase {false};
    int powerup_shooter_counter {0};
    CustomTimer *powerup_timer {nullptr}, *immune_timer {nullptr};

    void set_sprite(const char* sprite);
    void play_sound(MusicType type);

    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

public:
    ShooterPlayer(const int hp = DEFAULT_PLAYER_HP, const int& dx = 0, const int& dy = 0,
                  const int& shoot_freq = DEFAULT_SHOOT_FREQ, const bool& shoot = false,
                  const int size_x = PLAYER_SIZE_X, const int size_y = PLAYER_SIZE_Y,
                  const int& move_freq = DEFAULT_FREQ);
    QPointF get_pos();
    virtual void pause() override;
    virtual void unpause() override;
    void process_powerup(BulletPowerUp* bullet);
    virtual bool collision() override;
    bool collision(QGraphicsItem* collision_item);
    void reset_nullptr();

signals:
    void start_signal();
    void pause_all();
    void unpause_all();
    void player_dead(bool win);
    void powerup_text(int type);
    void shooter_text(int powerup_shooter);
    void clear_field(bool restart);

public slots:
    virtual void move() override;
    virtual void shoot() override;
    void reset_shooter();
    void reset_immunity();
    void begin_phase3();
};

#endif // SHOOTERPLAYER_H
