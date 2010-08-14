#include "Joint.h"
#include "Naub.h"
#include "QJoint.h"
#include "Naubino.h"

Joint::Joint(Naub *a, Naub *b) : a(a), b(b) {
    frequencyHz = 0.5f;
    dampingRatio = 0.1f;
    length = 40.0f;

    *a->joints << this;
    *a->jointNaubs << b;
    *b->joints << this;
    *b->jointNaubs << a;

    b2DistanceJointDef jointDef;
    jointDef.bodyA = a->body;
    jointDef.bodyB = b->body;
    jointDef.localAnchorA = a->body->GetLocalCenter();
    jointDef.localAnchorB = b->body->GetLocalCenter();
    jointDef.collideConnected = true;
    jointDef.frequencyHz = frequencyHz;
    jointDef.dampingRatio = dampingRatio;
    jointDef.length = length;
    a->naubino->world->CreateJoint(&jointDef);
}

void Joint::update() {
    if (qjoint) qjoint->notifyUpdate();
}
