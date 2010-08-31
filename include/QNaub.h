#ifndef QNAUB_H
#define QNAUB_H


#include "Prereqs.h"

#include <QtGui>

#include "Vec.h"

class Naub;
class Scene;


class QNaub : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    QNaub(Scene &scene, Naub &naub);
    ~QNaub();

    Naub& naub();
    Scene& scene();

    void naubChanged();
    void naubDeleted();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:

public slots:
    void deleted();
private:
    Naub *naub_;
    Scene *scene_;
};

#endif // QNaub_H
