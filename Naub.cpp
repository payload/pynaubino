#include "Naub.h"

#include <QPen>

Naub::Naub() {
	setup();
}

void Naub::setup() {
	setRect( qreal(0), qreal(0), qreal(30), qreal(30) );
	setPen( QPen( Qt::black, qreal(2) ) );
	setBrush( Qt::cyan );
}

void Naub::adjust() {
	moveBy( 1, 1 );
}
