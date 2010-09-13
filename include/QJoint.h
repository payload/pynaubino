#ifndef QJOINT_H
#define QJOINT_H

#include <QObject>

class Joint;

class QJoint : public QObject {
    Q_OBJECT
public slots:
    void update(Joint *joint);
};

#endif // QJOINT_H
