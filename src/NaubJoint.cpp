#include "NaubJoint.h"
#include "Naub.h"
#include "QJoint.h"
#include "Naubino.h"

NaubJoint::NaubJoint(Naubino *naubino, Naub *a, Naub *b)
    : naubino(naubino), a(a), b(b) {

    setup();
}

NaubJoint::~NaubJoint() {
    deleted();
}

void NaubJoint::update() {
    if (qjoint != NULL) qjoint->jointChanged();
}

void NaubJoint::deleted() {
    if (qjoint != NULL) qjoint->jointDeleted();
}

void NaubJoint::setup() {
    qjoint = NULL;

    {
        b2DistanceJointDef def;
        def.Initialize(a->body, b->body, a->pos(), b->pos());
        def.length = (a->radius + b->radius) * 1.40;
        def.frequencyHz = 1;
        def.dampingRatio = 0;
        naubino->world->CreateJoint(&def);
    }
}
