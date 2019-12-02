#include "pauseButton.h"
#include <QGraphicsTextItem>
#include <QBrush>

PauseButton::PauseButton(QString name, QGraphicsItem *parent): QGraphicsRectItem(parent){
    // draw the rect
    setRect(0,0,50,50);
    setBrush(Qt:: red);

    // draw the text
    text = new QGraphicsTextItem(name,this);
    int xPos = rect().width()/2 - text->boundingRect().width()/2;
    int yPos = rect().height()/2 - text->boundingRect().height()/2;
    text->setPos(xPos,yPos);
}

void PauseButton::mousePressEvent(QGraphicsSceneMouseEvent *event){
    emit clicked();
}
