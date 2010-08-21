#include <QtCore/QString>
#include <QtTest/QtTest>

#include <Naubino.h>

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
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(tst_Naubino);

#include "tst_Naubino.moc"
