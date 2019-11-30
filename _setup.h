#ifndef _SETUP_H
#define _SETUP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>

#include "shooterPlayer.h"
#include "shooterEnemy.h"

/**
 * @brief The _SetUp class
 * Call this once to initialize the screen, player, game event handler, etc.
 * @include GameScene: //TODO
 * @include GameView: //TODO
 * @include shooter: The player's shooter
 * @include health: //remove this later? check the .cpp file
 */

class _SetUp
{

public:
    _SetUp();
    QGraphicsScene* GameScene;
    QGraphicsView* GameView;
    //QGraphicsScene* MenuScene;
    //QGraphicsView* MenuView;
    ShooterPlayer* shooter;
    Health* health;
};


#endif // _SETUP_H
