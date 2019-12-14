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
        CoutTestEndl,   //increase shooter strength
        Random          //constructor choose from above 3
    };


private:
    PowerUpType power_type;

public:
    BulletPowerUp(const int& dx = 0, const int& dy = 0, const PowerUpType& power_type = Random,
                  const int size_x = BULLET_SIZE, const int size_y = BULLET_SIZE,
                  const int& move_freq = DEFAULT_FREQ);
    PowerUpType get_power_type();
};

#endif // BULLETPOWERUP_H
