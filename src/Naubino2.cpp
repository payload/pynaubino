#include "Naubino2.h"

Naubino2::Naubino2() :
    QObject()
{
    naubs_ = new NaubManager();
    joints_ = new JointManager();
}

Naubino2::~Naubino2() {
    delete naubs_; naubs_ = 0;
    delete joints_; joints_ = 0;
}

Naub& Naubino2::addNaub(Vec pos) {
    return naubs_->add(pos);
}

void Naubino2::removeNaub(Naub &naub) {
    naubs_->remove(naub);
}

NaubJoint& Naubino2::joinNaubs(Naub &a, Naub &b) {
    return joints_->joinNaubs(a, b);
}

void Naubino2::unjoinNaubs(NaubJoint &joint) {
    joints_->unjoinNaubs(joint);
}

NaubJoint* Naubino2::naubJoint(Naub &a, Naub &b) {
    return joints_->naubJoint(a, b);
}

CenterJoint& Naubino2::joinWithCenter(Naub &naub) {
    return joints_->joinWithCenter(naub);
}

void Naubino2::unjoinFromCenter(CenterJoint &joint) {
    unjoinFromCenter(joint);
}

CenterJoint* Naubino2::centerJoint(Naub &naub) {
    return joints_->centerJoint(naub);
}

PointerJoint& Naubino2::selectNaub(Naub &naub) {
    return joints_->selectNaub(naub);
}

void Naubino2::deselectNaub(Naub &naub) {
    joints_->deselectNaub(naub);
}

PointerJoint* Naubino2::pointerJoint(Naub &naub) {
    return joints_->pointerJoint(naub);
}

void Naubino2::mergeNaubs(Naub &a, Naub &b) {
    QMapIterator<Naub *, NaubJoint *> i(*b.jointNaubs);
    while (i.hasNext()) {
        i.next();
        if (&a == i.key())
            unjoinNaubs(i.value());
        else
            rejoin(*i.value(), a, *(i.key()));
    }
    removeNaub(b);
    mergedNaub(a);
}

void Naubino2::rejoin(NaubJoint &joint, Naub &a, Naub &b) {
    joint.rejoin(a, b);
}
