#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include <QPauseAnimation>
#include <QKeyEvent>

#include "shooterBase.h"

/**
 * @brief The ShooterPlayer class
 * Class for player
 *
 * PRIVATE DATA MEMBERS
 * @include speed: player's moving speed
 *
 * PRIVATE MEMBER FUNCTION RE-IMPLEMENTATIONS
 * @implements keyPressEvent(QKeyEvent*): handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): handles keyboard input, resets player velocity and is_shooting
 * @implements focusOutEvent(QFocusEvent*): keeps the shooter to be focused
 *
 * PUBLIC MEMBER FUNCITONS
 * @include create_health(): write health
 * @include pause(), unpause(): override shooterBase's functions
 * @include get_pos(): return the player's position
 *
 * SIGNALS
 * @include pause_all(), unpause_all(): signals to send to the main game
 * @include player_dead(): signal triggered when health reaches 0
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
    int speed;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

public:
    ShooterPlayer(int hp = DEFAULT_PLAYER_HP, int speed = DEFAULT_SPEED, int dx = 0, int dy = 0,
                  int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                  int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ,
                  int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false);
    void create_health();
    virtual void pause() override;
    virtual void unpause() override;
    QPointF get_pos();

signals:
    void pause_all();
    void unpause_all();
    void player_dead();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;


};

#endif // SHOOTERPLAYER_H
