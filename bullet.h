#ifndef BULLET_H
#define BULLET_H
#include <QGraphicsRectItem>
#include <QObject>

class Bullet:public QObject, public QGraphicsRectItem{
    Q_OBJECT //implies an object can handle signals

private:
    int dx;
    int dy;

public:
    Bullet(int, int);

public slots:
    void move();

};

#endif // BULLET_H

