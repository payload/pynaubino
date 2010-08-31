#include "Joints.h"

#include <Box2D/Dynamics/Joints/b2FrictionJoint.h>
#include <Box2D/Dynamics/Joints/b2WeldJoint.h>

#include "Naub.h"
#include "QNaubJoint.h"


/* *** Joint *************************************************************** */

Joint::Joint(b2World *world) : world_(world) {}


Joint::~Joint() {
    world_ = 0;
}


/* *** NaubJoint ********************************************************** */

NaubJoint::NaubJoint(b2World *world) : Joint(world), a_(0),
        b_(0), helpBody_(0), qnaubjoint_(0) { }


NaubJoint::~NaubJoint() {
    unjoin();
    qnaubjoint_ = 0;
}


void NaubJoint::update() {
    if (qnaubjoint_ != 0) {
        qnaubjoint_->jointChanged();
    }
}


void NaubJoint::join(Naub *a, Naub *b) {
    a_ = a;
    b_ = b;

    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = a_->pos();
        helpBody_ = world_->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(&a_->body(), helpBody_, a_->pos());
        world_->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = helpBody_;
        def.bodyB = &b->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.6;
        def.dampingRatio = 0.5;
        def.frequencyHz = 3;
        world_->CreateJoint(&def);
    }
}


void NaubJoint::unjoin() {
    a_ = 0;
    b_ = 0;
    if (helpBody_ != 0) {
        world_->DestroyBody(helpBody_);
        helpBody_ = 0;
    }
}


Naub& NaubJoint::a() { return *a_; }
const Naub& NaubJoint::a() const { return *a_; }
Naub& NaubJoint::b() { return *b_; }
const Naub& NaubJoint::b() const { return *b_; }
void NaubJoint::setQNaubJoint(QNaubJoint *n) { qnaubjoint_ = n; }

/* *** CenterJoint ********************************************************* */

CenterJoint::CenterJoint(b2World *world) : Joint(world), naub_(0),
        center_(0), helpBody_(0) {}


CenterJoint::~CenterJoint() {
    unjoin();
}


void CenterJoint::update() {
}


void CenterJoint::join(Naub *naub, b2Body *center) {
    naub_ = naub;
    center_ = center;

    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = center_->GetPosition();
        helpBody_ = world_->CreateBody(&def);
    }
    {
        b2RevoluteJointDef def;
        def.bodyA = center_;
        def.bodyB = helpBody_;
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.enableLimit = false;
        world_->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = &naub_->body();
        def.bodyB = helpBody_;
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.001;
        def.dampingRatio = 0.8;
        def.frequencyHz = 2.0;
        world_->CreateJoint(&def);
    }
    {
        b2FrictionJointDef def;
        def.bodyA = center_;
        def.bodyB = &naub_->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.maxForce = 2;
        def.maxTorque = 2;
        world_->CreateJoint(&def);
    }
}


void CenterJoint::unjoin() {
    naub_ = 0;
    center_ = 0;
    if (helpBody_ != 0) {
        world_->DestroyBody(helpBody_);
        helpBody_ = 0;
    }
}


Naub& CenterJoint::naub() { return *naub_; }
const Naub& CenterJoint::naub() const { return *naub_; }
b2Body& CenterJoint::center() { return *center_; }
const b2Body& CenterJoint::center() const { return *center_; }


/* *** PointerJoint ******************************************************** */

PointerJoint::PointerJoint(b2World *world) : Joint(world), naub_(0),
        pointer_(0), helpBody_(0) {
}


PointerJoint::~PointerJoint() {
    unjoin();
}


void PointerJoint::update() {
}


void PointerJoint::join(Naub *naub, Pointer *pointer) {
    naub_ = naub;
    pointer_ = pointer;

    {
        b2BodyDef def;
        def.type = b2_dynamicBody;
        def.position = naub_->pos();
        helpBody_ = world_->CreateBody(&def);
    }
    {
        b2WeldJointDef def;
        def.Initialize(&naub_->body(), helpBody_, naub_->pos());
        world_->CreateJoint(&def);
    }
    {
        b2DistanceJointDef def;
        def.bodyA = helpBody_;
        def.bodyB = &pointer_->body();
        def.localAnchorA = Vec();
        def.localAnchorB = Vec();
        def.length = 0.01;
        def.dampingRatio = 0.8;
        def.frequencyHz = 1;
        world_->CreateJoint(&def);
    }
}


void PointerJoint::unjoin() {
    naub_ = 0;
    pointer_ = 0;
    if (helpBody_ != 0) {
        world_->DestroyBody(helpBody_);
        helpBody_ = 0;
    }
}


Naub& PointerJoint::naub() { return *naub_; }
const Naub& PointerJoint::naub() const { return *naub_; }
Pointer& PointerJoint::pointer() { return *pointer_; }
const Pointer& PointerJoint::pointer() const { return *pointer_; }

