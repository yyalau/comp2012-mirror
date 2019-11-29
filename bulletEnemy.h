#ifndef BULLETENEMY_H
#define BULLETENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include "bulletBase.h"

class BulletEnemy:public BulletBase{
private:
    int dx;
    int dy;

public:
    BulletEnemy(int dx=0, int dy=0);
    virtual ~BulletEnemy()=default;

public slots:
    virtual void move();

};

#endif // BULLETENEMY_H

