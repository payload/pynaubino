#include "Simulator.h"
#include <Box2D/Dynamics/b2World.h>
#include <Vec.h>

Simulator::Simulator() : QTimer() {
    _world = new b2World(Vec(), true);
}

Simulator::~Simulator() {
    delete _world; _world = NULL;
}

void Simulator::timerEvent(QTimerEvent *e) {
    _world->Step(interval()/1000.0, 10, 10);
    _world->ClearForces();
    QTimer::timerEvent(e);
}
