#ifndef DEFINE_H
#define DEFINE_H

/**
  * Some defines to make the code easier to read
  * TODO: change to const int and templates?
  */

#define INFOBOX_LENGTH      300
#define GAMEAREA_LENGTH     800
#define SCREEN_HEIGHT       600
#define SCREEN_LENGTH       GAMEAREA_LENGTH+INFOBOX_LENGTH

//for out of bound checking
#define INSCREEN_LEFT(X)        (X) >= 0
#define INSCREEN_RIGHT(X)       (X)+boundingRect().width() <= scene()->width()-INFOBOX_LENGTH
#define INSCREEN_UP(Y)          (Y) >= 0
#define INSCREEN_DOWN(Y)        (Y)+boundingRect().height() <= scene()->height()

//player's starting position
#define START_POS_X         400
#define START_POS_Y         500

//timer update duration (= 1000/frame per sec)
//MIN_FREQ: ensures the slots are triggered in sync
#define MIN_FREQ            20
#define DEFAULT_FREQ        MIN_FREQ
#define DEFAULT_SHOOT_FREQ  5*MIN_FREQ

//hitbox sizes
#define BULLET_SIZE 30
#define ENTITY_SIZE 40
#define ENEMY_SIZE 50
#define PLAYER_SIZE 70

//player and enemy's health
#define DEFAULT_PLAYER_HP   50
#define DEFAULT_ENEMY_HP    3

//boss
#define BOSS_HP             1000
#define BOSS_SIZE_X         300
#define BOSS_SIZE_Y         200
#define BOSS_POS_X          (GAMEAREA_LENGTH-BOSS_SIZE_X)/2      //250
#define BOSS_POS_Y          10

//for removing a bullet/enemy out of the screen (lmao can we do this?)
#define REMOVE_ENTITY(X) { scene()->removeItem(X); delete (X); }

#endif // DEFINE_H
