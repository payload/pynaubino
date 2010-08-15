#include "Naubino.h"
#include "Naub.h"
#include "Joint.h"
#include "Pointer.h"
#include "Event.h"
#include "NaubinoContactListener.h"
#include "Cycler.h"
#include "Scorer.h"
#include "Color.h"

Naubino::Naubino(QObject *parent) :
    QObject(parent)
{
    setup();
}

//
Naub* Naubino::addNaub(Vec pos, QColor color) {
    Naub *naub = new Naub(this, pos, color);
    naubs->append(naub);
    newNaub(naub);
    return naub;
}

void Naubino::deleteNaub(Naub *naub) {
    foreach (Joint *j, naub->jointNaubs->values())
        unjoinNaubs(j);
    naubs->removeOne(naub);
    delete naub;
}
//

//
Joint* Naubino::joinNaubs(Naub *a, Naub *b) {
    Joint *joint = new Joint(this, a, b);
    a->jointNaubs->insertMulti(b, joint);
    b->jointNaubs->insertMulti(a, joint);
    newJoint(joint);
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
            joinNaubs(a, i.key());
        }
    }
    deleteNaub(b);
    mergedNaub(a);
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

    world->SetContactListener(new NaubinoContactListener(this));
    cycler = new Cycler(this);
    scorer = new Scorer(this);
    connect(cycler, SIGNAL(sccFound(QList<Naub*>*)),
            scorer, SLOT(  sccFound(QList<Naub*>*)));
}

void Naubino::setupWorld() {
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;
    world = new b2World(gravity, doSleep);
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
    qreal r = 150;
    for (float32 x = 0; x < M_PI*2; x += M_PI * 0.3)
        randomPair( Vec(qCos(x)*r, qSin(x)*r) );
}

void Naubino::randomPair(Vec pos) {
    qreal x = qrand();
    Vec add(qCos(x), qSin(x));
    add *= 50;
    Naub *n0 = addNaub(pos - add, Color::randomNaub().qcolor());
    Naub *n1 = addNaub(pos + add, Color::randomNaub().qcolor());
    joinNaubs(n0, n1);
    joinWithCenter(n0);
    joinWithCenter(n1);
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

