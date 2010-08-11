#include "NaubContext.h"

NaubContext::NaubContext(b2World *world) {
	this->world = world;

	root = new QGraphicsItemGroup();
	naubs = new QGraphicsItemGroup();
	joints = new QGraphicsItemGroup();
	root->addToGroup(joints);
	root->addToGroup(naubs);

	b2BodyDef centerDef;
	center = world->CreateBody(&centerDef);
}
