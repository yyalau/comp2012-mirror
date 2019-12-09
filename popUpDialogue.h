#ifndef POPUPDIALOGUE_H
#define POPUPDIALOGUE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>
#include <QTimer>

#include "define.h"

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
 * @include popup_type: See enum above
 * @include message: Dialogue's message
 * @include color, opacity: Dialogue's color properties
 * @include x, y, width, height: Dialogue's position and size
 * @include duration: Time that the dialogue remains active
 * @include create_dialogue(), set_duration(): For constructors' use
 *
 * PUBLIC MEMBER FUNCTIONS:
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
        BossHealth  //for drawing boss's health bar
    };

private:
    QGraphicsScene* parent_scene;
    QGraphicsRectItem* popup_scene;
    QGraphicsTextItem* popup_text;

    PopUpType popup_type;
    QString message;
    QColor color;
    double opacity;
    int x, y;
    int width, height;
    int duration;

    void create_dialogue(QString message, QColor color, double opacity,
                         int x, int y, int width, int height);
    void set_duration(int duration);

public:
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, QColor color, double opacity,
                  int x, int y, int width, int height);
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, int duration, PopUpType popup_type);
    ~PopUpDialogue();
    void set_message(QString message);
    void set_width(int width);

public slots:
    void remove();


};

#endif // POPUPDIALOGUE_H
