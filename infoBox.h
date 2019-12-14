#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QGraphicsTextItem>
#include <popUpDialogue.h>

#include "shooterPlayer.h"

/**
 * @brief The InfoBox class
 * Put a rectangle on the side with information such as player's health
 *
 * PRIVATE DATA MEMBERS
 * @include shooter: Pointer to player (to get health)
 * @include powerup_text: Displays the corresponding power up message
 * @include shooter_text: Displays the remaining time of CoutTestEndl powerup
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include show_general_info(): Call this upon initialization to show general info (eg. players health)
 *
 * PUBLIC SLOTS
 * @include show_powerup_info(), show_shooter_info(): Sets and displays the powerup_text, shooter_text to scene
 */

class InfoBox : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

private:
    ShooterPlayer* shooter;
    PopUpDialogue* powerup_text {nullptr};
    PopUpDialogue* shooter_text {nullptr};
    QFont font {"Joystix Monospace", 9} ;

public:
    InfoBox(ShooterPlayer*);
    ~InfoBox();
    void show_general_info();

public slots:
    void show_powerup_info(const int& event);
    void show_shooter_info(const int& powerup_shooter);

};

#endif // INFOBOX_H
