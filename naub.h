#ifndef NAUB_H
#define NAUB_H

#include <QGraphicsRectItem>

class Naub : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Naub(qreal x = 0, qreal y = 0, QGraphicsItem *parent = 0);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
signals:

public slots:

};

#endif // NAUB_H
