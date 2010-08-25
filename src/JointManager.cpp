#include "JointManager.h"

JointManager::JointManager(Naubino *naubino) :
        QObject(), naubino(naubino) {
    joints_ = new QList<Joint *>();
}

JointManager::~JointManager() {
    foreach (Joint *joint, *joints_)
        delete joint;
    delete joints_;
    joints_ = 0;
    naubino = 0;
}

const QList<Joint *>& JointManager::joints() {
    return *joints_;
}

NaubJoint& JointManager::joinNaubs(Naub &a, Naub &b) {
    NaubJoint *joint = new NaubJoint(*naubino, a, b);
    a.jointNaubs->insert(&b, joint);
    b.jointNaubs->insert(&a, joint);
    joints_->append(joint);
    newJoint(joint);
    return *joint;
}

void JointManager::remove(Joint *joint) {
    joints_->removeOne(joint);
    delete joint;
}

void JointManager::remove(NaubJoint *joint) {
    remove(joint->a, joint->b);
}

void JointManager::remove(Naub *a, Naub *b) {
    Joint *j = a->jointNaubs->take(b);
    b->jointNaubs->remove(a);
    remove(j);
}

int JointManager::count() {
    return joints_->count();
}

void JointManager::update() {
    foreach (Joint *joint, *joints_) joint->update();
}
