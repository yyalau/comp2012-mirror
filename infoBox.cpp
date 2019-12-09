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
    shooter->get_health_var()->setPos(GAMEAREA_LENGTH, 10);
    scene()->addItem(shooter->get_health_var());
    shooter->get_health_var()->setDefaultTextColor(Qt::yellow);

    //instructions
    QGraphicsTextItem* general_text= new QGraphicsTextItem;
    general_text->setPlainText("Press P to pause. \nPress R to restart.");
    general_text->setFont(font);
    general_text->setDefaultTextColor(Qt::black);
    general_text->setPos(GAMEAREA_LENGTH,500);
    scene()->addItem(general_text);
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

    powerup_text->setFont(font);
    powerup_text->setDefaultTextColor(Qt:: cyan);
    powerup_text->setPos(GAMEAREA_LENGTH,100);
    scene()->addItem(powerup_text);

    QTimer::singleShot(3000, this, SLOT(clear_powerup_info()));
}
