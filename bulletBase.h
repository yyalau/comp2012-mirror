#ifndef BULLETBASE_H
#define BULLETBASE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QList>

#include "define.h"

/**
 * @brief The BulletBase class
 * Abstract Base Class for bullets
 *
 * PROTECTED DATA MEMBERS
 * @include dx, dy: velocity of bullet
 * @include move_freq: milliseconds between times move() is called
 * @include move_timer: QTimer for triggering move()
 *
 * PUBLIC FUNCTIONS
 * @include pause(), unpause(): stopping/restarting the timers
 *
 * PUBLIC SLOTS
 * @include move(): virtual slot for updating the position of bullet, has out of bound handling
 * @include collision(): pure virtual slot for checking bullet collision with other entities (REMOVED)
 */

class BulletBase: public QObject, public QGraphicsPixmapItem{
     Q_OBJECT //implies the object can handle signals
protected:
    int dx, dy;
    int size_x, size_y;
    int move_freq/*, coll_freq*/;
    QTimer *move_timer/*, *coll_timer*/;

public:
    BulletBase(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
               int move_freq = DEFAULT_FREQ/*, int coll_freq = DEFAULT_FREQ*/);
    ~BulletBase();
    virtual void pause();
    virtual void unpause();

public slots:
    virtual void move();
    //virtual void collision() = 0;
};

#endif // BULLETBASE_H
