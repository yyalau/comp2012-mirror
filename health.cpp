#include "health.h"

#include <QFont>

#include "_setup.h"

Health::Health(const QString& name, int max_health, QGraphicsItem *parent): name(name)
{
    health = max_health;

    setPlainText(QString(this->name)+QString(" Health: ")+ QString::number(health));
    setDefaultTextColor(Qt::yellow);
    setFont(QFont("Times, 16"));

}
int Health::get_health()
{
    return health;
}

void Health::increase_health()
{
    ++health;
    setPlainText(QString(name)+QString(" Health: ")+ QString::number(health));
}

void Health::decrease_health()
{
    if(health > 0) --health;
    setPlainText(QString(name)+QString(" Health: ")+ QString::number(health));
}

bool Health::is_dead()
{
    return (health == 0);
}

