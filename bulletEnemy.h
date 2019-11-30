#ifndef BULLETENEMY_H
#define BULLETENEMY_H
#include <QGraphicsRectItem>
#include <QObject>
#include "bulletBase.h"

/**
 * @brief The BulletEnemy class
 * Class for bullets shot by enemies
 * @include collision(): overrides bulletBase's function (UNUSED)
 */

class BulletEnemy:public BulletBase{

public:
    BulletEnemy(int dx=0, int dy=0);
    virtual ~BulletEnemy()=default;

public slots:
    virtual void collision() override;

};

#endif // BULLETENEMY_H

