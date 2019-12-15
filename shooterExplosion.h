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
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include explosion_timer: CustomTimer for displaying the explosion
 * @include size_x, size_y: Sprite's size
 * @include sprite_counter: Count the sprite to be displayed
 * @include set_sprite(): Update the sprite with an image
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Pause/Unpause explosion_timer
 *
 * PUBLIC SLOTS
 * @include update(): Update the sprite and destroys this object at the end
 */

class ShooterExplosion : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT

public:
    constexpr static const int EXPLOSION_DURATION {6*MIN_FREQ};

private:
    CustomTimer* explosion_timer;
    int size_x, size_y;
    int sprite_counter {1};
    void set_sprite(const char* sprite);

public:
    ShooterExplosion(const int& size_x, const int& size_y, int duration = EXPLOSION_DURATION);
    ~ShooterExplosion();
    void pause();
    void unpause();

public slots:
    void update();

};

#endif // SHOOTEREXPLOSION_H
