#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H
#include <QGraphicsRectItem>
#include <QObject>
#include "bulletBase.h"

class BulletPlayer:public BulletBase{
private:
    int dx;
    int dy;

public:
    BulletPlayer(int dx=0, int dy=0);
    virtual ~BulletPlayer()=default;

public slots:
    virtual void move();

};

#endif // BULLETSHOOTER_H

