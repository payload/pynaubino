#include "Naubino.h"
#include "QNaub.h"

Naubino::Naubino(QObject *parent) :
    QObject(parent)
{
}

void Naubino::start() {
    calcTimer->start( FRAMERATE * 1000 );
}

void Naubino::calc() {
    /*world->Step(B2_TIMESTEP, B2_VELITERATIONS, B2_POSITERATIONS);
    foreach (QNaub *naub, *naubs) {
        naub->adjust();
    }
    world->ClearForces();*/
}

void Naubino::setupCalcTimer() {
    calcTimer = new QTimer();
    connect(calcTimer, SIGNAL(timeout()), this, SLOT(calc()));
}
