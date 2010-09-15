#include "QScene.h"
#include <QNaub.h>
#include <QJoint.h>
#include <Pointer.h>
#include <QGraphicsSceneMouseEvent>
#include <Vec.h>
#include <Box2D/Dynamics/b2World.h>

QScene::QScene(b2World *world, QObject *parent) : QGraphicsScene(parent) {
    pointer = new Pointer(world, this);
}

QScene::~QScene() {
    delete pointer;
    pointer = NULL;
}

void QScene::add(QNaub *qnaub) {
    qnaub->pointer = pointer;
    addItem(qnaub);
}

void QScene::add(QJoint *qjoint) {
    addItem(qjoint);
}

void QScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    pointer->setPos(Vec(event->scenePos()));
    QGraphicsScene::mouseMoveEvent(event);
}
