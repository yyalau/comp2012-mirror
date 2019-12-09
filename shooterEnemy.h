#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <stdlib.h> //rand()
#include <cmath>
#include <QPainterPath>

#include "shooterBase.h"
#include "shooterPlayer.h"

/**
 * @brief The ShooterEnemy class
 * Class for enemies
 *
 * ENUMS
 * @enum EnemyPathingType: How the enemy moves after spawned
 * @enum EnemyShootingType: How the enemy shoots bullets
 *
 * PRIVATE DATA MEMBERS
 * @include pathing_type, shooting_type: See enum above
 * @include player: Pointer to the player. Use set_player() when initializing the player in SetUp
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include create_health(): write health //TODO: remove?
 * @include set_player(): Set the shooter to point to the player
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

class ShooterEnemy:public ShooterBase{
    Q_OBJECT //implies an object can handle signals

public:
    enum EnemyPathingType
    {
        Linear,             //Move in straight line, disappears when out of bound
        BorderBounce,        //Move in straight line, reverse direction when hitting border
        Circular
        //TODO
    };

    enum EnemyShootingType
    {
        Random,             //Bullet's dy = 10; dx = random from -20 to 20
        AimAtPlayer,        //Aimed at the player's position when shot
        Circle,             //Shoot bullets in every directions
        ExplodeOnDeath,     //For Boss's 3rd phase
        NoShooting
        //TODO
    };

private:
    EnemyPathingType pathing_type;
    EnemyShootingType shooting_type;
    static ShooterPlayer* player;
    //"static" variables for each enemy movement
    double circular_angle {0.0};

public:
    ShooterEnemy(EnemyPathingType pathing_type, EnemyShootingType shooting_type,
                 int hp = DEFAULT_ENEMY_HP, int dx = 0, int dy = 0,
                 int shoot_freq = 2*DEFAULT_SHOOT_FREQ, bool shoot = true,
                 int size_x = ENTITY_SIZE, int size_y = ENTITY_SIZE,
                 int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    static void set_player(ShooterPlayer* shooter);

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;
};


#endif // SHOOTERENEMY_H
