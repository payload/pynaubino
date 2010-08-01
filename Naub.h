#ifndef NAUB_H
#define NAUB_H

#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>

class Naub : public QGraphicsEllipseItem {
 public:
	Naub();
	void setup(b2World *world);
	void adjust();

	bool isSetup;

	enum { Type = UserType + 1 };
	int type() const { return Type; }
 protected:
	void setupGraphics();
	void setupPhysics(b2World *world);
 private:
	b2World *world;
	b2Body *body;
};

#endif
