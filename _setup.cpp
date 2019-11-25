#include <_setup.h>
#include <stdlib.h>

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
    Shooter* shooter= new Shooter(); //create a rect
    scene->addItem(shooter); //put rect into the scene
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2
    shooter->setPos(view->width()/2, view->height()-shooter->rect().height());// set the position of the shooter

    //enemy
    Enemy* enemy= new Enemy();
    enemy->setPos(view->width()/2, 0);
    scene->addItem(enemy);

    show();

}
