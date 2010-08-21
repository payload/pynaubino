#include "NaubinoContactListener.h"

NaubinoContactListener::NaubinoContactListener(Naubino *naubino)
    : naubino(naubino) {}

void NaubinoContactListener::PostSolve(
        b2Contact* contact, const b2ContactImpulse* impulse) {
    Event *event;
    event = new MergeWithEvent(naubino);
    if (event->filter(contact, impulse)) naubino->events->append(event);
}
