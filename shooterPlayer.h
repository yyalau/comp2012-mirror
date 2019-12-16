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
 * ENUMS
 * @enum SoundType: Different sounds for different actions
 *
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include speed: Player's moving speed
 * @include immune: Set to true if the player is immune (for 1 second after being hit)
 * @include powerup_shooter: Is greater than 0 if the shooter has been improved
 * @include paused: Static variable storing the pause state of the game, changed with keyboard P
 * @include dead: Static boolean of whether player is dead or not, to allow for 3-second break before game over screen
 * @include nullptr_phase: For boss's phase 3, remove the player's ability to move
 * @include powerup_shooter_counter: If in powerup mode, shoot extra bullets once every 3 shoot()
 * @include powerup_timer, immune_timer: CustomTimer for keeping track of StackOverflow powerup and immunity's time
 * @include set_sprite(): Change the sprite to indicate immunity
 *
 * FUNCTION RE-IMPLEMENTATIONS
 * @implements keyPressEvent(QKeyEvent*): Handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): Handles keyboard input, resets player velocity and is_shooting
 * @implements focusOutEvent(QFocusEvent*): Keeps the shooter focused
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Overrides ShooterBase's functions
 * @include get_pos(): Return the player's position
 * @include process_powerup(BulletPowerUp*): Handles power-up tasks when ShooterPlayer/BulletPlayer collided with BulletPowerUp
 * @include collision():
 *              No parameter: Overrides shooterBase's function (do NOTHING)
 *              1 argument (collision_item): Call this function instead and pass the collision item (bullet/enemy/boss)
 * @include reset_nullptr(): Call in gameEvent's restart function to set nullptr_phase to false
 *
 * SIGNALS
 * @include start_signal(), pause_all(), unpause_all(): Signals to send to the main game
 * @include player_dead(): Signal triggered when health reaches 0
 * @include powerup_text(int), shooter_text(int): Signal to send to infoBox, to display the correct power-up message in infoBox
 * @include clear_field(bool): Signal triggered when player pressed 'R' key or hit BulletPowerUp with clear field function
 *
 * PUBLIC SLOTS
 * @include move(): Overrides shooterBase's function, prevents going out of bound
 * @include shoot(): Overrides shooterBase's function
 * @include reset_shooter(): Sets powerup_shooter to false after 10 seconds
 * @include reset_immune(): Reset immunity after 1 second
 * @include begin_phase3(): Set null_pointer to true when boss's phase 3 starts
 */

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

public:
    constexpr static const int DEFAULT_SPEED {10};
    constexpr static const int PLAYER_SIZE_X {24};
    constexpr static const int PLAYER_SIZE_Y {38};
    constexpr static const int DEFAULT_PLAYER_HP {25};

    enum SoundType
    {
        Hurt,
        Powerup,
        Shoot,
        NUM_SOUND_TYPES
    };

private:
    int speed {DEFAULT_SPEED};
    bool immune {false};
    int powerup_shooter {0};
    static bool paused, dead;
    bool nullptr_phase {false};
    int powerup_shooter_counter {0};
    CustomTimer *powerup_timer {nullptr}, *immune_timer {nullptr};

    void set_sprite(const char* sprite);

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
