#include "Naub.h"
#include "QNaub.h"
#include "Vec.h"
#include "Naubino.h"
#include "NaubJoint.h"
#include "Pointer.h"
#include "Cycler.h"

Naub::Naub(Naubino *naubino, Vec pos, QColor color)
    : naubino(naubino), color(color)
{
    setup();
    body->SetTransform(pos, rot());
}

Naub::~Naub() {
    naubino->world->DestroyBody(body);
}

void Naub::deleted() {
    if (qnaub != NULL) qnaub->naubDeleted();
    body->SetActive(false);
}

Vec Naub::pos() {
    return Vec(body->GetWorldCenter());
}

float32 Naub::rot() {
    return body->GetAngle();
}

void Naub::changed() {
    if (qnaub != NULL) qnaub->naubChanged();
    foreach (NaubJoint *j, jointNaubs->values())
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
    jointNaubs = new QMap<Naub *, NaubJoint *>();
    pointerJoints = new QMap<Pointer *, b2Joint *>();
    tarjan = new NaubTarjan();
    setupBody();
    setupFixture();
}

void Naub::setupBody() {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    def.fixedRotation = 0;
    b2Body *body = naubino->world->CreateBody(&def);
    body->SetUserData(this);
    this->body = body;
}

void Naub::setupFixture() {
    radius = 0.15f;
    friction = 0;
    density = 1;
    restitution = 0.4f;

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
