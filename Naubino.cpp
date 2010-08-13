#include "Naubino.h"
#include "Naub.h"

Naubino::Naubino(QObject *parent) :
    QObject(parent)
{
    setup();
    testSetting();
}

void Naubino::testSetting() {
    addNaub();
}

void Naubino::addNaub() {
    Naub *naub = new Naub(this);
    *naubs << naub;
    newNaub(naub);
    qDebug("new naub ->");
}

void Naubino::start() {
    calcTimer->start( FRAMERATE * 1000 );
}

void Naubino::calc() {
    world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
    foreach (Naub *naub, *naubs) {
        naub->update();
    }
    world->ClearForces();
}

void Naubino::setup() {
    naubs = new QList<Naub *>();
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
}
