#ifndef NAUBGRAPHICS_H
#define NAUBGRAPHICS_H

#include "Naub.h"

#include <QGraphicsRectItem>
#include <QGraphicsItem>

class NaubGraphics : public QGraphicsRectItem {
 public:
	NaubGraphics(Naub *naub, qreal w = 20, qreal h = 20);

	Naub *naub;

	enum { Type = UserType + 1 };
	int type() const { return Type; }
};

#endif
