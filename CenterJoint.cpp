#include "CenterJoint.h"
#include "Naub.h"

CenterJoint::CenterJoint(b2World *world, b2Body *center)
    : world(world), center_(center) {
}

b2Body* CenterJoint::center() { return center_; }
void CenterJoint::setCenter(b2Body *center) { center_ = center; }

void CenterJoint::join(Naub *naub) {
    naub_ = naub;
}

void CenterJoint::update() {
    if (naub_) {
        Vec force = center_->GetPosition() - naub_->pos();
        force *= 0.008;
        naub_->body->ApplyForce(force, naub_->pos());
    }
}

void CenterJoint::unjoin() {
    naub_ = 0;
}
