#include "Naubino.h"
#include "Naub.h"
#include "Joint.h"
#include "Pointer.h"
#include "Event.h"
#include "NaubinoContactListener.h"
#include "Cycler.h"
#include "Scorer.h"
#include "Color.h"
#include "Spammer.h"
#include "CenterJoint.h"

static const float32 FPS = 20;

Naubino::Naubino() :
    QObject()
{
    setup();
}

//
Naub* Naubino::addNaub(Vec pos, QColor color) {
    Naub *naub = new Naub(this, pos, color);
    naubs->append(naub);
    newNaub(naub);

    {
        b2FrictionJointDef def;
        def.Initialize(ground_body, naub->body,
                       ground_body->GetWorldCenter());
        def.maxForce = 0.01;
        def.maxTorque = 0.01;
        world->CreateJoint(&def);
    }

    return naub;
}

void Naubino::deleteNaub(Naub *naub) {
    foreach (Joint *j, naub->jointNaubs->values())
        unjoinNaubs(j);
    naubs->removeOne(naub);
    naub->deleted();
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
    joint->deleted();
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
        naub->centerJoint = new CenterJoint(world, center);
        naub->centerJoint->join(naub);
        joints->append(naub->centerJoint);
    }
}

void Naubino::unjoinFromCenter(Naub *naub) {
    naub->centerJoint->unjoin();
    delete naub->centerJoint;
    naub->centerJoint = 0;
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
    mergedNaub(*a);
}
//

//
void Naubino::select(Naub *naub, Pointer *pointer) {
    naub->selected++;

    b2MouseJointDef def;
    def.maxForce = naub->body->GetMass() * 2;
    def.frequencyHz = 20;
    def.dampingRatio = 1;
    def.bodyA = ground_body;
    def.bodyB = naub->body;
    def.target = pointer->pos();
    def.userData = pointer;

    b2MouseJoint *joint = (b2MouseJoint *)world->CreateJoint(&def);
    naub->pointerJoints->insert(pointer, joint);
    pointerJoints->append(joint);
}

void Naubino::deselect(Naub *naub, Pointer *pointer) {
    if (naub->pointerJoints->count() > 0) {
        QList<b2Joint *> list = naub->pointerJoints->values(pointer);
        for (int i = 0; i < list.count(); i++) {
            b2Joint *joint = list[i];
            world->DestroyJoint(joint);
            pointerJoints->removeOne((b2MouseJoint *)joint);
            list.removeAt(i);
        }
        naub->pointerJoints->remove(pointer);
        naub->selected--;
    }
}
//

// setups
void Naubino::setup() {
    naubs = new QList<Naub *>();
    joints = new QList<CenterJoint *>();
    events = new QList<Event *>();
    pointerJoints = new QList<b2MouseJoint *>();
    setupWorld();
    setupCenter();
    setupCalcTimer();

    b2BodyDef def;
    def.type = b2_staticBody;
    ground_body = world->CreateBody(&def);

    setupPointers();

    world->SetContactListener(new NaubinoContactListener(this));
    cycler = new Cycler(this);
    scorer = new Scorer(this);
    connect(cycler, SIGNAL(sccFound(QList<Naub*>&)),
            scorer, SLOT(  sccFound(QList<Naub*>&)));
    spammer = new Spammer(this);
    spammer->start();
}

void Naubino::setupWorld() {
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;
    world = new b2World(gravity, doSleep);
}

void Naubino::setupCenter() {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    center = world->CreateBody(&def);
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

}

void Naubino::randomPair(Vec pos) {
    qreal x = qrand();
    Vec add(qCos(x), qSin(x));
    add *= 0.2;
    Naub *n0 = addNaub(pos - add, Color::randomNaub().qcolor());
    Naub *n1 = addNaub(pos + add, Color::randomNaub().qcolor());
    joinNaubs(n0, n1);
    joinWithCenter(n0);
    joinWithCenter(n1);
}

void Naubino::start() {
    testSetting();
    calcTimer->start( 1000/FPS );
}

// public slots
void Naubino::calc() {
    QTime t;
    timeperframe = 0;
    t.start();
    foreach (CenterJoint *joint, *joints)
        joint->update();

    foreach (b2MouseJoint *joint, *pointerJoints)
        joint->SetTarget( ((Pointer*)joint->GetUserData())->pos() );

    world->Step( 1.0f/FPS, 10, 10);
    world->ClearForces();

    foreach (Event *event, *events) {
        event->handle();
        delete event;
    }
    events->clear();

    foreach (Naub *naub, *naubs)
        naub->changed();

    timeperframe += t.elapsed();
}

