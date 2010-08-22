#ifndef NAUBJOINT_H
#define NAUBJOINT_H

#include <Box2D.h>

class Naub;
class QJoint;
class Naubino;

#include "Joint.h"

class NaubJoint : public Joint
{
public:
    NaubJoint(Naubino *naubino, Naub *a, Naub *b);
    ~NaubJoint();

    Naubino *naubino;
    Naub *a;
    Naub *b;
    QJoint *qjoint;
    float32 frequencyHz;
    float32 dampingRatio;
    float32 length;
    b2Joint *joint;

    void update();
    void deleted();

    void setup();

    Naub* other(Naub *x) { return a == x ? b : a; }
};

#endif // NAUBJOINT_H
