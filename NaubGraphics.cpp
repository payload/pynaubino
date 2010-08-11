#include "NaubGraphics.h"

#include <QBrush>

NaubGraphics::NaubGraphics
(qreal x, qreal y, qreal w, qreal h)
	: QGraphicsEllipseItem(x, y, w, h) {
	setBrush(QBrush(Qt::red));
}
