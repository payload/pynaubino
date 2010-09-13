#ifndef JOINT_H
#define JOINT_H

#include "Prereqs.h"

#include <QObject>

class Naub;

class Joint : public QObject {
    Q_OBJECT
signals:
    void changed(Joint *joint);
    void joined(Joint *joint);
    void unjoined(Joint *joint);
public slots:
    void join(Naub *a, Naub *b);
    void unjoin();
    void update();
};

#endif // JOINT_H
