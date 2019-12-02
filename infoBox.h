#ifndef INFOBOX_H
#define INFOBOX_H

#include <QObject>
#include <QGraphicsRectItem>

#include "shooterPlayer.h"
#include "pauseButton.h"

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
