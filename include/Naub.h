#ifndef NAUB_H
#define NAUB_H

#include <QtCore>
#include <QColor>
#include <Box2D.h>

#include "Vec.h"

class QNaub;
class Naubino;
class NaubJoint;
class Pointer;
class NaubTarjan;
class CenterJoint;

class Naub
{
public:
    Naub(Naubino *naubino, Vec pos, QColor color);
    ~Naub();

    Naubino *naubino;
    QNaub *qnaub;
    b2Body *body;
    QMap<Naub *, NaubJoint *> *jointNaubs;
    QMap<Pointer *, b2Joint *> *pointerJoints;
    QColor color;
    int selected;
    float32 radius;
    float32 density;
    float32 friction;
    float32 restitution;
    CenterJoint *centerJoint;

    NaubTarjan *tarjan;

    Vec pos();
    float32 rot();

    void changed();
    void deleted();

    void select(Pointer *pointer);
    void deselect(Pointer *pointer);

    void setup();
    void setupBody();
    void setupFixture();
};

#endif // NAUB_H
