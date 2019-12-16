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
 * ENUMS
 * @enum PopUpType: Serves as default configuration for easy dialogue initialization
 *
 * PRIVATE DATA MEMBERS/MEMBER FUNCTIONS
 * @include parent_scene, popup_scene, popup_text: Handles creating the popup box
 * @include popup_timer: Keep track of time that popup dialogue is active
 * @include popup_type: See enum above
 * @include message: Dialogue's message
 * @include color, opacity: Dialogue's color properties
 * @include x, y, width, height: Dialogue's position and size
 * @include text_x, text_y: Text's position
 * @include duration: Time that the dialogue remains active
 * @include create_dialogue(), set_duration(): For constructors' use
 *
 * PUBLIC MEMBER FUNCTIONS
 * @include pause(), unpause(): Pause/Unpause the popup_timer
 * @include set_width(): Change the popup box's width (for boss health)
 * @include set_font(): Change the text's font
 *
 * PUBLIC SLOTS
 * @include remove(): Deletes the object itself, and returns nullptr to its pointer
 */

class PopUpDialogue : public QObject
{
    Q_OBJECT

public:
    constexpr static const int NO_DURATION {0};

public:
    enum PopUpType
    {
        GameArea,   //for pausing/game over screens, the dialogue covers 800*600
        FullScreen, //the dialogue covers 1100*600
        Dialogue,   //for dialogue messages
        BossHealth, //for drawing boss's health bar
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

    void create_dialogue(const QString& message, const QColor& color, const double& opacity,
                         const int& x, const int& y, const int& width, const int& height,
                         const int& text_x, const int& text_y, const int& fontsize);
    void set_duration(const int duration);

public:
    PopUpDialogue(QGraphicsScene* parent_scene, const QString& message, const int duration, const QColor& color, const double& opacity,
                  const int& x, const int& y, const int& width, const int& height, const int& text_x, const int& text_y);
    PopUpDialogue(QGraphicsScene* parent_scene, const QString& message, const int duration, const PopUpType& popup_type,
                  const int& text_x = 100, const int& text_y = SCREEN_HEIGHT/2);
    ~PopUpDialogue();
    void pause();
    void unpause();
    void set_width(const int& width);
    void set_font(const QFont& font={"Joystix Monospace", 12} , const QColor& Color=Qt::black);

public slots:
    PopUpDialogue* remove();


};

#endif // POPUPDIALOGUE_H
