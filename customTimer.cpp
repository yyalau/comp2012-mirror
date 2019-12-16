#include "customTimer.h"

CustomTimer::CustomTimer(int interval, const bool& singleShot, const QObject *receiver, const char *member)
{
    start_timer(interval, singleShot, receiver, member);
}

void CustomTimer::start_timer(int interval, const bool& singleShot, const QObject *receiver, const char *member)
{
    time_left = initial_interval = interval;
    this->singleShot = singleShot;

    //start the timer
    timer = new QTimer();
    timer->start(interval);

    //connect the QTimer with the receiving slot
    if (receiver != nullptr && member != nullptr)
        connect(timer, SIGNAL(timeout()), receiver, member);
    //also connect with restart_timer to reset time_left
    connect(timer, SIGNAL(timeout()), this, SLOT(restart_timer()));
}

CustomTimer::~CustomTimer()
{
    if (timer != nullptr) delete timer;
}

void CustomTimer::pause()
{
    if (timer == nullptr) return;
    time_left = timer->remainingTime(); //get the remaining time
    if (time_left < 0) time_left = initial_interval; //just to be safe
    timer->stop();
}

void CustomTimer::unpause()
{
    if (timer == nullptr) return;
    timer->start(time_left); //start QTimer with duration as the remaining time
    if (time_left < initial_interval) restart = true; //in order to reset time_left
}

void CustomTimer::set_interval(int interval)
{
    initial_interval = interval;
    timer->start(interval);
}

void CustomTimer::stop()
{
    if (timer != nullptr) timer->stop();
}


void CustomTimer::restart_timer()
{
    if (singleShot)
    {
        delete timer;
        timer = nullptr; //timer should be set to nullptr if the QTimer is deleted
        return;
    }
    if (!restart) return;
    timer->start(initial_interval);
    restart = false;
    time_left = initial_interval;
}

