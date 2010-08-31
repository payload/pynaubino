#ifndef JOINTS_H
#define JOINTS_H


#include "Prereqs.h"

#include <Box2D/Box2D.h>

#include "Pointer.h"

class Naub;
class QNaubJoint;


class Joint {
public:
    Joint(b2World *world);
    virtual ~Joint();

    virtual void update() = 0;

protected:
    b2World *world_;
};


class NaubJoint : public Joint {
public:
    NaubJoint(b2World *world);
    virtual ~NaubJoint();

    virtual void update();

    void join(Naub *a, Naub *b);
    void unjoin();

    Naub &a();
    const Naub &a() const;
    Naub &b();
    const Naub &b() const;

    void setQNaubJoint(QNaubJoint*);

private:
    Naub *a_, *b_;
    b2Body *help_body_;
    QNaubJoint *qnaubjoint_;
};


class CenterJoint : public Joint {
public:
    CenterJoint(b2World *world);
    virtual ~CenterJoint();

    virtual void update();

    void join(Naub *naub, b2Body *center);
    void unjoin();

    Naub &naub();
    const Naub &naub() const;
    b2Body &center();
    const b2Body &center() const;

private:
    Naub *naub_;
    b2Body *center_;
    b2Body *help_body_;
};


class PointerJoint : public Joint {
public:
    PointerJoint(b2World *world);
    virtual ~PointerJoint();

    virtual void update();

    void join(Naub *naub, Pointer *pointer);
    void unjoin();

    Naub& naub();
    const Naub& naub() const;
    Pointer& pointer();
    const Pointer& pointer() const;

private:
    Naub *naub_;
    Pointer *pointer_;
    b2Body *help_body_;
};


#endif // JOINTS_H

