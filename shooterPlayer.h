#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include "health.h"
#include "shooterBase.h"
#include "bulletEnemy.h"
#include <QObject>
#include <QGraphicsRectItem>

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

class ShooterPlayer: public ShooterBase{
    Q_OBJECT

private:
    qreal speed {20};
    void keyPressEvent(QKeyEvent* event) override;
    void keyReleaseEvent(QKeyEvent* event) override;

public:
    ShooterPlayer();
    void create_health();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;

};

#endif // SHOOTERPLAYER_H
