#include "NaubManager.h"
#include "Naub.h"
#include "Color.h"
#include "Vec.h"

NaubManager::NaubManager(Naubino *naubino) :
        QObject(), naubino(naubino) {
    naubs_ = new QList<Naub *>();
}

NaubManager::~NaubManager() {
    foreach (Naub *naub, *naubs_)
        delete naub;
    delete naubs_;
    naubs_ = 0;
    naubino = 0;
}

const QList<Naub *>& NaubManager::naubs() {
    return *naubs_;
}

Naub* NaubManager::add(Vec pos) {
    return add(pos, Color::randomNaub().qcolor());
}

Naub* NaubManager::add(Vec pos, QColor color) {
    Naub *naub = new Naub(naubino, pos, color);
    naubs_->append(naub);
    newNaub(naub);
    return naub;
}

void NaubManager::remove(Naub *naub) {
    naubs_->removeOne(naub);
    delete naub;
}

int NaubManager::count() {
    return naubs_->count();
}
