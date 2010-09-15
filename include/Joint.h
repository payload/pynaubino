#ifndef JOINT_H
#define JOINT_H

#include "Prereqs.h"

#include <QObject>
#include <Vec.h>

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
public:
    virtual ~Joint();
    virtual Vec posA() const = 0;
    virtual Vec posB() const = 0;
    bool isJoined() const { return _isJoined; }
private:
    bool _isJoined;
};

#endif // JOINT_H
