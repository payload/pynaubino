#ifndef JOINTMANAGER_H
#define JOINTMANAGER_H


#include "Prereqs.h"

#include <Box2D/Box2D.h>

#include "Naub.h"

class Joint;


class JointManager {
public:
    JointManager(b2World &world);
    ~JointManager();

    NaubJoint* joinNaubs(Naub *a, Naub *b);
    void unjoinNaubs(NaubJoint *joint);
    void rejoinNaubs(NaubJoint *joint, Naub *a, Naub *b);
    NaubJoint* naubJoint(Naub *a, Naub *b);

    CenterJoint* joinWithCenter(Naub *naub, b2Body *center);
    void unjoinFromCenter(CenterJoint *joint);
    CenterJoint* centerJoint(Naub *naub);

    PointerJoint* selectNaub(Naub *naub, Pointer *pointer);
    void deselectNaub(PointerJoint *joint);
    PointerJoint* pointerJoint(Naub *naub, Pointer *pointer);

    int count();
    void update();

    b2World& world();
    QList<Joint *>& joints();

private:
    QList<Joint *> *_joints;
    b2World *_world;
};


#endif // JOINTMANAGER_H

