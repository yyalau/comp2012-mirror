#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <cmath>
#include <QPainterPath>
#include <QMediaPlayer>

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
 * @include music: music player for the explosion sound
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_player(): Set the shooter to point to the player
 * @include set_targetPos(): For GotoTarget's case
 * @include collision(): overrides shooterBase's function
 * @include set_drop_powerup(): Set drop_powerup to true
 * @include out_of_bound(): Check if enemy is out of bound to remove
 * @include safe_kill(): Set health to 0 (to generate explosion)
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include shoot(): overrides shooterBase's function
 */

class ShooterEnemy: public ShooterBase {
    Q_OBJECT //implies an object can handle signals

public:
    constexpr static const int ENEMY_SIZE {35};
    constexpr static const int DEFAULT_ENEMY_HP {3};

public:
    enum EnemyPathingType
    {
        Linear,             //Move in straight line, disappears when out of bound
        BorderBounce,       //Move in straight line, reverse direction when hitting border
        Circular,           //Move in an ellipse trajectory
        GotoTarget,         //Move to a specific position
        Wave                //Move in a wave trajectory
    };

    enum EnemyShootingType
    {
        Random,             //Bullet's dy = 10; dx = random from -20 to 20
        AimAtPlayer,        //Aimed at the player's position when shot
        NoShooting,         //Don't shoot at all (UNUSED)
        Forward,            //Shoot 1 bullet forward
        Triple,             //Shoot 3 bullets forward
        Double,             //Shoot 2 bullets forward
        Circle,             //Shoot bullets in every directions
        ExplodeOnDeath,     //For Boss's 3rd phase
    };

private:
    EnemyPathingType pathing_type;
    const EnemyShootingType shooting_type;
    static ShooterPlayer* player;
    bool drop_powerup {false};
    QMediaPlayer* music;

    //type-specific variables
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
    virtual bool collision() override;
    bool out_of_bound();
    void set_drop_powerup();
    void safe_kill();

public slots:
    virtual void move() override;
    virtual void shoot() override;
};


#endif // SHOOTERENEMY_H
