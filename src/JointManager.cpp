#include "JointManager.h"


#include <QMap>

#include "Joints.h"


JointManager::JointManager(b2World &world) : world_(&world) {
    joints_ = new QList<Joint *>();
}


JointManager::~JointManager() {
    foreach (Joint *joint, *joints_) {
        delete joint;
    }
    delete joints_;
    joints_ = 0;
    world_ = 0;
}


NaubJoint& JointManager::joinNaubs(Naub &a, Naub &b) {
    NaubJoint *joint = new NaubJoint(&world());
    joints().append(joint);
    a.jointNaubs().insert(&b, joint);
    b.jointNaubs().insert(&a, joint);
    joint->join(&a, &b);
    return *joint;
}


void JointManager::unjoinNaubs(NaubJoint &joint) {
    joint.a().jointNaubs().remove(&joint.b());
    joint.b().jointNaubs().remove(&joint.a());
    joint.unjoin();
    joints().removeOne(&joint);
    delete &joint;
}


void JointManager::rejoinNaubs(NaubJoint &joint,
                               Naub &a, Naub &b) {
    joint.a().jointNaubs().remove(&joint.b());
    joint.b().jointNaubs().remove(&joint.a());
    joint.unjoin();
    a.jointNaubs().insert(&b, &joint);
    b.jointNaubs().insert(&a, &joint);
    joint.join(&a, &b);
}


NaubJoint* JointManager::naubJoint(Naub &a, Naub &b) {
    return a.jointNaubs().value(&b, 0);
}


CenterJoint& JointManager::joinWithCenter(Naub &naub, b2Body &center) {
    CenterJoint *joint = new CenterJoint(&world());
    joints().append(joint);
    naub.centerJoint = joint;
    joint->join(&naub, &center);
    return *joint;
}


void JointManager::unjoinFromCenter(CenterJoint &joint) {
    joint.unjoin();
    joint.naub().centerJoint = 0;
    joints().removeOne(&joint);
    delete &joint;
}


CenterJoint* JointManager::centerJoint(Naub &naub) {
    return naub.centerJoint;
}


PointerJoint& JointManager::selectNaub(Naub &naub,
                                       Pointer &pointer) {
    PointerJoint *joint = new PointerJoint(&world());
    joints().append(joint);
    naub.pointerJoints().insert(&pointer, joint);
    pointer.joints().append(joint);
    joint->join(&naub, &pointer);
    return *joint;
}


void JointManager::deselectNaub(PointerJoint &joint) {
    joint.naub().pointerJoints().remove(&joint.pointer());
    joint.pointer().joints().removeOne(&joint);
    joint.unjoin();
    joints().removeOne(&joint);
    delete &joint;
}


PointerJoint* JointManager::pointerJoint(Naub &naub, Pointer &pointer) {
    return naub.pointerJoints().value(&pointer, 0);
}


int JointManager::count() {
    return joints().count();
}


void JointManager::update() {
    foreach (Joint *joint, joints()) {
        joint->update();
    }
}


b2World& JointManager::world() { return *world_; }


QList<Joint *>& JointManager::joints() { return *joints_; }

