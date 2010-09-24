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

void Naub::touch(Naub *a, Naub *b) {
    if (a == b) return;
    if (a != this) {
        if (b != this) return;
        else {
            Naub *c = b;
            b = a;
            a = c;
        }
    }
    emit touched(this, b);
    if (true
        && b->color() == color()
        && !joinedNaubs().contains(b)
        && !bfsDistanceLess3(b)) {
        join(b);
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

int Naub::bfsDistanceLess3(Naub *naub) {
    if (this == naub) return true;
    if (joinedNaubs().contains(naub)) return true;
    foreach (Naub *naub, joinedNaubs())
        if (naub->joinedNaubs().contains(naub))
            return true;
    return false;
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
    b2Fixture *fix = _body->CreateFixture(&shape, 1);
    fix->SetUserData(static_cast<void*>(this));
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
