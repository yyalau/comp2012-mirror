#include "_setup.h"

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

    //background image
    QGraphicsPixmapItem* background  = new QGraphicsPixmapItem(QPixmap(":/image/images/bg.png"));
    background->setPixmap(background->pixmap().scaled(GAMEAREA_LENGTH, SCREEN_HEIGHT, Qt::IgnoreAspectRatio));
    background->setShapeMode(QGraphicsPixmapItem::MaskShape);
    background->setTransformOriginPoint(background->boundingRect().width()/2,background->boundingRect().height()/2);
    background->setScale(1);
    GameScene->addItem(background);

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

    //show the game
    GameView->show();

    //Instructions of the game
    QString instructions{
        "\t\tCOMP2012H-ShootTheBugs \n\n\n"
        "Instructions: \n\n"
        "You are controlling a debugger.\n"
        "Do your best to survive and defeat the bugs!\n"
        "Hold Up, Down, Left or Right to move around.\n"
        "Hold Spacebar to shoot.\n"
        "You start with 25 health. \n"
        "Don't let it go to 0.\n"
        "\n\n\n"
        "\t\t\tPress S to start"
    };

    //time counter to trigger events
    gameEvent = new GameEvent(GameScene, shooter, instructions);
}


