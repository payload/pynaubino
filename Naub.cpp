#include <QtDebug>
#include "Naub.h"

#include "NaubGraphics.h"

#include <QPen>

static const float PI = 3.14159;

Naub::Naub(NaubContext *context, Vec pos) : context(context) {
	setup();
	setPos(pos);
}

void Naub::setPos(Vec pos) {
	body->SetTransform(pos.toB2Vec2(), body->GetAngle());
	graphics->setPos(pos.toPointF());
}

qreal Naub::x() {
	return body->GetPosition().x;
}

qreal Naub::y() {
	return body->GetPosition().y;
}

void Naub::setup() {
	joints = new QList<Joint *>();
	graphics = new NaubGraphics(this);
	context->naubs->addToGroup(graphics);
	setupBody();
	setupFixture();
	joinWithCenter();
}

void Naub::setupBody() {
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	b2Body *body = context->world->CreateBody(&bodyDef);
	body->SetUserData(this);
	this->body = body;
}

void Naub::setupFixture() {
	b2CircleShape shape;
	shape.m_radius = 10.0f;
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &shape;
	fixtureDef.friction = 0.5f;
	fixtureDef.restitution = 0.5f;
	fixtureDef.density = 1.0f;
	body->CreateFixture(&fixtureDef);
}

void Naub::joinWithCenter() {
  b2DistanceJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.bodyB = context->center;
	jointDef.localAnchorA = body->GetLocalCenter();
	jointDef.localAnchorB = context->center->GetLocalCenter();
	jointDef.collideConnected = false;
	jointDef.frequencyHz = 0.1f;
	jointDef.dampingRatio = 0.6f;
	jointDef.length = 0.0f;
	context->world->CreateJoint(&jointDef);
}

void Naub::join(Naub *other) {
  b2DistanceJointDef jointDef;
	jointDef.bodyA = body;
	jointDef.bodyB = other->body;
	jointDef.localAnchorA = body->GetLocalCenter();
	jointDef.localAnchorB = other->body->GetLocalCenter();
	jointDef.collideConnected = true;
	jointDef.frequencyHz = 0.5f;
	jointDef.dampingRatio = 0.1f;
	jointDef.length = 40.0f;
	context->world->CreateJoint(&jointDef);

	Joint *joint = new Joint(this, other);
	*joints << joint;
	*other->joints << joint;
}

void Naub::adjust() {
	b2Vec2 position = body->GetPosition();
	float32 angle = body->GetAngle();
	graphics->setPos(position.x, position.y);
	graphics->setRotation(-(angle * 360.0) / (2 * PI));
}
