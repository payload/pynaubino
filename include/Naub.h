#ifndef NAUB_H
#define NAUB_H

#include <QtCore>
#include <Box2D.h>

#include "Vec.h"
#include "Pointer.h"
#include "Color.h"
#include "Joints.h"

class Naub {
public:
    Naub(b2World &world);
    ~Naub();
    void update();

    void setPos(Vec pos);
    void setColor(Color color);

    b2World& world();
    Vec pos();
    float32 rot();
    float32 radius();
    Color color();

    // JointManager >>
    CenterJoint *centerJoint;
    QMap<Naub *, NaubJoint *>& jointNaubs();
    QMap<Pointer *, PointerJoint *>& pointerJoints();
    // << JointManager
private:
    void setupPhysics();

    b2World *world_;
    b2Body *body_;
    float32 radius_, friction_, density_, restitution_;
    Color color_;

    QMap<Naub *, NaubJoint *> *jointNaubs_;
    QMap<Pointer *, PointerJoint *> *pointerJoints_;
};

#endif // NAUB_H
