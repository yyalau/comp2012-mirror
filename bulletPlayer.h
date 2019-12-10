#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H

#include "bulletBase.h"

/**
 * @brief The BulletPlayer class
 * Class for bullets shot by player
 *
 * PUBLIC MEMBER FUNCTIONS
 *
 * PUBLIC SLOTS
 */

class BulletPlayer:public BulletBase{

public:
    //bullet sprite is flipped 90 degrees
    static const int BULLETPLAYER_SIZE_X {31};
    static const int BULLETPLAYER_SIZE_Y {18};

public:
    BulletPlayer(int dx = 0, int dy = 0,
                 int size_x = BULLETPLAYER_SIZE_X, int size_y = BULLETPLAYER_SIZE_Y,
                 int move_freq = DEFAULT_FREQ);

public slots:

};

#endif // BULLETSHOOTER_H

