#include "Popper.h"
#include "Naub.h"
#include "Naubino.h"

Popper::Popper(Naubino *naubino) : _naubino(naubino) {}

void Popper::popNaubs(QList<Naub*> *naubs) {
    foreach(Naub *naub, *naubs)
        _naubino->removeNaub(naub);
}
