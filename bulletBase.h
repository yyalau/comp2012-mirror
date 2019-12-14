#ifndef BULLETBASE_H
#define BULLETBASE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QDebug>
#include <QList>

#include "define.h"
#include "customTimer.h"

/**
 * @brief The BulletBase class
 * Abstract Base Class for bullets
 *
 * PROTECTED DATA MEMBERS
 * @include dx, dy: Velocity of bullet
 * @include size_x, size_y: Bullet's size
 * @include move_freq: Milliseconds between times move() is called
 * @include move_timer: CustomTimer for triggering move()
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Stopping/restarting the timers
 * @include out_of_bound(): Virtual function for checking out of bound, can be overloaded for OutOfBound bullet
 *
 * PUBLIC SLOTS
 * @include move(): Virtual slot for updating the position of bullet, has out of bound handling
 */

class BulletBase: public QObject, public QGraphicsPixmapItem{
     Q_OBJECT //implies the object can handle signals
public:
    static const int BULLET_SIZE {30};

protected:
    int dx, dy;
    int size_x, size_y;
    int move_freq;
    CustomTimer *move_timer;

public:
    BulletBase(int dx = 0, int dy = 0, const int& size_x = BULLET_SIZE, const int& size_y = BULLET_SIZE,
               const int move_freq = DEFAULT_FREQ);
    ~BulletBase();
    void pause();
    void unpause();
    virtual bool out_of_bound();

public slots:
    virtual void move();
};

#endif // BULLETBASE_H
