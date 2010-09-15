#ifndef QJOINT_H
#define QJOINT_H

#include <QObject>
#include <QGraphicsLineItem>

class Joint;

class QJoint : public QObject, public QGraphicsLineItem {
    Q_OBJECT
signals:
    void removed(QJoint *qjoint);
public slots:
    void remove();
    void setJoint(Joint *joint);
public:
    QJoint(QObject *parent = 0);
    virtual ~QJoint();
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
private:
    Joint *_joint;
};

#endif // QJOINT_H
