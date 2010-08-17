#include "QJoint.h"
#include "Joint.h"
#include "Naub.h"
#include "Scene.h"

QJoint::QJoint(Scene *scene, Joint *joint) :
        QObject(), QGraphicsLineItem(), scene(scene), joint(joint)
{
    setZValue(99);
    setPen( QPen( QBrush(Qt::black), 4.0f ) );
    joint->qjoint = this;
    changed();
}

void QJoint::changed() {
    Vec a = joint->a->pos();
    Vec b = joint->b->pos();
    setLine(a.x, a.y, b.x, b.y);
}

void QJoint::deleted() {
    scene->removeItem(this);
}
