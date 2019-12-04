#ifndef BULLETPOWERUP_H
#define BULLETPOWERUP_H
#include <QtDebug>

#include "bulletBase.h"
#include "bulletPlayer.h"

class BulletPowerUp: public BulletBase{
private:
    QTimer* coll_timer;

public:
    BulletPowerUp(int dx = 0, int dy = 0, int size_x = BULLET_SIZE, int size_y = BULLET_SIZE,
               int move_freq = DEFAULT_FREQ/*, int coll_freq = DEFAULT_FREQ*/);
public slots:
};

#endif // BULLETPOWERUP_H
