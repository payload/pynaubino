#include "Joints.h"
#include "Naub.h"

Joint::Joint(b2World &world) : world_(&world) {}

Joint::~Joint() {
    world_ = 0;
}

b2World& Joint::world() { return *world_; }

NaubJoint::NaubJoint(b2World &world)
    : Joint(world), a_(0), b_(0) {}

NaubJoint::~NaubJoint() {
    unjoin();
}

void NaubJoint::update() {

}

void NaubJoint::join(Naub &a, Naub &b) {
    a_ = &a;
    b_ = &b;
}

void NaubJoint::unjoin() {
    a_ = 0;
    b_ = 0;
}

Naub& NaubJoint::a() { return *a_; }
Naub& NaubJoint::b() { return *b_; }

CenterJoint::CenterJoint(b2World &world)
    : Joint(world), naub_(0), center_(0) {}


CenterJoint::~CenterJoint() {
    unjoin();
}

void CenterJoint::update() {

}

void CenterJoint::join(Naub &naub, b2Body &center) {
    naub_ = &naub;
    center_ = &center;
}

void CenterJoint::unjoin() {
    naub_ = 0;
    center_ = 0;
}

Naub& CenterJoint::naub() { return *naub_; }

b2Body& CenterJoint::center() { return *center_; }

PointerJoint::PointerJoint(b2World &world)
    : Joint(world), naub_(0), pointer_(0) {}

PointerJoint::~PointerJoint() {
    unjoin();
}

void PointerJoint::update() {

}

void PointerJoint::join(Naub &naub, Pointer &pointer) {
    naub_ = &naub;
    pointer_ = &pointer;
}

void PointerJoint::unjoin() {
    naub_ = 0;
    pointer_ = 0;
}

Naub& PointerJoint::naub() { return *naub_; }

Pointer& PointerJoint::pointer() { return *pointer_; }
