#ifndef JOINT_H
#define JOINT_H

#include "Prereqs.h"

#include <QObject>

class Joint : public QObject {
    Q_OBJECT
signals:
    void changed(Joint *joint);
    void joined(Joint *joint);
    void unjoined(Joint *joint);
public slots:
    virtual void join();
    virtual void unjoin();
    virtual void update();
};

#endif // JOINT_H
