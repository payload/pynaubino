#include "Qb2DebugDraw.h"

Qb2DebugDrawItem::Qb2DebugDrawItem(b2World *world) : world(world) {
    drawer = new Qb2DebugDraw();
    world->SetDebugDraw(drawer);
    startTimer(50);
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
