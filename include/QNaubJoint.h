#ifndef QNAUBJOINT_H
#define QNAUBJOINT_H


#include "Prereqs.h"

#include <QGraphicsLineItem>
#include <QObject>

class NaubJoint;


class QNaubJoint : public QObject, public QGraphicsLineItem {
    Q_OBJECT
    Q_PROPERTY(qreal penWidth READ penWidth WRITE setPenWidth)
public:
    QNaubJoint(NaubJoint &joint);
    ~QNaubJoint();

    NaubJoint& joint();

    void jointChanged();
    void jointDeleted();

    qreal penWidth();
    void setPenWidth(qreal width);

public slots:
    void deleted();

private:
    NaubJoint *_joint;
};


#endif // QNAUBJOINT_H

