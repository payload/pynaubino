#include "QNaub.h"
#include "Naub.h"
#include "Vec.h"

QNaub::QNaub(Naub *naub, QGraphicsItem *parent) :
    QGraphicsRectItem(0, 0, 10, 10, parent)
{
    setBrush(QBrush(Qt::black));
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    this->naub = naub;
    notifyUpdate();
}

void QNaub::notifyUpdate() {
    setX(naub->pos().x);
    setY(naub->pos().y);
    qreal r = naub->radius;
    setRect(x()-r, y()-r, r*2, r*2);
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
