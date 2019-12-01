#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include <QObject>
#include <QGraphicsRectItem>

#include "health.h"
#include "shooterBase.h"
#include "bulletEnemy.h"

/**
 * @brief The ShooterPlayer class
 * Class for player
 * @include speed: player's moving speed
 * @implements keyPressEvent(QKeyEvent*): handles keyboard input, updates player velocity and is_shooting
 * @implements keyReleaseEvent(QKeyEvent*): handles keyboard input, resets player velocity and is_shooting
 * @include create_health(): write health
 * @include move(): overrides shooterBase's function, prevents going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

#define DEFAULT_SPEED 20

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

private:
    int speed;
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public:
    ShooterPlayer(int hp = DEFAULT_PLAYER_HP, int speed = DEFAULT_SPEED, int dx = 0, int dy = 0,
                  int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                  int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ,
                  int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false);
    void create_health();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;

};

#endif // SHOOTERPLAYER_H
