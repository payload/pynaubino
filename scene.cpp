#include "scene.h"
#include "naub.h"
#include <QDebug>

Scene::Scene(QObject *parent) :
    QGraphicsScene(parent)
{
    addItem(new Naub(10));
    addItem(new Naub(-10));
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
