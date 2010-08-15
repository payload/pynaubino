#include "Scorer.h"
#include "Naubino.h"
#include "Naub.h"

Scorer::Scorer(Naubino *naubino, QObject *parent) :
        QObject(parent), naubino(naubino) {}

void Scorer::sccFound(QList<Naub *> *scc) {
    foreach (Naub *naub, *scc) {
        naubino->deleteNaub(naub);
    }
}
