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
public slots:
    void join(Naub *a, Naub *b);
};


#endif // JOINTMANAGER_H

