#include "Naub.h"
#include "QNaub.h"
#include "Vec.h"
#include "Naubino.h"
#include "Joint.h"

#include <QDebug>

Naub::Naub(Naubino *naubino, Vec pos)
{
    this->naubino = naubino;
    jointNaubs = new QList<Naub *>();
    joints = new QList<Joint *>();
    radius = 15.0f;
    friction = 0.5f;
    density = 1.0f;
    restitution = 0.1f;
    setup();
    body->SetTransform(pos, rot());
}

Vec Naub::pos() {
    return Vec(body->GetPosition());
}

float32 Naub::rot() {
    return body->GetAngle();
}

void Naub::update() {
    if(qnaub) qnaub->notifyUpdate();
}

Joint* Naub::join(Naub *other) {
    return new Joint(this, other);
}

void Naub::setup() {
    setupBody();
    setupFixture();
    body->ApplyLinearImpulse(1000*Vec(5, 10), Vec(10, 0));
}

void Naub::setupBody() {
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    b2Body *body = naubino->world->CreateBody(&bodyDef);
    body->SetUserData(this);
    this->body = body;
}

void Naub::setupFixture() {
    b2CircleShape shape;
    shape.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.density = density;
    body->CreateFixture(&fixtureDef);
}
