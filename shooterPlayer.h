#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include <QPauseAnimation>
#include <QKeyEvent>

#include "shooterBase.h"
#include "bulletPowerUp.h"

/**
 * @brief The ShooterPlayer class
 * Class for player
 *
 * PRIVATE DATA MEMBERS
 * @include speed: player's moving speed
 * @include immune_counter: player is immune for 1 second (50 * MIN_FREQ) when hit
 *
 * PRIVATE MEMBER FUNCTION RE-IMPLEMENTATIONS
 * @implements keyPressEvent(QKeyEvent*): handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): handles keyboard input, resets player velocity and is_shooting
 * @implements focusOutEvent(QFocusEvent*): keeps the shooter to be focused
 *
 * PUBLIC MEMBER FUNCITONS
 * @include create_health(): write health
 * @include get_pos(): return the player's position
 *
 * SIGNALS
 * @include pause_all(), unpause_all(): signals to send to the main game
 * @include player_dead(): signal triggered when health reaches 0
 * @include powerup(): signal to send to gameEvent, indicating that the shooter hits Bullet_PowerUp
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, prevents going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

#define DEFAULT_SPEED 10

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

private:
    int speed {DEFAULT_SPEED};
    int immune_counter {0};
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

public:
    ShooterPlayer(int hp = DEFAULT_PLAYER_HP, int dx = 0, int dy = 0,
                  int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false,
                  int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                  int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    QPointF get_pos();

signals:
    void pause_all();
    void unpause_all();
    void player_dead();
    void powerup();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;

};

#endif // SHOOTERPLAYER_H
