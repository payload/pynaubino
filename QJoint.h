#ifndef QJOINT_H
#define QJOINT_H

#include <QtGui>

class Joint;
class Scene;

class QJoint : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth)
public:
    explicit QJoint(Scene *scene, Joint *joint);
    Scene *scene;
    Joint *joint;

    void jointChanged();
    void jointDeleted();

    qreal penWidth();
    void setPenWidth(qreal width);
public slots:
    void deleted();
signals:
};

#endif // QJOINT_H
