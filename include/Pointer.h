#ifndef POINTER_H
#define POINTER_H


#include "Prereqs.h"

#include <QList>

#include <Box2D/Box2D.h>

#include "Vec.h"


class PointerJoint;


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
    b2World *world_;
    b2Body *body_;
    QList<PointerJoint *> *joints_;
};

#endif // POINTER_H
