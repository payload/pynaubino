#include "Naub.h"

Naub::Naub(b2World &world)
    : world_(&world) {
    jointNaubs_ = new QMap<Naub *, NaubJoint *>();
    pointerJoints_ = new QMap<Pointer *, PointerJoint *>();
    centerJoint = 0;

    color_ = Color::randomNaub();

    setupPhysics();
}

Naub::~Naub() {
    delete jointNaubs_; jointNaubs_ = 0;
    delete pointerJoints_; pointerJoints_ = 0;
    centerJoint = 0;
    world_ = 0;
}

void Naub::update() {

}

void Naub::setupPhysics() {
    radius_ = 0.15f;
    friction_ = 0;
    density_ = 1;
    restitution_ = 0.4f;

    b2BodyDef def;
    def.type = b2_dynamicBody;
    b2Body *body = world().CreateBody(&def);
    body->SetUserData(this);
    b2CircleShape shape;
    shape.m_radius = radius_;
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.friction = friction_;
    fixtureDef.restitution = restitution_;
    fixtureDef.density = density_;
    b2Fixture *fix = body->CreateFixture(&fixtureDef);
    fix->SetUserData(this);

    body_ = body;
}

void Naub::setPos(Vec pos) { body_->SetTransform(pos, rot()); }
void Naub::setColor(Color color) { color_ = color; }

b2World& Naub::world() { return *world_; }
Vec Naub::pos() { return Vec(body_->GetWorldCenter()); }
float32 Naub::rot() { return body_->GetAngle(); }
float32 Naub::radius() { return radius_; }
Color Naub::color() { return color_; }
QMap<Naub *, NaubJoint *>& Naub::jointNaubs() { return *jointNaubs_; }
QMap<Pointer *, PointerJoint *>& Naub::pointerJoints() { return *pointerJoints_; }
