#ifndef JOINTMANAGER_H
#define JOINTMANAGER_H

#include <QtCore>
#include "Naub.h"
#include "Joints.h"

class JointManager : public QObject
{
    Q_OBJECT
public:
    explicit JointManager();
    ~JointManager();

    NaubJoint& joinNaubs(Naub &a, Naub &b);
    void unjoinNaubs(NaubJoint &joint);
    NaubJoint* naubJoint(Naub &a, Naub &b);

    CenterJoint& joinWithCenter(Naub &naub);
    void unjoinFromCenter(CenterJoint &joint);
    CenterJoint* centerJoint(Naub &naub);

    PointerJoint& selectNaub(Naub &naub);
    void deselectNaub(Naub &naub);
    PointerJoint* pointerJoint(Naub &naub);

    int count();
    void update();
signals:
    void newJoint(NaubJoint *joint);
public slots:

private:
    QList<Joint *> *joints_;
};

#endif // JOINTMANAGER_H
