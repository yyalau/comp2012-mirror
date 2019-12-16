#ifndef SHOOTERBASE_H
#define SHOOTERBASE_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QMediaPlayer>

#include "define.h"
#include "customTimer.h"
#include "health.h"
#include "bulletPlayer.h"
#include "bulletEnemy.h"

/**
 * @brief The ShooterBase class
 * Abstract Base Class for player/enemy
 *
 * PROTECTED DATA MEMBERS/MEMBER FUNCTIONS
 * @include dx, dy: Entity's velocity
 * @include size_x, size_y: Entity's size
 * @include move_freq, coll_freq, shoot_freq: Milliseconds between times move(), collision(), shoot() are called
 * @include move_timer, coll_timer, shoot_timer: CustomTimer for triggering move(), collision(), shoot()
 * @include is_shooting: Set to true if the entity will shoot bullet (called automatically)
 * @include sound: Array of shooter's sound effects. Set the size in constructor
 * @include num_sound_types: sound's array size for deleting
 * @include play_sound(): Set sound position back to 0 and play again
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include health: Pointer to dynamic Health object, created in constructor and deleted in destructor
 * @include pause(), unpause(): Virtual functions for stopping/restarting the timers
 * @include shoot_bullet(): Convenient function for creating a bullet
 * @include collision(): Pure virtual slot for handling collision effects
 *
 * PUBLIC SLOTS
 * @include move(): Pure virtual slot for updating entity's position
 * @include shoot(): Pure virtual slot for shooting bullets
 */

class ShooterBase: public QObject, public QGraphicsPixmapItem {
    Q_OBJECT

public:
    constexpr static const int ENTITY_SIZE {40};

protected:
    int dx, dy;
    int size_x, size_y;
    int move_freq, shoot_freq;
    CustomTimer *move_timer, *shoot_timer;
    bool is_shooting;
    QMediaPlayer** sound;
    int num_sound_types;

    void play_sound(QMediaPlayer* sound_to_play);

public:
    ShooterBase(const QString& name, const int& hp, const int& dx = 0, const int& dy = 0,
                const int& shoot_freq = DEFAULT_SHOOT_FREQ, const bool& shoot = false,
                const int size_x = ENTITY_SIZE, const int size_y = ENTITY_SIZE,
                const int move_freq = DEFAULT_FREQ, const int& num_sound_types = 0);
    virtual ~ShooterBase();
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
