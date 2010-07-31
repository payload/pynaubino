#include "Naub.h"

#include <QPen>

Naub::Naub() {
	setRect( qreal(0), qreal(0), qreal(30), qreal(30) );
	setPen( QPen( Qt::black, qreal(2) ) );
	setBrush( Qt::cyan );
}

void Naub::advance(int phase) {
	if (phase == 0) {
	}
	if (phase == 1) {
		moveBy( 1, 1 );
	}
}
