#include "Scene.h"
#include "QNaub.h"
#include "QJoint.h"
#include "Naubino.h"
#include "Pointer.h"

Scene::Scene(Naubino *naubino, QObject *parent) :
    QGraphicsScene(parent)
{
    this->naubino = naubino;

    connect(naubino, SIGNAL(newNaub(Naub *)), this, SLOT(newNaub(Naub*)));
    connect(naubino, SIGNAL(newJoint(NaubJoint *)), this, SLOT(newJoint(NaubJoint*)));
}

void Scene::newNaub(Naub *naub) {
    QNaub *qnaub = new QNaub(this, naub);
    addItem(qnaub);
}

void Scene::newJoint(NaubJoint *joint) {
    QJoint *qjoint = new QJoint(this, joint);
    addItem(qjoint);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();
    getMainPointer()->setPos( Vec(pos) );
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}

Pointer* Scene::getMainPointer() {
    return naubino->pointers->value(0);
}
