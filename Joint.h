#ifndef JOINT_H
#define JOINT_H

#include <Box2D.h>

class Naub;
class QJoint;

class Joint
{
public:
    Joint(Naub *a, Naub *b);
    Naub *a;
    Naub *b;
    float32 frequencyHz;
    float32 dampingRatio;
    float32 length;
    QJoint *qjoint;
    void update();
};

#endif // JOINT_H
