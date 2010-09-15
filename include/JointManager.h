#ifndef JOINTMANAGER_H
#define JOINTMANAGER_H

#include "Prereqs.h"

#include <QObject>

class Naub;
class Joint;

class JointManager : public QObject {
    Q_OBJECT
signals:
    void added(Joint *joint);
    void joined(Joint *joint);
public slots:
    void add(Joint *joint);
    void join(Joint *joint);
    void unjoin(Joint *joint);
public:
    JointManager(QObject *parent = 0) : QObject(parent) {}
};


#endif // JOINTMANAGER_H

