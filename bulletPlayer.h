#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include "bulletBase.h"

/**
 * @brief The BulletPlayer class
 * Class for bullets shot by player
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): override bulletBase's functions
 *
 * PUBLIC SLOTS
 * @include collision(): overrides bulletBase's function (REMOVED)
 */

class BulletPlayer:public BulletBase{

public:
    BulletPlayer(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                 int move_freq = DEFAULT_FREQ/*, int coll_freq = DEFAULT_FREQ*/);
    virtual void pause() override;
    virtual void unpause() override;

public slots:
    //virtual void collision() override;

};

#endif // BULLETSHOOTER_H

