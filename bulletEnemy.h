#ifndef BULLETENEMY_H
#define BULLETENEMY_H

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
 * @include pause(), unpause(): override bulletBase's functions
 *
 * PUBLIC SLOTS
 * @include move(): overrides bulletBase's function to reimplement out-of-bound case
 * @include collision(): overrides bulletBase's function (REMOVED)
 */

class BulletEnemy:public BulletBase{

public:
    enum BulletType {
        Normal,     //dx, dy are constant
        OutOfBound, //ignores left, right boundaries
        Falling,    //dy increases with time
        Homing,     //always aim at the player (DOES NOT WORK CURRENTLY)
        Explode     //when reaching the bottom, explodes into multiple Falling bullets
        //TODO
    };

private:
    BulletType bullet_type;

public:
    BulletEnemy(int dx = 0, int dy = 0, BulletType bullet_type = Normal,
                int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
                int move_freq = DEFAULT_FREQ/*, int coll_freq = DEFAULT_FREQ*/);
    virtual void pause() override;
    virtual void unpause() override;

public slots:
    virtual void move() override;
    //virtual void collision() override;

};

#endif // BULLETENEMY_H

