#ifndef SHOOTERPLAYER_H
#define SHOOTERPLAYER_H

#include "health.h"
#include "shooterBase.h"
#include "bulletEnemy.h"
#include <QObject>
#include <QGraphicsRectItem>

class ShooterPlayer: public ShooterBase{
    Q_OBJECT
public:
    ShooterPlayer();
    virtual void create_health();
    void keyPressEvent(QKeyEvent* event);

public slots:
    void check_health();

};

#endif // SHOOTERPLAYER_H
