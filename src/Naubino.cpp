#include "Naubino.h"
#include <Simulator.h>
#include <Naub.h>
#include <NaubJoint.h>
#include <Box2D/Dynamics/b2World.h>

Naubino::Naubino(QObject *parent) : QObject(parent) {
    sim = new Simulator(this);
    sim->start(50);
}

b2World& Naubino::world() const {
    return sim->world();
}

void Naubino::add(Joint *joint) {
    connect(joint,
            SIGNAL(removed(Joint*)),
            SLOT(remove(Joint*)));
    emit added(joint);
}

void Naubino::add(Naub *naub) {
    naub->setNaubino(*this);
    connect(naub,
            SIGNAL(removed(Naub*)),
            SLOT(remove(Naub*)));
    connect(naub,
            SIGNAL(added(Joint*)),
            SLOT(add(Joint*)));
    emit added(naub);
}

void Naubino::remove(Naub *obj) {
    obj->deleteLater();
}

void Naubino::remove(Joint *obj) {
    obj->deleteLater();
}
