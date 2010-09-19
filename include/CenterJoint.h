#ifndef CENTERJOINT_H
#define CENTERJOINT_H

#include "Joint.h"
class Naub;
class b2Body;
class b2World;
class Vec;

class CenterJoint : public Joint {
    Q_OBJECT
public slots:
    void join(Naub *naub, b2Body *center);
    void unjoin();
public:
    virtual void init() const {}
    virtual Vec posA() const;
    virtual Vec posB() const;
private:
    Naub *_naub;
    b2Body *_center;
    b2Body *_helpBody;
    b2World *_world;
};

#endif // CENTERJOINT_H
