#include "Naubino.h"
#include "Naub.h"
#include "Joint.h"

Naubino::Naubino(QObject *parent) :
    QObject(parent)
{
    setup();
}

void Naubino::testSetting() {
    qreal r = 150;
    for (float32 x = 0; x < M_PI*2; x += M_PI * 1)
        randomPair( Vec(qCos(x)*r, qSin(x)*r) );
}

void Naubino::randomPair(Vec pos) {
    qreal x = qrand();
    Vec add(qCos(x), qSin(x));
    add *= 50;
    Naub *n0 = addNaub(pos - add);
    Naub *n1 = addNaub(pos + add);
    Joint *j = joinNaubs(n0, n1);
}

Naub* Naubino::addNaub(Vec pos) {
    Naub *naub = new Naub(this, pos);
    joinWithCenter(naub);
    *naubs << naub;
    newNaub(naub);
    return naub;
}

Joint* Naubino::joinNaubs(Naub *a, Naub *b) {
    Joint *joint = a->join(b);
    *joints << joint;
    newJoint(joint);
    return joint;
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

void Naubino::joinWithCenter(Naub *naub) {
    centerJointDef->bodyA = naub->body;
    centerJointDef->localAnchorB = center->GetLocalCenter();
    world->CreateJoint(centerJointDef);
}

void Naubino::start() {
    testSetting();
    calcTimer->start( FRAMERATE * 1000 );
}

void Naubino::calc() {    
    world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
    foreach (Naub *naub, *naubs) {
        naub->update();
    }
    foreach (Joint *joint, *joints) {
        joint->update();
    }
    world->ClearForces();
}

void Naubino::setup() {
    naubs = new QList<Naub *>();
    joints = new QList<Joint *>();
    setupWorld();
    setupCalcTimer();
}

void Naubino::setupCalcTimer() {
    calcTimer = new QTimer();
    connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}

void Naubino::setupWorld() {
    b2Vec2 gravity(0.0f, 0.0f);
    bool doSleep = true;
    world = new b2World(gravity, doSleep);

    setupCenter();
}
