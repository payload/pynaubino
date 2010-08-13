#include "Scene.h"
#include "QNaub.h"

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    addItem(new QNaub(10));
    addItem(new QNaub(-10));
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
