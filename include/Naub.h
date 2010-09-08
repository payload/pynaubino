#ifndef NAUB_H
#define NAUB_H


#include "Prereqs.h"

#include <QColor>
#include <QMap>

#include <Box2D/Box2D.h>

#include "Color.h"
#include "Vec.h"
#include "Cycler.h" // NOTE payload: extra header for NaubTarjan?

class Naubino;

class CenterJoint;
class NaubJoint;
class QNaub;
class PointerJoint;

class Pointer;


class Naub {
public:
    Naub(Naubino *naubino);
    ~Naub();

    void update();

    void mergeNaub(Naub *other);
    bool isMergedWith(Naub * naub);

    void handleContact(Naub *naub);

    void setPos(const Vec& pos);
    void setColor(const QColor& color);

    b2World& world();
    const b2World& world() const;

    Vec pos() const;
    float rot() const;
    float radius() const;
    const QColor& color() const;
    b2Body& body();
    const b2Body& body() const;

    void setQNaub(QNaub*);

    CenterJoint *centerJoint();
    void setCenterJoint(CenterJoint *);

    bool deleted() const;
    void setDeleted(bool deleted);

    NaubTarjan tarjan; // NOTE payload: used by Cycler, maybe a friend?

    QMap<Naub *, NaubJoint *>& jointNaubs();
    QMap<Pointer *, PointerJoint *>& pointerJoints();

private:
    void setupPhysics();

    Naubino *_naubino;
    b2World *_world;
    b2Body *_body;
    float _radius, _friction, _density, _restitution;

    QColor _color;
    bool _deleted;

    QNaub *_qnaub;

    CenterJoint *_centerJoint;

    QMap<Naub *, NaubJoint *> _jointNaubs;
    QMap<Pointer *, PointerJoint *> _pointersJoints;
};


#endif // NAUB_H

