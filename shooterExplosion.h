#ifndef SHOOTEREXPLOSION_H
#define SHOOTEREXPLOSION_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

#include "define.h"
#include "customTimer.h"

/**
 * @brief The ShooterExplosion class
 * Create a "dead" image when a shooter is destroyed. Call this object when a shooter reaches 0 health
 *
 * PRIVATE DATA MEMBERS
 * @include explosion_timer: CustomTimer for displaying the explosion
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Pause/Unpause explosion_timer
 *
 * PUBLIC SLOTS
 * @include remove_this(): Delete this object after some time
 */

class ShooterExplosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    static const int EXPLOSION_DURATION {500};

private:
    CustomTimer* explosion_timer;

public:
    ShooterExplosion(const int& size_x, const int& size_y, int duration = EXPLOSION_DURATION);
    ~ShooterExplosion();
    void pause();
    void unpause();

public slots:
    void remove_this();

};

#endif // SHOOTEREXPLOSION_H
