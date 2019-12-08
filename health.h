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
 * @include get_health(): return current health
 * @include increase_health(): +1 hp //TODO: just do set_health()? maybe boss do more damage
 * @include decrease_health(): -1 hp
 * @include is_dead(): check if hp is 0
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
    void increase_health();
    void decrease_health();
    bool is_dead();
    void reset_health();
};

#endif // HEALTH_H
