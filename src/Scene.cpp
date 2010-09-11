#include "Scene.h"

#include <QGraphicsSceneMouseEvent>

#include "Naubino.h"
#include "QNaub.h"
#include "QNaubJoint.h"
#include "Pointer.h"


Scene::Scene(Naubino *naubino) : QGraphicsScene(), _naubino(naubino) {

}


void Scene::newNaub(Naub *naub) {
    QNaub *qnaub = new QNaub(this, naub);
    addItem(qnaub);
}


void Scene::newNaubJoint(NaubJoint *joint) {
    QNaubJoint *qjoint = new QNaubJoint(*joint);
    addItem(qjoint);
}


void Scene::selectNaub(QNaub *qnaub) {
    naubino().selectNaub(&qnaub->naub());
}


void Scene::deselectNaub(QNaub *qnaub) {
    naubino().deselectNaub(&qnaub->naub());
}


Pointer& Scene::mainPointer() { return naubino().pointer(); }
const Pointer& Scene::mainPointer() const { return naubino().pointer(); }
Naubino& Scene::naubino() { return *_naubino; }
const Naubino& Scene::naubino() const { return *_naubino; }


void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();
    mainPointer().setPos(Vec(pos));
    QGraphicsScene::mouseMoveEvent(event);
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
}


void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}

