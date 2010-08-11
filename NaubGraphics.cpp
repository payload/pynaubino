#include "NaubGraphics.h"

#include <QBrush>

NaubGraphics::NaubGraphics
(Naub *naub, qreal w, qreal h) 
	: QGraphicsRectItem(0, 0, w, h), naub(naub) {
	setBrush(QBrush(Qt::red));
	setTransformOriginPoint( w*0.5f, h*0.5f );
}
