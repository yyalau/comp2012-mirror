#ifndef BULLETBASE_H
#define BULLETBASE_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QList>

#include "define.h"

/**
 * @brief The BulletBase class
 * Abstract Base Class for bullets
 * @include dx, dy: velocity of bullet
 * @include size_x, size_y: bullet's hitbox size
 * @include move_freq: milliseconds between times move() is called
 * @include coll_freq: milliseconds between times collision() is called
 * @include move(): slot for updating the position of bullet, has out of bound handling
 * @include collision(): pure virtual slot for checking bullet collision with other entities
 */

class BulletBase: public QObject, public QGraphicsRectItem{
     Q_OBJECT //implies the object can handle signals
protected:
    int dx, dy;
    int size_x, size_y;
    int move_freq, coll_freq;

public:
    BulletBase(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
               int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    virtual ~BulletBase()=default;

public slots:
    void move();
    virtual void collision() = 0;
};

#endif // BULLETBASE_H
