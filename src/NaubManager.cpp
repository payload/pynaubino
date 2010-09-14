#include "NaubManager.h"
#include <Naub.h>

void NaubManager::add(Naub *naub) {
    connect(naub, SIGNAL(removed(Naub*)), SLOT(remove(Naub*)));
    naub->connect(this, SIGNAL(updated()), SLOT(update()));
    emit added(naub);
}

void NaubManager::remove(Naub *naub) {
    emit removed(naub);
}

void NaubManager::join(Naub *a, Naub *b) {
    emit joined(a, b);
}

void NaubManager::merge(Naub *a, Naub *b) {
    emit merged(a, b);
}

void NaubManager::update() {
    emit updated();
}
