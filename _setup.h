#ifndef _SETUP_H
#define _SETUP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>

#include "shooterPlayer.h"
#include "shooterEnemy.h"


class _SetUp
{

public:
    _SetUp();
    QGraphicsScene* GameScene;
    QGraphicsView* GameView;
    QGraphicsScene* MenuScene;
    QGraphicsView* MenuView;
    ShooterPlayer* shooter;
    Health* health;
};


#endif // _SETUP_H
