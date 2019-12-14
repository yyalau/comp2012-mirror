#ifndef SHOOTERBASE_H
#define SHOOTERBASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>

#include "define.h"
#include "customTimer.h"
#include "health.h"
#include "bulletPlayer.h"
#include "bulletEnemy.h"

/**
 * @brief The ShooterBase class
 * Abstract Base Class for player/enemy
 *
 * PROTECTED DATA MEMBERS
 * @include dx, dy: entity's velocity
 * @include size_x, size_y: entity's size
 * @include move_freq, coll_freq, shoot_freq: milliseconds between times move(), collision(), shoot() are called
 * @include move_timer, coll_timer, shoot_timer: CustomTimer for triggering move(), collision(), shoot()
 * @include is_shooting: set to true if the entity will shoot bullet (called automatically)
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include health: Pointer to dynamic Health object, created in constructor and deleted in destructor
 * @include pause(), unpause(): virtual functions for stopping/restarting the timers
 * @include shoot_bullet(): convenient function for creating a bullet
 * @include collision(): pure virtual slot for handling collision effects
 *
 * PUBLIC SLOTS
 * @include move(): pure virtual slot for updating entity's position
 * @include shoot(): pure virtual slot for shooting bullets
 */

class ShooterBase: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    static const int ENTITY_SIZE {40};

protected:
    int dx, dy;
    int size_x, size_y;
    int move_freq, shoot_freq;
    CustomTimer *move_timer, *shoot_timer;
    bool is_shooting;

public:
    ShooterBase(const QString& name, const int& hp, const int& dx = 0, const int& dy = 0,
                const int& shoot_freq = DEFAULT_SHOOT_FREQ, const bool& shoot = false,
                const int size_x = ENTITY_SIZE, const int size_y = ENTITY_SIZE,
                const int move_freq = DEFAULT_FREQ);
    ~ShooterBase();
    Health* health;
    virtual void pause();
    virtual void unpause();
    void shoot_bullet(BulletBase* bullet);
    virtual bool collision() = 0;

public slots:
    virtual void move() = 0;
    virtual void shoot() = 0;

};


#endif // SHOOTERBASE_H
