#ifndef SHOOTER_H
#define SHOOTER_H

#include <QGraphicsRectItem>

class Shooter: public QGraphicsRectItem{
public:
    void keyPressEvent(QKeyEvent* event);

};

#endif // SHOOTER_H
