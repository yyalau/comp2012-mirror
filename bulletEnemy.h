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
        Explode     //when reaching the bottom, explodes into multiple Falling bullets      //FOR BOSS PHASE 3
        //TODO
    };

private:
    BulletType bullet_type;
    bool bounced {false};

    int fall_counter{0};
    const int FALL_COUNTER_MAX {3};

public:
    BulletEnemy(const int& dx = 0, const int& dy = 0, const BulletType& bullet_type = Normal,
                const int size_x = BULLET_SIZE, const int size_y = BULLET_SIZE,
                const int& move_freq = DEFAULT_FREQ);
    virtual bool out_of_bound() override;

public slots:
    virtual void move() override;

};

#endif // BULLETENEMY_H

