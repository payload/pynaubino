#ifndef QJOINT_H
#define QJOINT_H

#include <QtGui>

class Joint;
class Scene;

class QJoint : public QGraphicsLineItem
{
public:
    explicit QJoint(Scene *scene, Joint *joint, QGraphicsItem *parent = 0);
    Scene *scene;
    Joint *joint;

    void changed();
    void deleted();
};

#endif // QJOINT_H
