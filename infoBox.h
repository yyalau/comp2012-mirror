#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <popUpDialogue.h>

#include "shooterPlayer.h"
#include "customTimer.h"

/**
 * @brief The InfoBox class
 * Put a rectangle on the side with the player's health
 *
 * PRIVATE DATA MEMBERS
 * @include shooter: Pointer to player (to get health)
 * @include powerup_text: stores the corresponding power up message
 * @include powerup_timer: Keep track of time the powerup text is shown
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_general_info(): Call this upon initialization to show general info (eg. players health)
 * @include pause(), unpause(): Pause/Unpause the powerup_timer
 *
 * PUBLIC SLOTS
 * @include show_powerup_info(int event): sets and displays the powerup_text to scene
 */

class InfoBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    ShooterPlayer* shooter;
    PopUpDialogue* powerup_text {nullptr};
    PopUpDialogue* shooter_text {nullptr};
    QFont font {"Joystix Monospace", 9} ;
    CustomTimer* powerup_timer {nullptr};

public:
    InfoBox(ShooterPlayer*);
    ~InfoBox();
    void show_general_info();
    void pause();
    void unpause();

public slots:
    void show_powerup_info(int event);
    void show_shooter_info(int powerup_shooter);

};

#endif // INFOBOX_H
