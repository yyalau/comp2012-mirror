#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QObject>

class Enemy:public QObject, public QGraphicsRectItem{
    Q_OBJECT //implies an object can handle signals
public:
    Enemy();

public slots:
    void move();

};


#endif // ENEMY_H
