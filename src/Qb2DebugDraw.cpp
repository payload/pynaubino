#include "Qb2DebugDraw.h"

Qb2DebugDrawItem::Qb2DebugDrawItem(b2World *world) : _world(world) {
    _drawer = new Qb2DebugDraw();
    if (false) {
        _world->SetDebugDraw(_drawer);
        startTimer(50);
    }
}

Qb2DebugDrawItem::~Qb2DebugDrawItem() {
    delete _drawer;
    _drawer = NULL;
}


void Qb2DebugDrawItem::timerEvent(QTimerEvent *event) {
    Q_UNUSED(event);
    update();
}


Qb2DebugDraw::Qb2DebugDraw() : b2DebugDraw() {
    SetFlags( e_shapeBit
            | e_jointBit
            //| e_aabbBit
            | e_pairBit
            | e_centerOfMassBit);
}

