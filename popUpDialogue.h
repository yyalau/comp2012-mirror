#ifndef POPUPDIALOGUE_H
#define POPUPDIALOGUE_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsRectItem>

#include "define.h"

/**
 * @brief The PopUpDialogue class
 * Creates a dialogue on the screen. Can be used for pause/gameover messages, as well as game dialogues
 *
 * ENUMS:
 * @enum PopUpType: Serves as default configuration for easy dialogue initialization
 *
 * PRIVATE DATA MEMBERS:
 * @include parent_scene, popup_scene, popup_text: Handles creating the pop-up box
 * @include popup_type: See enum above
 * @include message: Dialogue's message
 * @include color, opacity: Dialogue's color properties
 * @include x, y, width, height: Dialogue's position and size
 * @include create_dialogue(): For constructors' use
 *
 * PUBLIC MEMBER FUNCTIONS:
 * @include set_message(): Change the current message (for game dialogues)
 */

class PopUpDialogue : public QObject
{
    Q_OBJECT

public:
    enum PopUpType
    {
        FullScreen, //for pausing/game over screens
        Dialogue    //for dialogue messages
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

    void create_dialogue(QString message, QColor color, double opacity,
                         int x, int y, int width, int height);

public:
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, QColor color, double opacity,
                  int x, int y, int width, int height);
    PopUpDialogue(QGraphicsScene* parent_scene, QString message, PopUpType popup_type);
    ~PopUpDialogue();
    void set_message(QString message);


};

#endif // POPUPDIALOGUE_H
