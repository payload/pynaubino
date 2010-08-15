#ifndef JOINT_H
#define JOINT_H

#include <Box2D.h>

class Naub;
class QJoint;
class Naubino;

class Joint
{
public:
    Joint(Naubino *naubino, Naub *a, Naub *b);
    ~Joint();

    Naubino *naubino;
    Naub *a;
    Naub *b;
    QJoint *qjoint;
    float32 frequencyHz;
    float32 dampingRatio;
    float32 length;
    b2Joint *joint;

    void changed();
    void setup();

    Naub* other(Naub *x) { return a == x ? b : a; }
};

#endif // JOINT_H
