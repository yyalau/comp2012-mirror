#ifndef SHOOTERBOSS_H
#define SHOOTERBOSS_H

#include "shooterBase.h"

#include <QGraphicsRectItem>

/**
 * @brief The ShooterBoss class
 * Class for the final boss
 *
 * ENUMS
 * @enum BossPhase: Name of the phase the boss is in
 *
 * PRIVATE DATA MEMBERS
 * @include phase: See enum above
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_health(): Show the boss's remaining health
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 */

#define BOSS_HP 1000
#define BOSS_SIZE_X 400
#define BOSS_SIZE_Y 200

class ShooterBoss : public ShooterBase
{
    Q_OBJECT

public:
    enum BossPhase
    {
        Phase1,
        Phase2,
        Phase3
        //TODO
    };

private:
    BossPhase phase {Phase1};

public:
    ShooterBoss(int hp = BOSS_HP, int dx = 0, int dy = 0,
                int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = true,
                int size_x = BOSS_SIZE_X, int size_y = BOSS_SIZE_Y,
                int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    void show_health();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;
};

#endif // SHOOTERBOSS_H
