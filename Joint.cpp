#include "Joint.h"
#include "JointGraphics.h"
#include "Naub.h"

Joint::Joint(Naub *a, Naub *b) : a(a), b(b) {
	graphics = new JointGraphics(this);
	a->context->joints->addToGroup(graphics);
}

void Joint::adjust() {
	isAdjusted();
}
