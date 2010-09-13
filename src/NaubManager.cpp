#include "NaubManager.h"
#include <Naub.h>

void NaubManager::add(Naub *naub) {
    connect(naub, SIGNAL(remove(Naub*)), SLOT(remove(Naub*)));
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
