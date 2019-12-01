#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <QObject>
#include <QGraphicsRectItem>

#include "bulletPlayer.h"
#include "shooterBase.h"

/**
 * @brief The ShooterEnemy class
 * Class for enemies
 * @include create_health(): write health //TODO: remove?
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

class ShooterEnemy:public ShooterBase{
    Q_OBJECT //implies an object can handle signals

public:
    ShooterEnemy(int hp = DEFAULT_ENEMY_HP, int dx = 0, int dy = 0,
                 int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                 int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ,
                 int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false);
    void create_health();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;
};


#endif // SHOOTERENEMY_H
