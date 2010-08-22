#include <QtCore/QString>
#include <QtTest/QtTest>

#include <Naubino.h>
#include <Color.h>
#include <Vec.h>

#include "NaubManager.h"
#include "JointManager.h"

class tst_Naubino : public QObject
{
    Q_OBJECT

public:
    tst_Naubino();

    Naubino *naubino;

private Q_SLOTS:
    void init();
    void cleanup();
    void addDeleteNaub();
    void joinUnjoinNaubs();
};

tst_Naubino::tst_Naubino()
{
}

void tst_Naubino::init() {
    naubino = new Naubino();
}

void tst_Naubino::cleanup() {
    delete naubino;
}

void tst_Naubino::addDeleteNaub()
{
    Naub *n0;
    int c = naubino->joints->count();
    n0 = naubino->naubs->add(Vec(10, 10));
    QVERIFY(naubino->naubs->count() == c+1);
    naubino->naubs->remove(n0);
    QVERIFY(naubino->naubs->count() == c);
}

void tst_Naubino::joinUnjoinNaubs()
{
    Naub *n0, *n1;
    n0 = naubino->naubs->add(Vec(-10, 0));
    n1 = naubino->naubs->add(Vec( 10, 0));
    int c = naubino->joints->count();
    NaubJoint *j = naubino->joints->joinNaubs(n0, n1);
    QVERIFY(naubino->joints->count() == c+1);
    naubino->joints->remove(j);
    QVERIFY(naubino->joints->count() == c);
}

QTEST_APPLESS_MAIN(tst_Naubino);

#include "tst_Naubino.moc"
