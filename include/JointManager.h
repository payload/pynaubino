#ifndef JOINTMANAGER_H
#define JOINTMANAGER_H

#include <QtCore>
#include "Naub.h"
#include "Joint.h"
#include "NaubJoint.h"

class JointManager : public QObject
{
    Q_OBJECT
public:
    explicit JointManager(Naubino *naubino);
    ~JointManager();

    NaubJoint* joinNaubs(Naub *a, Naub *b);
    void remove(Naub *a, Naub *b);
    void remove(NaubJoint *joint);
    void remove(Joint *joint);
    int count();
    const QList<Joint *>& joints();
signals:
    void newJoint(NaubJoint *joint);
public slots:

private:
    Naubino *naubino;
    QList<Joint *> *joints_;
};

#endif // JOINTMANAGER_H
