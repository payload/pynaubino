#include "Naub.h"
#include <NaubJoint.h>
#include <PointerJoint.h>
#include <Pointer.h>
#include <QList>
#include <Naubino.h>

void Naub::select(Pointer *pointer) {
    PointerJoint *joint = new PointerJoint();
    emit added(joint);
    joint->init();

    joint->join(this, pointer);
    joint->connect(this, SIGNAL(deselected(Pointer*)), SLOT(unjoin()));
    joint->connect(this, SIGNAL(removed(Naub*)), SLOT(unjoin()));
    _isSelected = true;
    emit selected(pointer);
}

void Naub::remove() {
    emit removed(this);
}

void Naub::deselect(Pointer *pointer) {
    if (!_isSelected) return;
    _isSelected = false;
    emit deselected(pointer);
}

void Naub::touch(Naub *naub) {
    emit touched(this, naub);
    if (true
        && naub->color() == color()
        && !joinedNaubs().contains(naub)
        && bfsDistance(naub) > 2) {
        join(naub);
    }
}

void Naub::join(Naub *naub) {
    if (!joinedNaubs().contains(naub)) {
        NaubJoint *joint = new NaubJoint();
        emit added(joint);
        joint->init();

        joinedNaubs().append(naub);
        naub->joinedNaubs().append(this);
        joint->join(this, naub);
        connect(naub,
                SIGNAL(removed(Naub*)),
                SLOT(unjoin(Naub*)));
        joint->connect(this,
                       SIGNAL(removed(Naub*)),
                       SLOT(unjoin()));
        joint->connect(this,
                       SIGNAL(unjoined(Naub*, Naub*)),
                       SLOT(unjoin()));
        emit joined(this, naub);
    }
}

void Naub::unjoin(Naub *naub) {
    joinedNaubs().removeOne(naub);
    naub->disconnect(this, SLOT(unjoin(Naub*)));
        emit unjoined(this, naub);
}

int Naub::bfsDistance(Naub *naub) {
    return 0;
}

Naub::Naub() : QObject() {}

void Naub::setNaubino(Naubino &naubino) {
    _naubino = &naubino;
}

void Naub::init() {
    _world = &_naubino->world();
    b2BodyDef def;
    def.type = b2_dynamicBody;
    _body = _world->CreateBody(&def);
    b2CircleShape shape;
    shape.m_radius = 0.15;
    _body->CreateFixture(&shape, 1);
    _color = Qt::black;
    _isSelected = false;
    _joinedNaubs = new QList<Naub*>();
}

Naub::~Naub() {
    _world->DestroyBody(_body);
    _body = NULL;
    _world = NULL;
    delete _joinedNaubs;
    _joinedNaubs = NULL;
}

void Naub::setPos(const Vec &pos) {
    _body->SetTransform(pos, _body->GetAngle());
}
