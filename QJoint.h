#ifndef QJOINT_H
#define QJOINT_H

#include <QtGui>

class Joint;

class QJoint : public QGraphicsLineItem
{
public:
    explicit QJoint(Joint *joint, QGraphicsItem *parent = 0);
    Joint *joint;
    void notifyUpdate();
};

#endif // QJOINT_H
