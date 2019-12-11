#ifndef DEFINE_H
#define DEFINE_H

#include <QGraphicsScene>
#include <stdlib.h> //rand()
#include <time.h>

/**
  * Some defines to make the code easier to read
  * TODO: change to const int and templates?
  */

#define INFOBOX_LENGTH      300
#define GAMEAREA_LENGTH     800
#define SCREEN_HEIGHT       600
#define SCREEN_LENGTH       GAMEAREA_LENGTH+INFOBOX_LENGTH

//for out of bound checking
#define INSCREEN_LEFT(X)        (X) >= -50
#define INSCREEN_RIGHT(X)       (X)+boundingRect().width() <= scene()->width()-INFOBOX_LENGTH+15
#define INSCREEN_UP(Y)          (Y) >= -50
#define INSCREEN_DOWN(Y)        (Y)+boundingRect().height() <= scene()->height()+50

#define INSCREEN_LEFT_RIGID(X)        (X) >= 0
#define INSCREEN_RIGHT_RIGID(X)       (X)+boundingRect().width() <= scene()->width()-INFOBOX_LENGTH
#define INSCREEN_UP_RIGID(Y)          (Y) >= 0
#define INSCREEN_DOWN_RIGID(Y)        (Y)+boundingRect().height() <= scene()->height()


//player's starting position
#define START_POS_X         400
#define START_POS_Y         500

//timer update duration (= 1000/frame per sec)
//MIN_FREQ: ensures the slots are triggered in sync
#define MIN_FREQ            20
#define DEFAULT_FREQ        MIN_FREQ
#define DEFAULT_SHOOT_FREQ  5*MIN_FREQ

//player and enemy's health
#define DEFAULT_PLAYER_HP   25
#define DEFAULT_ENEMY_HP    3

//for removing a bullet/enemy out of the screen

template <typename T>
void REMOVE_ENTITY(QGraphicsScene* scene, T* X)
{
    scene->removeItem(X);
    delete (X);
}

#endif // DEFINE_H
