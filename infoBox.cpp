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
    shooter->get_health_var()->setPos(GAMEAREA_LENGTH, 10);
    scene()->addItem(shooter->get_health_var());
    shooter->get_health_var()->setDefaultTextColor(Qt::yellow);

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
    //TODO
    qDebug()<<"powerup_shooter: "<<powerup_shooter;
    QString message = QString::number(powerup_shooter)+ QString(" seconds left");
    shooter_text= new PopUpDialogue(scene(),message,1000,
                                    PopUpDialogue::InfoBox,GAMEAREA_LENGTH,200);
    shooter_text->set_font(font, Qt::blue);
}

void InfoBox::show_powerup_info(int event)
{
    QString text;

    switch(event){
        case BulletPowerUp::Breakpoint:
            text = QString {
                "Breakpoint added!\n"
                "Your debugger gained 1 Health!"
            };
            break;
        case BulletPowerUp::StackOverflow:
            text = QString {
                "Your question on StackOverflow\n"
                "was answered!\n"
                "This code section is bug-free!"
            };
            break;
        case BulletPowerUp::CoutTestEndl:
            text = QString {
                "cout << \"test\" << endl;\n"
                "Your debugger is temporarily stronger!"
            };
            break;
        default:
            return;
    }

    powerup_text= new PopUpDialogue(scene(), text, 4000, PopUpDialogue::InfoBox, GAMEAREA_LENGTH, 100);

    powerup_text->set_font(font, Qt::cyan);
}
