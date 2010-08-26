#ifndef SCENE_H
#define SCENE_H

#include <QtGui>
#include "Naubino.h"

class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit Scene(Naubino &naubino);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    Pointer& mainPointer();
    Naubino& naubino();
signals:

public slots:
    void newNaub(Naub &naub);
    void newNaubJoint(NaubJoint &joint);
private:
    Naubino *naubino_;
};

#endif // SCENE_H
