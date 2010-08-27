#ifndef JOINTS_H
#define JOINTS_H

#include <Box2D.h>
#include "Pointer.h"
#include "QNaubJoint.h"

class Naub;

class Joint {
public:
    Joint(b2World &world);
    virtual ~Joint();
    virtual void update()=0;
protected:
    b2World& world();
private:
    b2World *world_;
};

class NaubJoint : public Joint {
public:
    NaubJoint(b2World &world);
    virtual ~NaubJoint();
    void update();
    void join(Naub &a, Naub &b);
    void unjoin();
    Naub &a();
    Naub &b();

    // QNaubJoint >>
    QNaubJoint *qnaubjoint;
    // << QNaubJoint
private:
    Naub *a_, *b_;
    b2Body *help_body_;
};

class CenterJoint : public Joint {
public:
    CenterJoint(b2World &world);
    virtual ~CenterJoint();
    void update();
    void join(Naub &naub, b2Body &center);
    void unjoin();
    Naub &naub();
    b2Body &center();
private:
    Naub *naub_;
    b2Body *center_;
};

class PointerJoint : public Joint {
public:
    PointerJoint(b2World &world);
    virtual ~PointerJoint();
    void update();
    void join(Naub &naub, Pointer &pointer);
    void unjoin();
    Naub& naub();
    Pointer& pointer();
private:
    Naub *naub_;
    Pointer *pointer_;
    b2Body *help_body_;
};

#endif // JOINTS_H
