#ifndef POINTERJOINT_H
#define POINTERJOINT_H

#include "Joint.h"
class Naub;
class Pointer;
class b2World;
class b2Body;

class PointerJoint : public Joint {
    Q_OBJECT
public slots:
    void join(Naub *naub, Pointer *pointer);
    void unjoin();
private:
    b2World *_world;
    b2Body *_helpBody;
};

#endif // POINTERJOINT_H
