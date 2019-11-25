#ifndef _SETUP_H
#define _SETUP_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QWidget>

#include "shooter.h"
#include "enemy.h"


class _SetUp: public QGraphicsView
{

public:
    _SetUp();

    QGraphicsScene* scene;
    QGraphicsView* view;
    Shooter* shooter;

public slots:

    void start();


};


#endif // _SETUP_H
