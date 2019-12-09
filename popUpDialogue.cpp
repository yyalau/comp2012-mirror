#include "popUpDialogue.h"

PopUpDialogue::PopUpDialogue(QGraphicsScene* parent_scene, QString message, QColor color, double opacity,
                             int x, int y, int width, int height):
    parent_scene(parent_scene)
{
    create_dialogue(message, color, opacity, x, y, width, height);
}

PopUpDialogue::PopUpDialogue(QGraphicsScene* parent_scene, QString message, PopUpType popup_type):
    parent_scene(parent_scene), popup_type(popup_type)
{
    switch (popup_type)
    {
        case GameArea:
            create_dialogue(message, Qt::gray, 0.5, 0, 0, GAMEAREA_LENGTH, SCREEN_HEIGHT);
            break;
        case FullScreen:
            create_dialogue(message, Qt::gray, 0.5, 0, 0, SCREEN_LENGTH, SCREEN_HEIGHT);
            popup_text->setPos(100,100);
            break;
        case Dialogue:
            create_dialogue(message, Qt::gray, 0.5, 0, SCREEN_HEIGHT/3, GAMEAREA_LENGTH, SCREEN_HEIGHT/3);
            break;
        case BossHealth:
            create_dialogue(message, Qt::red, 1, 0, SCREEN_HEIGHT-10, GAMEAREA_LENGTH, 10); //TODO: 10?
            break;
    }
}

void PopUpDialogue::create_dialogue(QString message, QColor color, double opacity, int x, int y, int width, int height)
{
    //similar part of constructors
    this->message = message;
    this->color = color;
    this->opacity = opacity;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    //popup a new scene
    popup_scene = new QGraphicsRectItem(x,y,width,height);
    popup_scene->setBrush(color);
    popup_scene->setOpacity(opacity);
    parent_scene->addItem(popup_scene);

    //show the message
    popup_text = new QGraphicsTextItem(message);
    QFont Font("Times", 16);
    popup_text->setFont(Font);

    popup_text->setPos(0, SCREEN_HEIGHT/2);
    parent_scene->addItem(popup_text);
}

PopUpDialogue::~PopUpDialogue()
{
    parent_scene->removeItem(popup_scene);
    delete popup_scene;
    parent_scene->removeItem(popup_text);
    delete popup_text;
}

void PopUpDialogue::set_message(QString message)
{
    this->message = message;
}

void PopUpDialogue::set_width(int width)
{
    this->width = width;
    popup_scene->setRect(x,y,width,height);
}
