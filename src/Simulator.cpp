#include "Simulator.h"
#include <Box2D/Dynamics/b2World.h>
#include <Vec.h>
#include <ContactListener.h>
#include <Naub.h>

class Contact
{
public:
    Naub *a;
    Naub *b;
};

Simulator::Simulator(QObject *parent) : QTimer(parent) {
    _world = new b2World(Vec(), true);
    _contacts = new ContactListener();
    _contact_list = new QList<Contact*>();
    _world->SetContactListener(_contacts);
    connect(_contacts,
            SIGNAL(naubOnNaub(Naub*,Naub*)),
            SLOT(contact(Naub*,Naub*)));
}

Simulator::~Simulator() {
    if (!_contact_list->empty())
        foreach (Contact *c, *_contact_list)
            delete c;
    delete _contact_list; _contact_list = NULL;
    delete _contacts; _contacts = NULL;
    delete _world; _world = NULL;
}

void Simulator::timerEvent(QTimerEvent *e) {
    _world->Step(interval()/1000.0, 10, 10);
    _world->ClearForces();

    foreach (Contact *c, *_contact_list) {
        emit naubOnNaub(c->a, c->b);
        delete c;
    }
    _contact_list->clear();

    QTimer::timerEvent(e);
}

void Simulator::contact(Naub *a, Naub *b) {
    Contact *c = new Contact();
    c->a = a;
    c->b = b;
    _contact_list->append(c);
}
