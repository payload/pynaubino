#ifndef NAUBINOCONTACTLISTENER_H
#define NAUBINOCONTACTLISTENER_H

#include <Box2D.h>
#include "Naub.h"
#include "Naubino.h"
#include "Event.h"
#include "MergeWithEvent.h"

class NaubinoContactListener : public b2ContactListener
{
public:
    NaubinoContactListener(Naubino *naubino)
        : naubino(naubino) {}
    Naubino *naubino;

    void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse) {
        Event *event = new Event(naubino);
        if (event->filter(contact, impulse)) naubino->events->append(event);
        event = new MergeWithEvent(naubino);
        if (event->filter(contact, impulse)) naubino->events->append(event);
    }
};

#endif // NAUBINOCONTACTLISTENER_H
