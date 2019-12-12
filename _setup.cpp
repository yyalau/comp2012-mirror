#include "_setup.h"

/**
 * TODO: Document this more properly
 */

_SetUp::_SetUp()
{
    //-----------------------------------GameSetting-------------------------------
    //scene
    QFontDatabase::addApplicationFont(":/fontstyle/font/ARCADECLASSIC.TTF");
    QFontDatabase::addApplicationFont(":/fontstyle/font/PressStart2P.ttf");
    QFontDatabase::addApplicationFont(":/fontstyle/font/joystix monospace.ttf");

    GameScene = new QGraphicsScene(); //create a scene
    GameScene->setSceneRect(0, 0, SCREEN_LENGTH, SCREEN_HEIGHT);

    //view
    GameView = new QGraphicsView();
    GameView->setScene(GameScene); // view is scene's boss
    GameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    GameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    GameView->setFixedSize(SCREEN_LENGTH, SCREEN_HEIGHT); //set view and scene are of the same size

    //shooter
    shooter= new ShooterPlayer();
    GameScene->addItem(shooter);
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2
    shooter->setPos(START_POS_X, START_POS_Y);// set the initial position of the shooter
    ShooterEnemy::set_player(shooter);
    ShooterBoss::set_player(shooter);

    //------------------------------------------------InfoBoxSetting-------------------------------------------

    //add infoBox into the GameScene
    infoBox = new InfoBox(shooter);
    infoBox->setPos(GAMEAREA_LENGTH, 0);
    GameScene->addItem(infoBox);
    infoBox->show_general_info();

    //Layout Setting
    layout = new QHBoxLayout();
    layout->addWidget(GameView);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    window = new QWidget();
    window->setLayout(layout);
    window->show();

    //set the instructions of the game
    //should i move this to somewhere else? (nah here is ok, it's for setup)
    QString instructions{
        "\t COMP2012H-ShootTheBugs \n\n"
        "Some instructions \n"
        "1. \t ... \n"
        "2. \t ... \n"
        "\n"
        "\t \t Press P to play"
    };

    //time counter to trigger events
    gameEvent = new GameEvent(GameScene, shooter, instructions);
}


