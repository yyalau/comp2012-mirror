#ifndef SHOOTERBASE_H
#define SHOOTERBASE_H

#include "health.h"
#include "bulletPlayer.h"
#include "bulletEnemy.h"
#include <QObject>
#include <QGraphicsRectItem>


class ShooterBase: public QObject, public QGraphicsRectItem{
    Q_OBJECT

protected:
    Health* health;
public:
    ShooterBase(QString);
    void create_health(int posx, int posy);

};


#endif // SHOOTERBASE_H
