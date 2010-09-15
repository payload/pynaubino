#include "Pointer.h"
#include <Vec.h>
#include <Box2D/Dynamics/b2Body.h>
#include <Box2D/Dynamics/b2World.h>

Pointer::Pointer(b2World *world, QObject *parent)
    : QObject(parent), _world(world) {
    b2BodyDef def;
    def.type = b2_kinematicBody;
    _body = _world->CreateBody(&def);
}

void Pointer::setPos(const Vec &pos) {
    _body->SetTransform(pos, 0);
}
