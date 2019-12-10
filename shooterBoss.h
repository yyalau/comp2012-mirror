#ifndef SHOOTERBOSS_H
#define SHOOTERBOSS_H

#include <cmath>

#include "shooterBase.h"
#include "shooterPlayer.h"
#include "popUpDialogue.h"

/**
 * @brief The ShooterBoss class
 * Class for the final boss
 *
 * ENUMS
 * @enum BossPhase: Name of the phase the boss is in
 *
 * PRIVATE DATA MEMBERS
 * @include PHASE_HEALTH: Health when the boss switches to next state. PHASE_HEALTH[X] -> go to state X
 * @include phase: See enum above
 * @include boss_to_next_phase: flag for allowing boss to switch from Dialogue to other phases
 * @include health_bar: PopUpDialogue for displaying the health bar
 * @include dialogue_counter: Counter to keep track of dialogues shown
 * @include dialogue_timer: CustomTimer for displaying pre-battle dialogue
 * @include flag_timer: CustomTimer for setting flag to true after some time
 * @include player: Pointer to the player. Use set_player() when initializing the player in SetUp
 * @include set_shoot_freq(): change the shooting frequency (for each pattern)
 * @include set_phase(): change to a certain phase. handles specific configuration when entering phase
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_player(): Set the shooter to point to the player
 * @include pause(), unpause(): Overrides ShooterBase's functions
 * @include show_health(): Show the boss's remaining health. ONLY CALL AFTER parent_scene->addItem()
 * @include start_bossfight(): Call this after the intro dialogue finishes //TODO: can remove
 *
 * SIGNALS
 * @include start_phase3(): sent to the shooterPlayer
 * @include boss_dead(): sent when boss is defeated -> win!
 *
 * PUBLIC SLOTS
 * @include move(): overrides shooterBase's function, handles going out of bound
 * @include collision(): overrides shooterBase's function
 * @include shoot(): overrides shooterBase's function
 * @include enable_flag(): set flag to true after the pattern name finishes showing
 * @include show_dialogue(): display the dialogue before the battle
 */

class ShooterBoss : public ShooterBase
{
    Q_OBJECT

public:
    static const int BOSS_HP {1000};
    static const int BOSS_SIZE_X {300};
    static const int BOSS_SIZE_Y {200};
    static const int BOSS_POS_X {(GAMEAREA_LENGTH-BOSS_SIZE_X)/2};
    static const int BOSS_POS_Y {10};
    static const int DIALOGUE_FREQ {3000};       //each dialogue line lasts for 5 seconds

public:
    enum BossPhase
    {
        Entrance = -2,  //for entering the screen only
        Dialogue,       //do nothing, does not take damage either
        PhasePre1,      //spam Random bullets
        Phase1,         //IndexOutOfBoundException, shoot 2 rays of OutOfBound bullets (bulletEnemy handles the pattern)
        PhasePre2,      //2 rays of "spaghetti code"
        Phase2,         //LEAK X DIRECT BYTES, Explode bullets fall from the top
        Phase3          //NullPointerException, disable moving?
    };

private:
    const int PHASE_HEALTH[6] = {BOSS_HP, 825, 625, 400, 175, 0};

    BossPhase phase {Entrance};
    bool boss_to_next_phase {false};
    PopUpDialogue* health_bar;
    CustomTimer *dialogue_timer {nullptr}, *flag_timer {nullptr};
    int dialogue_counter {0};
    static ShooterPlayer* player;
    void set_shoot_freq(int shoot_freq);
    void set_phase(BossPhase phase);

    //phase-specific variables
    int phase_dir {1};
    double phase_angle {0.0};

public:
    ShooterBoss(int hp = BOSS_HP, int dx = 0, int dy = 1,
                int shoot_freq = DEFAULT_SHOOT_FREQ, bool shoot = true,
                int size_x = BOSS_SIZE_X, int size_y = BOSS_SIZE_Y,
                int move_freq = DEFAULT_FREQ);
    ~ShooterBoss() override;
    static void set_player(ShooterPlayer* shooter);
    virtual void pause() override;
    virtual void unpause() override;
    void show_health();
    void start_bossfight();
    virtual bool collision() override;

signals:
    void start_phase3();
    void boss_dead();

public slots:
    virtual void move() override;
    virtual void shoot() override;
    void enable_flag();
    void show_dialogue();
};

#endif // SHOOTERBOSS_H
