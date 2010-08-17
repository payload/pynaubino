#include "QNaub.h"
#include "Scene.h"
#include "Naub.h"

QNaub::QNaub(Scene *scene, Naub *naub) :
    QObject(), QGraphicsEllipseItem(0, 0, 10, 10), scene(scene), naub(naub)
{
    setZValue(101);
    setPen( Qt::NoPen );
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    naub->qnaub = this;
    naubChanged();
}

QNaub::~QNaub() {
    scene = 0;
    naub = 0;
}

void QNaub::naubChanged() {
    qreal x = naub->pos().x;
    qreal y = naub->pos().y;
    qreal r = naub->radius;
    setRect( QRectF(0-r, 0-r, r*2, r*2).normalized() );
    setX(x);
    setY(y);
    setRotation(naub->rot());
    if (naub->color != brush().color())
        setBrush( QBrush( naub->color) );
}

void QNaub::naubDeleted() {
    deleted();
}

void QNaub::deleted() {
    setVisible(false);
}

void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    naub->select(scene->getMainPointer());
    Q_UNUSED(event);
}

void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}

void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    naub->deselect(scene->getMainPointer());
    Q_UNUSED(event);
}

void QNaub::hoverMoveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
}

void QNaub::hoverEnterEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
}

void QNaub::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) {
    Q_UNUSED(event);
}
