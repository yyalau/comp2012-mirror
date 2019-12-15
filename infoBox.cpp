#include "infoBox.h"
#include "bulletPowerUp.h"

InfoBox::InfoBox(ShooterPlayer* shooter) :
    shooter(shooter)
{
    setBrush(Qt::gray);
    setRect(0, 0, INFOBOX_LENGTH, SCREEN_HEIGHT);

    connect(shooter, SIGNAL(powerup_text(int)), this, SLOT(show_powerup_info(int)));
    connect(shooter, SIGNAL(shooter_text(int)), this, SLOT(show_shooter_info(int)));

}

InfoBox::~InfoBox()
{
    if (powerup_text != nullptr) delete powerup_text;
    if (shooter_text != nullptr) delete shooter_text;
}

void InfoBox::show_general_info()
{
    //add health
    QGraphicsTextItem* health = new QGraphicsTextItem("Player Health:");
    health->setFont(font);
    health->setPos(GAMEAREA_LENGTH, 10);
    health->setDefaultTextColor(Qt::red);
    scene()->addItem(health);

    shooter->health->setPos(GAMEAREA_LENGTH+100, 50);
    scene()->addItem(shooter->health);
    shooter->health->setDefaultTextColor(Qt::red);

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

void InfoBox::show_shooter_info(const int& powerup_shooter)
{
    QString message = QString::number(powerup_shooter)+ QString(" seconds left");
    shooter_text = new PopUpDialogue(scene(), message, 1000,
                                    PopUpDialogue::InfoBox, GAMEAREA_LENGTH, 350);
    shooter_text->set_font(QFont("Joystix Monospace",8), Qt::blue);
}

void InfoBox::show_powerup_info(const int& event)
{
    QString text;
    QFont font("Joystix Monospace",8);
    switch(event){
        case BulletPowerUp::Breakpoint:
            text = QString {
                "Breakpoint added!\n"
                "Your debugger gained 1 Health!"
            };
            break;
        case BulletPowerUp::StackOverflow:
            text = QString {
                "Your question on StackOverflow was answered!\n\n"
                "This code section is bug-free!"
            };
                        font.setPointSize(7);
            break;
        case BulletPowerUp::CoutTestEndl:
            text = QString {
                "cout<< \"test\" <<endl;\n"
                "Your debugger is \n"
                "temporarily stronger!"
            };
            break;
        default:
            return;
    }


    powerup_text = new PopUpDialogue(scene(), text, 4000, PopUpDialogue::InfoBox, GAMEAREA_LENGTH, (event+1)*100);

    powerup_text->set_font(font, Qt::yellow);
}
