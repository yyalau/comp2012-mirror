#ifndef DEFINE_H
#define DEFINE_H

/**
  * Some defines to make the code easier to read
  * TODO: change to const int and templates?
  */

#define INFOBOX_LENGTH  300
#define SCREEN_LENGTH   800
#define SCREEN_HEIGHT   600

//for out of bound checking
#define INSCREEN_LEFT(X)        (X) >= 0
#define INSCREEN_RIGHT(X)       (X)+rect().width() <= scene()->width()-INFOBOX_LENGTH
#define INSCREEN_RIGHT_OOB(X)   (X)+rect().width() <= scene()->width()
#define INSCREEN_DOWN(Y)        (Y) >= 0
#define INSCREEN_UP(Y)          (Y)+rect().height() <= scene()->height()

//timer update duration (= 1000/frame per sec)
//MIN_FREQ: ensures the slots are triggered in sync
#define MIN_FREQ            50
#define DEFAULT_FREQ        MIN_FREQ
#define DEFAULT_SHOOT_FREQ  4*MIN_FREQ

//hitbox sizes
#define BULLET_SIZE 20
#define ENTITY_SIZE 40
#define ENEMY_SIZE 40
#define PLAYER_SIZE 40

//player and enemy's health
#define DEFAULT_PLAYER_HP   5
#define DEFAULT_ENEMY_HP    3

//for removing a bullet/enemy out of the screen (lmao can we do this?)
#define REMOVE_ENTITY(X) { scene()->removeItem(X); delete (X); }

#endif // DEFINE_H
