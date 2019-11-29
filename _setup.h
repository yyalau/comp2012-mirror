#ifndef _SETUP_H
#define _SETUP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

#include "shooterPlayer.h"
#include "shooterEnemy.h"


class _SetUp: public QGraphicsView
{

public:
    _SetUp();

    QGraphicsScene* scene;
    ShooterPlayer* player;

public slots:

    void start();


};


#endif // _SETUP_H
