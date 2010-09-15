#include "Naub.h"
#include <NaubJoint.h>
#include <PointerJoint.h>
#include <Pointer.h>

void Naub::select(Pointer *pointer) {
    PointerJoint *joint = new PointerJoint();
    emit added(joint);
    joint->join(this, pointer);
    emit joined(joint);
    _isSelected = true;
    emit selected(pointer);
    joint->connect(this, SIGNAL(deselected(Pointer*)), SLOT(unjoin()));
}

void Naub::deselect(Pointer *pointer) {
    if (!_isSelected) return;
    _isSelected = false;
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
    b2CircleShape shape;
    shape.m_radius = 0.15;
    _body->CreateFixture(&shape, 1);
    _color = Qt::black;
    _isSelected = false;
}

Naub::~Naub() {
    _world->DestroyBody(_body);
    _body = NULL;
    _world = NULL;
}
