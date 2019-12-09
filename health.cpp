#include "health.h"

Health::Health(const QString& name, int max_health, bool show_name, QGraphicsItem *parent):
    name(name), max_health(max_health), show_name(show_name)
{
    health = max_health;

    set_text();
    setDefaultTextColor(Qt::red);
    setFont(QFont("Times, 12"));
}

void Health::set_text()
{
    if (show_name)
        setPlainText(QString(name)+QString(" Health: ")+ QString::number(health));
    else
        setPlainText(QString::number(health));
}

int Health::get_health()
{
    return health;
}

void Health::increase_health()
{
    ++health;
    set_text();
}

void Health::decrease_health()
{
    if(health > 0) --health;
    set_text();
}

bool Health::is_dead()
{
    return (health == 0);
}

void Health::reset_health()
{
    health=max_health;
    set_text();
}

