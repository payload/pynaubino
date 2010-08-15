#ifndef QNAUB_H
#define QNAUB_H

#include <QtGui>

class Naub;
class Pointer;
class Scene;

class QNaub : public QGraphicsEllipseItem
{
public:
    explicit QNaub(Scene *scene, Naub *naub, QGraphicsItem *parent = 0);
    Scene *scene;
    Naub *naub;
    Pointer *pointer;

    void changed();
    void deleted();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
};

#endif // QNAUB_H
