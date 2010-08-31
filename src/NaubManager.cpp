#include "NaubManager.h"


NaubManager::NaubManager(b2World *world) : world_(world) {
}


NaubManager::~NaubManager() {
    world_ = 0;
}


Naub* NaubManager::add(const Vec& pos) {
    return add(pos, Color::randomNaub());
}


Naub* NaubManager::add(const Vec& pos, const Color& color) {
    Naub *naub = new Naub(*world_);
    Q_ASSERT(naubs_.contains(naub) == false);

    naub->setPos(pos);
    naub->setColor(color);
    naubs_.insert(naub);

    return naub;
}


void NaubManager::remove(Naub *naub) {
    naubs_.remove(naub);
    delete naub;
}


int NaubManager::count() const { return naubs_.count(); }


void NaubManager::update() {
    foreach (Naub *naub, naubs_) {
        naub->update();
    }
}

