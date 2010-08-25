#ifndef NAUBINO2_H
#define NAUBINO2_H

#include <QObject>
#include "NaubManager.h"
#include "JointManager.h"
#include "Joints.h"

class Naubino2 : public QObject
{
    Q_OBJECT
public:
    explicit Naubino2();
    ~Naubino2();

    Naub& addNaub(Vec pos);
    void removeNaub(Naub &naub);

    NaubJoint& joinNaubs(Naub &a, Naub &b);
    void unjoinNaubs(NaubJoint &joint);
    NaubJoint* naubJoint(Naub &a, Naub &b);

    CenterJoint& joinWithCenter(Naub &naub);
    void unjoinFromCenter(CenterJoint &joint);
    CenterJoint* centerJoint(Naub &naub);

    PointerJoint& selectNaub(Naub &naub);
    void deselectNaub(Naub &naub);
    PointerJoint* pointerJoint(Naub &naub);

    void mergeNaubs(Naub &a, Naub &b);

signals:
    void newNaub(Naub &naub);
    void newNaubJoint(NaubJoint &joint);
    void newCenterJoint(CenterJoint &joint);
    void newPointerJoint(PointerJoint &joint);
    void mergedJoint(NaubJoint &joint);
    void mergedNaub(Naub &naub);
public slots:

private:
    NaubManager *naubs_;
    JointManager *joints_;
};

#endif // NAUBINO2_H
