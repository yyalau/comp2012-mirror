#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>

/**
 * @brief The Health class
 * Class for players/enemies health
 * @include health: entity's remaining health
 * @include name: entity's name (ShooterEnemy/ShooterPlayer)
 * @include get_health(): return current health
 * @include increase_health(): +1 hp //TODO: just do set_health()? maybe boss do more damage
 * @include decrease_health(): -1 hp
 */

class Health: public QGraphicsTextItem{

private:
    //TODO: ehh just have 0 as min health and initialize max health upon object creation
    const int max_health {5};
    const int min_health {0};

    int health;
    QString name;

public:
    Health(const QString& name, QGraphicsItem* parent=nullptr);
    int get_health();
    void increase_health();
    void decrease_health();
};

#endif // HEALTH_H
