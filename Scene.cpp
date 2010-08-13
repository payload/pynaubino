#include "Scene.h"
#include "QNaub.h"
#include "Naubino.h"

#include <QDebug>

Scene::Scene(Naubino *naubino, QObject *parent) :
    QGraphicsScene(parent)
{
    connect(naubino, SIGNAL(newNaub(Naub *)), this, SLOT(newNaub(Naub *)));

    foreach (Naub *naub, *naubino->naubs) {
        newNaub(naub);
    }
}

void Scene::newNaub(Naub *naub) {
    qDebug("new naub <-");
    QNaub *qnaub = new QNaub(naub);
    qDebug() << qnaub->boundingRect().width();
    addItem(qnaub);
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
