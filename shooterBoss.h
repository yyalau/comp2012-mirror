#ifndef SHOOTERBOSS_H
#define SHOOTERBOSS_H

#include <cmath>

#include "shooterBase.h"
#include "shooterPlayer.h"
#include "popUpDialogue.h"
#include "shooterExplosion.h"

/**
 * @brief The ShooterBoss class
 * Class for the final boss
 *
 * ENUMS
 * @enum BossPhase: Name of the phase the boss is in
 * @enum SoundType: Different sounds for different actions
 *
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include PHASE_HEALTH: Health when the boss switches to next state. PHASE_HEALTH[X] -> go to state X
 * @include phase: See enum above
 * @include boss_to_next_phase: Flag for allowing boss to switch from Dialogue to other phases
 * @include health_bar: PopUpDialogue for displaying the health bar
 * @include dialogue_counter: Counter to keep track of dialogues shown
 * @include dialogue_timer: CustomTimer for displaying pre-battle dialogue
 * @include flag_timer: CustomTimer for setting flag to true after some time
 * @include player: Pointer to the player. Use set_player() when initializing the player in SetUp
 * @include set_shoot_freq(): Change the shooting frequency (for each pattern)
 * @include set_phase(): Change to a certain phase. handles specific configuration when entering phase
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_player(): Set the shooter to point to the player
 * @include pause(), unpause(): Overrides ShooterBase's functions
 * @include show_health(): Show the boss's remaining health. ONLY CALL AFTER parent_scene->addItem()
 * @include collision(): Overrides shooterBase's function
 *
 * SIGNALS
 * @include start_phase3(): Sent to the shooterPlayer
 * @include boss_dead(): Sent when boss is defeated -> win!
 *
 * PUBLIC SLOTS
 * @include move(): Overrides shooterBase's function, handles going out of bound
 * @include shoot(): Overrides shooterBase's function
 * @include enable_flag(): Set flag to true after the pattern name finishes showing
 * @include show_dialogue(): Display the dialogue before the battle
 */

class ShooterBoss : public ShooterBase
{
    Q_OBJECT

public:
    constexpr static const int BOSS_HP {1000};
    constexpr static const int BOSS_SIZE_X {300};
    constexpr static const int BOSS_SIZE_Y {200};
    constexpr static const int BOSS_POS_X {(GAMEAREA_LENGTH-BOSS_SIZE_X)/2};
    constexpr static const int BOSS_POS_Y {10};
    constexpr static const int DIALOGUE_FREQ {5000};       //each dialogue line lasts for 5 seconds

public:
    enum BossPhase
    {
        Entrance = -2,  //for entering the screen only
        Dialogue,       //do nothing, does not take damage either
        PhasePre1,      //spam Random bullets
        Phase1,         //IndexOutOfBoundException, shoot 2 rays of OutOfBound bullets (bulletEnemy handles the pattern)
        PhasePre2,      //2 rays of "spaghetti code"
        Phase2,         //LEAK X DIRECT BYTES, Explode bullets fall from the top
        Phase3,         //NullPointerException, disable moving
        //Dead
    };
    enum SoundType
    {
        Hurt,
        PhaseComplete,
        NUM_SOUND_TYPES
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
    void set_phase(const BossPhase& phase);

    //phase-specific variables
    int phase_dir {1};
    double phase_angle {0.0};

public:
    ShooterBoss(const int hp = BOSS_HP, const int& dx = 0, const int& dy = 1,
                const int& shoot_freq = DEFAULT_SHOOT_FREQ, const bool& shoot = true,
                const int size_x = BOSS_SIZE_X, const int size_y = BOSS_SIZE_Y,
                const int& move_freq = DEFAULT_FREQ);
    ~ShooterBoss() override;
    static void set_player(ShooterPlayer* shooter);
    virtual void pause() override;
    virtual void unpause() override;
    void show_health();
    virtual bool collision() override;

signals:
    void start_phase3();
    void boss_dead(bool win);

public slots:
    virtual void move() override;
    virtual void shoot() override;
    void enable_flag();
    void show_dialogue();
};

#endif // SHOOTERBOSS_H
