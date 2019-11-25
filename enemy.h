#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>
#include <health.h>

class Enemy:public QObject, public QGraphicsRectItem{
    Q_OBJECT //implies an object can handle signals

private:
    Health* health= new Health("Enemy");

public:
    Enemy();

public slots:
    void move();
    void shootbullets();
};


#endif // ENEMY_H
