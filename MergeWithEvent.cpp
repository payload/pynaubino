#include "MergeWithEvent.h"
#include "Naub.h"
#include "Naubino.h"

MergeWithEvent::MergeWithEvent(Naubino *naubino) : Event(naubino) {}

bool MergeWithEvent::filter(b2Contact *contact, const b2ContactImpulse *impulse) {
    Q_UNUSED(impulse);
    a = (Naub *)contact->GetFixtureA()->GetUserData();
    b = (Naub *)contact->GetFixtureB()->GetUserData();
    if (a->color == b->color) {
        if (b->selected > 0) {
            Naub *c;
            c = a;
            a = b;
            b = c;
        }
        if (a->selected > 0 && shortDistance(a, b) > 2)
            return true;
    }
    return false;
}

void MergeWithEvent::handle() {
    naubino->mergeNaubs(a, b);
}

int MergeWithEvent::shortDistance(Naub *a, Naub *b) {
    if (a->jointNaubs->contains(b))
        return 1;
    foreach (Naub *c, a->jointNaubs->keys()) {
        if (c->jointNaubs->contains(b))
            return 2;
    }
    return 3;
}
