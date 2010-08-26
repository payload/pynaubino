#ifndef QNAUBJOINT_H
#define QNAUBJOINT_H

#include <QtGui>

class NaubJoint;
class Scene;

class QNaubJoint : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth)
public:
    explicit QNaubJoint(Scene *scene, NaubJoint *joint);
    Scene *scene;
    NaubJoint *joint;

    void jointChanged();
    void jointDeleted();

    qreal penWidth();
    void setPenWidth(qreal width);
public slots:
    void deleted();
signals:
};

#endif // QNAUBJOINT_H
