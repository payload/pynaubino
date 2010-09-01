#include "Joints.h"

#include <Box2D/Dynamics/Joints/b2FrictionJoint.h>
#include <Box2D/Dynamics/Joints/b2WeldJoint.h>

#include "Naub.h"
#include "QNaubJoint.h"


/* *** Joint *************************************************************** */

Joint::Joint(b2World *world) : _world(world) {}


Joint::~Joint() {
    _world = 0;
}


/* *** NaubJoint ********************************************************** */

NaubJoint::NaubJoint(b2World *world) : Joint(world), _a(0),
        _b(0), _helpBody(0), _qnaubJoint(0) { }


NaubJoint::~NaubJoint() {
    unjoin();
    _qnaubJoint = 0;
}


void NaubJoint::update() {
    if (_qnaubJoint != 0) {
        _qnaubJoint->jointChanged();
    }
}


void NaubJoint::join(Naub *a, Naub *b) {
    _a = a;
    _b = b;

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
        def.bodyB = &b->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.6;
        def.dampingRatio = 0.5;
        def.frequencyHz = 3;
        _world->CreateJoint(&def);
    }
}


void NaubJoint::unjoin() {
    _a = 0;
    _b = 0;
    if (_helpBody != 0) {
        _world->DestroyBody(_helpBody);
        _helpBody = 0;
    }
}


Naub& NaubJoint::a() { return *_a; }
const Naub& NaubJoint::a() const { return *_a; }
Naub& NaubJoint::b() { return *_b; }
const Naub& NaubJoint::b() const { return *_b; }
void NaubJoint::setQNaubJoint(QNaubJoint *n) { _qnaubJoint = n; }

/* *** CenterJoint ********************************************************* */

CenterJoint::CenterJoint(b2World *world) : Joint(world), _naub(0),
        _center(0), _helpBody(0) {}


CenterJoint::~CenterJoint() {
    unjoin();
}


void CenterJoint::update() {
}


void CenterJoint::join(Naub *naub, b2Body *center) {
    _naub = naub;
    _center = center;

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
        def.frequencyHz = 1.5;
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
}


void CenterJoint::unjoin() {
    _naub = 0;
    _center = 0;
    if (_helpBody != 0) {
        _world->DestroyBody(_helpBody);
        _helpBody = 0;
    }
}


Naub& CenterJoint::naub() { return *_naub; }
const Naub& CenterJoint::naub() const { return *_naub; }
b2Body& CenterJoint::center() { return *_center; }
const b2Body& CenterJoint::center() const { return *_center; }


/* *** PointerJoint ******************************************************** */

PointerJoint::PointerJoint(b2World *world) : Joint(world), _naub(0),
        _pointer(0), _helpBody(0) {
}


PointerJoint::~PointerJoint() {
    unjoin();
}


void PointerJoint::update() {
}


void PointerJoint::join(Naub *naub, Pointer *pointer) {
    _naub = naub;
    _pointer = pointer;

    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = _naub->pos();
        _helpBody = _world->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(&_naub->body(), _helpBody, _naub->pos());
        _world->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = _helpBody;
        def.bodyB = &_pointer->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.01;
        def.dampingRatio = 0.8;
        def.frequencyHz = 1;
        _world->CreateJoint(&def);
    }
}


void PointerJoint::unjoin() {
    _naub = 0;
    _pointer = 0;
    if (_helpBody != 0) {
        _world->DestroyBody(_helpBody);
        _helpBody = 0;
    }
}


Naub& PointerJoint::naub() { return *_naub; }
const Naub& PointerJoint::naub() const { return *_naub; }
Pointer& PointerJoint::pointer() { return *_pointer; }
const Pointer& PointerJoint::pointer() const { return *_pointer; }

