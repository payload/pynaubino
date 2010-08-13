#ifndef QNAUB_H
#define QNAUB_H

#include <QtGui>

class Naub;

class QNaub : public QGraphicsRectItem
{
public:
    explicit QNaub(Naub *naub, QGraphicsItem *parent = 0);
    Naub *naub;

    void notifyUpdate();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // QNAUB_H
