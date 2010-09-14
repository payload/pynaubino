#include "Naub.h"
#include "NaubJoint.h"

void Naub::select() {
    emit selected();
}

void Naub::deselect() {
    emit deselected();
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
