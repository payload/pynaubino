#ifndef NAUB_H
#define NAUB_H

#include <Box2D/Box2D.h>
#include <QGraphicsEllipseItem>

class Naub : public QGraphicsEllipseItem {
 public:
	Naub();
	void setup();
	void adjust();

	enum { Type = UserType + 1 };
	int type() const { return Type; }
};

#endif
