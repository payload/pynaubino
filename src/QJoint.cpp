#include "QJoint.h"
#include <Joint.h>
#include <Vec.h>
#include <QPen>
#include <PointerJoint.h>

QJoint::QJoint(QObject *parent)
    : QObject(parent), QGraphicsLineItem() {
    setPen(QPen( QBrush(Qt::red), 4 ));
    _joint = NULL;
}

QJoint::~QJoint() {
    _joint = NULL;
}

void QJoint::remove() {
    emit removed(this);
}

void QJoint::setJoint(Joint *joint) {
    _joint = joint;
}

void QJoint::paint(QPainter *painter,
                   const QStyleOptionGraphicsItem *option,
                   QWidget *widget) {
    if (_joint == NULL || !_joint->isJoined()) return;
    QPointF a = _joint->posA().q();
    QPointF b = _joint->posB().q();
    setLine(a.x(), a.y(), b.x(), b.y());
    QGraphicsLineItem::paint(painter, option, widget);
}
