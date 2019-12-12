#include "infoBox.h"
#include "bulletPowerUp.h"

InfoBox::InfoBox(ShooterPlayer* shooter) :
    shooter(shooter)
{
    setBrush(Qt::gray);
    setRect(0, 0, INFOBOX_LENGTH, SCREEN_HEIGHT);

    powerup_timer = new CustomTimer();

    connect(shooter, SIGNAL(powerup_text(int)), this, SLOT(show_powerup_info(int)));
    connect(shooter, SIGNAL(shooter_text(int)), this, SLOT(show_shooter_info(int)));

}

InfoBox::~InfoBox()
{
    if (powerup_timer!= nullptr) delete powerup_timer;
    if (powerup_text!=nullptr) delete powerup_text;
}

void InfoBox::show_general_info()
{
    //add health
    QGraphicsTextItem* health = new QGraphicsTextItem("Player Health:");
    health->setFont(font);
    health->setPos(GAMEAREA_LENGTH, 10);
    health->setDefaultTextColor(Qt::red);
    scene()->addItem(health);

    shooter->get_health_var()->setPos(GAMEAREA_LENGTH+100, 50);
    scene()->addItem(shooter->get_health_var());
    shooter->get_health_var()->setDefaultTextColor(Qt::red);

    QPixmap Heart(":/image/images/heart.png");
    QGraphicsPixmapItem* heart;
    heart = new QGraphicsPixmapItem(Heart.scaled(30,30));
    heart->setShapeMode(QGraphicsPixmapItem::MaskShape);
    heart->setPos(GAMEAREA_LENGTH+60,50);
    scene()->addItem(heart);

    //instructions
    QGraphicsTextItem* general_text= new QGraphicsTextItem("Press P to pause.");
    general_text->setFont(font);
    general_text->setDefaultTextColor(Qt::black);
    general_text->setPos(GAMEAREA_LENGTH,550);
    scene()->addItem(general_text);
}

void InfoBox::pause()
{
    powerup_timer->pause();
}

void InfoBox::unpause()
{
    powerup_timer->unpause();
}

void InfoBox::show_shooter_info(int powerup_shooter)
{
    qDebug()<<"powerup_shooter: "<<powerup_shooter;
    QString message=QString("Power-Up Shooter: ")+ QString::number(powerup_shooter)+ QString(" s");
    shooter_text= new PopUpDialogue(scene(),message,1000,
                                    PopUpDialogue::InfoBox,GAMEAREA_LENGTH,200);
    shooter_text->set_font(QFont("Joystix Monospace",8), Qt::blue);
}

void InfoBox::show_powerup_info(int event)
{
    switch(event){
        case BulletPowerUp::Breakpoint:
            powerup_text= new PopUpDialogue(scene(),"Breakpoint: \n\n  Added Health!",4000,
                                    PopUpDialogue::InfoBox,GAMEAREA_LENGTH,100);
            break;
        case BulletPowerUp::StackOverflow:
            powerup_text= new PopUpDialogue(scene(),"StackOverflow: \n\n  Cleared field!",4000,
                                        PopUpDialogue::InfoBox,GAMEAREA_LENGTH,100);
            break;
        case BulletPowerUp::CoutTestEndl:
            powerup_text= new PopUpDialogue(scene(),"CoutTestEndl:\n\n"
                                                    "    Powered up \n"
                                                    "   your shooter!",4000,
                                            PopUpDialogue::InfoBox,GAMEAREA_LENGTH,100);
            break;
        default:
            return;
    }
    powerup_text->set_font(font,Qt::cyan);


}
