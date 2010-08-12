#include <QDebug>

#include "NaubGraphics.h"

#include <QBrush>

NaubGraphics::NaubGraphics
(Naub *naub, qreal w, qreal h) 
	: QGraphicsRectItem(0, 0, w, h), naub(naub) {
	setBrush(QBrush(Qt::red));
	setTransformOriginPoint( w*0.5f, h*0.5f );
}

void NaubGraphics::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
	event->ignore();
}

void NaubGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event) {
	event->accept();
	qDebug() << "mousePress";
	naub->selected();
}

void NaubGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
	event->accept();
	qDebug() << "mouseRelease";
	naub->deselected();
}
