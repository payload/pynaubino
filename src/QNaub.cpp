#include "QNaub.h"

#include "Naub.h"
#include "Scene.h"


QNaub::QNaub(Scene &scene, Naub &naub) :
        QObject(), QGraphicsEllipseItem(0, 0, 10, 10),
        scene_(&scene), naub_(&naub)
{
    setZValue(101);
    setPen(QPen( Qt::NoPen ));
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    naub.qnaub = this;
    naubChanged();
}


QNaub::~QNaub() {
    naub().qnaub = 0;
    naub_ = 0;
    scene_ = 0;
}


Naub& QNaub::naub() { return *naub_; }
Scene& QNaub::scene() { return *scene_; }


void QNaub::naubChanged() {
    QPointF pos = naub().pos().q();
    qreal x = pos.x();
    qreal y = pos.y();
    qreal r = naub().radius() * 100;
    setRect( QRectF(0-r, 0-r, r*2, r*2).normalized() );
    setX(x);
    setY(y);
    setRotation(naub().rot());
    QColor qcolor = naub().color().qcolor();
    if (qcolor != brush().color())
        setBrush(QBrush( qcolor ));
}


void QNaub::naubDeleted() {
    QPropertyAnimation *ani = new QPropertyAnimation(this, "scale");
    ani->setEndValue(0);
    ani->setDuration(500);
    connect(ani, SIGNAL(finished()), SLOT(deleted()));
    ani->start();
}


void QNaub::deleted() {
    setVisible(false);
}


void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    scene().selectNaub(*this);
}


void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}


void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    scene().deselectNaub(*this);
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

