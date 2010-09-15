#include "Naub.h"
#include <NaubJoint.h>
#include <PointerJoint.h>
#include <Pointer.h>

void Naub::select(Pointer *pointer) {
    PointerJoint *joint = new PointerJoint();
    emit added(joint);
    joint->join(this, pointer);
    emit joined(joint);
    joint->connect(this, SIGNAL(deselected(Pointer*)), SLOT(unjoin()));
    emit selected(pointer);
    qDebug("select");
}

void Naub::deselect(Pointer *pointer) {
    emit deselected(pointer);
}

void Naub::contact(Naub *naub) {
    NaubJoint *joint = new NaubJoint();
    emit added(joint);
    joint->join(this, naub);
    emit joined(joint);
    /*
    emit removed(naub);
    emit joined(this, naub);
    emit merged(this, naub);
    */
}

void Naub::update() {
    _pos = _body->GetPosition();
    emit changed(this);
}

Naub::Naub(b2World *world) : _world(world) {
    b2BodyDef def;
    def.type = b2_dynamicBody;
    _body = _world->CreateBody(&def);
    _color = Qt::black;
}

Naub::~Naub() {
    _world->DestroyBody(_body);
    _body = NULL;
    _world = NULL;
}
