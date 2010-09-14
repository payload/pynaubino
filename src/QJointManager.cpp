#include "QJointManager.h"
#include <QJoint.h>
#include <Joint.h>

void QJointManager::add(Joint *joint) {
    QJoint *qjoint = new QJoint();
    qjoint->connect(joint,
                    SIGNAL(changed(Joint*)),
                    SLOT(update(Joint*)));
    emit added(qjoint);
}
