#include "bulletBase.h"

BulletBase::BulletBase(int dx, int dy, int size_x, int size_y, int move_freq, int coll_freq):
    dx(dx), dy(dy), size_x(size_x), size_y(size_y), move_freq(move_freq), coll_freq(coll_freq)
{
    QTimer* move_timer= new QTimer();

    //connect timer and move slot
    connect(move_timer, SIGNAL(timeout()), this, SLOT(move()));
    move_timer->start(move_freq);
}

void BulletBase::move()
{
    //move the bullets
    setPos(x()+dx,y()+dy);

    //remove the bullets once its out of bound
    if (!(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x())) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y())))
    {
        REMOVE_ENTITY(this)
    }
}
