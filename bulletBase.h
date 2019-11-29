#ifndef BULLETBASE_H
#define BULLETBASE_H
#include <QObject>
#include <QGraphicsRectItem>
#include <QGraphicsScene>

class BulletBase: public QObject, public QGraphicsRectItem{
     Q_OBJECT //implies the object can handle signals
private:
    int dx;
    int dy;

public:
    BulletBase(int dx=0, int dy=0);
    virtual ~BulletBase()=default;

public slots:
    virtual void move()=0;
};

#endif // BULLETBASE_H
