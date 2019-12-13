#include "popUpDialogue.h"

PopUpDialogue::PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, QColor color, double opacity,
                             int x, int y, int width, int height, int text_x, int text_y):
    parent_scene(parent_scene)
{
    create_dialogue(message, color, opacity, x, y, width, height, text_x, text_y,12);
    set_duration(duration);
}

PopUpDialogue::PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, PopUpType popup_type, int text_x, int text_y):
    parent_scene(parent_scene), popup_type(popup_type)
{
    switch (popup_type)
    {
        case GameArea:
            create_dialogue(message, Qt::gray, 0.5, 0, 0, GAMEAREA_LENGTH, SCREEN_HEIGHT, text_x, text_y,12);
            break;
        case FullScreen:
            create_dialogue(message, Qt::gray, 0.5, 0, 0, SCREEN_LENGTH, SCREEN_HEIGHT, text_x, text_y,10);
            break;
        case Dialogue:
            create_dialogue(message, Qt::gray, 0.5, 0, SCREEN_HEIGHT/3, GAMEAREA_LENGTH, SCREEN_HEIGHT/3, text_x, text_y,9);
            break;
        case BossHealth:
            create_dialogue(message, Qt::red, 1, 0, SCREEN_HEIGHT-10, GAMEAREA_LENGTH, 10, text_x, text_y,12);
            break;
        case InfoBox:
            create_dialogue(message, Qt::red, 0, 0, 0, INFOBOX_LENGTH, SCREEN_HEIGHT, text_x, text_y,12);
            break;
    }
    set_duration(duration);
}

PopUpDialogue::~PopUpDialogue()
{
    parent_scene->removeItem(popup_scene);
    delete popup_scene;
    parent_scene->removeItem(popup_text);
    delete popup_text;
}

void PopUpDialogue::create_dialogue(QString message, QColor color, double opacity, int x, int y, int width, int height, int text_x, int text_y,int fontsize)
{
    //similar part of constructors
    this->message = message;
    this->color = color;
    this->opacity = opacity;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->text_x=text_x;
    this->text_y= text_y;

    //popup a new scene
    popup_scene = new QGraphicsRectItem(x,y,width,height);
    popup_scene->setBrush(color);
    popup_scene->setOpacity(opacity);
    parent_scene->addItem(popup_scene);

    //show the message
    popup_text = new QGraphicsTextItem(message);
    set_font(QFont("Joystix MonoSpace",fontsize));
    popup_text->setTextWidth(width);

    popup_text->setPos(text_x, text_y);
    parent_scene->addItem(popup_text);
}

void PopUpDialogue::set_duration(int duration)
{
    if (duration == NO_DURATION) return;
    this->duration = duration;
    popup_timer = new CustomTimer(duration, true, this, SLOT(remove()));
}

void PopUpDialogue::pause()
{
    if (popup_timer != nullptr) popup_timer->pause();
}

void PopUpDialogue::unpause()
{
    if (popup_timer != nullptr) popup_timer->unpause();
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

void PopUpDialogue::set_font(QFont font, QColor color)
{
    popup_text->setFont(font);
    popup_text->setDefaultTextColor(color);
}

PopUpDialogue* PopUpDialogue::remove()
{
    delete this;
    return nullptr;
}
