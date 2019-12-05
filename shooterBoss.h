#ifndef SHOOTERBOSS_H
#define SHOOTERBOSS_H

#include <cmath>

#include "shooterBase.h"
#include "popUpDialogue.h"

/**
 * @brief The ShooterBoss class
 * Class for the final boss
 *
 * ENUMS
 * @enum BossPhase: Name of the phase the boss is in
 *
 * PRIVATE DATA MEMBERS
 * @include phase: See enum above
 * @include PHASE_HEALTH: Health when the boss switches to next state. PHASE_HEALTH[X] -> go to state X
 * @include boss_to_next_phase: flag for allowing boss to switch from Dialogue to other phases
 * @include health_bar: PopUpDialogue for displaying the health bar
 * @include pattern_name: PopUpDialogue for displaying pattern name at the beginning of phase
 * @include pattern_name_counter: counter for displaying the pattern name 1 second
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_health(): Show the boss's remaining health. ONLY CALL AFTER parent_scene->addItem()
 * @include start_bossfight(): Call this after the intro dialogue finishes
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
        Dialogue = -2,  //do nothing, does not take damage either
        PhasePre1,      //spam Random bullets
        Phase1,         //IndexOutOfBoundException, shoot 2 rays of OutOfBound bullets (bulletEnemy handles the pattern)
        PhasePre2,      //TODO
        Phase2,         //LEAK X DIRECT BYTES, Explode bullets fall from the top
        Phase3          //NullPointerException, TODO (disable moving?)
        //TODO
    };

private:
    BossPhase phase {Dialogue};
    const int PHASE_HEALTH[4] {850, 650, 500, 300};
    bool boss_to_next_phase {false};
    PopUpDialogue* health_bar;
    PopUpDialogue* pattern_name;
    int pattern_name_counter;

public:
    ShooterBoss(int hp = BOSS_HP, int dx = 0, int dy = 0,
                int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = true,
                int size_x = BOSS_SIZE_X, int size_y = BOSS_SIZE_Y,
                int move_freq = DEFAULT_FREQ, int coll_freq = DEFAULT_FREQ);
    ~ShooterBoss() override;
    void show_health();
    void start_bossfight();

public slots:
    virtual void move() override;
    virtual void collision() override;
    virtual void shoot() override;
};

#endif // SHOOTERBOSS_H
