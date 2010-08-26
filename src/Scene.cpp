#include "Scene.h"
//#include "QNaub.h"
//#include "QJoint.h"
#include "Naubino.h"
#include "Pointer.h"
#include "NaubManager.h"
#include "JointManager.h"

Scene::Scene(Naubino &naubino)
    : QGraphicsScene(), naubino_(&naubino) {

    connect(&naubino,
            SIGNAL(newNaub(Naub&)),
            SLOT  (newNaub(Naub&)));
    connect(&naubino,
            SIGNAL(newJoint(NaubJoint&)),
            SLOT  (newJoint(NaubJoint&)));
}

void Scene::newNaub(Naub &naub) {
    //QNaub *qnaub = new QNaub(this, naub);
    //addItem(qnaub);
}

void Scene::newJoint(NaubJoint &joint) {
    //QJoint *qjoint = new QJoint(this, joint);
    //addItem(qjoint);
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

Pointer& Scene::mainPointer() { return naubino().pointer(); }
Naubino& Scene::naubino() { return *naubino_; }
