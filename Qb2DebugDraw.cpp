#include "Qb2DebugDraw.h"

Qb2DebugDrawItem::Qb2DebugDrawItem(b2World *world) : world(world) {
    drawer = new Qb2DebugDraw();
    world->SetDebugDraw(drawer);
}

Qb2DebugDraw::Qb2DebugDraw() : b2DebugDraw() {
    SetFlags(e_shapeBit | e_jointBit | e_aabbBit | e_pairBit | e_centerOfMassBit);
}
