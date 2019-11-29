#include "_setup.h"
#include <stdlib.h>
#include <QtDebug>

extern _SetUp* setup;
_SetUp::_SetUp()
{
    //scene
    scene = new QGraphicsScene(); //create a scene
    scene->setSceneRect(0,0,800,600);

    //view
    setScene(scene); // view is scene's boss
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    setFixedSize(800,600); //set view and scene are of the same size

    //shooter
    player= new ShooterPlayer(); //create a rect
    scene->addItem(player); //put rect into the scene
    player->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    player->setFocus(); //setfocus2
    player->setPos(scene->width()/2, scene->height()-player->rect().height());// set the position of the shooter

    //enemy
    ShooterEnemy* enemy= new ShooterEnemy();
    enemy->setPos(scene->width()/2, 0);
    scene->addItem(enemy);

    show();

}
