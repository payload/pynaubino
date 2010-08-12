#include <QDebug>

#include "NaubView.h"

#include <QPainter>

NaubView::NaubView(NaubScene *scene) {
	setScene(scene);
	setRenderHint(QPainter::Antialiasing);
	setMouseTracking(true);
}

static bool mouseMoved = false;

void NaubView::mouseMoveEvent(QMouseEvent *event) {
	if (!mouseMoved) {
		qDebug() << "view mouse moved!";
		mouseMoved = true;
	}
	QGraphicsView::mouseMoveEvent(event);
}
