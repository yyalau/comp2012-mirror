#include <QApplication>
#include "shooter.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "enemies.h"
#include <QObject>
#include <QTimer>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // MainWindow w;
    //w.show();

    QGraphicsScene* scene = new QGraphicsScene(); //create a scene
    Shooter* shooter= new Shooter(); //create a rect
    shooter->setRect(0,0, 50, 40); //set the rect to the screen (0,0) position, 50 px width, 50 px tall

    scene->addItem(shooter); //put rect into the scene
    shooter->setFlag(QGraphicsItem::ItemIsFocusable); // setfocus1
    shooter->setFocus(); //setfocus2

    QGraphicsView* view= new QGraphicsView(scene); // view is scene's boss
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable horizontal scroll bar
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff); //disable vertical scroll bar
    view->show(); //show the scene in view

    view->setFixedSize(800,600); //set view and scene are of the same size
    scene->setSceneRect(0,0,800,600);
    shooter->setPos(view->width()/2, view->height()-shooter->rect().height());// set the position of the shooter

    //create manymany enemies
    QTimer* timer= new QTimer();
    QObject::connect(timer, SIGNAL(timeout()),enemy, SLOT(create_enemies()));



    return a.exec();
}
