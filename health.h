#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>

#include "define.h"

/**
 * @brief The Health class
 * Class for players/enemies health
 * @include health: entity's remaining health
 * @include name: entity's name (ShooterEnemy/ShooterPlayer)
 * @include get_health(): return current health
 * @include increase_health(): +1 hp //TODO: just do set_health()? maybe boss do more damage
 * @include decrease_health(): -1 hp
 * @include is_dead(): check if hp is 0
 */

class Health: public QGraphicsTextItem{

private:
    int health;
    QString name;

public:
    Health(const QString& name, int max_health, QGraphicsItem* parent=nullptr);
    int get_health();
    void increase_health();
    void decrease_health();
    bool is_dead();
};

#endif // HEALTH_H
