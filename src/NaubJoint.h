#ifndef NAUBJOINT_H
#define NAUBJOINT_H

#include <Box2D.h>

class Naub;
class QJoint;
class Naubino;

class NaubJoint
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

    void changed();
    void deleted();

    void setup();

    Naub* other(Naub *x) { return a == x ? b : a; }
};

#endif // NAUBJOINT_H
