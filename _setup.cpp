#include "_setup.h"

/**
 * TODO: Document this more properly
 */

extern _SetUp* setup;
_SetUp::_SetUp()
{
    //-----------------------------------GameSetting-------------------------------
    //scene
    GameScene = new QGraphicsScene(); //create a scene
    GameScene->setSceneRect(0, 0, SCREEN_LENGTH+INFOBOX_LENGTH, SCREEN_HEIGHT);

    //view
    GameView = new QGraphicsView();
    GameView->setScene(GameScene); // view is scene's boss
    GameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    GameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    GameView->setFixedSize(SCREEN_LENGTH+INFOBOX_LENGTH, SCREEN_HEIGHT); //set view and scene are of the same size

    //shooter
    ShooterPlayer* shooter= new ShooterPlayer(); //create a rect
    GameScene->addItem(shooter); //put rect into the scene
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2
    shooter->setPos(400, 540);// set the initial position of the shooter

    //time counter to trigger events. no need pointer for now? we only need to delete when the game ends
    new GameEvent(GameScene);

    //------------------------------------------------InfoBoxSetting-------------------------------------------
    //Scene&view setting
    infoBox = new InfoBox(shooter->get_health());
    infoBox->setPos(SCREEN_LENGTH, 0);
    GameScene->addItem(infoBox);
    infoBox->show_info();

    //Layout Setting
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(GameView);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* window = new QWidget();
    window->setLayout(layout);
    window->show();

}
