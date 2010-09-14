#include "NaubJoint.h"
#include "Naub.h"
#include <Box2D/Dynamics/b2World.h>
#include <Box2D/Dynamics/b2Body.h>

void NaubJoint::join(Naub *a, Naub *b) {
    _a = a;
    _b = b;
    _world = _a->world();
    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = _a->pos();
        _helpBody = _world->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(_a->body(), _helpBody, _a->pos());
        _world->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = _helpBody;
        def.bodyB = _b->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.6;
        def.dampingRatio = 0.5;
        def.frequencyHz = 3;
        _world->CreateJoint(&def);
    }
    Joint::join();
}
