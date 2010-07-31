#include "Naub.h"

#include <QPen>

Naub::Naub() {
	isSetup = false;
}

void Naub::setup(b2World *world) {
	this->world = world;
	setupGraphics();
	setupPhysics();
	isSetup = true;
}

void Naub::setupGraphics() {
	setRect( qreal(0), qreal(0), qreal(30), qreal(30) );
	setPen( QPen( Qt::black, qreal(2) ) );
	setBrush( Qt::cyan );
}

void Naub::setupPhysics() {
}

void Naub::adjust() {
	moveBy( 1, 1 );
}
