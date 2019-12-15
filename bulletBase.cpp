#include "bulletBase.h"

BulletBase::BulletBase(int dx, int dy, const int& size_x, const int& size_y, const int move_freq):
    dx(dx), dy(dy), size_x(size_x), size_y(size_y), move_freq(move_freq)
{
    move_timer = new CustomTimer(move_freq, false, this, SLOT(move()));
    //connect timer and move slot

    //timer is started in bulletEnemy/bulletPlayer's unpause()
}

BulletBase::~BulletBase()
{
    delete move_timer;
}

void BulletBase::pause()
{
    move_timer->pause();
}

void BulletBase::unpause()
{
    move_timer->unpause();
}

bool BulletBase::out_of_bound()
{
    return !(INSCREEN_LEFT(pos().x())) || !(INSCREEN_RIGHT(pos().x(), this)) ||
            !(INSCREEN_UP(pos().y())) || !(INSCREEN_DOWN(pos().y(), this));
}

void BulletBase::move()
{
    //move the bullets
    setPos(x()+dx,y()+dy);

    if (out_of_bound())
        REMOVE_ENTITY(scene(), this);
}
