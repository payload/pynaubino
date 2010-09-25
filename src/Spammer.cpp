#include "Spammer.h"
#include "Prereqs.h"
#include <Naubino.h>
#include <CenterJoint.h>
#include <Naub.h>
#include <Box2D/Dynamics/b2Body.h>

Spammer::Spammer(Naubino &naubino) : QTimer(&naubino), _naubino(&naubino) {
}

void Spammer::timerEvent(QTimerEvent *e) {
    Naubino &naubino = *_naubino;

    Naub *n0 = new Naub();
    naubino.add(n0);
    n0->init();

    Naub *n1 = new Naub();
    naubino.add(n1);
    n1->init();

    Vec a = Vec(-0.4, 0).rotate(2*M_PI*drand());
    Vec b = Vec( 0.4, 0).rotate(2*M_PI*drand());
    Vec x = Vec(2, 0).rotate(2*M_PI*drand());

    n0->setPos(x+a);
    n1->setPos(x+b);
    n0->join(n1);
    n1->join(n0);

    CenterJoint *j0 = new CenterJoint();
    naubino.add(j0);
    j0->init();

    CenterJoint *j1 = new CenterJoint();
    naubino.add(j1);
    j1->init();

    j0->join(n0, naubino.center);
    j1->join(n1, naubino.center);

    QTimer::timerEvent(e);
}
