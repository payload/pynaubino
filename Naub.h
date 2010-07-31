#ifndef NAUB_H
#define NAUB_H

#include <QGraphicsEllipseItem>

class Naub : public QGraphicsEllipseItem {
 public:
	Naub();
	void advance(int phase);

	enum { Type = UserType + 1 };
	int type() const { return Type; }
};

#endif
