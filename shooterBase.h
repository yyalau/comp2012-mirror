#ifndef SHOOTERBASE_H
#define SHOOTERBASE_H

#include <QObject>
#include <QGraphicsRectItem>

#include "define.h"
#include "health.h"
#include "bulletPlayer.h"
#include "bulletEnemy.h"

/**
 * @brief The ShooterBase class
 * Abstract Base Class for player/enemy
 * @include health: Pointer to dynamic Health object, created in constructor and deleted in destructor
 * @include dx, dy: entity's velocity
 * @include size_x, size_y: entity's size
 * @include move_freq: milliseconds between times move() is called
 * @include coll_freq: milliseconds between times coll() is called
 * @include shoot_freq: milliseconds between times shoot() is called
 * @include is_shooting: set to true if the entity will shoot bullet (called automatically)
 * @include create_health(int, int): write entity's health on screen //TODO: remove? just need this for player
 * @include get_health(): return pointer to this entity's health
 * @include move(): pure virtual slot for updating entity's position
 * @include collision(): pure virtual slot for checking collision with other entities/bullets
 * @include shoot(): pure virtual slot for shooting bullets
 */

class ShooterBase: public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    Health* health;
    int dx, dy;
    int size_x, size_y;
    int move_freq, coll_freq, shoot_freq;
    bool is_shooting;

public:
    ShooterBase(QString, int hp, int dx = 0, int dy = 0, int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ,
                int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = false);
    ~ShooterBase();
    void create_health(int posx, int posy);
    Health* get_health();

public slots:
    virtual void move() = 0;
    virtual void collision() = 0;
    virtual void shoot() = 0;

};


#endif // SHOOTERBASE_H
