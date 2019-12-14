#ifndef DEFINE_H
#define DEFINE_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <stdlib.h> //rand()
#include <time.h>

/**
  * Some "defines" and templates to make the code easier to read
  */

static const int INFOBOX_LENGTH     {300};
static const int GAMEAREA_LENGTH    {800};
static const int SCREEN_HEIGHT      {600};
static const int SCREEN_LENGTH      {GAMEAREA_LENGTH+INFOBOX_LENGTH};

//for out of bound checking with some tolerance
inline bool INSCREEN_LEFT(double x) {
    return x >= -50;
}
inline bool INSCREEN_RIGHT(double x, QGraphicsItem* item) {
    return x + item->boundingRect().width() <= item->scene()->width()-INFOBOX_LENGTH+15;
}
inline bool INSCREEN_UP(double y) {
    return y >= -50;
}
inline bool INSCREEN_DOWN(double y, QGraphicsItem* item) {
    return y + item->boundingRect().height() <= item->scene()->height()+50;
}

//check without the tolerance
inline bool INSCREEN_LEFT_RIGID(double x) {
    return x >= 0;
}
inline bool INSCREEN_RIGHT_RIGID(double x, QGraphicsItem* item) {
    return x + item->boundingRect().width() <= item->scene()->width()-INFOBOX_LENGTH;
}
inline bool INSCREEN_UP_RIGID(double y) {
    return y >= 0;
}
inline bool INSCREEN_DOWN_RIGID(double y, QGraphicsItem* item) {
    return y + item->boundingRect().height() <= item->scene()->height();
}

//player's starting position
static const int START_POS_X    {400};
static const int START_POS_Y    {500};

//timer update duration (= 1000/frame per sec)
//MIN_FREQ: ensures the slots are triggered in sync
static const int MIN_FREQ            {20};
static const int DEFAULT_FREQ        {MIN_FREQ};
static const int DEFAULT_SHOOT_FREQ  {5*MIN_FREQ};

//for removing a bullet/enemy out of the screen
template <typename T>
void REMOVE_ENTITY(QGraphicsScene* scene, T* X)
{
    scene->removeItem(X);
    delete (X);
    X=nullptr;
}

#endif // DEFINE_H
