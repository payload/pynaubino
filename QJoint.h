#ifndef QJOINT_H
#define QJOINT_H

#include <QtGui>

class Joint;
class Scene;

class QJoint : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
public:
    explicit QJoint(Scene *scene, Joint *joint);
    Scene *scene;
    Joint *joint;

    void changed();
    void deleted();
public slots:
signals:
};

#endif // QJOINT_H
