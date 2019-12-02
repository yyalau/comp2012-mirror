#ifndef PAUSEBUTTON_H
#define PAUSEBUTTON_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

class PauseButton:public QObject, public QGraphicsRectItem{
    Q_OBJECT
private:
    QGraphicsTextItem* text;

public:
    // constructors
    PauseButton(QString name, QGraphicsItem* parent=0);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);

signals:
    void clicked();
};

#endif // PAUSE_H
