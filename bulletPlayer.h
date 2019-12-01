#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include <QGraphicsRectItem>
#include <QObject>

#include "bulletBase.h"

/**
 * @brief The BulletPlayer class
 * Class for bullets shot by player
 * @include coll_freq: milliseconds between times collision() is called
 * @include collision(): overrides bulletBase's function
 */

class BulletPlayer:public BulletBase{

public:
    BulletPlayer(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                 int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    virtual ~BulletPlayer()=default;

public slots:
    virtual void collision() override;

};

#endif // BULLETSHOOTER_H

