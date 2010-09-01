#ifndef NAUBINO_H
#define NAUBINO_H


#include "Prereqs.h"

#include <QObject>

#include <Box2D/Box2D.h>

#include "NaubManager.h"
#include "JointManager.h"
#include "Joints.h"


class Naubino : public QObject
{
    Q_OBJECT
public:
    Naubino();
    ~Naubino();

    Naub& addNaub(Vec pos);
    void removeNaub(Naub &naub);

    NaubJoint& joinNaubs(Naub &a, Naub &b);
    void unjoinNaubs(NaubJoint &joint);
    void rejoinNaubs(NaubJoint &joint, Naub &a, Naub &b);
    NaubJoint* naubJoint(Naub &a, Naub &b);

    CenterJoint& joinWithCenter(Naub &naub);
    void unjoinFromCenter(CenterJoint &joint);
    CenterJoint* centerJoint(Naub &naub);

    PointerJoint& selectNaub(Naub &naub);
    void deselectNaub(Naub &naub);
    PointerJoint* pointerJoint(Naub &naub);

    void mergeNaubs(Naub &a, Naub &b);

    NaubManager& naubs();
    const NaubManager& naubs() const;
    JointManager& joints();
    const JointManager& joints() const;
    b2World& world();
    const b2World& world() const;
    b2Body& center();
    const b2Body& center() const;
    Pointer& pointer();
    const Pointer& pointer() const;

signals:
    void newNaub(Naub &naub);
    void newNaubJoint(NaubJoint &joint);
    void newCenterJoint(CenterJoint &joint);
    void newPointerJoint(PointerJoint &joint);
    void mergedJoint(NaubJoint &joint);
    void mergedNaub(Naub &naub);

public slots:
    void update();

private:
    void setupCenter();

    b2World *_world;
    NaubManager *_naubs;
    JointManager *_joints;
    b2Body *_center;
    Pointer *_pointer;
};


#endif // NAUBINO_H

