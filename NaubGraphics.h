#ifndef NAUBGRAPHICS_H
#define NAUBGRAPHICS_H

#include <QGraphicsEllipseItem>
#include <QGraphicsItem>

class NaubGraphics : public QGraphicsEllipseItem {
 public:
	NaubGraphics(qreal x = 0, qreal y = 0, qreal w = 20, qreal h = 20);

	enum { Type = UserType + 1 };
	int type() const { return Type; }
};

#endif
