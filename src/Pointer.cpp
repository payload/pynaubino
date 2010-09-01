#include "Pointer.h"

#include "Joints.h"


Pointer::Pointer(b2World &world) : _world(&world) {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    _body = this->world().CreateBody(&def);
    _joints = new QList<PointerJoint *>();
}


Pointer::~Pointer() {
    world().DestroyBody(_body);
    _body = 0;
    _world = 0;
    delete _joints; _joints = 0;
}


void Pointer::setPos(Vec pos) {
    _body->SetTransform(pos, 0);
}


Vec Pointer::pos() {
    return Vec(_body->GetWorldCenter());
}


b2World& Pointer::world() { return *_world; }
b2Body& Pointer::body() { return *_body; }
QList<PointerJoint*>& Pointer::joints() { return *_joints; }

