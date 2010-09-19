#ifndef TESTGAME_H
#define TESTGAME_H

#include <Naub.h>
#include <Naubino.h>
#include <CenterJoint.h>

void foo(Naubino &naubino) {
    Naub *n0 = new Naub();
    naubino.add(n0);
    n0->init();

    Naub *n1 = new Naub();
    naubino.add(n1);
    n1->init();

    n0->setPos(Vec(-0.4, 0));
    n1->setPos(Vec( 0.4, 0));
    n0->join(n1);
    n1->join(n0);

    b2BodyDef def;
    def.type = b2_kinematicBody;
    def.position = Vec();
    b2Body *center = naubino.world().CreateBody(&def);

    CenterJoint *j0 = new CenterJoint();
    naubino.add(j0);
    j0->init();

    CenterJoint *j1 = new CenterJoint();
    naubino.add(j1);
    j1->init();

    j0->join(n0, center);
    j1->join(n1, center);
}

#endif // TESTGAME_H
