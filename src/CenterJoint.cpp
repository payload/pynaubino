#include "CenterJoint.h"
#include <Box2D.h>
#include <Naub.h>

void CenterJoint::join(Naub *naub, b2Body *center) {
    _naub = naub;
    _center = center;
    _world = &_naub->world();
    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = _center->GetPosition();
        _helpBody = _world->CreateBody(&def);
    }
    {
        b2RevoluteJointDef def;
        def.bodyA = _center;
        def.bodyB = _helpBody;
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.enableLimit = false;
        _world->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = &_naub->body();
        def.bodyB = _helpBody;
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.001;
        def.dampingRatio = 0.8;
        def.frequencyHz = 1.1;
        _world->CreateJoint(&def);
    }
    {
        b2FrictionJointDef def;
        def.bodyA = _center;
        def.bodyB = &_naub->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.maxForce = 2;
        def.maxTorque = 2;
        _world->CreateJoint(&def);
    }
    Joint::join();
}

void CenterJoint::unjoin() {
    if (!isJoined()) return;
    _naub = NULL;
    _center = NULL;
    _world->DestroyBody(_helpBody);
    _helpBody = NULL;
    Joint::unjoin();
}

Vec CenterJoint::posA() const {
    return Vec(_helpBody->GetPosition());
}

Vec CenterJoint::posB() const {
    return _naub->pos();
}
