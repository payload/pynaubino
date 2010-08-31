#include "Naub.h"

#include "QNaub.h"


Naub::Naub(b2World *world) : world_(world) {
    centerJoint_ = 0;
    qnaub_ = 0;

    color_ = Color::randomNaub();

    setupPhysics();
}


Naub::~Naub() {
    centerJoint_ = 0;
    world_ = 0;
    qnaub_ = 0;
}


void Naub::update() {
    if (qnaub_ != 0) {
        qnaub_->naubChanged();
    }
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


void Naub::setPos(const Vec& pos) { body_->SetTransform(pos, rot()); }
void Naub::setColor(const Color& color) { color_ = color; }


b2World& Naub::world() { return *world_; }
const b2World& Naub::world() const { return *world_; }
Vec Naub::pos() const { return Vec(body_->GetWorldCenter()); }
float Naub::rot() const { return body_->GetAngle(); }
float Naub::radius() const { return radius_; }
const Color& Naub::color() const { return color_; }
b2Body& Naub::body() { return *body_; }
const b2Body& Naub::body() const { return *body_; }
void Naub::setQNaub(QNaub *n) { qnaub_ = n; }
CenterJoint *Naub::centerJoint() { return centerJoint_; }
void Naub::setCenterJoint(CenterJoint *j) { centerJoint_ = j; }
QMap<Naub *, NaubJoint *>& Naub::jointNaubs() { return jointNaubs_; }
QMap<Pointer *, PointerJoint *>& Naub::pointerJoints() { return pointerJoints_; }

