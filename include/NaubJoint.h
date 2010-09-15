#ifndef NAUBJOINT_H
#define NAUBJOINT_H

#include "Joint.h"
class Naub;
class b2Body;
class b2World;
class Vec;

class NaubJoint : public Joint {
    Q_OBJECT
public slots:
    void join(Naub *a, Naub *b);
    void unjoin();
public:
    virtual Vec posA() const;
    virtual Vec posB() const;
private:
    Naub *_a;
    Naub *_b;
    b2Body *_helpBody;
    b2World *_world;
};

#endif // NAUBJOINT_H
