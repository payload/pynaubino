#ifndef TESTGAME_H
#define TESTGAME_H

#include <Naub.h>
#include <Naubino.h>

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
}

#endif // TESTGAME_H
