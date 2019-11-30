#ifndef BULLETBASE_H
#define BULLETBASE_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QTimer>
#include <QDebug>
#include <QList>

/**
 * @brief The BulletBase class
 * Abstract Base Class for bullets
 * @include dx, dy: velocity of bullet
 * @include move(): slot for updating the position of bullet, has out of bound handling
 * @include collision(): pure virtual slot for checking bullet collision with other entities
 */

class BulletBase: public QObject, public QGraphicsRectItem{
     Q_OBJECT //implies the object can handle signals
protected:
    //TODO: change to qreal? some weird stuff happened with the player's dx dy when using int
    int dx;
    int dy;

public:
    BulletBase(int dx=0, int dy=0);
    virtual ~BulletBase()=default;

public slots:
    void move();
    virtual void collision() = 0;
};

#endif // BULLETBASE_H
