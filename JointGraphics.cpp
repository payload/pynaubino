#include "JointGraphics.h"
#include "Joint.h"
#include "Naub.h"

#include <QPen>
#include <QBrush>

JointGraphics::JointGraphics(Joint *joint) : joint(joint) {
	setPen(QPen(QBrush(Qt::black), 3));
	connect(joint, SIGNAL(isAdjusted()), this, SLOT(adjust()));
	adjust();
}

#include <QDebug>

void JointGraphics::adjust() {
	setLine(joint->a->x(), joint->a->y(),
					joint->b->x(), joint->b->y());
}
