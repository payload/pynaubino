#include "QNaubJoint.h"
#include "Naub.h"

QNaubJoint::QNaubJoint(NaubJoint &joint) :
        QObject(), QGraphicsLineItem(), joint_(&joint)
{
    setZValue(99);
    setPen( QPen( Qt::black ) );
    setPenWidth( 4.0f );

    jointChanged();
}

QNaubJoint::~QNaubJoint() {
    joint_ = 0;
}

NaubJoint& QNaubJoint::joint() { return *joint_; }

void QNaubJoint::jointChanged() {
    QPointF a = joint().a().pos().q();
    QPointF b = joint().b().pos().q();
    setLine(a.x(), a.y(), b.x(), b.y());
}

void QNaubJoint::jointDeleted() {
    QPropertyAnimation *ani = new QPropertyAnimation(this, "penWidth");
    ani->setEndValue(0);
    ani->setDuration(500);
    connect(ani, SIGNAL(finished()), SLOT(deleted()));
    ani->start();
}

void QNaubJoint::deleted() {
    setVisible(false);
}

qreal QNaubJoint::penWidth() {
    return pen().widthF();
}

void QNaubJoint::setPenWidth(qreal width) {
    QPen p = pen();
    p.setWidthF(width);
    setPen( p );
}
