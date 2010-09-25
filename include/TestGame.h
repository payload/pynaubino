#ifndef TESTGAME_H
#define TESTGAME_H

#include <Prereqs.h>

#include <QObject>
#include <QList>
class Naubino;
class Naub;
class Vec;

class TestGame : public QObject {
    Q_OBJECT
public:
    TestGame(Naubino &naubino);
    Naubino *_naubino;
    Naubino& naubino() const;

    Naub* addNaub();

    QList<Naub*> addNaubPair(Vec pos);
    QList<Naub*> addNaubTriple(Vec pos);
public slots:
    void foo();
};

#endif // TESTGAME_H
