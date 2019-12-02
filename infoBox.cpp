#include "infoBox.h"

InfoBox::InfoBox(Health* player_health) :
    player_health(player_health)
{
    setBrush(Qt::black);
    setRect(0, 0, INFOBOX_LENGTH, SCREEN_HEIGHT);
}

void InfoBox::show_info()
{
    player_health->setPos(SCREEN_LENGTH, 10);
    scene()->addItem(player_health);
    player_health->setDefaultTextColor(Qt::yellow);
}
