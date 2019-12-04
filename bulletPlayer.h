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
    BulletPlayer(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                 int move_freq = DEFAULT_FREQ);

public slots:

};

#endif // BULLETSHOOTER_H

