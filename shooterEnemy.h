#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <cmath>
#include <QPainterPath>

#include "shooterBase.h"
#include "shooterPlayer.h"
#include "shooterExplosion.h"

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
 * @include drop_powerup: True if this enemy will drop a powerup upon death, false by default
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_player(): Set the shooter to point to the playe
 * @include set_drop_powerup(): Set drop_powerup to true
 * @include safe_kill(): Set health to 0 (to generate explosion)
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

class ShooterEnemy:public ShooterBase{
    Q_OBJECT //implies an object can handle signals

public:
    static const int ENEMY_SIZE {40};

public:
    enum EnemyPathingType
    {
        Linear,             //Move in straight line, disappears when out of bound
        BorderBounce,        //Move in straight line, reverse direction when hitting border
        Circular,
        GotoTarget,
        LeaveScreen,
        Wave
        //TODO
    };

    enum EnemyShootingType
    {
        Random,             //Bullet's dy = 10; dx = random from -20 to 20
        AimAtPlayer,        //Aimed at the player's position when shot
        NoShooting,
        Forward,
        Triple,
        Double,
        Circle,             //Shoot bullets in every directions
        ExplodeOnDeath,     //For Boss's 3rd phase
        //TODO
    };

private:
    EnemyPathingType pathing_type;
    const EnemyShootingType shooting_type;
    static ShooterPlayer* player;
    bool drop_powerup {true};

    QPoint target_pos;
    double cirPathCounter;
    double circular_angle {0.0};

public:
    ShooterEnemy(const EnemyPathingType& pathing_type, const EnemyShootingType& shooting_type,
                 const int& hp = DEFAULT_ENEMY_HP, const int& dx = 0, const int& dy = 0,
                 const int& shoot_freq = 2*DEFAULT_SHOOT_FREQ, const bool& shoot = true,
                 const int size_x = ENEMY_SIZE, const int size_y = ENEMY_SIZE,
                 const int& move_freq = DEFAULT_FREQ);
    static void set_player(ShooterPlayer* shooter);
    void set_targetPos(int x, int y);
    void set_pathing_type(EnemyPathingType pathingType);
    virtual bool collision() override;
    bool out_of_bound();
    void set_drop_powerup();
    void safe_kill();

public slots:
    virtual void move() override;
    virtual void shoot() override;
};


#endif // SHOOTERENEMY_H
