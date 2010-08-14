#include "Naub.h"
#include "QNaub.h"
#include "Vec.h"
#include "Naubino.h"
#include "Joint.h"
#include "Pointer.h"

Naub::Naub(Naubino *naubino, Vec pos)
{
    this->naubino = naubino;
    jointNaubs = new QList<Naub *>();
    joints = new QList<Joint *>();
    mouseJoints = new QMap<Pointer *, b2Joint *>();
    radius = 15.0f;
    friction = 0.5f;
    density = 1.0f;
    restitution = 0.1f;
    setup();
    body->SetTransform(pos, rot());
}

void Naub::selected(Pointer *pointer) {
    b2DistanceJointDef def;
    def.frequencyHz = 0.5f;
    def.dampingRatio = 0.1f;
    def.length = 0.0f;
    def.bodyA = body;
    def.bodyB = pointer->body;
    def.localAnchorA = body->GetLocalCenter();
    def.localAnchorB = pointer->body->GetLocalCenter();
    def.collideConnected = false;
    mouseJoints->insert(
            pointer,
            naubino->world->CreateJoint(&def));
}

void Naub::deselected(Pointer *pointer) {
    QList<b2Joint *> list = mouseJoints->values(pointer);
    for (int i = 0; i < list.count(); i++) {
        b2Joint *joint = list[i];
        naubino->world->DestroyJoint(joint);
        list.removeAt(i);
    }
    mouseJoints->remove(pointer);
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
