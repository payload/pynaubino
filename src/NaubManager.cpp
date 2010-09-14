#include "NaubManager.h"
#include <Naub.h>
#include <Joint.h>

void NaubManager::add(Naub *naub) {
    connect(naub, SIGNAL(removed(Naub*)), SLOT(remove(Naub*)));
    connect(naub, SIGNAL(joined(Joint*)), SLOT(join(Joint*)));
    connect(naub, SIGNAL(added(Joint*)), SIGNAL(added(Joint*)));
    naub->connect(this, SIGNAL(updated()), SLOT(update()));
    emit added(naub);
}

void NaubManager::remove(Naub *naub) {
    emit removed(naub);
}

void NaubManager::join(Joint *joint) {
    emit joined(joint);
}

void NaubManager::merge(Naub *a, Naub *b) {
    emit merged(a, b);
}

void NaubManager::update() {
    emit updated();
}
