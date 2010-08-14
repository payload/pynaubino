#include "QNaub.h"
#include "Naub.h"
#include "Vec.h"
#include "Pointer.h"
#include "Scene.h"

//#define DEBUG_EVENTS
#ifdef DEBUG_EVENTS
#include <QDebug>
#endif

QNaub::QNaub(Scene *scene, Naub *naub, QGraphicsItem *parent) :
    QGraphicsEllipseItem(0, 0, 10, 10, parent)
{
    setZValue(100);
    setPen( QPen( QBrush(Qt::black), 2.0f ) );
    setBrush( QBrush(Qt::darkGray) );
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    this->scene = scene;

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
    qDebug() << "press" << this;
#endif
    Q_UNUSED(event);
    naub->selected(scene->getMainPointer());
}

void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
#ifdef DEBUG_EVENTS
    static int spam = 0;
    if (spam % 100 == 0) qDebug() << "move" << this;
    spam++;
#endif
    Q_UNUSED(event);
}

void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "release" << this;
#endif
    Q_UNUSED(event);
    naub->deselected(scene->getMainPointer());
}

void QNaub::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    static int spam = 0;
    if (spam % 100 == 0) qDebug() << "hover" << this;
    spam++;
#endif
    Q_UNUSED(event);
}

void QNaub::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "enter" << this;
#endif
    Q_UNUSED(event);
}

void QNaub::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
#ifdef DEBUG_EVENTS
    qDebug() << "leave" << this;
#endif
    Q_UNUSED(event);
}
