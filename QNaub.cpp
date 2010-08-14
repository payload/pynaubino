#include "QNaub.h"
#include "Naub.h"
#include "Vec.h"

//#define DEBUG_EVENTS
#ifdef DEBUG_EVENTS
#include <QDebug>
#endif

QNaub::QNaub(Naub *naub, QGraphicsItem *parent) :
    QGraphicsEllipseItem(0, 0, 10, 10, parent)
{
    setZValue(100);
    setPen( QPen( QBrush(Qt::black), 2.0f ) );
    setBrush( QBrush(Qt::darkGray) );
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    this->naub = naub;
    naub->qnaub = this;
    notifyUpdate();
}

void QNaub::notifyUpdate() {
    qreal x = naub->pos().x;
    qreal y = naub->pos().y;
    qreal r = naub->radius;
    setRect( QRectF(0-r, 0-r, r*2, r*2).normalized() );
    setX(x);
    setY(y);
    setRotation(naub->rot());
}

void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "press" << this->pos();
#endif
    QGraphicsItem::mousePressEvent(event);
}

void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "move" << this->pos();
#endif
    QGraphicsItem::mouseMoveEvent(event);
}

void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "release" << this->pos();
#endif
    QGraphicsItem::mouseReleaseEvent(event);
}

void QNaub::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "hover" << this->pos();
#endif
    QGraphicsItem::hoverMoveEvent(event);
}

void QNaub::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "enter" << this->pos();
#endif
    QGraphicsItem::hoverEnterEvent(event);
}

void QNaub::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "leave" << this->pos();
#endif
    QGraphicsItem::hoverLeaveEvent(event);
}
