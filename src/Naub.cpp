#include "Naub.h"
#include <NaubJoint.h>
#include <PointerJoint.h>
#include <Pointer.h>
#include <QList>
#include <Naubino.h>
#include <Color.h>

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
    _isRemoved = true;
    emit removed(this);
}

void Naub::deselect(Pointer *pointer) {
    if (!_isSelected) return;
    _isSelected = false;
    emit deselected(pointer);
}

void Naub::touch(Naub *a, Naub *b) {
    if (a->isRemoved()) return; //TODO look how to get rid of this
    if (b->isRemoved()) return;
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
    if (isJokerNaub())
        join(b);
    if (b->color() == color()
        && !b->isJokerNaub()
        && !joinedNaubs().contains(b)
        && !bfsDistanceLess3(b)) {
        merge(b);
    }
}

void Naub::join(Naub *naub) {
    if (naub == this) return;
    bool me_to_other = this->joinedNaubs().contains(naub);
    bool other_to_me = naub->joinedNaubs().contains(this);
    if ( me_to_other &&  other_to_me) return;
    if (!me_to_other && !other_to_me) {
        this->joinedNaubs().append(naub);
        me_to_other = true;

        NaubJoint *joint = new NaubJoint();
        emit added(joint);
        joint->init();

        joint->join(this, naub);
        connect(naub,
                SIGNAL(removed(Naub*)),
                SLOT(unjoin(Naub*)));
        joint->connect(this,
                       SIGNAL(unjoined(Naub*, Naub*)),
                       SLOT(unjoin(Naub*,Naub*)));
        emit joined(this, naub);
    }
    if (me_to_other && !other_to_me)
        naub->join(this);
    if (!me_to_other && other_to_me) {
        this->joinedNaubs().append(naub);
        this->connect(naub,
                      SIGNAL(removed(Naub*)),
                      SLOT(unjoin(Naub*)));
    }
}

void Naub::unjoin(Naub *naub) {
    joinedNaubs().removeOne(naub);
    naub->disconnect(this, SLOT(unjoin(Naub*)));
    emit unjoined(this, naub);
}

void Naub::merge(Naub *naub) {
    foreach (Naub *other, naub->joinedNaubs())
        join(other);
    naub->remove();
    emit merged(this);
}

int Naub::bfsDistanceLess3(Naub *naub) {
    if (this == naub) return true;
    if (joinedNaubs().contains(naub)) return true;
    foreach (Naub *third, joinedNaubs())
        if (third->joinedNaubs().contains(naub))
            return true;
    return false;
}

bool Naub::isJokerNaub() const {
    return joinedNaubs().empty();
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
    _color = Color::randomNaub().first;
    _isSelected = false;
    _joinedNaubs = new QList<Naub*>();
    _isRemoved = false;
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
