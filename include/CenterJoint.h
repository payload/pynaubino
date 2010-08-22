#ifndef CENTERJOINT_H
#define CENTERJOINT_H

#include <Box2D.h>

class Naub;

class CenterJoint
{
public:
    explicit CenterJoint(b2World *world, b2Body *center);

    b2Body* center();
    void setCenter(b2Body *center);

    void join(Naub *naub);
    void unjoin();
    void update();

    b2World *world;
protected:
    b2Body *center_;
    Naub *naub_;
};

#endif // CENTERJOINT_H
