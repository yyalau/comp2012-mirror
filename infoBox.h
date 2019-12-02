#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

#include "shooterPlayer.h"
#include "pauseButton.h"

/**
 * @brief The InfoBox class
 * Put a rectangle on the side with the player's health
 *
 * PRIVATE DATA MEMBERS
 * @include player_health: Pointer to player's health
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_info(): Call this upon initialization to show info
 */

class InfoBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    Health* player_health;

public:
    InfoBox(Health*);
    void show_info();

};

#endif // INFOBOX_H
