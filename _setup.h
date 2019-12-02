#ifndef _SETUP_H
#define _SETUP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QWidget>

#include "define.h"
#include "shooterPlayer.h"
#include "shooterEnemy.h"
#include "infoBox.h"
#include "gameEvent.h"


/**
 * @brief The _SetUp class
 * Call this once to initialize the screen, player, game event handler, etc.
 * @include GameScene: //TODO
 * @include GameView: //TODO
 * @include shooter: The player's shooter
 * @include infoBox: The info screen on the right
 * @include gameEvent: No pointer needed (for now?), this just counts the time and trigger events
 */

class _SetUp{
public:
    _SetUp();
    QGraphicsScene* GameScene;
    QGraphicsView* GameView;
    ShooterPlayer* shooter;
    InfoBox* infoBox;
};


#endif // _SETUP_H
