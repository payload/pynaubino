#include "Pointer.h"
#include "Joints.h"

Pointer::Pointer(b2World &world) : world_(&world) {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    body_ = this->world().CreateBody(&def);
    joints_ = new QList<PointerJoint *>();
}

Pointer::~Pointer() {
    world().DestroyBody(body_);
    body_ = 0;
    world_ = 0;
    delete joints_; joints_ = 0;
}

void Pointer::setPos(Vec pos) {
    body_->SetTransform(pos, 0);
}

Vec Pointer::pos() {
    return Vec(body_->GetWorldCenter());
}

b2World& Pointer::world() { return *world_; }
QList<PointerJoint*>& Pointer::joints() { return *joints_; }
