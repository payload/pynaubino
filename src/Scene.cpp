#include "Scene.h"


Scene::Scene(Naubino &naubino) : QGraphicsScene(), naubino_(&naubino) {
    connect(&naubino,
            SIGNAL(newNaub(Naub&)),
            SLOT  (newNaub(Naub&)));
    connect(&naubino,
            SIGNAL(newNaubJoint(NaubJoint&)),
            SLOT  (newNaubJoint(NaubJoint&)));
}


void Scene::newNaub(Naub &naub) {
    QNaub *qnaub = new QNaub(this, &naub);
    addItem(qnaub);
}


void Scene::newNaubJoint(NaubJoint &joint) {
    QNaubJoint *qjoint = new QNaubJoint(joint);
    addItem(qjoint);
}


void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QPointF pos = event->scenePos();
    mainPointer().setPos( Vec(pos) );
    QGraphicsScene::mouseMoveEvent(event);
}


void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
}


void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}


void Scene::selectNaub(QNaub &qnaub) {
    naubino().selectNaub(qnaub.naub());
}


void Scene::deselectNaub(QNaub &qnaub) {
    naubino().deselectNaub(qnaub.naub());
}


Pointer& Scene::mainPointer() { return naubino().pointer(); }
Naubino& Scene::naubino() { return *naubino_; }

