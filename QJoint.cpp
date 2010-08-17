#include "QJoint.h"
#include "Joint.h"
#include "Naub.h"
#include "Scene.h"

QJoint::QJoint(Scene *scene, Joint *joint) :
        QObject(), QGraphicsLineItem(), scene(scene), joint(joint)
{
    setZValue(99);
    setPen( QPen( Qt::black ) );
    setPenWidth( 4.0f );
    joint->qjoint = this;
    jointChanged();
}

void QJoint::jointChanged() {
    Vec a = joint->a->pos();
    Vec b = joint->b->pos();
    setLine(a.x, a.y, b.x, b.y);
}

void QJoint::jointDeleted() {
    QPropertyAnimation *ani = new QPropertyAnimation(this, "penWidth");
    ani->setEndValue(0);
    ani->setDuration(500);
    connect(ani, SIGNAL(finished()), SLOT(deleted()));
    ani->start();
}

void QJoint::deleted() {
    setVisible(false);
}

qreal QJoint::penWidth() {
    return pen().widthF();
}

void QJoint::setPenWidth(qreal width) {
    QPen p = pen();
    p.setWidthF(width);
    setPen( p );
}
