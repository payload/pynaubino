#include "PointerJoint.h"
#include <Pointer.h>
#include <Naub.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>
#include <Vec.h>

void PointerJoint::join(Naub *naub, Pointer *pointer) {
    _world = naub->world();
    _pointerBody = pointer->body();
    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = naub->pos();
        _helpBody = _world->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(naub->body(), _helpBody, naub->pos());
        _world->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = _helpBody;
        def.bodyB = _pointerBody;
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.01;
        def.dampingRatio = 0.8;
        def.frequencyHz = 1.3;
        _world->CreateJoint(&def);
    }
    Joint::join();
}

void PointerJoint::unjoin() {
    // TODO payload: defensive prog or trace where a wrong usage occurs?
    if (!isJoined()) return;
    _world->DestroyBody(_helpBody);
    _helpBody = NULL;
    Joint::unjoin();
}

Vec PointerJoint::posA() const {
    if (!isJoined()) return Vec();
    return Vec(_helpBody->GetPosition());
}

Vec PointerJoint::posB() const {
    if (!isJoined()) return Vec();
    return Vec(_pointerBody->GetPosition());
}
