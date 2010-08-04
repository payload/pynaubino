#ifndef NAUB_H
#define NAUB_H

#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>

class Naub : public QGraphicsEllipseItem {
 public:
	Naub(b2World *world, qreal x = 0, qreal y = 0, QGraphicsItem *parent = 0);
	void setup(b2World *world);
	void adjust();

	bool isSetup;
	b2Body *body;

	enum { Type = UserType + 1 };
	int type() const { return Type; }
 protected:
	void setupGraphics();
	void setupPhysics(b2World *world);
 private:
	b2World *world;
};

#endif
