#include <QtCore/QString>
#include <QtTest/QtTest>

#include <Naubino.h>
#include <Color.h>
#include <Vec.h>

#include "NaubManager.h"
#include "JointManager.h"
#include "Joints.h"

class tst_Naubino : public QObject
{
    Q_OBJECT
private slots:
    void init();
    void cleanup();
    void addDeleteNaub();
    void joinUnjoinNaubs();
    void mergeNaubs();

    void initTestCase(){}
    void cleanupTestCase(){}
    void initTestCase_data(){}
    void addDeleteNaub_data(){}
    void joinUnjoinNaubs_data(){}
    void mergeNaubs_data(){}
private:
    Naubino& naubino();
    Naubino *naubino_;
};

Naubino& tst_Naubino::naubino() { return *naubino_; }

void tst_Naubino::init() {
    naubino_ = new Naubino();
}

void tst_Naubino::cleanup() {
    delete naubino_; naubino_ = 0;
}

void tst_Naubino::addDeleteNaub()
{
    int c = naubino().naubs().count();
    Naub *n0 = naubino().addNaub(Vec(10, 10));
    QVERIFY(naubino().naubs().count() == c+1);
    naubino().removeNaub(n0);
    QVERIFY(naubino().naubs().count() == c);
}

void tst_Naubino::joinUnjoinNaubs()
{
    Naub *n0 = naubino().addNaub(Vec(-10, 0));
    Naub *n1 = naubino().addNaub(Vec( 10, 0));
    int c = naubino().joints().count();
    NaubJoint *j = naubino().joinNaubs(n0, n1);
    QVERIFY(naubino().joints().count() == c+1);
    naubino().unjoinNaubs(j);
    QVERIFY(naubino().joints().count() == c);
}

void tst_Naubino::mergeNaubs() {
    Naub *n0 = naubino().addNaub(Vec(-10, -10));
    Naub *n1 = naubino().addNaub(Vec( 10, -10));
    Naub *n2 = naubino().addNaub(Vec(-10,  10));
    Naub *n3 = naubino().addNaub(Vec( 10,  10));
    Naub *n4 = naubino().addNaub(Vec(-10,  20));
    Naub *n5 = naubino().addNaub(Vec( 10,  20));

    NaubJoint *j01 = naubino().joinNaubs(n0, n1);
    NaubJoint *j23 = naubino().joinNaubs(n2, n3);
    NaubJoint *j45 = naubino().joinNaubs(n4, n5);

    naubino().mergeNaubs(n1, n2);
    naubino().mergeNaubs(n3, n4);
    naubino().mergeNaubs(n5, n0);

    QVERIFY(&j01->a() == n5);
    QVERIFY(&j01->b() == n1);
    QVERIFY(&j23->a() == n1);
    QVERIFY(&j23->b() == n3);
    QVERIFY(&j45->a() == n3);
    QVERIFY(&j45->b() == n5);
}

QTEST_APPLESS_MAIN(tst_Naubino);

#include "tst_Naubino.moc"
