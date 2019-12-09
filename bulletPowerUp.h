#ifndef BULLETPOWERUP_H
#define BULLETPOWERUP_H
#include <QtDebug>
#include <stdlib.h>

#include "bulletBase.h"
#include "bulletPlayer.h"

class BulletPowerUp: public BulletBase{
public:
    enum PowerUpType
    {
        Breakpoint,     //health increase
        StackOverflow,  //clear field
        CoutTestEndl    //increase shooter strength
    };


private:
    PowerUpType power_type;

public:
    BulletPowerUp(int dx = 0, int dy = 0, PowerUpType power_type = Breakpoint,
                  int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                  int move_freq = DEFAULT_FREQ);
    PowerUpType get_power_type();
};

#endif // BULLETPOWERUP_H
