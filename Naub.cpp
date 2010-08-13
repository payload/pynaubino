#include "Naub.h"
#include "QNaub.h"
#include "Vec.h"
#include "Naubino.h"

Naub::Naub(Naubino *naubino)
{
    this->naubino = naubino;
    radius = 15.0f;
    friction = 0.5f;
    density = 1.0f;
    restitution = 0.1f;
}

Vec Naub::pos() {
    return Vec(body->GetPosition());
}

void Naub::update() {
    if(qnaub) qnaub->notifyUpdate();
}

void Naub::setup() {
    setupBody();
    setupFixture();
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
