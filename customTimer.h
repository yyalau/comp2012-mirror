#ifndef CUSTOMTIMER_H
#define CUSTOMTIMER_H

#include <QObject>
#include <QTimer>

/**
 * @brief The CustomTimer class
 * QTimer with the ability to pause and keep the remaining time
 * (Can't seem to inherit QTimer, runs into trouble with custom slots. Creates a QTimer inside instead)
 * NOTE: Must delete in destructor, even singleShot will only delete the QTimer
 *       Constant timers can use the second constructor, while singleShot should use the default one and call start_timer()
 *
 * PRIVATE DATA MEMBERS
 * @include initial_interval: interval set at the beginning
 * @include time_left: keep track of the remaining time when paused
 * @include restart: for resetting the timer after unpause
 * @include singleShot: customTimer can have its own singleShot that supports pause()
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include start_timer(): Begins the timer, mainly used for singleShot for the purpose of reusing the customTimer
 * @include pause(): Stops the timer, keep the remaining time
 * @include unpause(): Resets the timer with the remaining time, then switch to initial timer after 1 timeout()
 * (pause() and unpause() handle the case where timer is deleted already, just sont delete the customTimer too soon)
 * @include set_interval(): Resets the timer with new interval
 * @include stop(): Stops the timer, similar to QTimer
 *
 * PUBLIC SLOTS
 * @include restart_timer(): See unpause(). Delete this timer if custom_singleshot is true
 */

class CustomTimer: public QObject
{
    Q_OBJECT

private:
    QTimer* timer {nullptr};
    int initial_interval;
    int time_left;
    bool restart {false};
    bool singleShot {false};

public:
    CustomTimer() = default;
    CustomTimer(int interval, const bool& singleShot,
                const QObject* receiver = nullptr, const char* member = nullptr);
    void start_timer(int interval, const bool& singleShot,
                const QObject* receiver = nullptr, const char* member = nullptr);
    virtual ~CustomTimer();
    void pause();
    void unpause();
    void set_interval(int interval);
    void stop();

public slots:
    void restart_timer();

};

#endif // CUSTOMTIMER_H
