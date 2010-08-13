#ifndef NAUB_H
#define NAUB_H

#include <Box2D.h>

class QNaub;
class Vec;
class Naubino;

class Naub
{
public:
    Naub(Naubino *naubino);
    void update();
    QNaub *qnaub;
    Naubino *naubino;

    void setup();
    void setupBody();
    void setupFixture();
    Vec pos();
    b2Body *body;

    float32 radius;
    float32 density;
    float32 friction;
    float32 restitution;
};

#endif // NAUB_H
