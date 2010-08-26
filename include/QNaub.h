#ifndef QNAUB_H
#define QNAUB_H

#include <QtGui>
#include "Vec.h"
class Naub;

class QNaub : public QObject, public QGraphicsEllipseItem
{
    Q_OBJECT
    Q_PROPERTY(qreal scale READ scale WRITE setScale)
public:
    explicit QNaub(Naub &naub);
    ~QNaub();

    Naub& naub();

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
};

#endif // QNaub_H
