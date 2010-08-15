#include "Joint.h"
#include "Naub.h"
#include "QJoint.h"
#include "Naubino.h"

#include <QDebug>

Joint::Joint(Naubino *naubino, Naub *a, Naub *b)
    : naubino(naubino), a(a), b(b) {

    setup();
}

Joint::~Joint() {
    if (qjoint != NULL) qjoint->deleted();
    naubino->world->DestroyJoint(joint);
}

void Joint::changed() {
    if (qjoint != NULL) qjoint->changed();
}

void Joint::setup() {
    qjoint = NULL;

    frequencyHz = 0.5f;
    dampingRatio = 0.1f;
    length = 40.0f;

    b2DistanceJointDef jointDef;
    jointDef.bodyA = a->body;
    jointDef.bodyB = b->body;
    jointDef.localAnchorA = a->body->GetLocalCenter();
    jointDef.localAnchorB = b->body->GetLocalCenter();
    jointDef.collideConnected = true;
    jointDef.frequencyHz = frequencyHz;
    jointDef.dampingRatio = dampingRatio;
    jointDef.length = length;
    joint = naubino->world->CreateJoint(&jointDef);
}
