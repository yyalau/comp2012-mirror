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
 * @include GameScene: defines the size of the screen and what items should be included for the output programme
 * @include GameView: divides the scene into 2 parts: GameView and infoBox, then add into GameScene
 * @include shooter: The player's shooter
 * @include infoBox: The info screen on the right
 * @include gameEvent: Counts the time and trigger events. Also handles pause, unpause
 * @include layout: //TODO @scarlett
 * @include window: //TODO @scarlett
 */

class _SetUp{
public:
    _SetUp();

    QGraphicsScene* GameScene;
    QGraphicsView* GameView;
    ShooterPlayer* shooter;
    GameEvent* gameEvent;
    InfoBox* infoBox;
    QHBoxLayout* layout;
    QWidget* window;
};


#endif // _SETUP_H
