#ifndef JOINTMANAGER_H
#define JOINTMANAGER_H

#include "Prereqs.h"

#include <QObject>
#include "Naub.h"
#include "Joint.h"

class JointManager : public QObject {
    Q_OBJECT
signals:
    void joined(Joint *joint);
public slots:
    void join(Naub *a, Naub *b);
};


#endif // JOINTMANAGER_H

