#include "NaubManager.h"

#include "Naubino.h"

NaubManager::NaubManager(Naubino *naubino) : _naubino(naubino),
        _world(&naubino->world()) {
}


NaubManager::~NaubManager() {
    foreach (Naub* naub, _naubs) {
        delete naub;
    }
    _world = 0;
}


Naub* NaubManager::add(const Vec& pos) {
    return add(pos, Color::randomNaub());
}


Naub* NaubManager::add(const Vec& pos, const Color& color) {
    Naub *naub = new Naub(_naubino);
    Q_ASSERT(_naubs.contains(naub) == false);

    naub->setPos(pos);
    naub->setColor(color);
    _naubs.insert(naub);

    return naub;
}


void NaubManager::remove(Naub *naub) {
    _naubs.remove(naub);
    naub->setDeleted(true);
}


int NaubManager::count() const { return _naubs.count(); }


void NaubManager::update() {
    foreach (Naub *naub, _naubs) {
        naub->update();
    }
}

