#ifndef QJOINTMANAGER_H
#define QJOINTMANAGER_H

#include <QObject>

class QJoint;
class Joint;

class QJointManager : public QObject {
    Q_OBJECT
signals:
    void added(QJoint *qjoint);
public slots:
    void add(Joint *joint);
};

#endif // QJOINTMANAGER_H
