#include "QNaub.h"

QNaub::QNaub(qreal x, qreal y, QGraphicsItem *parent) :
    QGraphicsRectItem(x, y, 20, 20, parent)
{
    setBrush(QBrush(Qt::black));
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);
}

void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "press" << this->pos();
    QGraphicsItem::mousePressEvent(event);
}

void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "move" << this->pos();
    QGraphicsItem::mouseMoveEvent(event);
}

void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    qDebug() << "release" << this->pos();
    QGraphicsItem::mouseReleaseEvent(event);
}

void QNaub::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "hover" << this->pos();
    QGraphicsItem::hoverMoveEvent(event);
}

void QNaub::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "enter" << this->pos();
    QGraphicsItem::hoverEnterEvent(event);
}

void QNaub::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    qDebug() << "leave" << this->pos();
    QGraphicsItem::hoverLeaveEvent(event);
}
