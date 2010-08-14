#ifndef NAUB_H
#define NAUB_H

#include <QtCore>
#include <Box2D.h>

#include "Vec.h"

class QNaub;
class Naubino;
class Joint;
class Pointer;

class Naub
{
public:
    Naub(Naubino *naubino, Vec pos);
    void update();
    QNaub *qnaub;
    Naubino *naubino;

    void setup();
    void setupBody();
    void setupFixture();
    Vec pos();
    float32 rot();
    b2Body *body;

    Joint* join(Naub *other);
    QList<Joint *> *joints;
    QList<Naub *> *jointNaubs;

    float32 radius;
    float32 density;
    float32 friction;
    float32 restitution;

    void selected(Pointer *pointer);
    QMap<Pointer *, b2Joint *> *mouseJoints;
    void deselected(Pointer *pointer);
};

#endif // NAUB_H
