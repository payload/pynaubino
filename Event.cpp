#include "Event.h"
#include "Naubino.h"

Event::Event(Naubino *naubino) : naubino(naubino) {}

bool Event::filter(b2Contact *contact, const b2ContactImpulse *impulse) {
    Q_UNUSED(contact);
    Q_UNUSED(impulse);
    return false;
}

void Event::handle() {}
