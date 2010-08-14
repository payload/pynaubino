#include "QJoint.h"
#include "Joint.h"
#include "Naub.h"

QJoint::QJoint(Joint *joint, QGraphicsItem *parent) :
    QGraphicsLineItem(parent)
{
    setZValue(99);
    setPen( QPen( QBrush(Qt::black), 4.0f ) );
    this->joint = joint;
    joint->qjoint = this;
    notifyUpdate();
}

void QJoint::notifyUpdate() {
    Vec a = joint->a->pos();
    Vec b = joint->b->pos();
    setLine(a.x, a.y, b.x, b.y);
}
