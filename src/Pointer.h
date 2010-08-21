#ifndef POINTER_H
#define POINTER_H

#include <Box2D.h>

#include "Vec.h"

class Naubino;

class Pointer
{
public:
    Pointer(Naubino *naubino);
    Naubino *naubino;
    b2Body *body;
    void setPos(Vec pos);
    Vec pos();
};

#endif // POINTER_H
