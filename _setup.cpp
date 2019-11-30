#include "_setup.h"

extern _SetUp* setup;
_SetUp::_SetUp()
{
    //-----------------------------------GameSetting-------------------------------
    //scene
    GameScene = new QGraphicsScene(); //create a scene
    GameScene->setSceneRect(0,0,1100,600);

    //view
    GameView = new QGraphicsView();
    GameView->setScene(GameScene); // view is scene's boss
    GameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    GameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    GameView->setFixedSize(1100,600); //set view and scene are of the same size

    //shooter
    ShooterPlayer* shooter= new ShooterPlayer(); //create a rect
    GameScene->addItem(shooter); //put rect into the scene
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2
    shooter->setPos(GameView->width()/2, GameView->height()-shooter->rect().height());// set the position of the shooter

    //enemy
    //TODO: replace this with gameEvent
    ShooterEnemy* enemy= new ShooterEnemy();
    enemy->setPos(GameView->width()/2, 0);
    GameScene->addItem(enemy);

    //------------------------------------------------MenuBarSetting-------------------------------------------
    //Scene&view setting
    //TODO: add a black rectangle (800,0,300,600)
    //MenuScene = new QGraphicsScene;
    //MenuScene->setSceneRect(800,0,300,600);
    //MenuScene->setBackgroundBrush(Qt::black);

    //MenuView = new QGraphicsView(MenuScene);
    //MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    //MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    //MenuView->setFixedSize(300,600); //set view and scene are of the same size

    //items
    //TODO: move all info box stuff to one class?
    health = new Health("Player");
    GameScene->addItem(health);
    health->setPos(800,0);

    //Layout Setting
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(GameView);
    //layout->addWidget(MenuView);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* window = new QWidget();
    window->setLayout(layout);
    window->show();

}
