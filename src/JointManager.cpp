#include "JointManager.h"
#include "Naub.h"
#include "Joint.h"

void JointManager::add(Joint *joint) {
    connect(joint, SIGNAL(joined(Joint*)), SLOT(join(Joint*)));
    emit added(joint);
}

void JointManager::join(Joint *joint) {
    emit joined(joint);
}
