#ifndef NAUBCONTEXT_H
#define NAUBCONTEXT_H

#include <Box2D/Box2D.h>
#include <QGraphicsItemGroup>

class NaubContext {
 public:
	NaubContext(b2World *world);
	b2World *world;
	QGraphicsItemGroup *root;
	QGraphicsItemGroup *naubs;
	QGraphicsItemGroup *joints;
	b2Body *center;
};

#endif
