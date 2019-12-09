#ifndef BULLETENEMY_H
#define BULLETENEMY_H

#include <cmath>

#include "bulletBase.h"

/**
 * @brief The BulletEnemy class
 * Class for bullets shot by enemies
 *
 * ENUMS:
 * @enum BulletType: How the bullet behaves
 *
 * PRIVATE DATA MEMBERS
 * @include bullet_type: See enum above
 *
 * PUBLIC MEMBER FUNCTIONS
 *
 * PUBLIC SLOTS
 * @include move(): overrides bulletBase's function to reimplement out-of-bound case
 */

class BulletEnemy:public BulletBase{

public:
    enum BulletType {
        Normal,     //dx, dy are constant
        OutOfBound, //ignores left, right boundaries        //FOR BOSS PHASE 1
        Falling,    //dy increases with time
        Homing,     //always aim at the player (DOES NOT WORK CURRENTLY)
        Explode     //when reaching the bottom, explodes into multiple Falling bullets      //FOR BOSS PHASE 3
        //TODO
    };

private:
    BulletType bullet_type;
    bool bounced {false};
    //"static" variable for bullet movement
    int fall_counter{0};
    const int FALL_COUNTER_MAX {3};

public:
    BulletEnemy(int dx = 0, int dy = 0, BulletType bullet_type = Normal,
                int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                int move_freq = DEFAULT_FREQ);

public slots:
    virtual void move() override;

};

#endif // BULLETENEMY_H

