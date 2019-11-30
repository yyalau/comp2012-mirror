#ifndef BULLETSHOOTER_H
#define BULLETSHOOTER_H
#include <QGraphicsRectItem>
#include <QObject>
#include "bulletBase.h"

/**
 * @brief The BulletPlayer class
 * Class for bullets shot by player
 * @include collision(): overrides bulletBase's function
 */

class BulletPlayer:public BulletBase{

public:
    BulletPlayer(int dx=0, int dy=0);
    virtual ~BulletPlayer()=default;

public slots:
    virtual void collision() override;

};

#endif // BULLETSHOOTER_H

