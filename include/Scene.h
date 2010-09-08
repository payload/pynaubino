#ifndef SCENE_H
#define SCENE_H


#include "Prereqs.h"

#include <QGraphicsScene>

class Naub;
class NaubJoint;
class Naubino;
class Pointer;
class QNaub;


class Scene : public QGraphicsScene {
    Q_OBJECT
public:
    Scene(Naubino *naubino);

    void selectNaub(QNaub*);
    void deselectNaub(QNaub*);

    Pointer& mainPointer();
    const Pointer& mainPointer() const;
    Naubino& naubino();
    const Naubino& naubino() const;

public slots:
    void newNaub(Naub *naub);
    void newNaubJoint(NaubJoint *joint);

protected:
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

private:
    Naubino *_naubino;
};


#endif // SCENE_H

