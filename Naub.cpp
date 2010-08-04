#include "Naub.h"

#include <QPen>

static const float PI = 3.14159;

Naub::Naub(b2World *world, qreal x, qreal y, QGraphicsItem *parent) : QGraphicsEllipseItem( 0, 0, 30, 30, parent) {
	setup(world);
	body->SetTransform(b2Vec2(x, y), body->GetAngle());
	adjust();
}

void Naub::setup(b2World *world) {
	setupGraphics();
	setupPhysics(world);
}

void Naub::setupGraphics() {
	setPen( QPen( Qt::black, qreal(2) ) );
	setBrush( Qt::cyan );
}

void Naub::setupPhysics(b2World *world) {
	setPos(10.0f, 10.0f);
	this->world = world;
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(x(), y());
	bodyDef.angle = -(rotation()) * (2 * PI) / 360.0;
	body = world->CreateBody(&bodyDef);
	b2CircleShape shape;
	shape.m_radius = 15.0f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

void Naub::adjust() {
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	setPos(position.x, position.y);
	setRotation(-(angle * 360.0) / (2 * PI));
}
