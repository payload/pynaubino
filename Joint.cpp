#include "Joint.h"
#include "Naub.h"
#include "QJoint.h"
#include "Naubino.h"

Joint::Joint(Naubino *naubino, Naub *a, Naub *b)
    : naubino(naubino), a(a), b(b) {

    setup();
}

Joint::~Joint() {
    deleted();
}

void Joint::changed() {
    if (qjoint != NULL) qjoint->jointChanged();
}

void Joint::deleted() {
    if (qjoint != NULL) qjoint->jointDeleted();
}

void Joint::setup() {
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
