#include "customTimer.h"

CustomTimer::CustomTimer(int interval, bool singleShot, const QObject *receiver, const char *member)
{
    start_timer(interval, singleShot, receiver, member);
}

void CustomTimer::start_timer(int interval, bool singleShot, const QObject *receiver, const char *member)
{
    time_left = initial_interval = interval;
    this->singleShot = singleShot;

    timer = new QTimer();
    timer->start(interval);

    if (receiver != nullptr && member != nullptr)
        connect(timer, SIGNAL(timeout()), receiver, member);

    connect(timer, SIGNAL(timeout()), this, SLOT(restart_timer()));
}

CustomTimer::~CustomTimer()
{
    if (timer != nullptr) delete timer;
}

void CustomTimer::pause()
{
    if (timer == nullptr) return;
    time_left = timer->remainingTime();
    if (time_left < 0) time_left = initial_interval; //sometimes the application reports back that "QTimer cannot set negative time"
    timer->stop();
}

void CustomTimer::unpause()
{
    if (timer == nullptr) return;
    timer->start(time_left);
    if (time_left < initial_interval) restart = true;
}

void CustomTimer::set_interval(int interval)
{
    initial_interval = interval;
    timer->start(interval);
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

