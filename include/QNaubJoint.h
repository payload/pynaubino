#ifndef QNAUBJOINT_H
#define QNAUBJOINT_H

#include <QtGui>
#include "Joints.h"

class QNaubJoint : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth)
public:
    explicit QNaubJoint(NaubJoint &joint);
    ~QNaubJoint();

    NaubJoint& joint();

    void jointChanged();
    void jointDeleted();

    qreal penWidth();
    void setPenWidth(qreal width);
public slots:
    void deleted();
signals:
private:
    NaubJoint *joint_;
};

#endif // QNAUBJOINT_H
