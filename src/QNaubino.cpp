#include "QNaubino.h"
#include <Naubino.h>
#include <Naub.h>
#include <Joint.h>
#include <QNaub.h>
#include <QJoint.h>
#include <QScene.h>
#include <Qb2DebugDraw.h>
#include <QGraphicsView>
#include <Box2D/Dynamics/b2World.h>

QNaubino::QNaubino(Naubino &naubino, QObject *parent)
    : QObject(parent), _naubino(&naubino) {
}

void QNaubino::setNaubino(Naubino &naubino) {
    _naubino = &naubino;
}

void QNaubino::init() {
    scene   = new QScene(this);
    view    = new QGraphicsView();
    dd      = new Qb2DebugDrawItem(&world());

    scene->connect(this, SIGNAL(added(QJoint*)), SLOT(add(QJoint*)));
    scene->connect(this, SIGNAL(added(QNaub*)), SLOT(add(QNaub*)));

    connect(_naubino, SIGNAL(added(Joint*)), SLOT(add(Joint*)));
    connect(_naubino, SIGNAL(added(Naub*)), SLOT(add(Naub*)));

    view->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    scene->addItem(dd);

    view->setScene(scene);
    view->show();
}

b2World& QNaubino::world() const {
    return _naubino->world();
}

void QNaubino::add(Naub *naub) {
    QNaub *qnaub = new QNaub();
    qnaub->setNaub(naub);
    qnaub->connect(naub,
                   SIGNAL(removed(Naub*)),
                   SLOT(remove()));
    naub->connect(qnaub,
                  SIGNAL(selected(Pointer*)),
                  SLOT(select(Pointer*)));
    naub->connect(qnaub,
                  SIGNAL(deselected(Pointer*)),
                  SLOT(deselect(Pointer*)));
    connect(qnaub,
            SIGNAL(removed(QNaub*)),
            SLOT(remove(QNaub*)));
    emit added(qnaub);
}

void QNaubino::add(Joint *joint) {
    QJoint *qjoint = new QJoint();
    qjoint->setJoint(joint);
    qjoint->connect(joint,
                    SIGNAL(removed(Joint*)),
                    SLOT(remove()));
    qjoint->connect(joint,
                    SIGNAL(unjoined(Joint*)),
                    SLOT(remove()));
    connect(qjoint,
            SIGNAL(removed(QJoint*)),
            SLOT(remove(QJoint*)));
    emit added(qjoint);
}

void QNaubino::remove(QNaub *obj) {
    obj->deleteLater();
}

void QNaubino::remove(QJoint *obj) {
    obj->deleteLater();
}
