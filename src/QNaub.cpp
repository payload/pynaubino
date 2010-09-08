#include "QNaub.h"

#include <QPropertyAnimation>

#include "Naub.h"
#include "Scene.h"


QNaub::QNaub(Scene *scene_, Naub *naub_) :
        QObject(), QGraphicsEllipseItem(0, 0, 10, 10),
        _naub(naub_), _scene(scene_)
{
    setZValue(101);
    setPen(Qt::NoPen);
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable);
    setFlag(QGraphicsItem::ItemIsMovable);

    _contactHighlight = 0;
    _contactAni = new QPropertyAnimation(this, "contactHighlight");
    _contactAni->setStartValue(100);
    _contactAni->setEndValue(0);
    _contactAni->setDuration(100);

    naub().setQNaub(this);
    naubChanged();
}


QNaub::~QNaub() {
    naub().setQNaub(0);
    _naub = 0;
    _scene = 0;
    delete _contactAni; _contactAni = NULL;
}


Naub& QNaub::naub() { return *_naub; }
const Naub& QNaub::naub() const { return *_naub; }
Scene& QNaub::scene() { return *_scene; }
const Scene& QNaub::scene() const { return *_scene; }


void QNaub::handleContact(Naub *other) {
    Q_UNUSED(other);
    _contactAni->stop();
    _contactAni->start();
    qDebug(".");
}

void QNaub::naubChanged() {
    QPointF pos = naub().pos().q();
    float x = pos.x();
    float y = pos.y();
    float r = naub().radius() * 100;
    setRect(QRectF(0-r, 0-r, r*2, r*2).normalized());
    setX(x);
    setY(y);
    setRotation(naub().rot());

    QColor color = naub().color();
    if (contactHighlight() > 0)
        setBrush(QBrush( Qt::red ));
    else
        if(color != brush().color())
            setBrush(QBrush(color));
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

