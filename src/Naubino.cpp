#include "Naubino.h"

#include <QMapIterator>


Naubino::Naubino() : QObject() {
    world_ = new b2World(Vec(), true);
    naubs_ = new NaubManager(world());
    joints_ = new JointManager(world());
    setupCenter();
    setupPointer();
}


Naubino::~Naubino() {
    delete world_; world_ = 0;
    delete naubs_; naubs_ = 0;
    delete joints_; joints_ = 0;
    center_ = 0;
    pointer_ = 0;
}


Naub& Naubino::addNaub(Vec pos) {
    Naub &naub = naubs().add(pos);
    newNaub(naub);
    return naub;
}


void Naubino::removeNaub(Naub &naub) {
    naubs().remove(naub);
}


NaubJoint& Naubino::joinNaubs(Naub &a, Naub &b) {
    NaubJoint &joint = joints().joinNaubs(a, b);
    newNaubJoint(joint);
    return joint;
}


void Naubino::unjoinNaubs(NaubJoint &joint) {
    joints().unjoinNaubs(joint);
}


void Naubino::rejoinNaubs(NaubJoint &joint, Naub &a, Naub &b) {
    joints().rejoinNaubs(joint, a, b);
}


NaubJoint* Naubino::naubJoint(Naub &a, Naub &b) {
    return joints().naubJoint(a, b);
}


CenterJoint& Naubino::joinWithCenter(Naub &naub) {
    return joints().joinWithCenter(naub, *center_);
}


void Naubino::unjoinFromCenter(CenterJoint &joint) {
    unjoinFromCenter(joint);
}


CenterJoint* Naubino::centerJoint(Naub &naub) {
    return joints().centerJoint(naub);
}


PointerJoint& Naubino::selectNaub(Naub &naub) {
    return joints().selectNaub(naub, pointer());
}


void Naubino::deselectNaub(Naub &naub) {
    PointerJoint *joint = pointerJoint(naub);
    if (joint != 0) joints().deselectNaub(*joint);
}


PointerJoint* Naubino::pointerJoint(Naub &naub) {
    return joints().pointerJoint(naub, pointer());
}


void Naubino::mergeNaubs(Naub &a, Naub &b) {
    QMapIterator<Naub *, NaubJoint *> i(b.jointNaubs());
    while (i.hasNext()) {
        i.next();
        if (&a == i.key())
            unjoinNaubs(*i.value());
        else
            rejoinNaubs(*i.value(), a, *i.key());
    }
    removeNaub(b);
    mergedNaub(a);
}


void Naubino::update() {
    world().Step(0.04, 10, 10);
    world().ClearForces();
    naubs().update();
    joints().update();
}


void Naubino::setupCenter() {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    center_ = world().CreateBody(&def);
}


void Naubino::setupPointer() {
    pointer_ = new Pointer(world());
}


NaubManager& Naubino::naubs() { return *naubs_; }
JointManager& Naubino::joints() { return *joints_; }
b2World& Naubino::world() { return *world_; }
b2Body& Naubino::center() { return *center_; }
Pointer& Naubino::pointer() { return *pointer_; }

