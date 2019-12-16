#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsTextItem>
#include <QFont>

#include "define.h"

/**
 * @brief The Health class
 * Class for players/enemies health
 *
 * PRIVATE DATA MEMBERS
 * @include health: Entity's remaining health
 * @include max_health: Entity's max_health, initialized with constructor
 * @include name: Entity's name (ShooterEnemy/ShooterPlayer)
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_text(): Displays the correct health value on screen
 * @include get_health(): Return current health
 * @include set_health(): Change health (normally use 1 or -1)
 * @include is_dead(): Check if hp is 0
 * @include reset_health(): Reset the health of the entity (use on player when pressing restart)
 */

class Health: public QGraphicsTextItem{

private:
    int health;
    const int max_health;
    const QString name;

public:
    Health(const QString& name, const int& max_health);
    void set_text();
    int get_health();
    void set_health(const int& increment);
    bool is_dead();
    void reset_health();
};

#endif // HEALTH_H
