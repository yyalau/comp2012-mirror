#ifndef SHOOTERENEMY_H
#define SHOOTERENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include "bulletPlayer.h"
#include "shooterBase.h"

class ShooterEnemy:public ShooterBase{
    Q_OBJECT //implies an object can handle signals

public:
    ShooterEnemy();
    void create_health();

public slots:
    void move();
    void shoot_bullets();
};


#endif // SHOOTERENEMY_H
