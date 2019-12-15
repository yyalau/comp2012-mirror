#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include "bulletBase.h"

/**
 * @brief The BulletPlayer class
 * Class for bullets shot by player
 */

class BulletPlayer:public BulletBase{

public:
    //bullet sprite is flipped 90 degrees
    constexpr static const int BULLETPLAYER_SIZE_X {18};
    constexpr static const int BULLETPLAYER_SIZE_Y {31};

public:
    BulletPlayer(const int& dx = 0, const int& dy = 0,
                 const int size_x = BULLETPLAYER_SIZE_X, const int size_y = BULLETPLAYER_SIZE_Y,
                 const int& move_freq = DEFAULT_FREQ);

};

#endif // BULLETSHOOTER_H

