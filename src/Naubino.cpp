#include "Naubino.h"

#include <QMapIterator>


Naubino::Naubino() : QObject(), _center(0) {
    _world = new b2World(Vec(), true);
    _naubs = new NaubManager(&world());
    _joints = new JointManager(world());
    _pointer = new Pointer(world());

    setupCenter();
}


Naubino::~Naubino() {
    _center = 0; //cannot be deleted
    delete _pointer; _pointer = 0;
    delete _joints; _joints = 0;
    delete _naubs; _naubs = 0;
    delete _world; _world = 0;
}


Naub& Naubino::addNaub(Vec pos) {
    Naub *naub = naubs().add(pos);
    emit newNaub(*naub);
    return *naub;
}


void Naubino::removeNaub(Naub &naub) {
    naubs().remove(&naub);
}


NaubJoint& Naubino::joinNaubs(Naub &a, Naub &b) {
    NaubJoint &joint = joints().joinNaubs(a, b);
    emit newNaubJoint(joint);
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
    return joints().joinWithCenter(naub, *_center);
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
    emit mergedNaub(a);
}


void Naubino::update() {
    world().Step(0.04, 10, 10);
    world().ClearForces();
    naubs().update();
    joints().update();
}


NaubManager& Naubino::naubs() { return *_naubs; }
const NaubManager& Naubino::naubs() const { return *_naubs; }
JointManager& Naubino::joints() { return *_joints; }
const JointManager& Naubino::joints() const { return *_joints; }
b2World& Naubino::world() { return *_world; }
const b2World& Naubino::world() const { return *_world; }
b2Body& Naubino::center() { return *_center; }
const b2Body& Naubino::center() const { return *_center; }
Pointer& Naubino::pointer() { return *_pointer; }
const Pointer& Naubino::pointer() const { return *_pointer; }


void Naubino::setupCenter() {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    _center = world().CreateBody(&def);
}
