#include "QJointManager.h"
#include <QJoint.h>
#include <Joint.h>
#include <NaubJoint.h>

#include <QDebug>

void QJointManager::add(Joint *joint) {
    QJoint *qjoint = new QJoint();
    qjoint->setJoint(joint);
    qjoint->connect(joint,
                    SIGNAL(unjoined(Joint*)),
                    SLOT(remove()));
    connect(qjoint,
            SIGNAL(removed(QJoint*)),
            SLOT(remove(QJoint*)));
    emit added(qjoint);
}

void QJointManager::remove(QJoint *qjoint) {
}
