#include "NaubManager.h"

void NaubManager::add(Naub *naub) {
    emit added(naub);
}

void NaubManager::remove(Naub *naub) {
    emit remove(naub);
}

void NaubManager::join(Naub *a, Naub *b) {
    emit joined(a, b);
}

void NaubManager::merge(Naub *a, Naub *b) {
    emit merged(a, b);
}
