#ifndef SHOOTERBASE_H
#define SHOOTERBASE_H

#include "health.h"
#include "bulletPlayer.h"
#include "bulletEnemy.h"
#include <QObject>
#include <QGraphicsRectItem>

/**
 * @brief The ShooterBase class
 * Abstract Base Class for player/enemy
 * @include health: Pointer to dynamic Health object, created in constructor and deleted in destructor
 * @include dx, dy: entity's velocity
 * @include is_shooting: set to true if the entity will shoot bullet (called automatically)
 * @include create_health(int, int): write entity's health on screen //TODO: remove? just need this for player
 * @include move(): pure virtual slot for updating entity's position
 * @include collision(): pure virtual slot for checking collision with other entities/bullets
 * @include shoot(): pure virtual slot for shooting bullets
 */

class ShooterBase: public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    Health* health;
    int dx;
    int dy;
    bool is_shooting;

public:
    ShooterBase(QString, int dx=0, int dy=0, bool shoot=false);
    ~ShooterBase();
    void create_health(int posx, int posy);

public slots:
    virtual void move() = 0;
    virtual void collision() = 0;
    virtual void shoot() = 0;

};


#endif // SHOOTERBASE_H
