#ifndef HEALTH_H
#define HEALTH_H
#include <QGraphicsTextItem>

class Health: public QGraphicsTextItem{

private:
    const int max_health=5;
    const int min_health=0;

    int health;
    QString name;

public:
    Health(const QString& name, QGraphicsItem* parent=nullptr);
    int get_health();
    void increase_health();
    void decrease_health();
};

#endif // HEALTH_H
