#include <Prereqs.h>

#include "TestGame.h"
#include <Naub.h>
#include <Naubino.h>
#include <CenterJoint.h>
#include <QList>
#include <Vec.h>
#include <Color.h>

TestGame::TestGame(Naubino &naubino) : _naubino(&naubino) {}

Naubino& TestGame::naubino() const { return *_naubino; }

Naub* TestGame::addNaub() {
    Naub *n = new Naub();
    naubino().add(n);
    n->init();

    CenterJoint *j = new CenterJoint();
    naubino().add(j);
    j->init();
    j->join(n, naubino().center);

    return n;
}

QList<Naub*> TestGame::addNaubPair(Vec pos) {
    Naub *n0 = addNaub();
    Naub *n1 = addNaub();
    Vec v = Vec(0.4, 0).rotate( 2*M_PI*drand() );
    n0->setPos(-v + pos);
    n1->setPos( v + pos);
    n0->join(n1);
    QList<Naub*> naubs;
    naubs.append(n0);
    naubs.append(n1);
    return naubs;
}

QList<Naub*> TestGame::addNaubTriple(Vec pos) {
    Naub *n0 = addNaub();
    Naub *n1 = addNaub();
    Naub *n2 = addNaub();
    Vec v = Vec(0.8, 0).rotate( 2*M_PI*drand() );
    n0->setPos(-v + pos);
    n1->setPos(     pos);
    n2->setPos( v + pos);
    n0->join(n1);
    n1->join(n2);
    QList<Naub*> naubs;
    naubs.append(n0);
    naubs.append(n1);
    naubs.append(n2);
    return naubs;
}

void TestGame::foo() {
    Vec v = Vec(2, 0);
    QList<Naub*> naubs;
    naubs.append(addNaubTriple(-v));
    naubs.append(addNaubTriple( v));

    foreach (Naub *naub, naubs)
        naub->setColor(Qt::black);

    naubs[0]->setColor(Qt::red);
    naubs[3]->setColor(Qt::red);
    naubs[2]->setColor(Qt::blue);
    naubs[4]->setColor(Qt::blue);
}
