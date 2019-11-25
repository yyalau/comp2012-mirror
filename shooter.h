#ifndef SHOOTER_H
#define SHOOTER_H

#include "health.h"
#include <QGraphicsRectItem>

class Shooter: public QGraphicsRectItem{
private:
    Health* health= new Health("Shooter");
public:
    Shooter();
    void keyPressEvent(QKeyEvent* event);

};

#endif // SHOOTER_H
