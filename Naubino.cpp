#include "Naubino.h"
#include "Naub.h"
#include "Joint.h"
#include "Pointer.h"
#include "Event.h"
#include "NaubinoContactListener.h"

Naubino::Naubino(QObject *parent) :
    QObject(parent)
{
    setup();
}

//
Naub* Naubino::addNaub(Vec pos, QColor color) {
    Naub *naub = new Naub(this, pos, color);
    naubs->append(naub);
    return naub;
}

void Naubino::deleteNaub(Naub *naub) {
    naubs->removeOne(naub);
    delete naub;
}
//

//
Joint* Naubino::joinNaubs(Naub *a, Naub *b) {
    Joint *joint = new Joint(this, a, b);
    a->jointNaubs->insertMulti(b, joint);
    b->jointNaubs->insertMulti(a, joint);
    return joint;
}

void Naubino::unjoinNaubs(Naub *a, Naub *b) {
    a->jointNaubs->remove(b);
    Joint *joint = b->jointNaubs->take(a);
    delete joint;
}

void Naubino::unjoinNaubs(Joint *j) {
    j->a->jointNaubs->remove(j->b);
    j->b->jointNaubs->remove(j->a);
    delete j;
}
//

//
void Naubino::joinWithCenter(Naub *naub) {
    if (naub->centerJoint == NULL) {
        centerJointDef->bodyA = naub->body;
        centerJointDef->localAnchorA = naub->body->GetLocalCenter();
        naub->centerJoint = world->CreateJoint(centerJointDef);
    }
}

void Naubino::unjoinFromCenter(Naub *naub) {
    world->DestroyJoint(naub->centerJoint);
    naub->centerJoint = NULL;
}
//

//
void Naubino::mergeNaubs(Naub *a, Naub *b) {
    QMapIterator<Naub *, Joint *> i(*b->jointNaubs);
    while (i.hasNext()) {
        i.next();
        unjoinNaubs(i.value());
        if (a != i.key()) {
            newJoint(joinNaubs(a, i.key()));
        }
    }
    deleteNaub(b);
}
//

//
void Naubino::select(Naub *naub, Pointer *pointer) {
    naub->selected++;
    b2DistanceJointDef def;
    def.frequencyHz = 0.5f;
    def.dampingRatio = 0.1f;
    def.length = 0.0f;
    def.bodyA = naub->body;
    def.bodyB = pointer->body;
    def.localAnchorA = naub->body->GetLocalCenter();
    def.localAnchorB = pointer->body->GetLocalCenter();
    def.collideConnected = false;
    naub->pointerJoints->insert(
            pointer,
            world->CreateJoint(&def));
}

void Naubino::deselect(Naub *naub, Pointer *pointer) {
    QList<b2Joint *> list = naub->pointerJoints->values(pointer);
    for (int i = 0; i < list.count(); i++) {
        b2Joint *joint = list[i];
        world->DestroyJoint(joint);
        list.removeAt(i);
    }
    naub->pointerJoints->remove(pointer);
    naub->selected--;
}
//

// setups
void Naubino::setup() {
    naubs = new QList<Naub *>();
    events = new QList<Event *>();
    setupWorld();
    setupCenter();
    setupCalcTimer();
    setupPointers();
}

void Naubino::setupWorld() {
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;
    world = new b2World(gravity, doSleep);
    world->SetContactListener(new NaubinoContactListener(this));
}

void Naubino::setupCenter() {
    b2BodyDef centerDef;
    center = world->CreateBody(&centerDef);

    centerJointDef = new b2DistanceJointDef();
    centerJointDef->bodyB = center;
    centerJointDef->localAnchorB = center->GetLocalCenter();
    centerJointDef->collideConnected = false;
    centerJointDef->frequencyHz = 0.1f;
    centerJointDef->dampingRatio = 0.6f;
    centerJointDef->length = 0.0f;
}

void Naubino::setupCalcTimer() {
    calcTimer = new QTimer();
    connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}

void Naubino::setupPointers() {
    pointers = new QList<Pointer *>();
    Pointer *pointer = new Pointer(this);
    b2BodyDef def;
    def.type = b2_kinematicBody;
    pointer->body = world->CreateBody(&def);
    pointers->append(pointer);
}
// setups ^^

void Naubino::testSetting() {
    /*
    qreal r = 150;
    for (float32 x = 0; x < M_PI*2; x += M_PI * 1)
        randomPair( Vec(qCos(x)*r, qSin(x)*r) );
    */
    Vec pos(-100, -100);
    Naub *n0 = addNaub(pos + Vec( 0,  0), Qt::red);
    Naub *n1 = addNaub(pos + Vec(40,  0), Qt::cyan);
    Naub *n2 = addNaub(pos + Vec(40, 80), Qt::red);
    Naub *n3 = addNaub(pos + Vec(40, 40), Qt::cyan);
    Joint *j0 = joinNaubs(n0, n1);
    Joint *j1 = joinNaubs(n2, n3);

    joinWithCenter(n0);
    joinWithCenter(n1);
    joinWithCenter(n2);
    joinWithCenter(n3);

    qreal imp = 1000.0f;
    n0->body->ApplyLinearImpulse(imp * Vec::rand(), Vec());
    n0->body->ApplyLinearImpulse(imp * Vec::rand(), Vec());
    n0->body->ApplyLinearImpulse(imp * Vec::rand(), Vec());
    n0->body->ApplyLinearImpulse(imp * Vec::rand(), Vec());

    newNaub(n0);
    newNaub(n1);
    newNaub(n2);
    newNaub(n3);
    newJoint(j0);
    newJoint(j1);
}

void Naubino::randomPair(Vec pos) {
    Q_UNUSED(pos);
    /*
    qreal x = qrand();
    Vec add(qCos(x), qSin(x));
    add *= 50;
    Naub *n0 = addNaub(pos - add);
    Naub *n1 = addNaub(pos + add);
    joinNaubs(n0, n1);*/
}

void Naubino::start() {
    testSetting();
    calcTimer->start( FRAMERATE * 1000 );
}

// public slots
void Naubino::calc() {
    events->clear();
    world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
    foreach (Event *event, *events) event->handle();
    foreach (Naub *naub, *naubs) naub->changed();
    world->ClearForces();
}

