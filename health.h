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
 * @include health: entity's remaining health
 * @include name: entity's name (ShooterEnemy/ShooterPlayer)
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include set_text(): displays the correct health value on screen
 * @include get_health(): return current health
 * @include set_health(): change health
 * @include is_dead(): check if hp is 0
 * @include reset_health(): whenever the programme restarts, this function will be called to reset the health of the player
 */

class Health: public QGraphicsTextItem{

private:
    int health;
    int max_health;
    QString name;
    bool show_name;

public:
    Health(const QString& name, int max_health, bool show_name=true, QGraphicsItem* parent=nullptr);
    void set_text();
    int get_health();
    void set_health(int increment);
    bool is_dead();
    void reset_health();
};

#endif // HEALTH_H
