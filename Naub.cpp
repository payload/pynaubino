#include "Naub.h"
#include "QNaub.h"
#include "Vec.h"
#include "Naubino.h"
#include "Joint.h"
#include "Pointer.h"

Naub::Naub(Naubino *naubino, Vec pos, QColor color)
    : naubino(naubino), color(color)
{
    setup();
    body->SetTransform(pos, rot());
}

Naub::~Naub() {
    if (qnaub != NULL) qnaub->deleted();
    naubino->world->DestroyBody(body);
}

Vec Naub::pos() {
    return Vec(body->GetPosition());
}

float32 Naub::rot() {
    return body->GetAngle();
}

void Naub::changed() {
    if (qnaub != NULL) qnaub->changed();
    foreach (Joint *j, jointNaubs->values())
        j->changed();
}

void Naub::select(Pointer *pointer) {
    naubino->select(this, pointer);
}

void Naub::deselect(Pointer *pointer) {
    naubino->deselect(this, pointer);
}

void Naub::setup() {
    selected = 0;
    qnaub = NULL;
    centerJoint = NULL;
    jointNaubs = new QMap<Naub *, Joint *>();
    pointerJoints = new QMap<Pointer *, b2Joint *>();
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
    radius = 15.0f;
    friction = 0.5f;
    density = 1.0f;
    restitution = 0.1f;

    b2CircleShape shape;
    shape.m_radius = radius;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.density = density;
    b2Fixture *fix = body->CreateFixture(&fixtureDef);
    fix->SetUserData(this);
}
