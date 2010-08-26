#include "NaubManager.h"

NaubManager::NaubManager(b2World &world)
    : world_(&world) {
    naubs_ = new QList<Naub *>();
}

NaubManager::~NaubManager() {
    foreach (Naub *naub, *naubs_)
        delete naub;
    delete naubs_;
    naubs_ = 0;
    world_ = 0;
}

Naub& NaubManager::add(Vec pos) {
    return add(pos, Color::randomNaub());
}

Naub& NaubManager::add(Vec pos, Color color) {
    Naub *naub = new Naub(world());
    naubs().append(naub);
    naub->setPos(pos);
    naub->setColor(color);
    return *naub;
}

void NaubManager::remove(Naub &naub) {
    naubs().removeOne(&naub);
    delete &naub;
}

int NaubManager::count() {
    return naubs().count();
}

void NaubManager::update() {
    foreach (Naub *naub, naubs()) naub->update();
}

b2World& NaubManager::world() { return *world_; }
QList<Naub *>& NaubManager::naubs() { return *naubs_; }
