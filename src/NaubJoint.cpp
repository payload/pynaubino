#include "NaubJoint.h"
#include "Naub.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

void NaubJoint::join(Naub *a, Naub *b) {
    connect(a, SIGNAL(removed(Naub*)), SLOT(unjoin()));
    connect(b, SIGNAL(removed(Naub*)), SLOT(unjoin()));
    _a = a;
    _b = b;
    _world = &_a->world();
    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = _a->pos();
        _helpBody = _world->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(&_a->body(), _helpBody, _a->pos());
        _world->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = _helpBody;
        def.bodyB = &_b->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.6;
        def.dampingRatio = 0.5;
        def.frequencyHz = 3;
        _world->CreateJoint(&def);
    }
    Joint::join();
}

void NaubJoint::unjoin() {
    if (!isJoined()) return;
    _world->DestroyBody(_helpBody);
    _helpBody = NULL;
    Joint::unjoin();
}

void NaubJoint::unjoin(Naub *a, Naub *b) {
    if ((a == _a && b == _b)
    ||  (a == _b && b == _a))
        unjoin();
}

Vec NaubJoint::posA() const {
    if (!isJoined()) return Vec();
    return Vec(_a->body().GetPosition());
}

Vec NaubJoint::posB() const {
    if (!isJoined()) return Vec();
    return Vec(_b->body().GetPosition());
}
