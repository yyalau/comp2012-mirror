#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <QTimer>

#include "shooterPlayer.h"

/**
 * @brief The InfoBox class
 * Put a rectangle on the side with the player's health
 *
 * PRIVATE DATA MEMBERS
 * @include shooter: Pointer to player (to get health)
 * @include powerup_text: stores the corresponding power up message
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_general_info(): Call this upon initialization to show general info (eg. players health)
 *
 * PUBLIC SLOTS
 * @include show_powerup_info(int event): sets and displays the powerup_text to scene
 * @include clear_powerup_info(): clears the powerup_text
 */

class InfoBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    ShooterPlayer* shooter;
    QGraphicsTextItem* powerup_text;
    QFont font {"Times", 12};

public:
    InfoBox(ShooterPlayer*);
    void show_general_info();

public slots:
    void show_powerup_info(int event);
    void clear_powerup_info();

};

#endif // INFOBOX_H
