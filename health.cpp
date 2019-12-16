#include "health.h"

Health::Health(const QString& name, const int& max_health):
    name(name), max_health(max_health)
{
    health = max_health;

    setDefaultTextColor(Qt::red);
    set_text();
    setFont(QFont("Joystix Monospace", 9));
}

void Health::set_text()
{
    if(name=="Player")
        setPlainText(QString("X")+QString::number(health));
    else
        setPlainText(QString::number(health));
}

int Health::get_health()
{
    return health;
}

void Health::set_health(const int& increment)
{
    health += increment;
    set_text();
}

bool Health::is_dead()
{
    return (health == 0);
}

void Health::reset_health()
{
    health = max_health;
    set_text();
}

