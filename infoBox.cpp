#include "infoBox.h"

InfoBox::InfoBox(ShooterPlayer* shooter) :
    shooter(shooter)
{
    setBrush(Qt::gray);
    setRect(0, 0, INFOBOX_LENGTH, SCREEN_HEIGHT);

    connect(shooter, SIGNAL(powerup_text(int)), this, SLOT(show_powerup_info(int)));
}

void InfoBox::show_general_info()
{
    //add health
    shooter->get_health_var()->setPos(SCREEN_LENGTH, 10);
    scene()->addItem(shooter->get_health_var());
    shooter->get_health_var()->setDefaultTextColor(Qt::yellow);
}

void InfoBox::clear_powerup_info()
{
    scene()->removeItem(powerup_text);
    delete  powerup_text;
}

void InfoBox::show_powerup_info(int event)
{
    qDebug()<<"event: "<< event;

    switch(event){
    case 0:
        powerup_text=new QGraphicsTextItem("Breakpoint: Added Health!");
        break;
    case 1:
        powerup_text=new QGraphicsTextItem("StackOverflow: Cleared field!");
        break;
    case 2:
        powerup_text=new QGraphicsTextItem("CoutTestEndl: \nPowered up your shooter!");
        break;
    default:
        return;
    }

    static QFont font {"Times", 11};
    powerup_text->setFont(font);
    powerup_text->setDefaultTextColor(Qt:: cyan);
    powerup_text->setPos(SCREEN_LENGTH,100);
    scene()->addItem(powerup_text);

    QTimer::singleShot(3000, this, SLOT(clear_powerup_info()));
}
