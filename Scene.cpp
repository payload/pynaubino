#include "Scene.h"
#include "QNaub.h"
#include "QJoint.h"
#include "Naubino.h"

Scene::Scene(Naubino *naubino, QObject *parent) :
    QGraphicsScene(parent)
{
    connect(naubino, SIGNAL(newNaub(Naub *)), this, SLOT(newNaub(Naub*)));
    connect(naubino, SIGNAL(newJoint(Joint *)), this, SLOT(newJoint(Joint*)));

    addRect(-300, -200, 600, 400);
}

void Scene::newNaub(Naub *naub) {
    QNaub *qnaub = new QNaub(naub);
    addItem(qnaub);
}

void Scene::newJoint(Joint *joint) {
    QJoint *qjoint = new QJoint(joint);
    addItem(qjoint);
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseMoveEvent(event);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mousePressEvent(event);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsScene::mouseReleaseEvent(event);
}
