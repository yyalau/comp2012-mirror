#ifndef DEFINE_H
#define DEFINE_H

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <random>

/**
  * Some "defines" and templates to make the code easier to read
  */

constexpr static const int INFOBOX_LENGTH     {300};
constexpr static const int GAMEAREA_LENGTH    {800};
constexpr static const int SCREEN_HEIGHT      {600};
constexpr static const int SCREEN_LENGTH      {GAMEAREA_LENGTH+INFOBOX_LENGTH};

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
constexpr static const int START_POS_X    {400};
constexpr static const int START_POS_Y    {500};

//timer update duration (= 1000/frame per sec)
//MIN_FREQ: ensures the slots are triggered in sync
constexpr static const int MIN_FREQ            {20};
constexpr static const int DEFAULT_FREQ        {MIN_FREQ};
constexpr static const int DEFAULT_SHOOT_FREQ  {5*MIN_FREQ};
constexpr static const int FREQ_PER_SEC        {1000/MIN_FREQ}; //a MIN_FREQ slot updates this much tme per second

//for removing a bullet/enemy out of the screen
template <typename T>
void REMOVE_ENTITY(QGraphicsScene* scene, T* X)
{
    scene->removeItem(X);
    delete (X);
    X=nullptr;
}

//random number generator
inline int RANDOM(int min, int max)
{
    static std::random_device rd;
    return min + rd()%(max-min+1);
}

#endif // DEFINE_H
