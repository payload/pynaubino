#include "QScene.h"
#include <QNaub.h>
#include <QJoint.h>
#include <Pointer.h>
#include <QGraphicsSceneMouseEvent>
#include <Vec.h>
#include <Box2D/Dynamics/b2World.h>
#include <QNaubino.h>
#include <QKeyEvent>

QScene::QScene(QNaubino *qnaubino)
    : QGraphicsScene(qnaubino), _qnaubino(qnaubino) {
    pointer = new Pointer(_qnaubino->world(), this);
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

void QScene::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_Q) emit play();
    if (event->key() == Qt::Key_W) emit tutorial();
    if (event->key() == Qt::Key_E) emit highscore();
    QGraphicsScene::keyPressEvent(event);
}
