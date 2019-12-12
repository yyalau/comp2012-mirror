#ifndef POPUPDIALOGUE_H
#define POPUPDIALOGUE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "define.h"
#include "customTimer.h"

/**
 * @brief The PopUpDialogue class
 * Creates a dialogue on the screen. Can be used for pause/gameover messages, as well as game dialogues
 * (added a third type for displaying boss health)
 *
 * ENUMS:
 * @enum PopUpType: Serves as default configuration for easy dialogue initialization
 *
 * PRIVATE DATA MEMBERS:
 * @include parent_scene, popup_scene, popup_text: Handles creating the popup box
 * @include popup_timer: Keep track of time that popup dialogue is active
 * @include popup_type: See enum above
 * @include message: Dialogue's message
 * @include color, opacity: Dialogue's color properties
 * @include x, y, width, height: Dialogue's position and size
 * @include duration: Time that the dialogue remains active
 * @include create_dialogue(), set_duration(): For constructors' use
 *
 * PUBLIC MEMBER FUNCTIONS:
 * @include pause(), unpause(): Pause/Unpause the popup_timer
 * @include set_message(): Change the current message (for game dialogues)
 * @include set_width(): Change the popup box's width (for boss health)
 *
 * PUBLIC SLOTS:
 * @include remove():
 */

#define NO_DURATION 0

class PopUpDialogue : public QObject
{
    Q_OBJECT

public:
    enum PopUpType
    {
        GameArea, //for pausing/game over screens, the dialogue covers 800*600
        FullScreen, //the dialogue covers 1100*600
        Dialogue,   //for dialogue messages
        BossHealth,  //for drawing boss's health bar
        InfoBox     //show message on InfoBox
    };

private:
    QGraphicsScene* parent_scene;
    QGraphicsRectItem* popup_scene;
    QGraphicsTextItem* popup_text;

    CustomTimer* popup_timer {nullptr};
    PopUpType popup_type;
    QString message;
    QColor color;
    double opacity;
    int x, y;
    int text_x, text_y;
    int width, height;
    int duration;

    void create_dialogue(QString message, QColor color, double opacity,
                         int x, int y, int width, int height,int text_x, int text_y);
    void set_duration(int duration);

public:
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, QColor color, double opacity,
                  int x, int y, int width, int height, int text_x=100, int text_y=SCREEN_HEIGHT/2);
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, PopUpType popup_type,
                  int text_x=100, int text_y=SCREEN_HEIGHT/2);
    ~PopUpDialogue();
    void pause();
    void unpause();
    void set_message(QString message);
    void set_width(int width);
    void set_font(QFont font={"Joystix Monospace", 12} , QColor Color=Qt::black);

public slots:
    PopUpDialogue* remove();


};

#endif // POPUPDIALOGUE_H
