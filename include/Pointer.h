#ifndef POINTER_H
#define POINTER_H


#include "Prereqs.h"

#include <QList>

#include <Box2D/Box2D.h>

#include "Vec.h"


class PointerJoint;


class Pointer {
public:
    Pointer(b2World &world);
    ~Pointer();
    void setPos(Vec pos);
    Vec pos();
    b2World& world();
    b2Body& body();
    QList<PointerJoint *>& joints();

private:
    b2World *_world;
    b2Body *_body;
    QList<PointerJoint *> *_joints;
};


#endif // POINTER_H

