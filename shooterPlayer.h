#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include <QPauseAnimation>
#include <QKeyEvent>
#include <QDebug>
#include <QList>

#include "shooterBase.h"
#include "bulletPowerUp.h"

/**
 * @brief The ShooterPlayer class
 * Class for player
 *
 * PRIVATE DATA MEMBERS
 * @include speed: player's moving speed
 * @include immune: set to true if the player is immune (for 1 second after being hit)
 * @include powerup_shooter: return true if the shooter has been improved
 *
 * PRIVATE MEMBER FUNCTION RE-IMPLEMENTATIONS
 * @implements keyPressEvent(QKeyEvent*): handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): handles keyboard input, resets player velocity and is_shooting
 * @implements focusOutEvent(QFocusEvent*): keeps the shooter to be focused
 *
 * PUBLIC MEMBER FUNCITONS
 * @include create_health(): write health
 * @include get_pos(): return the player's position
 * @include process_powerup(BulletPowerUp*): handles power-up tasks when ShooterPlayer/BulletPlayer collided with BulletPowerUp
 *
 * SIGNALS
 * @include pause_all(), unpause_all(): signals to send to the main game
 * @include player_dead(): signal triggered when health reaches 0
 * @include powerup_text(int): signal to send to infoBox, to display the correct power-up message in infoBox
 * @include clear_field(bool): signal triggered when player pressed 'R' key or hit BulletPowerUp with clear field function
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, prevents going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 * @include reset_shooter(): sets powerup_shooter to false after 10 seconds
 * @include reset_immune(): reset immunity after 1 second
 */

#define DEFAULT_SPEED 10
class BulletPowerUp;

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

private:
    int speed {DEFAULT_SPEED};
    bool immune {false};
    bool powerup_shooter {false};
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void focusOutEvent(QFocusEvent* event) override;

public:
    ShooterPlayer(int hp = DEFAULT_PLAYER_HP, int dx = 0, int dy = 0,
                  int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false,
                  int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                  int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    QPointF get_pos();
    void process_powerup(BulletPowerUp* bullet);

signals:
    void pause_all();
    void unpause_all();
    void player_dead();
    void powerup_text(int type);
    void clear_field(bool restart);

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;
    void reset_shooter();
    void reset_immunity();
};

#endif // SHOOTERPLAYER_H
