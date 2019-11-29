#include "_setup.h"


_SetUp::_SetUp()
{
    //-----------------------------------GameSetting-------------------------------
    //scene
    GameScene = new QGraphicsScene(); //create a scene
    GameScene->setSceneRect(0,0,800,600);

    //view
    GameView = new QGraphicsView();
    GameView->setScene(GameScene); // view is scene's boss
    GameView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    GameView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    GameView->setFixedSize(800,600); //set view and scene are of the same size


    //shooter
    Shooter* shooter= new Shooter(); //create a rect
    GameScene->addItem(shooter); //put rect into the scene
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2
    shooter->setPos(GameView->width()/2, GameView->height()-shooter->rect().height());// set the position of the shooter

    //enemy
    Enemy* enemy= new Enemy();
    enemy->setPos(GameView->width()/2, 0);
    GameScene->addItem(enemy);

    //------------------------------------------------MenuBarSetting-------------------------------------------
    //Scene&view setting
    MenuScene = new QGraphicsScene;
    MenuScene->setSceneRect(800,0,300,600);
    MenuScene->setBackgroundBrush(Qt::black);

    MenuView = new QGraphicsView(MenuScene);
    MenuView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    MenuView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    MenuView->setFixedSize(300,600); //set view and scene are of the same size

    //items
    health = new Health("Player"  );
    MenuScene->addItem(health);
    health->setPos(800,0);

    //Layout Setting
    QHBoxLayout* layout = new QHBoxLayout();
    layout->addWidget(GameView);
    layout->addWidget(MenuView);
    layout->setSizeConstraint(QLayout::SetFixedSize);

    QWidget* window = new QWidget();
    window->setLayout(layout);
    window->show();

}
