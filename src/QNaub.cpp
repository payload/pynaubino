#include "QNaub.h"

#include <QPropertyAnimation>

#include "Naub.h"
#include "Scene.h"


QNaub::QNaub(Scene *scene, Naub *naub) :
        QObject(), QGraphicsItemGroup(), _naub(naub), _scene(scene)
{
    setZValue(101);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    _contactItem = new QGraphicsEllipseItem(this);
    _contactItem->setPen(Qt::NoPen);
    _contactItem->setBrush(QBrush( Qt::black ));

    _naubItem = new QGraphicsEllipseItem(this);
    _naubItem->setPen(Qt::NoPen);

    addToGroup(_contactItem);
    addToGroup(_naubItem);

    _contactAni = new QPropertyAnimation(this, "contactScale");
    _contactAni->setStartValue(1.2);
    _contactAni->setEndValue(1);
    _contactAni->setDuration(500);

    this->naub().setQNaub(this);
    naubChanged();
}

QNaub::~QNaub() {
    naub().setQNaub(0);
    _naub = 0;
    _scene = 0;
}

Naub& QNaub::naub() { return *_naub; }
const Naub& QNaub::naub() const { return *_naub; }
Scene& QNaub::scene() { return *_scene; }
const Scene& QNaub::scene() const { return *_scene; }


void QNaub::handleContact(Naub *other) {
    Q_UNUSED(other);
    _contactAni->stop();
    _contactAni->start();
}

void QNaub::naubChanged() {
    QPointF pos = naub().pos().q();
    float x = pos.x();
    float y = pos.y();
    float r = naub().radius() * 100;
    _naubItem->setRect(QRectF(0-r, 0-r, r*2, r*2).normalized());
    _contactItem->setRect(_naubItem->rect());

    setX(x);
    setY(y);
    setRotation(naub().rot());

    QColor color = naub().color();
    if(color != _naubItem->brush().color())
        _naubItem->setBrush(QBrush(color));
}


void QNaub::naubDeleted() {
    QPropertyAnimation *ani = new QPropertyAnimation(this, "scale");
    ani->setEndValue(0);
    ani->setDuration(500);
    connect(ani, SIGNAL(finished()), SLOT(naubDeletionAnimationFinished()));
    ani->start();
}


void QNaub::naubDeletionAnimationFinished() {
    setVisible(false);
}


void QNaub::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    scene().selectNaub(this);
}


void QNaub::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
}


void QNaub::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Q_UNUSED(event);
    scene().deselectNaub(this);
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

